#include "StableDiffusionApi.h"





JNIEXPORT jlong JNICALL Java_org_javaai_stablediffusion_api_StableDiffusion_newInstance(
    JNIEnv* env,
    jobject, 
    jint n_threads,
    jboolean vae_decode_only,
    jstring taesd_path,
    jboolean free_params_immediately,
    jstring lora_model_dir,
    jint rng_type) {
	
	StableDiffusion* psd = new StableDiffusion();



	return (jlong)psd;

}

JNIEXPORT void JNICALL Java_org_javaai_stablediffusion_api_StableDiffusion_delete(
    JNIEnv* env,
    jobject, 
    jlong pointer) {
    delete (StableDiffusion*)pointer;
}

JNIEXPORT jboolean JNICALL Java_org_javaai_stablediffusion_api_StableDiffusion_loadFromFile0(
    JNIEnv* env,
    jobject,
    jlong pointer, 
    jstring model_path,
    jstring vae_path,
    jint ggml_type_value,
    jint schedule) {
    StableDiffusion * psd = (StableDiffusion*)pointer;

    const char* native_model_path = "";
    const char* native_vae_path   = "";
    
    if (model_path != nullptr) {
        native_model_path = env->GetStringUTFChars(model_path, nullptr);
    }
    if (vae_path != nullptr) {
        native_vae_path = env->GetStringUTFChars(vae_path, nullptr);
    }

    bool ret = psd->load_from_file(native_model_path, native_vae_path, (ggml_type)ggml_type_value, (Schedule)schedule);

    
    if (model_path != nullptr) {
        env->ReleaseStringUTFChars(model_path, native_model_path);
    }
    if (vae_path != nullptr) {
        env->ReleaseStringUTFChars(vae_path, native_vae_path);
    }

    return (jboolean)ret;



}

JNIEXPORT jobject JNICALL Java_org_javaai_stablediffusion_api_StableDiffusion_txt2img0(
    JNIEnv* env,
    jobject,
    jlong pointer,
    jstring prompt,
    jstring negative_prompt,
    jfloat cfg_scale,
    jint width,
    jint height,
    jint sample_method,
    jint sample_steps,
    jlong seed,
    jint batch_count)
{
    StableDiffusion* psd = (StableDiffusion*)pointer;


    
    const char* native_prompt = "";
    const char* native_negative_prompt   = "";

    if (prompt != nullptr) {
        native_prompt = env->GetStringUTFChars(prompt, nullptr);
    }
    if (negative_prompt != nullptr) {
        native_negative_prompt = env->GetStringUTFChars(negative_prompt, nullptr);
    }

    
    std::vector<uint8_t*> results = psd->txt2img(native_prompt, native_negative_prompt, 
        (float)cfg_scale, 
        (int)width, (int)height, 
        (SampleMethod)sample_method, 
        (long)sample_steps, 
        (int)seed, 
        (int)batch_count);

    jclass cArrayList = (env)->FindClass("java/util/ArrayList");
    jobject list       = env->NewObject(cArrayList, (*env).GetMethodID(cArrayList, "<init>", "()V"));

    
    jmethodID method_add = env->GetMethodID(cArrayList, "add", "(Ljava/lang/Object;)Z");

    int imgPixelSize = width * height * 3;
    for (int i = 0; i < results.size(); i ++) {
        uint8_t* pImg      = results[i];
        jbyteArray javaImg = env->NewByteArray(imgPixelSize);
        env->SetByteArrayRegion(javaImg, 0, imgPixelSize, reinterpret_cast<const jbyte*>(pImg));
        env->CallVoidMethod(list, method_add, javaImg);

        delete[] pImg;
    }


    if (prompt != nullptr) {
        env->ReleaseStringUTFChars(prompt, native_prompt);
    }
    if (negative_prompt != nullptr) {
        env->ReleaseStringUTFChars(negative_prompt, native_negative_prompt);
    }


    return list;



}


JNIEXPORT jobject JNICALL Java_org_javaai_stablediffusion_api_StableDiffusion_img2img0(
    JNIEnv* env,
    jobject,
    jlong pointer,
    jbyteArray init_img,
    jstring prompt,
    jstring negative_prompt,
    jfloat cfg_scale,
    jint width,
    jint height,
    jint sample_method,
    jint sample_steps,
    jfloat strength,
    jlong seed) {

    StableDiffusion* psd = (StableDiffusion*)pointer;

    const char* native_prompt          = "";
    const char* native_negative_prompt = "";

    if (prompt != nullptr) {
        native_prompt = env->GetStringUTFChars(prompt, nullptr);
    }
    if (negative_prompt != nullptr) {
        native_negative_prompt = env->GetStringUTFChars(negative_prompt, nullptr);
    }

    jint len = env->GetArrayLength(init_img);
    jboolean isCopy = false;
    jbyte* imgBytes = env->GetByteArrayElements(init_img, &isCopy);
    const uint8_t* init_img_data = (uint8_t *)imgBytes;

    std::vector<uint8_t*> results = psd->img2img(
        init_img_data, native_prompt, native_negative_prompt,
        (float)cfg_scale,
        (int)width, (int)height,
        (SampleMethod)sample_method,
        (long)sample_steps,
        (float)strength, 
        (int)seed);

    jclass cArrayList = (env)->FindClass("java/util/ArrayList");
    jobject list      = env->NewObject(cArrayList, (*env).GetMethodID(cArrayList, "<init>", "()V"));

    jmethodID method_add = env->GetMethodID(cArrayList, "add", "(Ljava/lang/Object;)Z");

    int imgPixelSize = width * height * 3;
    for (int i = 0; i < results.size(); i++) {
        uint8_t* pImg      = results[i];
        jbyteArray javaImg = env->NewByteArray(imgPixelSize);
        env->SetByteArrayRegion(javaImg, 0, imgPixelSize, reinterpret_cast<const jbyte*>(pImg));
        env->CallVoidMethod(list, method_add, javaImg);

        delete[] pImg;
    }

    env->ReleaseByteArrayElements(init_img, imgBytes, JNI_ABORT);

    if (prompt != nullptr) {
        env->ReleaseStringUTFChars(prompt, native_prompt);
    }
    if (negative_prompt != nullptr) {
        env->ReleaseStringUTFChars(negative_prompt, native_negative_prompt);
    }


    return list;


}


JNIEXPORT void JNICALL Java_org_javaai_stablediffusion_api_Util_setSDLogLevel(
    JNIEnv* env,
    jobject,
    jint logLevel) {
    set_sd_log_level((SDLogLevel)logLevel);
}









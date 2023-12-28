#ifndef __StableDifusionApi_H__
#define __StableDifusionApi_H__



#include "model.h"
#include "util.h"
#include "stable-diffusion.h"
#include "jni.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


    


JNIEXPORT jlong JNICALL Java_org_javaai_stablediffusion_api_StableDiffusion_newInstance(
    JNIEnv* env,
    jobject, 
    jint n_threads,
    jboolean vae_decode_only,
    jstring taesd_path,
    jboolean free_params_immediately,
    jstring lora_model_dir,
    jint rng_type);

JNIEXPORT void JNICALL Java_org_javaai_stablediffusion_api_StableDiffusion_delete(
    JNIEnv* env,
    jobject, 
    jlong pointer);


JNIEXPORT jboolean JNICALL Java_org_javaai_stablediffusion_api_StableDiffusion_loadFromFile0(
    JNIEnv* env,
    jobject,
    jlong pointer,
    jstring model_path, 
    jstring vae_path, 
    jint ggml_type_value, 
    jint schedule);


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
    jint batch_count);


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
    jlong seed);



JNIEXPORT void JNICALL Java_org_javaai_stablediffusion_api_Util_setSDLogLevel(
    JNIEnv* env,
    jobject,
    jint logLevel);









#ifdef __cplusplus
}
#endif // __cplusplus extern "C"


#endif  // __StableDifusionApi_H__
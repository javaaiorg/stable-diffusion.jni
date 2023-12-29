cmake_minimum_required (VERSION 3.3)
project("stable-diffusion.jni")

option(SD_BUILD_JAVA_BINDING "Build sd-jni project, make a shared lib that can be used by Java. " ON)

add_subdirectory(thirdparty/stable-diffusion.cpp)


if (SD_BUILD_JAVA_BINDING)
    add_subdirectory(sd-jni)
endif()










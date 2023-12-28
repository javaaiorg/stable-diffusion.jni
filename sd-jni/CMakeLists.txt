cmake_minimum_required (VERSION 3.3)
project(sdlib-jni VERSION 0.1.0)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")




if(NOT DEFINED ENV{JAVA_HOME}) 
	if(NOT DEFINED JAVA_HOME)
		message(FATAL_ERROR "This build requires setting your JAVA_HOME environment variable or JAVA_HOME CMake variable.")
	else()
		set(ENV{JAVA_HOME} "${JAVA_HOME}")

		find_package(JNI REQUIRED)
		if (JNI_FOUND)
			message (STATUS "JNI_INCLUDE_DIRS=${JNI_INCLUDE_DIRS}")
			message (STATUS "JNI_LIBRARIES=${JNI_LIBRARIES}")
		else()
			message(FATAL_ERROR "Failed to find JNI. JAVA_HOME:$ENV{JAVA_HOME}")
		endif()
	endif()

else()

	find_package(JNI REQUIRED)
	if (JNI_FOUND)
		message (STATUS "JNI_INCLUDE_DIRS=${JNI_INCLUDE_DIRS}")
		message (STATUS "JNI_LIBRARIES=${JNI_LIBRARIES}")
	else()
		message(FATAL_ERROR "Failed to find JNI. JAVA_HOME:$ENV{JAVA_HOME}")
	endif()


endif()

include_directories(${JNI_INCLUDE_DIRS})
LINK_DIRECTORIES(${JNI_LIBRARIES})



# options



set(SD_LIB_JNI sd-jni)

add_library(${SD_LIB_JNI} SHARED src/StableDiffusionApi.h src/StableDiffusionApi.cpp)
target_link_libraries(${SD_LIB_JNI} PUBLIC "stable-diffusion")
target_include_directories(${SD_LIB_JNI} PUBLIC ../thirdparty/stable-diffusion.cpp ../thirdparty/stable-diffusion.cpp/ggml/include ../thirdparty/stable-diffusion.cpp/thirdparty src/)
target_compile_features(${SD_LIB_JNI} PUBLIC cxx_std_11)


set_target_properties(${SD_LIB_JNI} PROPERTIES PUBLIC_HEADER "src/StableDiffusionApi.h")
install(
		TARGETS ${SD_LIB_JNI} 
		LIBRARY DESTINATION LIBRARY 
		PUBLIC_HEADER DESTINATION include/sd-jni
)





#include <jni.h>
#include <string>
#include <android/binder_ibinder_jni.h>

#include "NativeService.h"
using namespace aidl::io::s57;
extern "C" JNIEXPORT jstring JNICALL
Java_io_s57_smserver_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT jobject JNICALL
Java_io_s57_smserver_NativeServiceWrapper_getNativeService(
        JNIEnv* env,
        jobject /* this */) {
    static NativeService service;
    return env->NewGlobalRef(AIBinder_toJavaBinder(env, service.asBinder().get()));
}
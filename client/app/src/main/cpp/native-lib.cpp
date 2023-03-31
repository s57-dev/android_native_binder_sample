#include <jni.h>
#include <string>
#include <android/binder_ibinder_jni.h>
#include <android/binder_parcel_utils.h>
#include <aidl/io/s57/smserver/ISMService.h>

using namespace std;
using namespace aidl::io::s57::smserver;
std::shared_ptr<ISMService> g_service;

extern "C" JNIEXPORT jstring JNICALL
Java_io_s57_nclient_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

// Implementation of native methods declared in MainActivity.java

extern "C"
JNIEXPORT void JNICALL
Java_io_s57_nclient_MainActivity_onNativeServiceConnected(JNIEnv *env,
                                                          jobject thiz,
                                                          jobject binder) {
    AIBinder* pBinder = AIBinder_fromJavaBinder(env, binder);

    const ::ndk::SpAIBinder spBinder(pBinder);
    g_service = ISMService::fromBinder(spBinder);
}
extern "C"
JNIEXPORT void JNICALL
Java_io_s57_nclient_MainActivity_onNativeServiceDisconnected(JNIEnv *env, jobject thiz) {
    g_service = nullptr;
}
extern "C"
JNIEXPORT jstring JNICALL
Java_io_s57_nclient_MainActivity_sendBuffer(JNIEnv *env, jobject thiz) {

    if (g_service == nullptr) {
        return env->NewStringUTF("Service is not connected");
    }


    int32_t streamId = 1;
    int32_t fd = 1;
    ::ndk::ScopedFileDescriptor hwBufferFd(fd);

    /**
     * We send a file descriptor to the server. This could be for example a FD pointing
     * to a hardware buffer. The server will log
     * the stream ID and FD in processHardwareBuffer.
     * Note that the value of the FD is local to the process - it will be a different
     * value on the server side. This is expected and correct behaviour.
     */
    auto status = g_service->processHardwareBuffer(streamId, hwBufferFd);
    if (!status.isOk()) {
        return env->NewStringUTF("Failure");
    }

    return env->NewStringUTF("Success");
}
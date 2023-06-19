#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_com_zyl_yuvlib_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

#include <jni.h>
//#include "libyuv.h"
#include "libyuv/include/libyuv.h"
#include <cstring>
#include <android/log.h>

#define LOG_TAG "libyuv"
#define LOGV(...)  __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

using namespace libyuv;
extern "C"
JNIEXPORT void JNICALL
Java_com_zyl_yuvlib_YuvUtils_NV21ToI420(JNIEnv *env, jobject instance, jbyteArray input_,
                                         jbyteArray output_, jint in_width, jint in_height) {
    jbyte *srcData = env->GetByteArrayElements(input_, NULL);
    jbyte *dstData = env->GetByteArrayElements(output_, NULL);

    NV21ToI420((const uint8_t *)srcData, in_width,
               (uint8_t *)srcData + (in_width * in_height), in_width,
               (uint8_t *)dstData, in_width,
               (uint8_t *)dstData + (in_width * in_height), in_width / 2,
               (uint8_t *)dstData + (in_width * in_height * 5 / 4), in_width / 2,
               in_width, in_height);
    env->ReleaseByteArrayElements(input_, srcData, 0);
    env->ReleaseByteArrayElements(output_, dstData, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_zyl_yuvlib_YuvUtils_RotateI420(JNIEnv *env, jobject type, jbyteArray input_,
                                         jbyteArray output_, jint in_width, jint in_height,
                                         jint rotation) {
    jbyte *srcData = env->GetByteArrayElements(input_, NULL);
    jbyte *dstData = env->GetByteArrayElements(output_, NULL);


    RotationMode rotationMode = kRotate0;
    switch (rotation) {
        case 90:
            rotationMode = kRotate90;
            break;
        case 180:
            rotationMode = kRotate180;
            break;
        case 270:
            rotationMode = kRotate270;
            break;
    }
    I420Rotate((const uint8_t *)srcData, in_width,
               (uint8_t *)srcData + (in_width * in_height), in_width / 2,
               (uint8_t *)srcData + (in_width * in_height * 5 / 4), in_width / 2,
               (uint8_t *)dstData, in_height,
               (uint8_t *)dstData + (in_width * in_height), in_height / 2,
               (uint8_t *)dstData + (in_width * in_height * 5 / 4), in_height / 2,
               in_width, in_height,
               rotationMode);

    env->ReleaseByteArrayElements(input_, srcData, 0);
    env->ReleaseByteArrayElements(output_, dstData, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_zyl_yuvlib_YuvUtils_NV21ToI420andRotate90Clockwise(JNIEnv *env, jobject type,
                                                             jbyteArray input_,
                                                             jbyteArray output_,
                                                             jint in_width, jint in_height) {
    jbyte *srcData = env->GetByteArrayElements(input_, NULL);
    jbyte *dstData = env->GetByteArrayElements(output_, NULL);
    jsize size = env->GetArrayLength(input_);

    NV21ToI420((const uint8_t *) srcData, in_width,
               (uint8_t *)srcData + (in_width * in_height), in_width,
               (uint8_t *)dstData, in_width,
               (uint8_t *)dstData + (in_width * in_height), in_width / 2,
               (uint8_t *)dstData + (in_width * in_height * 5 / 4), in_width / 2,
               in_width, in_height);

    I420Rotate((const uint8_t *)dstData, in_width,
               (uint8_t *)dstData + (in_width * in_height), in_width / 2,
               (uint8_t *)dstData + (in_width * in_height * 5 / 4), in_width / 2,
               (uint8_t *)srcData, in_height,
               (uint8_t *)srcData + (in_width * in_height), in_height / 2,
               (uint8_t *)srcData + (in_width * in_height * 5 / 4), in_height / 2,
               in_width, in_height,
               kRotate90);
    memcpy(dstData, srcData, size);

//    fixme can't work
//    ConvertToI420((const uint8_t *) srcData, size,
//                  (uint8_t *)dstData, in_width,
//                  (uint8_t *)dstData + (in_width * in_height), in_width / 2,
//                  (uint8_t *)dstData + (in_width * in_height * 5 / 4), in_width / 2,
//                  0, 0,
//                  in_width, in_height,
//                  in_width, in_height,
//                  kRotate90,
//                  FOURCC_NV21);
//
//   fixme can't work
//    NV12ToI420Rotate((const uint8_t *) srcData, in_width,
//                     (uint8_t *) srcData + (in_width * in_height), in_width,
//                     (uint8_t *)dstData, in_width,
//                     (uint8_t *)dstData + (in_width * in_height * 5 / 4), in_width / 2,
//                     (uint8_t *)dstData + (in_width * in_height), in_width / 2,
//                     in_width, in_height,
//                     kRotate90);

    env->ReleaseByteArrayElements(input_, srcData, 0);
    env->ReleaseByteArrayElements(output_, dstData, 0);
}
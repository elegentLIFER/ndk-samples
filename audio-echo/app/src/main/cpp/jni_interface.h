#ifndef JNI_INTERFACE_H
#define JNI_INTERFACE_H

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL Java_com_google_sample_echo_MainActivity_createSLEngine(
    JNIEnv *env, jclass, jint, jint, jlong delayInMs, jfloat decay);
JNIEXPORT void JNICALL Java_com_google_sample_echo_MainActivity_deleteSLEngine(
    JNIEnv *env, jclass type);
JNIEXPORT jboolean JNICALL
Java_com_google_sample_echo_MainActivity_createSLBufferQueueAudioPlayer(
    JNIEnv *env, jclass);
JNIEXPORT void JNICALL
Java_com_google_sample_echo_MainActivity_deleteSLBufferQueueAudioPlayer(
    JNIEnv *env, jclass type);

JNIEXPORT jboolean JNICALL
Java_com_google_sample_echo_MainActivity_createAudioRecorder(JNIEnv *env,
                                                             jclass type);
JNIEXPORT void JNICALL
Java_com_google_sample_echo_MainActivity_deleteAudioRecorder(JNIEnv *env,
                                                             jclass type);
JNIEXPORT void JNICALL
Java_com_google_sample_echo_MainActivity_startPlay(JNIEnv *env, jclass type);
JNIEXPORT void JNICALL
Java_com_google_sample_echo_MainActivity_stopPlay(JNIEnv *env, jclass type);
JNIEXPORT jboolean JNICALL
Java_com_google_sample_echo_MainActivity_configureEcho(JNIEnv *env, jclass type,
                                                       jint delayInMs,
                                                       jfloat decay);
#ifdef __cplusplus
}
#endif

#endif  // JNI_INTERFACE_H

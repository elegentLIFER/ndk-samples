#include <jni.h>

extern "C" {

// Data callback stuff
JavaVM* theJvm;
jobject dataCallbackObj;
jmethodID midDataCallback;

/**
 * Initializes JNI interface stuff, specifically the info needed to call back
 * into the Java layer when MIDI data is received.
 */
JNICALL void Java_com_example_nativemidi_MainActivity_initNative(
    JNIEnv* env, jobject instance) {
  env->GetJavaVM(&theJvm);

  // Setup the receive data callback (into Java)
  jclass clsMainActivity =
      env->FindClass("com/example/nativemidi/MainActivity");
  dataCallbackObj = env->NewGlobalRef(instance);
  midDataCallback =
      env->GetMethodID(clsMainActivity, "onNativeMessageReceive", "([B)V");
}

}  // extern "C"

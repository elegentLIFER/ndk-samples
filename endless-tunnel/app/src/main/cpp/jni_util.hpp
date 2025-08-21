#ifndef endlesstunnel_jniutil_hpp
#define endlesstunnel_jniutil_hpp

struct JniSetup {
  jclass clazz;  // activity class
  jobject thiz;  // activity object
  JNIEnv* env;   // jni env
};

// Does JNI setup (if needed) and returns a struct with convenience objects.
struct JniSetup* GetJNISetup();

#endif

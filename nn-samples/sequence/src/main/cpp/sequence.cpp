#include <android/asset_manager_jni.h>
#include <android/log.h>
#include <android/sharedmem.h>
#include <fcntl.h>
#include <jni.h>
#include <sys/mman.h>

#include <iomanip>
#include <sstream>
#include <string>

#include "sequence_model.h"

extern "C" JNIEXPORT jlong JNICALL
Java_com_example_android_sequence_MainActivity_initModel(JNIEnv* env,
                                                         jobject /* this */,
                                                         jfloat ratio) {
  auto model = SimpleSequenceModel::Create(ratio);
  if (model == nullptr) {
    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG,
                        "Failed to create the model.");
    return 0;
  }

  return (jlong)(uintptr_t)model.release();
}

extern "C" JNIEXPORT jfloat JNICALL
Java_com_example_android_sequence_MainActivity_compute(JNIEnv* env,
                                                       jobject /* this */,
                                                       jfloat initialValue,
                                                       jint steps,
                                                       jlong _nnModel) {
  SimpleSequenceModel* nn_model = (SimpleSequenceModel*)_nnModel;
  float result = 0.0f;
  nn_model->Compute(initialValue, static_cast<uint32_t>(steps), &result);
  return result;
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_android_sequence_MainActivity_destroyModel(JNIEnv* env,
                                                            jobject /* this */,
                                                            jlong _nnModel) {
  SimpleSequenceModel* nn_model = (SimpleSequenceModel*)_nnModel;
  delete (nn_model);
}

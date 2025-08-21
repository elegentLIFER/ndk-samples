#include <jni.h>

#include "OboeSinePlayer.h"

static OboeSinePlayer *oboePlayer = nullptr;

extern "C" {
/* Create Oboe playback stream
 * Returns:  0 - success
 *          -1 - failed
 */
JNIEXPORT jint JNICALL
Java_com_google_example_hellooboe_MainActivity_createStream(
    JNIEnv * /* env */, jobject /* this */) {
  oboePlayer = new OboeSinePlayer();

  return oboePlayer ? 0 : -1;
}
JNIEXPORT void JNICALL
Java_com_google_example_hellooboe_MainActivity_destroyStream(
    JNIEnv * /* env */, jobject /* this */) {
  if (oboePlayer) {
    delete oboePlayer;
    oboePlayer = nullptr;
  }
}
/*
 * Play sound with pre-created Oboe stream
 * returns:  0  - success
 *          -1  - failed (stream has not created yet )
 */
JNIEXPORT jint JNICALL Java_com_google_example_hellooboe_MainActivity_playSound(
    JNIEnv * /* env */, jobject /* this */, jboolean enable) {
  jint result = 0;
  if (oboePlayer) {
    oboePlayer->enable(enable);
  } else {
    result = -1;
  }
  return result;
}
}

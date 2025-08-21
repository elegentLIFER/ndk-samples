#include <android/log.h>
#include <gmath.h>
#include <gperf.h>
#include <jni.h>

#include <cinttypes>
#include <cstring>
#include <string>

#define LOGI(...) \
  ((void)__android_log_print(ANDROID_LOG_INFO, "hello-libs::", __VA_ARGS__))

/* Do some calculations and measure how long they take.
 * See the corresponding Java source file located at:
 *
 *   app/src/main/java/com/example/hellolibs/MainActivity.java
 */
extern "C" JNIEXPORT jlong JNICALL
Java_com_example_hellolibs_MainActivity_measureTicks(JNIEnv *env,
                                                     jobject thiz) {
  auto ticks = GetTicks();

  for (auto exp = 0; exp < 1000; ++exp) {
    volatile unsigned val = gpower(exp);
    (void)val;  // to silence compiler warning
  }
  ticks = GetTicks() - ticks;

  LOGI("calculation time: %" PRIu64, ticks);

  return ticks;
}

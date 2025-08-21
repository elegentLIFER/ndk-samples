#include <jni.h>

#include <sstream>
#include <string>

#include "java_interop.h"
#include "json/json.h"

namespace jsonparse {

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_prefabdependency_MainActivity_getJsonValue(
    JNIEnv *env, jobject /* this */, jstring jsonFromJava,
    jstring keyFromJava) {
  if (jsonFromJava == nullptr) {
    logging::FatalError(env, "jsonFromJava argument cannot be null");
  }
  if (keyFromJava == nullptr) {
    logging::FatalError(env, "keyFromJava argument cannot be null");
  }

  const std::string json =
      jsonparse::jni::Convert<std::string>::from(env, jsonFromJava);
  const std::string key =
      jsonparse::jni::Convert<std::string>::from(env, keyFromJava);

  Json::Value root;
  std::istringstream(json) >> root;

  return jni::Convert<jstring>::from(env, root[key].asString());
}

}  // namespace jsonparse

#pragma once

#include <jni.h>

#include <cstdlib>
#include <functional>
#include <string>
#include <vector>

#include "logging.h"

namespace jsonparse::jni {

template <typename... ToTypes>
struct Convert;

template <>
struct Convert<std::string> {
  static std::string from(JNIEnv* env, const jstring& value) {
    typedef std::unique_ptr<const char[], std::function<void(const char*)>>
        JniString;

    JniString cstr(env->GetStringUTFChars(value, nullptr), [=](const char* p) {
      env->ReleaseStringUTFChars(value, p);
    });

    if (cstr == nullptr) {
      logging::FatalError(env, "%s: GetStringUTFChars failed", __func__);
    }

    return cstr.get();
  }
};

template <>
struct Convert<jstring> {
  static jstring from(JNIEnv* env, const std::string& from) {
    return env->NewStringUTF(from.c_str());
  }
};

}  // namespace jsonparse::jni

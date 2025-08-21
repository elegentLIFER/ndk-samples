#pragma once

#include <jni.h>

namespace jsonparse::logging {

[[noreturn, gnu::format(printf, 2, 3)]] void FatalError(JNIEnv* env,
                                                        const char* fmt, ...);

}  // namespace jsonparse::logging

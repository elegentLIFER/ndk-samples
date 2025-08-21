#pragma once

#include <jni.h>

namespace curlssl {
namespace logging {

[[noreturn, gnu::format(printf, 2, 3)]] void FatalError(JNIEnv* env,
                                                        const char* fmt, ...);

}  // namespace logging
}  // namespace curlssl

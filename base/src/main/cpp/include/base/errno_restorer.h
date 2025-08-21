#pragma once

#include <errno.h>

namespace ndksamples::base {

class ErrnoRestorer {
 public:
  ErrnoRestorer() : saved_errno_(errno) {}
  ErrnoRestorer(const ErrnoRestorer&) = delete;

  ~ErrnoRestorer() { errno = saved_errno_; }

  ErrnoRestorer& operator=(const ErrnoRestorer&) = delete;

  // Allow this object to be used as part of && operation.
  explicit operator bool() const { return true; }

 private:
  const int saved_errno_;
};

}  // namespace ndksamples::base

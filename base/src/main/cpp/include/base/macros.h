#pragma once

#include <stddef.h>  // for size_t

#include <utility>

// A macro to disallow the copy constructor and operator= functions
// This must be placed in the private: declarations for a class.
//
// For disallowing only assign or copy, delete the relevant operator or
// constructor, for example:
// void operator=(const TypeName&) = delete;
// Note, that most uses of DISALLOW_ASSIGN and DISALLOW_COPY are broken
// semantically, one should either use disallow both or neither. Try to
// avoid these in new code.
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName &) = delete;     \
  void operator=(const TypeName &) = delete

// A macro to disallow all the implicit constructors, namely the
// default constructor, copy constructor and operator= functions.
//
// This should be used in the private: declarations for a class
// that wants to prevent anyone from instantiating it. This is
// especially useful for classes containing only static methods.
#define DISALLOW_IMPLICIT_CONSTRUCTORS(TypeName) \
  TypeName() = delete;                           \
  DISALLOW_COPY_AND_ASSIGN(TypeName)

// The arraysize(arr) macro returns the # of elements in an array arr.
// The expression is a compile-time constant, and therefore can be
// used in defining new arrays, for example.  If you use arraysize on
// a pointer by mistake, you will get a compile-time error.
//
// One caveat is that arraysize() doesn't accept any array of an
// anonymous type or a type defined inside a function.  In these rare
// cases, you have to use the unsafe ARRAYSIZE_UNSAFE() macro below.  This is
// due to a limitation in C++'s template system.  The limitation might
// eventually be removed, but it hasn't happened yet.

// This template function declaration is used in defining arraysize.
// Note that the function doesn't need an implementation, as we only
// use its type.
template <typename T, size_t N>
char (&ArraySizeHelper(T (&array)[N]))[N];  // NOLINT(readability/casting)

#define arraysize(array) (sizeof(ArraySizeHelper(array)))

#define SIZEOF_MEMBER(t, f) sizeof(std::declval<t>().f)

// Changing this definition will cause you a lot of pain.  A majority of
// vendor code defines LIKELY and UNLIKELY this way, and includes
// this header through an indirect path.
#define LIKELY(exp) (__builtin_expect((exp) != 0, true))
#define UNLIKELY(exp) (__builtin_expect((exp) != 0, false))

/// True if the (runtime) version of the OS is at least x.
///
/// Clang is very particular about how __builtin_available is used. Logical
/// operations (including negation) may not be combined with
/// __builtin_available, so to negate this check you must do:
///
///     if (API_AT_LEAST(x)) {
///     } else {
///       // do negated stuff
///     }
#define API_AT_LEAST(x) __builtin_available(android x, *)

/// Marks a function as not callable on OS versions older than x.
///
/// This is a minor abuse of Clang's __attribute__((availability)), so the
/// diagnostic for this will be a little odd, but it allows us to extract
/// functions from code that already has an API_AT_LEAST guard without rewriting
/// the guard in every called function.
#define REQUIRES_API(x) __INTRODUCED_IN(x)

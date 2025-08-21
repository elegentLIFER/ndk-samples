#ifndef __GPERF_HPP__
#define __GPERF_HPP__

#include <sys/types.h>

/*
 * return current system ticks
 */
#ifdef __cplusplus
extern "C"
#endif  // __cplusplus
    uint64_t
    GetTicks(void);

#endif  //__GPERF_HPP__

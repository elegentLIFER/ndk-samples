#include "helloneon-intrinsics.h"
#if defined(HAVE_NEON) && defined(HAVE_NEON_X86)
/*
 * The latest version and instruction for NEON_2_SSE.h is at:
 *    https://github.com/intel/ARM_NEON_2_x86_SSE
 */
#include "NEON_2_SSE.h"
#elif defined(HAVE_NEON)
#include <arm_neon.h>
#endif

/* this source file should only be compiled by Android.mk /CMake when targeting
 * the armeabi-v7a ABI, and should be built in NEON mode
 */
void fir_filter_neon_intrinsics(short* output, const short* input,
                                const short* kernel, int width,
                                int kernelSize) {
#if 1
  int nn, offset = -kernelSize / 2;

  for (nn = 0; nn < width; nn++) {
    int mm, sum = 0;
    int32x4_t sum_vec = vdupq_n_s32(0);
    for (mm = 0; mm < kernelSize / 4; mm++) {
      int16x4_t kernel_vec = vld1_s16(kernel + mm * 4);
      int16x4_t input_vec = vld1_s16(input + (nn + offset + mm * 4));
      sum_vec = vmlal_s16(sum_vec, kernel_vec, input_vec);
    }

    sum += vgetq_lane_s32(sum_vec, 0);
    sum += vgetq_lane_s32(sum_vec, 1);
    sum += vgetq_lane_s32(sum_vec, 2);
    sum += vgetq_lane_s32(sum_vec, 3);

    if (kernelSize & 3) {
      for (mm = kernelSize - (kernelSize & 3); mm < kernelSize; mm++)
        sum += kernel[mm] * input[nn + offset + mm];
    }

    output[nn] = (short)((sum + 0x8000) >> 16);
  }
#else /* for comparison purposes only */
  int nn, offset = -kernelSize / 2;
  for (nn = 0; nn < width; nn++) {
    int sum = 0;
    int mm;
    for (mm = 0; mm < kernelSize; mm++) {
      sum += kernel[mm] * input[nn + offset + mm];
    }
    output[n] = (short)((sum + 0x8000) >> 16);
  }
#endif
}

// Copyright 2019 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.
//
// Auto-generated file. Do not edit!
//   Microkernel: qu8-vlrelu
//   Generator: tools/generate-vunary-test.py


#include <array>
#include <cmath>
#include <cstdint>
#include <cstddef>
#include <limits>

#include <gtest/gtest.h>
#include "xnnpack.h"
#include "xnnpack/common.h"
#include "xnnpack/isa-checks.h"
#include "xnnpack/microparams-init.h"
#include "xnnpack/microparams.h"
#include "xnnpack/vunary.h"
#include "next_prime.h"
#include "vunary-microkernel-tester.h"

using TestInfo = LeakyReLU;

#define XNN_UKERNEL_WITH_PARAMS(arch_flags, ukernel, batch_tile, vector_tile, datatype, params_type, init_params)                    \
  TEST(ukernel, batch_eq) { TestBatchEq<TestInfo, datatype, datatype>(arch_flags, batch_tile, ukernel, init_params); }               \
  TEST(ukernel, batch_div) { TestBatchDiv<TestInfo, datatype, datatype>(arch_flags, batch_tile, ukernel, init_params); }             \
  TEST(ukernel, batch_lt) { TestBatchLT<TestInfo, datatype, datatype>(arch_flags, batch_tile, ukernel, init_params); }               \
  TEST(ukernel, batch_gt) { TestBatchGT<TestInfo, datatype, datatype>(arch_flags, batch_tile, ukernel, init_params); }               \
  TEST(ukernel, inplace) { TestInPlace<TestInfo, datatype, datatype>(arch_flags, batch_tile, ukernel, init_params); }                \
TEST(ukernel, negative_slope) {                                                                                                      \
  TEST_REQUIRES_ARCH_FLAGS(arch_flags);                                                                                              \
  const size_t batch_scale = get_batch_scale<datatype>();                                                                            \
  const size_t batch_end = batch_tile * batch_scale;                                                                                 \
  const size_t batch_step = std::max(1, batch_tile - 1);                                                                             \
  for (float negative_slope : std::array<float, 3>({0.01f, 0.3f, 1.3f})) {                                                           \
    xnn_unary_params params;                                                                                                         \
    params.leaky_relu.negative_slope = negative_slope;                                                                               \
    for (size_t batch_size = 1; batch_size <= 5 * batch_end; batch_size += batch_step) {                                             \
      VUnaryMicrokernelTester()                                                                                                      \
        .batch_size(batch_size)                                                                                                      \
        .Test<TestInfo>(ukernel, init_params, params);                                                                               \
    }                                                                                                                                \
  }                                                                                                                                  \
}                                                                                                                                    \
TEST(ukernel, input_scale) { TestInputScale<TestInfo, datatype, datatype>(arch_flags, batch_tile, ukernel, init_params); }           \
TEST(ukernel, output_scale) { TestOutputScale<TestInfo, datatype, datatype>(arch_flags, batch_tile, ukernel, init_params); }         \
TEST(ukernel, input_zero_point) { TestInputZeroPoint<TestInfo, datatype, datatype>(arch_flags, batch_tile, ukernel, init_params); }  \
TEST(ukernel, output_zero_point) { TestOutputZeroPoint<TestInfo, datatype, datatype>(arch_flags, batch_tile, ukernel, init_params); }
#include "qu8-vlrelu/qu8-vlrelu.h"
#undef XNN_UKERNEL_WITH_PARAMS

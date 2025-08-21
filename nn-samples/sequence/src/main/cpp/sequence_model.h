#ifndef NNAPI_SIMPLE_MODEL_H
#define NNAPI_SIMPLE_MODEL_H

// #include "neuralnetworks_wrapper.h"
#include <android/NeuralNetworks.h>

#include <memory>

/**
 * SimpleSequenceModel
 * Build up the hardcoded graph of
 *
 *     sumIn ---+
 *              +--- ADD ---> sumOut
 *   stateIn ---+
 *              +--- MUL ---> stateOut
 *     ratio ---+
 *
 *   Operands are all 2-D TENSOR_FLOAT32 of:
 *       dimLength x dimLength
 *   with NO fused_activation operation
 *
 * This graph is used for computing a single step of accumulating a finite
 * geometry progression.
 *
 */
class SimpleSequenceModel {
 public:
  static std::unique_ptr<SimpleSequenceModel> Create(float ratio);

  // Prefer using SimpleSequenceModel::Create.
  explicit SimpleSequenceModel(float ratio);
  ~SimpleSequenceModel();

  bool Compute(float initialValue, uint32_t steps, float* result);

 private:
  bool CreateSharedMemories();
  bool CreateModel();
  bool CreateCompilation();
  bool CreateOpaqueMemories();

  ANeuralNetworksModel* model_ = nullptr;
  ANeuralNetworksCompilation* compilation_ = nullptr;

  static constexpr uint32_t dimLength_ = 200;
  static constexpr uint32_t tensorSize_ = dimLength_ * dimLength_;

  const float ratio_;

  // ASharedMemories. In reality, the values in the shared memory region will
  // be manipulated by other modules or processes.
  int initialStateFd_ = -1;
  int ratioFd_ = -1;
  int sumInFd_ = -1;
  int sumOutFd_ = -1;
  ANeuralNetworksMemory* memoryInitialState_ = nullptr;
  ANeuralNetworksMemory* memoryRatio_ = nullptr;
  ANeuralNetworksMemory* memorySumIn_ = nullptr;
  ANeuralNetworksMemory* memorySumOut_ = nullptr;

  // Opaque memories.
  ANeuralNetworksMemory* memoryOpaqueStateIn_ = nullptr;
  ANeuralNetworksMemory* memoryOpaqueStateOut_ = nullptr;
  ANeuralNetworksMemory* memoryOpaqueSumIn_ = nullptr;
  ANeuralNetworksMemory* memoryOpaqueSumOut_ = nullptr;
};

#define LOG_TAG "NNAPI_SEQUENCE"

#endif  // NNAPI_SIMPLE_MODEL_H

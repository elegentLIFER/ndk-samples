#ifndef NNAPI_SIMPLE_MODEL_H
#define NNAPI_SIMPLE_MODEL_H

#include <android/NeuralNetworks.h>
#include <android/asset_manager_jni.h>

#include <vector>

#define FLOAT_EPISILON (1e-6)
#define TENSOR_SIZE 200
#define LOG_TAG "NNAPI_BASIC"

/**
 * SimpleModel
 * Build up the hardcoded graph of
 *   ADD_1 ---+
 *            +--- MUL--->output result
 *   ADD_2 ---+
 *
 *   Operands are all 2-D TENSOR_FLOAT32 of:
 *       dimLength x dimLength
 *   with NO fused_activation operation
 *
 */
class SimpleModel {
 public:
  explicit SimpleModel(AAsset *asset);
  ~SimpleModel();

  bool CreateCompiledModel();
  bool Compute(float inputValue1, float inputValue2, float *result);

 private:
  ANeuralNetworksModel *model_;
  ANeuralNetworksCompilation *compilation_;
  ANeuralNetworksMemory *memoryModel_;
  ANeuralNetworksMemory *memoryInput2_;
  ANeuralNetworksMemory *memoryOutput_;

  uint32_t dimLength_;
  uint32_t tensorSize_;

  std::vector<float> inputTensor1_;
  int inputTensor2Fd_;
  int outputTensorFd_;
};

#endif  // NNAPI_SIMPLE_MODEL_H
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#pragma once

#include "core/common/common.h"
#include "core/framework/op_kernel.h"
#include <memory>
#include <vector>

namespace onnxruntime {
namespace contrib {

class Ngram final : public OpKernel {
 public:
  explicit Ngram(const OpKernelInfo& info);
  ~Ngram();
  ORT_DISALLOW_COPY_ASSIGNMENT_AND_MOVE(Ngram);

  Status Compute(OpKernelContext* ctx) const override;

 private:
  template <typename T>
  Status ComputeImpl(OpKernelContext* ctx) const;

  // Apply weighing criteria and output
  void OutputResult(OpKernelContext* ctx, size_t b_dim, const std::vector<uint32_t>& frequences) const;

  struct Impl;
  std::unique_ptr<Impl> impl_;
};

}  // namespace contrib
}  // namespace onnxruntime

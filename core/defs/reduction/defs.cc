// Copyright (c) Facebook Inc. and Microsoft Corporation.
// Licensed under the MIT license.

#ifdef ONNX_V1_OPSCHEMA_COMPAT
#include "op.h"
#include <functional>

namespace LotusIR {

std::function<void(OpSchema&)> ReduceDocGenerator(const char* name) {
    return [=](OpSchema& schema) {
        std::string doc = R"DOC(
Computes the {name} of the input tensor's element along the provided axes. The resulted
tensor has the same shape as the input if keepdims equal 1. If keepdims equal 0, then 
the resulted tensor have the reduced dimension pruned.

The above behavior is similar to numpy, with the exception that numpy default keepdims to
False instead of True.)DOC";
        ReplaceAll(doc, "{name}", name);
        schema.SetDoc(doc);
        schema.Attr("axes",
                    "A list of integers, along which to reduce max.",
                    AttrType::INTS);
        schema.Attr("keepdims",
                    "Keep the reduced dimension or not, default 1 mean keep reduced dimension.",
                    AttrType::INT);
        schema.Input(0, "data", "An input tensor.");
        schema.Output(0, "reduced", "Reduced output tensor.");
    };
}
  
OPERATOR_SCHEMA(ReduceMax)
    .NumInputs(1)
    .NumOutputs(1)
    .FillUsing(ReduceDocGenerator("max"));

OPERATOR_SCHEMA(ReduceMin)
    .NumInputs(1)
    .NumOutputs(1)
    .FillUsing(ReduceDocGenerator("min"));

OPERATOR_SCHEMA(ReduceSum)
    .NumInputs(1)
    .NumOutputs(1)
    .FillUsing(ReduceDocGenerator("sum"));

OPERATOR_SCHEMA(ReduceMean)
    .NumInputs(1)
    .NumOutputs(1)
    .FillUsing(ReduceDocGenerator("mean"));

OPERATOR_SCHEMA(ReduceProd)
    .NumInputs(1)
    .NumOutputs(1)
    .FillUsing(ReduceDocGenerator("product"));

OPERATOR_SCHEMA(ReduceLogSumExp)
    .NumInputs(1)
    .NumOutputs(1)
    .FillUsing(ReduceDocGenerator("log sum exponent"));

std::function<void(OpSchema&)> ArgReduceDocGenerator(const char* name) {
    return [=](OpSchema& schema) {
        std::string doc = R"DOC(
Computes the indices of the {name} elements of the input tensor's element along the 
provided axes. The resulted tensor has the same shape as the input if keepdims equal 1. 
If keepdims equal 0, then the resulted tensor have the reduced dimension pruned. 
The type of the output tensor is integer.)DOC";
        ReplaceAll(doc, "{name}", name);
        schema.SetDoc(doc);
        schema.Attr("axes",
                    "A list of integers, along which to reduce max.",
                    AttrType::INTS);
        schema.Attr("keepdims",
                    "Keep the reduced dimension or not, default 1 mean keep reduced dimension.",
                    AttrType::INT);
        schema.Input(0, "data", "An input tensor.");
        schema.Output(0, "reduced", "Reduced output tensor with integer data type.");
    };
}

OPERATOR_SCHEMA(ArgMax)
    .NumInputs(1)
    .NumOutputs(1)
    .FillUsing(ArgReduceDocGenerator("max"));

OPERATOR_SCHEMA(ArgMin)
    .NumInputs(1)
    .NumOutputs(1)
    .FillUsing(ArgReduceDocGenerator("min"));

}  // namespace LotusIR
#endif //#ifdef ONNX_V1_OPSCHEMA_COMPAT
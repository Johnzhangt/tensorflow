/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#ifndef TENSORFLOW_CORE_PROFILER_UTILS_XPLANE_SCHEMA_H_
#define TENSORFLOW_CORE_PROFILER_UTILS_XPLANE_SCHEMA_H_

#include "absl/strings/match.h"
#include "absl/strings/string_view.h"
#include "absl/types/optional.h"
#include "absl/types/span.h"
#include "tensorflow/core/platform/logging.h"

namespace tensorflow {
namespace profiler {

// Name of XPlane that contains TraceMe events.
ABSL_CONST_INIT extern const absl::string_view kHostThreads;
// Name prefix of XPlane that contains GPU events.
ABSL_CONST_INIT extern const absl::string_view kGpuPlanePrefix;

// Id of XPlane that contains TraceMe events.
ABSL_CONST_INIT extern const int32 kHostPlaneId;
// Ids prefix of XPlane that contains GPU events.
ABSL_CONST_INIT extern const int32 kGpuPlaneBaseId;

// Interesting event types (i.e., TraceMe names).
enum HostEventType {
  kFirstHostEventType = 0,
  kUnknownHostEventType = kFirstHostEventType,
  kTraceContext,
  kSessionRun,
  kFunctionRun,
  kRunGraph,
  kEagerKernelExecute,
  kExecutorStateProcess,
  kExecutorDoneCallback,
  kMemoryAllocation,
  kMemoryDeallocation,
  // Performance counter related.
  kRemotePerf,
  // tf.data captured function events.
  kTfDataCapturedFunctionRun,
  kTfDataCapturedFunctionRunWithBorrowedArgs,
  kTfDataCapturedFunctionRunInstantiated,
  kTfDataCapturedFunctionRunAsync,
  // Functional ops.
  kCallOp,
  kParallelForOp,
  kForeverOp,
  kNumericalGradientOpEvalRight,
  kNumericalGradientOpEvalLeft,
  kSymbolicGradientOp,
  kRemoteCallOp,
  kIfOp,
  kCaseOp,
  kWhileOpEvalCond,
  kWhileOpStartBody,
  kForOp,
  kPartitionedCallOp,
  kLastHostEventType = kPartitionedCallOp,
};

enum StatType {
  kFirstStatType = 0,
  kUnknownStatType = kFirstStatType,
  // TraceMe arguments.
  kStepId,
  kParentStepId,
  kFunctionStepId,
  kDeviceOrdinal,
  kChipOrdinal,
  kNodeOrdinal,
  kModelId,
  kQueueAddr,
  kRequestId,
  kRunId,
  kGraphType,
  kStepNum,
  kIterNum,
  kIndexOnHost,
  kAllocatorName,
  kBytesReserved,
  kBytesAllocated,
  kBytesAvailable,
  kFragmentation,
  kPeakBytesInUse,
  // Device trace arguments.
  kDeviceId,
  kContextId,
  kCorrelationId,
  kMemcpyDetails,
  kMemallocDetails,
  kKernelDetails,
  kStream,
  // Stats added when processing traces.
  kGroupId,
  kStepName,
  kLevel0,
  kTfOp,
  kHloOp,
  kHloModule,
  // Performance counter related.
  kRawValue,
  kScaledValue,
  kThreadId,
  // XLA metadata map related.
  kSelfDurationPs,
  kMinDurationPs,
  // Device capability related.
  kDevCapClockRateKHz,
  kDevCapCoreCount,
  kDevCapMemoryBandwidth,
  kDevCapMemorySize,
  kDevCapComputeCapMajor,
  kDevCapComputeCapMinor,
  kLastStatType = kDevCapComputeCapMinor,
};

absl::string_view GetHostEventTypeStr(HostEventType event_type);

bool IsHostEventType(HostEventType event_type, absl::string_view event_name);

inline bool IsHostEventType(HostEventType event_type,
                            absl::string_view event_name) {
  return GetHostEventTypeStr(event_type) == event_name;
}

absl::optional<int64> FindHostEventType(absl::string_view event_name);

absl::string_view GetStatTypeStr(StatType stat_type);

bool IsStatType(StatType stat_type, absl::string_view stat_name);

inline bool IsStatType(StatType stat_type, absl::string_view stat_name) {
  return GetStatTypeStr(stat_type) == stat_name;
}

absl::optional<int64> FindStatType(absl::string_view stat_name);

}  // namespace profiler
}  // namespace tensorflow

#endif  // TENSORFLOW_CORE_PROFILER_UTILS_XPLANE_SCHEMA_H_

//
// Created by kuscsik on 3/31/23.
//

#include "NativeService.h"

#include <android/log.h>
#include <android/binder_parcel_utils.h>

namespace aidl {
namespace io {
namespace s57 {
NativeService::NativeService() {
  __android_log_print(ANDROID_LOG_INFO, "NativeService", "NativeService::NativeService()");
}

NativeService::~NativeService() {
  __android_log_print(ANDROID_LOG_INFO, "NativeService", "NativeService::~NativeService()");
}

::ndk::ScopedAStatus NativeService::processHardwareBuffer(int32_t in_streamId, const ::ndk::ScopedFileDescriptor& in_hwBufferFd) {
  __android_log_print(ANDROID_LOG_INFO, "NativeService", "NativeService::processHardwareBuffer() :"
                                                         "Stream ID: %d FD: %d", in_streamId, in_hwBufferFd.get());
  return ::ndk::ScopedAStatus::ok();
}

}
}
}
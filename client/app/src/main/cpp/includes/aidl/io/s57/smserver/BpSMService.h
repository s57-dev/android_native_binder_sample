#pragma once

#include "aidl/io/s57/smserver/ISMService.h"

#include <android/binder_ibinder.h>

namespace aidl {
namespace io {
namespace s57 {
namespace smserver {
class BpSMService : public ::ndk::BpCInterface<ISMService> {
public:
  BpSMService(const ::ndk::SpAIBinder& binder);
  virtual ~BpSMService();

  ::ndk::ScopedAStatus processHardwareBuffer(int32_t in_streamId, const ::ndk::ScopedFileDescriptor& in_hwBufferFd) override;
};
}  // namespace smserver
}  // namespace s57
}  // namespace io
}  // namespace aidl

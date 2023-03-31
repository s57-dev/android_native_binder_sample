#pragma once

#include <android/binder_interface_utils.h>

#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <vector>
#ifdef BINDER_STABILITY_SUPPORT
#include <android/binder_stability.h>
#endif  // BINDER_STABILITY_SUPPORT

namespace aidl {
namespace io {
namespace s57 {
namespace smserver {
class ISMService : public ::ndk::ICInterface {
public:
  static const char* descriptor;
  ISMService();
  virtual ~ISMService();



  static std::shared_ptr<ISMService> fromBinder(const ::ndk::SpAIBinder& binder);
  static binder_status_t writeToParcel(AParcel* parcel, const std::shared_ptr<ISMService>& instance);
  static binder_status_t readFromParcel(const AParcel* parcel, std::shared_ptr<ISMService>* instance);
  static bool setDefaultImpl(std::shared_ptr<ISMService> impl);
  static const std::shared_ptr<ISMService>& getDefaultImpl();
  virtual ::ndk::ScopedAStatus processHardwareBuffer(int32_t in_streamId, const ::ndk::ScopedFileDescriptor& in_hwBufferFd) = 0;
private:
  static std::shared_ptr<ISMService> default_impl;
};
class ISMServiceDefault : public ISMService {
public:
  ::ndk::ScopedAStatus processHardwareBuffer(int32_t in_streamId, const ::ndk::ScopedFileDescriptor& in_hwBufferFd) override;
  ::ndk::SpAIBinder asBinder() override;
  bool isRemote() override;
};
}  // namespace smserver
}  // namespace s57
}  // namespace io
}  // namespace aidl

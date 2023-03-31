#pragma once

#include "aidl/io/s57/smserver/ISMService.h"

#include <android/binder_ibinder.h>

namespace aidl {
namespace io {
namespace s57 {
namespace smserver {
class BnSMService : public ::ndk::BnCInterface<ISMService> {
public:
  BnSMService();
  virtual ~BnSMService();
protected:
  ::ndk::SpAIBinder createBinder() override;
private:
};
}  // namespace smserver
}  // namespace s57
}  // namespace io
}  // namespace aidl

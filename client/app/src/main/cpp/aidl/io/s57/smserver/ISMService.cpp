#include <android/binder_parcel_utils.h>
#include <aidl/io/s57/smserver/BpSMService.h>
#include <aidl/io/s57/smserver/BnSMService.h>
#include <aidl/io/s57/smserver/ISMService.h>

namespace aidl {
namespace io {
namespace s57 {
namespace smserver {
static binder_status_t _aidl_onTransact(AIBinder* _aidl_binder, transaction_code_t _aidl_code, const AParcel* _aidl_in, AParcel* _aidl_out) {
  (void)_aidl_in;
  (void)_aidl_out;
  binder_status_t _aidl_ret_status = STATUS_UNKNOWN_TRANSACTION;
  std::shared_ptr<BnSMService> _aidl_impl = std::static_pointer_cast<BnSMService>(::ndk::ICInterface::asInterface(_aidl_binder));
  switch (_aidl_code) {
    case (FIRST_CALL_TRANSACTION + 0 /*processHardwareBuffer*/): {
      int32_t in_streamId;
      ::ndk::ScopedFileDescriptor in_hwBufferFd;

      _aidl_ret_status = AParcel_readInt32(_aidl_in, &in_streamId);
      if (_aidl_ret_status != STATUS_OK) break;

      _aidl_ret_status = ::ndk::AParcel_readRequiredParcelFileDescriptor(_aidl_in, &in_hwBufferFd);
      if (_aidl_ret_status != STATUS_OK) break;

      ::ndk::ScopedAStatus _aidl_status = _aidl_impl->processHardwareBuffer(in_streamId, in_hwBufferFd);
      _aidl_ret_status = AParcel_writeStatusHeader(_aidl_out, _aidl_status.get());
      if (_aidl_ret_status != STATUS_OK) break;

      if (!AStatus_isOk(_aidl_status.get())) break;

      break;
    }
  }
  return _aidl_ret_status;
}

static AIBinder_Class* _g_aidl_clazz = ::ndk::ICInterface::defineClass(ISMService::descriptor, _aidl_onTransact);

BpSMService::BpSMService(const ::ndk::SpAIBinder& binder) : BpCInterface(binder) {}
BpSMService::~BpSMService() {}

::ndk::ScopedAStatus BpSMService::processHardwareBuffer(int32_t in_streamId, const ::ndk::ScopedFileDescriptor& in_hwBufferFd) {
  binder_status_t _aidl_ret_status = STATUS_OK;
  ::ndk::ScopedAStatus _aidl_status;
  ::ndk::ScopedAParcel _aidl_in;
  ::ndk::ScopedAParcel _aidl_out;

  _aidl_ret_status = AIBinder_prepareTransaction(asBinder().get(), _aidl_in.getR());
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = AParcel_writeInt32(_aidl_in.get(), in_streamId);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = ::ndk::AParcel_writeRequiredParcelFileDescriptor(_aidl_in.get(), in_hwBufferFd);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = AIBinder_transact(
    asBinder().get(),
    (FIRST_CALL_TRANSACTION + 0 /*processHardwareBuffer*/),
    _aidl_in.getR(),
    _aidl_out.getR(),
    0
    #ifdef BINDER_STABILITY_SUPPORT
    | FLAG_PRIVATE_LOCAL
    #endif  // BINDER_STABILITY_SUPPORT
    );
  if (_aidl_ret_status == STATUS_UNKNOWN_TRANSACTION && ISMService::getDefaultImpl()) {
    return ISMService::getDefaultImpl()->processHardwareBuffer(in_streamId, in_hwBufferFd);
  }
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = AParcel_readStatusHeader(_aidl_out.get(), _aidl_status.getR());
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  if (!AStatus_isOk(_aidl_status.get())) return _aidl_status;

  _aidl_error:
  _aidl_status.set(AStatus_fromStatus(_aidl_ret_status));
  return _aidl_status;
}
// Source for BnSMService
BnSMService::BnSMService() {}
BnSMService::~BnSMService() {}
::ndk::SpAIBinder BnSMService::createBinder() {
  AIBinder* binder = AIBinder_new(_g_aidl_clazz, static_cast<void*>(this));
  #ifdef BINDER_STABILITY_SUPPORT
  AIBinder_markCompilationUnitStability(binder);
  #endif  // BINDER_STABILITY_SUPPORT
  return ::ndk::SpAIBinder(binder);
}
// Source for ISMService
const char* ISMService::descriptor = "io.s57.smserver.ISMService";
ISMService::ISMService() {}
ISMService::~ISMService() {}


std::shared_ptr<ISMService> ISMService::fromBinder(const ::ndk::SpAIBinder& binder) {
  if (!AIBinder_associateClass(binder.get(), _g_aidl_clazz)) { return nullptr; }
  std::shared_ptr<::ndk::ICInterface> interface = ::ndk::ICInterface::asInterface(binder.get());
  if (interface) {
    return std::static_pointer_cast<ISMService>(interface);
  }
  return ::ndk::SharedRefBase::make<BpSMService>(binder);
}

binder_status_t ISMService::writeToParcel(AParcel* parcel, const std::shared_ptr<ISMService>& instance) {
  return AParcel_writeStrongBinder(parcel, instance ? instance->asBinder().get() : nullptr);
}
binder_status_t ISMService::readFromParcel(const AParcel* parcel, std::shared_ptr<ISMService>* instance) {
  ::ndk::SpAIBinder binder;
  binder_status_t status = AParcel_readStrongBinder(parcel, binder.getR());
  if (status != STATUS_OK) return status;
  *instance = ISMService::fromBinder(binder);
  return STATUS_OK;
}
bool ISMService::setDefaultImpl(std::shared_ptr<ISMService> impl) {
  // Only one user of this interface can use this function
  // at a time. This is a heuristic to detect if two different
  // users in the same process use this function.
  assert(!ISMService::default_impl);
  if (impl) {
    ISMService::default_impl = impl;
    return true;
  }
  return false;
}
const std::shared_ptr<ISMService>& ISMService::getDefaultImpl() {
  return ISMService::default_impl;
}
std::shared_ptr<ISMService> ISMService::default_impl = nullptr;
::ndk::ScopedAStatus ISMServiceDefault::processHardwareBuffer(int32_t /*in_streamId*/, const ::ndk::ScopedFileDescriptor& /*in_hwBufferFd*/) {
  ::ndk::ScopedAStatus _aidl_status;
  _aidl_status.set(AStatus_fromStatus(STATUS_UNKNOWN_TRANSACTION));
  return _aidl_status;
}
::ndk::SpAIBinder ISMServiceDefault::asBinder() {
  return ::ndk::SpAIBinder();
}
bool ISMServiceDefault::isRemote() {
  return false;
}
}  // namespace smserver
}  // namespace s57
}  // namespace io
}  // namespace aidl

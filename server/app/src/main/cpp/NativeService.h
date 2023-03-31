//
// Created by kuscsik on 3/31/23.
//

#ifndef SERVER_APP_SRC_MAIN_CPP_NATIVESERVICE_H
#define SERVER_APP_SRC_MAIN_CPP_NATIVESERVICE_H

#include <aidl/io/s57/smserver/BnSMService.h>
namespace aidl {
namespace io {
namespace s57 {

class NativeService : public smserver::BnSMService {
public:
    NativeService();
    virtual ~NativeService();
    ::ndk::ScopedAStatus processHardwareBuffer(int32_t in_streamId, const ::ndk::ScopedFileDescriptor& in_hwBufferFd) override;
};

}
}
}

#endif //SERVER_APP_SRC_MAIN_CPP_NATIVESERVICE_H

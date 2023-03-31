// ISMService.aidl
package io.s57.smserver;
import	android.os.ParcelFileDescriptor;

// Declare any non-default types here with import statements

interface ISMService {
    /**
     * Pass a stream ID and a HW buffer as FD
     */
    void processHardwareBuffer(int streamId, in ParcelFileDescriptor hwBufferFd);
}
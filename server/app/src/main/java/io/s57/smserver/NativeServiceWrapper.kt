package io.s57.smserver

import android.app.Service
import android.content.Intent
import android.os.IBinder
import android.util.Log

class NativeServiceWrapper : Service() {
    val TAG = "NativeServiceWrapper"

    companion object {
        init {
            System.loadLibrary("smserver")
        }
    }

    private var mBinder: IBinder? = null

    override fun onCreate() {
        super.onCreate()
        mBinder = getNativeService()
        if (null == mBinder) {
            Log.e(TAG, "Failed to bind native service")
        } else {
            Log.i(TAG, "Native service bound")
        }
    }


    override fun onBind(intent: Intent): IBinder {
        return mBinder!!
    }


    private external fun getNativeService(): IBinder?

}
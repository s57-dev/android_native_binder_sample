package io.s57.nclient

import android.content.ComponentName
import android.content.Intent
import android.content.ServiceConnection
import android.os.Bundle
import android.os.ConditionVariable
import android.os.IBinder
import androidx.appcompat.app.AppCompatActivity


class MainActivity : AppCompatActivity(), ServiceConnection {
    @Volatile
    private var mIsServiceConnected = false
    private val mWaitLock: ConditionVariable = ConditionVariable()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
    }

    override fun onResume() {
        super.onResume()
        val intent = Intent()
        val componentName = ComponentName("io.s57.smserver", "io.s57.smserver.NativeServiceWrapper")
        intent.component = componentName

        val result = bindService(intent, this, BIND_AUTO_CREATE)

        if (!result) {
            throw RuntimeException("Failed to bind service")
        }

        Thread(object : Runnable {
            override fun run() {
                while (!mIsServiceConnected) {
                    mWaitLock.block()
                }
                sendBuffer()
            }
        }).start()
    }

    override fun onPause() {
        unbindService(this)
        mIsServiceConnected = false
        onNativeServiceDisconnected()
        super.onPause()
    }

    override fun onServiceConnected(componentName: ComponentName?, iBinder: IBinder?) {
        onNativeServiceConnected(iBinder)
        mIsServiceConnected = true
        mWaitLock.open()
    }

    override fun onServiceDisconnected(componentName: ComponentName?) {
        mIsServiceConnected = false
        onNativeServiceDisconnected()
    }


    /**
     * A native methods that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    external fun onNativeServiceConnected(binder: IBinder?)
    external fun onNativeServiceDisconnected()
    external fun sendBuffer(): String

    companion object {
        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("nclient")
        }
    }
}

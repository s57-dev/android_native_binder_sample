package io.s57.smserver

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import io.s57.smserver.databinding.ActivityMainBinding
class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        // Start NativeServiceWrapper
        startService(Intent(this, NativeServiceWrapper::class.java))
        setContentView(binding.root)
    }

}
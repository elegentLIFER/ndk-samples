package com.example.android.basic

import android.app.Activity
import android.content.res.AssetManager
import android.os.Bundle
import android.widget.Toast
import com.example.android.basic.databinding.ActivityMainBinding
import kotlinx.coroutines.*

/*
  MainActivity to take care of UI and user inputs
 */
class MainActivity : Activity() {
    private var modelHandle = 0L

    /*
       3 JNI functions managing NN models, refer to basic/README.md
       for model structure
     */
    private external fun initModel(assetManager: AssetManager?, assetName: String?): Long
    private external fun startCompute(modelHandle: Long, input1: Float, input2: Float): Float
    private external fun destroyModel(modelHandle: Long)

    private lateinit var binding: ActivityMainBinding
    private val activityJob = Job()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)
        CoroutineScope(Dispatchers.IO + activityJob).async(Dispatchers.IO) {
            modelHandle = this@MainActivity.initModel(assets, "model_data.bin")
        }

        binding.computButton.setOnClickListener {
            if (modelHandle == 0L) {
                Toast.makeText(applicationContext, "Model initializing, please wait",
                        Toast.LENGTH_SHORT).show()
            }

            if (binding.tensorSeed0.text.isNotEmpty() && binding.tensorSeed2.text.isNotEmpty()) {
                Toast.makeText(applicationContext, "Computing", Toast.LENGTH_SHORT).show()
                binding.computeResult.text = runBlocking {
                    val operand0 = binding.tensorSeed0.text.toString().toFloat()
                    val operand2 = binding.tensorSeed2.text.toString().toFloat()
                    startCompute(modelHandle, operand0, operand2).toString()
                }.toString()
            }
        }
    }

    override fun onDestroy() {
        activityJob.cancel()
        if (modelHandle != 0L) {
            destroyModel(modelHandle)
            modelHandle = 0
        }
        super.onDestroy()
    }

    companion object {
        init {
            System.loadLibrary("basic")
        }
    }
}


package com.example.prefabdependency

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import com.example.prefabdependency.databinding.ActivityJsonParseBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityJsonParseBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityJsonParseBinding.inflate(layoutInflater)
        val view = binding.root
        setContentView(view)
        binding.resultTextview.text = getJsonValue(
            """
            {
                "cpp": "clang",
                "aar": "Prefab",
                "package": "cmake",
                "app": "gradle"
            }
            """.trimIndent(), "aar"
        )

    }

    private external fun getJsonValue(jsonString: String, key: String): String

    companion object {
        init {
            System.loadLibrary("app")
        }
    }
}

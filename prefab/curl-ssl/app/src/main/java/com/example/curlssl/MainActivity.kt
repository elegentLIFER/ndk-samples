package com.example.curlssl

import android.app.ListActivity
import android.os.Bundle
import android.widget.ArrayAdapter
import java.io.FileOutputStream

class MainActivity : ListActivity() {
    private val cacert by lazy {
        val path = cacheDir.resolve("cacert.pem")
        assets.open("cacert.pem").copyTo(FileOutputStream(path))
        path
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        listAdapter = ArrayAdapter<String>(
            this,
            android.R.layout.simple_list_item_1,
            getGerritChanges(cacert.path)
        )
    }

    private external fun getGerritChanges(cacert: String): Array<String>

    companion object {
        init {
            System.loadLibrary("app")
        }
    }
}

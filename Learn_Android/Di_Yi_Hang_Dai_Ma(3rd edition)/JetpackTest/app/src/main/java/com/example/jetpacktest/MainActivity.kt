package com.example.jetpacktest

import android.content.SharedPreferences
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import android.widget.TextView
import androidx.core.content.edit
import androidx.lifecycle.Observer
import androidx.lifecycle.ViewModelProvider
import androidx.work.BackoffPolicy
import androidx.work.OneTimeWorkRequest
import androidx.work.WorkManager
import java.util.concurrent.TimeUnit

class MainActivity : AppCompatActivity() {
    lateinit var viewModel:MainVIewModel
    lateinit var plusOneBtn:Button
    lateinit var clearBtn:Button
    lateinit var infoText:TextView
    lateinit var getUserBtn:Button
    lateinit var sp:SharedPreferences

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        sp=getPreferences(MODE_PRIVATE)
        val countReserved = sp.getInt("count_reserved",0)
        viewModel = ViewModelProvider(this,MainViewModelFactory(countReserved)).get(MainVIewModel::class.java)
        plusOneBtn = findViewById(R.id.plusOneBtn)
        infoText = findViewById(R.id.infoText)
        clearBtn = findViewById(R.id.clearBtn)
        getUserBtn = findViewById(R.id.getUserBtn)
        plusOneBtn.setOnClickListener {
            viewModel.plusOne()
            refreshCounter()
        }
        clearBtn.setOnClickListener {
            viewModel.clear()
            refreshCounter()
        }
        lifecycle.addObserver(MyObserver(lifecycle))
        viewModel.counter.observe(this, {
            infoText.text = it.toString()
        })

        getUserBtn.setOnClickListener {
            val userId = (0..1000).random().toString()
            viewModel.getUser(userId)
        }
        viewModel.user.observe(this,{
            infoText.text = it.firstName
        })

        //WorkManager
        findViewById<Button>(R.id.doWorkBtn).setOnClickListener {
            val request = OneTimeWorkRequest.Builder(SimpleWorker::class.java)
                .setInitialDelay(5,TimeUnit.SECONDS)
                .setBackoffCriteria(BackoffPolicy.LINEAR,10,TimeUnit.SECONDS)
                .build()
            WorkManager.getInstance(this).enqueue(request)
        }

    }

    override fun onPause() {
        super.onPause()
        sp.edit {
            putInt("count_reserved",viewModel.counter.value?:0)
        }
    }

    private fun refreshCounter(){
        infoText.text = viewModel.counter.toString()
    }
}
package com.example.videoplay

import android.net.Uri
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.widget.VideoView

class MainActivity : AppCompatActivity() {
    lateinit var videoView: VideoView
    lateinit var play:View
    lateinit var pause:View
    lateinit var replay:View
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        val uri = Uri.parse("android.resource://$packageName/${R.raw.video}")
        videoView= findViewById<VideoView>(R.id.videoView)
        play = findViewById(R.id.play)
        pause = findViewById(R.id.pause)
        replay = findViewById(R.id.replay)
        videoView.setVideoURI(uri)
        findViewById<View>(R.id.play).setOnClickListener {
            if(!videoView.isPlaying){
                videoView.start()
            }
        }
        replay.setOnClickListener {
            if(videoView.isPlaying){
                videoView.resume()
            }
        }

        pause.setOnClickListener {
            if(videoView.isPlaying){
                videoView.pause()
            }
        }
    }
}
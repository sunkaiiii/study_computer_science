package com.example.beatbox

import androidx.databinding.BaseObservable
import androidx.databinding.Bindable
import androidx.lifecycle.MutableLiveData

class SoundViewModel(private val beatBox: BeatBox) {
    val title = MutableLiveData<String?>()

    var sound:Sound? = null
    set(sound){
        field = sound
        title.postValue(sound?.name)
    }

    fun onButtonClick(){
        beatBox.play(sound?:return)
    }
}

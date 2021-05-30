package com.example.jetpacktest

import androidx.lifecycle.*

class MainVIewModel(counterReserved:Int):ViewModel() {
    val counter:LiveData<Int>
    get() = _counter

    private val _counter = MutableLiveData<Int>()

    init{
        _counter.value = counterReserved
    }

    fun plusOne(){
        val count = _counter.value?:0
        _counter.value = count+1
    }

    fun clear(){
        _counter.value = 0
    }

    private val userIdLiveData = MutableLiveData<String>()

    val user:LiveData<User> = Transformations.switchMap(userIdLiveData){userId->
        Repository.getUser(userId)
    }

    fun getUser(userId:String){
        userIdLiveData.value = userId
    }
}

class MainViewModelFactory(private val counterReserved: Int):ViewModelProvider.Factory{
    override fun <T : ViewModel?> create(modelClass: Class<T>): T {
        return MainVIewModel(counterReserved) as T
    }
}
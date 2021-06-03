package com.example.photogallery

import android.app.Application
import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.Transformations
import androidx.lifecycle.ViewModel
import com.example.photogallery.api.FlickrFetchr

class PhotoGalleryViewModel(private val app: Application) : ViewModel() {
    val galleryItemLiveData: LiveData<List<GalleryItem>>
    val fecthr = FlickrFetchr()
    val searchTerm: String
        get() = mutableSearchTerm.value ?: ""
    private val mutableSearchTerm = MutableLiveData<String>()

    init {
        mutableSearchTerm.value = QueryPreferences.getStoredQuery(app)
        galleryItemLiveData = Transformations.switchMap(mutableSearchTerm) { searchTerm ->
            if (searchTerm.isBlank()) {
                fecthr.fetchPhotos()
            } else {
                fecthr.searchPhotos(searchTerm)
            }
        }
    }

    override fun onCleared() {
        super.onCleared()
        fecthr.cancelCall()
    }

    fun fetchPhotos(query: String = "") {
        QueryPreferences.setStoredQuery(app, query)
        mutableSearchTerm.value = query
    }
}
package com.example.sunkai.downloadservice;

/**
 * Created by sunkai on 2017/12/26.
 */

public interface DownloadListener {
    void onProgress(int progress);
    void onSuccess();
    void onFailed();
    void onPaused();
    void onCanceled();
}

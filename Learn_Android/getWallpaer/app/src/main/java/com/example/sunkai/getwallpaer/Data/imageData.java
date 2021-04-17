package com.example.sunkai.getwallpaer.Data;

/**
 * Created by sunkai on 2018/1/26.
 */

public final class imageData {
    private final String copyright;
    private final String url;
    private final String date;

    public imageData(final String copyright,final String url,final String date){
        this.copyright=copyright;
        this.url=url;
        this.date=date;
    }

    public String getCopyright() {
        return copyright;
    }

    public String getUrl() {
        return url;
    }

    public String getDate() {
        return date;
    }
}

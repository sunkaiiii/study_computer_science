package com.example.sunkai.activityproxyhost.myapplicaiton

import android.app.Activity
import android.content.pm.ActivityInfo
import android.content.pm.PackageInfo
import android.content.pm.PackageManager
import android.content.res.AssetManager
import android.content.res.Resources
import android.util.Log
import android.os.Build


/*
 * Created by sunkai on 2018/1/23.
 */
open class BaseActivity : Activity() {
    protected var mAssetManager: AssetManager? = null
    protected var mResources: Resources? = null
    protected var mTheme: Resources.Theme? = null
    private var mActivityInfo: ActivityInfo? = null
    private var packageInfo: PackageInfo? = null

    protected fun loadResources(dexPath: String, mProxyActivity: Activity) {
        initializeActivityInfo(dexPath)
        try {
            val assetManager = AssetManager::class.java.newInstance()
            val addAssetPath = assetManager.javaClass.getMethod("addAssetPath", String::class.java)
            addAssetPath.invoke(assetManager, dexPath)
            mAssetManager = assetManager
            val superRes = super.getResources()
            superRes.displayMetrics
            superRes.configuration
            if (mActivityInfo?.theme != null && mActivityInfo?.theme!! > 0) {
                mProxyActivity.setTheme(mActivityInfo?.theme!!)
            }
            val superTheme = mProxyActivity.theme
            mAssetManager?.let {
                mResources = Resources(mAssetManager, superRes.displayMetrics, superRes.configuration)
                mTheme = mResources?.newTheme()
                mTheme?.setTo(superTheme)
                try {
                    mActivityInfo?.theme?.let {
                        mTheme?.applyStyle(mActivityInfo?.theme!!, true)
                    }
                } catch (e: Exception) {
                    e.printStackTrace()
                }
            }
        } catch (e: Exception) {
            Log.i("inject", "loadResource error:" + Log.getStackTraceString(e))
            e.printStackTrace()
        }
    }

    override fun getAssets(): AssetManager {
        return mAssetManager ?: super.getAssets()
    }

    override fun getResources(): Resources {
        return mResources ?: super.getResources()
    }

    private fun initializeActivityInfo(dexPath: String) {
        val packageInfo = applicationContext.packageManager.getPackageArchiveInfo(dexPath,
                PackageManager.GET_ACTIVITIES or PackageManager.GET_SERVICES)
        if (packageInfo.activities != null && packageInfo.activities.isNotEmpty()) {


            //Finals 修复主题BUG
            val defaultTheme = packageInfo.applicationInfo.theme
            for (a in packageInfo.activities) {
                val mActivityInfo = a
                if (mActivityInfo.theme === 0) {
                    if (defaultTheme != 0) {
                        mActivityInfo.theme = defaultTheme
                    } else {
                        if (Build.VERSION.SDK_INT >= 14) {
                            mActivityInfo.theme = android.R.style.Theme_DeviceDefault
                        } else {
                            mActivityInfo.theme = android.R.style.Theme
                        }
                    }
                    //                    }
                }
                this.mActivityInfo=mActivityInfo
            }

        }
        this.packageInfo=packageInfo
    }

    override fun getTheme(): Resources.Theme {
        return mTheme?:super.getTheme()
    }
}
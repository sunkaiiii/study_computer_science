package com.example.sunkai.activityproxyhost.myapplicaiton

import android.app.Activity
import android.os.Bundle
import dalvik.system.DexClassLoader
import java.io.File
import java.lang.reflect.AccessibleObject.setAccessible



/**
 * Created by sunkai on 2018/1/23.
 */
class ProxyActivity:BaseActivity(){
    companion object {
        private const val dexPath="/data/data/com.example.sunkai.activityproxyhost/cache/app-debug.apk"
        private const val activityName="com.example.sunkai.activityproxy.MainActivity"

    }
    // dex解压之后存放的路径,如果是一个固定的路径运行程序的时候会报错：optimizedDirectory not readable/writable
    private var dexOutPutDir: File? = null
    private var clazz: Class<*>? = null

    private var plugProxyActivity:Any?=null

    override fun onCreate(savedInstanceState: Bundle?) {
        loadResources(dexPath,this)
        super.onCreate(savedInstanceState)
        try{
            val loader=initClassLoader()

            clazz=loader.loadClass(activityName)
            val localConstructor = clazz?.getConstructor(arrayOf<Class<*>>()::class.java)
            plugProxyActivity=localConstructor?.newInstance(arrayOf<Any>())

            val setProxy= clazz?.getMethod("setProxy", arrayOf<Class<*>>(Activity::class.java)::class.java)
            setProxy?.isAccessible=true
            setProxy?.invoke(plugProxyActivity, arrayOf<Any>(this))

            //调用onCreate
            val onCreate=clazz?.getDeclaredMethod("IonCreate", arrayOf<Class<*>>(Bundle::class.java)::class.java)
            onCreate!!.isAccessible=true
            onCreate.invoke(plugProxyActivity, arrayOf<Any>(Bundle())::class.java)
        }catch (e:Exception){}
    }

    private fun initClassLoader(): DexClassLoader {
        dexOutPutDir=applicationContext.getDir("dex",0)
        val filesDir=this.cacheDir.absolutePath
        val libPath=filesDir+File.separator+"app-debug.apk"
        return DexClassLoader(libPath, dexOutPutDir?.absolutePath,null, javaClass.classLoader)
    }

    override fun onDestroy() {
        super.onDestroy()
        try {
            val method = clazz?.getDeclaredMethod("onDestroy")
            method?.isAccessible = true
            method?.invoke(plugProxyActivity, arrayOf<Any>())
        } catch (e: Exception) {
        }

    }

    override fun onPause() {
        super.onPause()
        try {
            val method = clazz?.getDeclaredMethod("IonPause")
            method?.isAccessible = true
            method?.invoke(plugProxyActivity, arrayOf<Any>())
        } catch (e: Exception) {
        }

    }

    override fun onResume() {
        super.onResume()
        try {
            val method = clazz?.getDeclaredMethod("IonResume")
            method?.isAccessible = true
            method?.invoke(plugProxyActivity, arrayOf<Any>())
        } catch (e: Exception) {
        }

    }

    override fun onStart() {
        super.onStart()
        try {
            val method = clazz?.getDeclaredMethod("IonStart")
            method?.isAccessible = true
            method?.invoke(plugProxyActivity, arrayOf<Any>())
        } catch (e: Exception) {
        }

    }

    override fun onStop() {
        super.onStop()
        try {
            val method = clazz?.getDeclaredMethod("IonStop")
            method?.isAccessible = true
            method?.invoke(plugProxyActivity, arrayOf<Any>())
        } catch (e: Exception) {
        }

    }

}
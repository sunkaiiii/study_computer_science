package com.example.sunkai.activityproxyhost.myapplicaiton

import android.os.Bundle
import com.example.sunkai.activityproxyhost.proxy.PluginInterface
import dalvik.system.DexClassLoader
import java.io.File



/**
 * Created by sunkai on 2018/1/23.
 */
class PlugProxyActivity:BaseActivity(){
    companion object {
        private const val dexPath="/data/data/com.example.sunkai.activityproxyhost/cache/app-debug.apk"
        private const val activityName="com.example.sunkai.activityproxy.MainActivity"
    }
    private var dexOutPutDir: File?=null
    private var clazz:Class<*>?=null

    private var mPluginInterface: PluginInterface?=null

    override fun onCreate(savedInstanceState: Bundle?) {
        loadResources(dexPath,this)
        super.onCreate(savedInstanceState)
        try{
            val loader=initClassLoader()
            //动态加载插件Activity
            clazz=loader.loadClass(activityName)
            val localConstructor = clazz?.getConstructor(arrayOf<Class<*>>()::class.java)
            //拿到activity，强转成他实现的接口
            mPluginInterface = localConstructor?.newInstance(arrayOf<Any>()) as PluginInterface
            mPluginInterface!!.setProxy(this)
            val bundle=Bundle()
            mPluginInterface!!.IonCreate(bundle)
        }catch (e:Exception){

        }
    }

    private fun initClassLoader():DexClassLoader{
        dexOutPutDir=applicationContext.getDir("dex",0)
        val filesDir=this.cacheDir.absolutePath
        val libPath=filesDir+File.separator+"app-debug.apk"
        return DexClassLoader(libPath, dexOutPutDir?.absolutePath,null, javaClass.classLoader)
    }

    override fun onDestroy() {
        mPluginInterface?.IonDestroy()
        super.onDestroy()
    }

    override fun onPause() {
        mPluginInterface?.IonPause()
        super.onPause()
    }

    override fun onResume() {
        mPluginInterface?.IonResume()
        super.onResume()
    }

    override fun onStart() {
        mPluginInterface?.IonStart()
        super.onStart()
    }

    override fun onStop() {
        mPluginInterface?.IonStop()
        super.onStop()
    }
}
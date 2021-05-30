package com.example.sunkai.activityproxy

import android.app.Activity
import android.os.Bundle
import android.widget.TextView
import android.widget.Toast

/*
 * Created by sunkai on 2018/1/23.
 */
open class BaseActivity: PluginInterface,Activity() {

    var mProxyActivity:Activity?=null
    override fun IonCreate(saveInstance: Bundle?) {
        TODO("not implemented") //To change body of created functions use File | Settings | File Templates.
    }

    override fun setContentView(layoutResID: Int) {
        val activity=mProxyActivity
            activity!!.setContentView(layoutResID)
            val tv=activity.findViewById(R.id.textview)
        Toast.makeText(activity, "this is proxy activity", Toast.LENGTH_SHORT).show()
            tv.setOnClickListener {
                Toast.makeText(activity, "this is proxy activity", Toast.LENGTH_SHORT).show()
            }
    }

    override fun IonStart() {}

    override fun IonResume() {}

    override fun IonPause() {}

    override fun IonStop() {}

    override fun IonDestroy() {}

    override fun setProxy(proxyActivity: Activity) {
        mProxyActivity=proxyActivity
    }

}
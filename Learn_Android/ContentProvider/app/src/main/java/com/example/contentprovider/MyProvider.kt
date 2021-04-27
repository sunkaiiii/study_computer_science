package com.example.contentprovider

import android.content.ContentProvider
import android.content.ContentValues
import android.content.UriMatcher
import android.database.Cursor
import android.net.Uri

class MyProvider:ContentProvider() {
    private val tableDir = 0
    private val tableItem = 1
    private val table2Dir = 2
    private val table2Item = 3
    private val uriMaticher by later {
        val mathcher = UriMatcher(UriMatcher.NO_MATCH)
        mathcher.addURI("com.example.contentprovider","table1",tableDir)
        mathcher.addURI("com.example.contentprovider","table1/#",tableItem)
        mathcher.addURI("com.example.contentprovider","table2",table2Dir)
        mathcher.addURI("com.example.contentprovider","table2/#",table2Item)
        mathcher
    }

    override fun onCreate(): Boolean {
        TODO("Not yet implemented")
    }

    override fun query(
        uri: Uri,
        projection: Array<out String>?,
        selection: String?,
        selectionArgs: Array<out String>?,
        setOrder: String?
    ): Cursor? {
        when(uriMaticher.match(uri)){
            tableDir->{

            }
            tableItem->{

            }
            table2Dir->{

            }
            table2Item->{

            }
        }
        return null
    }

    override fun getType(uri: Uri): String? {
        return when(uriMaticher.match(uri)){
            tableDir->"vnd.android.cursor.dir/vnd.com.example.contentprovider.table1"
            tableItem->"vnd.android.cursor.item/vnd.com.example.contentprovider.table1"
            table2Dir->"vnd.android.cursor.dir/vnd.com.example.contentprovider.table2"
            table2Item->"vnd.android.cursor.item/vnd.com.example.contentprovider.table2"
            else->null
        }
    }

    override fun insert(p0: Uri, p1: ContentValues?): Uri? {
        TODO("Not yet implemented")
    }

    override fun delete(p0: Uri, p1: String?, p2: Array<out String>?): Int {
        TODO("Not yet implemented")
    }

    override fun update(p0: Uri, p1: ContentValues?, p2: String?, p3: Array<out String>?): Int {
        TODO("Not yet implemented")
    }
}
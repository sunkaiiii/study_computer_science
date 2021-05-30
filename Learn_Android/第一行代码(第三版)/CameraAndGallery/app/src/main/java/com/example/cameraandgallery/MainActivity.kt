package com.example.cameraandgallery

import android.app.Activity
import android.content.Intent
import android.graphics.Bitmap
import android.graphics.BitmapFactory
import android.graphics.Matrix
import android.media.ExifInterface
import android.net.Uri
import android.os.Build
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.provider.MediaStore
import android.widget.Button
import android.widget.ImageView
import androidx.core.content.FileProvider
import java.io.File

class MainActivity : AppCompatActivity() {
    val takePhoto = 1
    val fromAlbum = 2
    lateinit var imageUri:Uri
    lateinit var outputImage:File
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        findViewById<Button>(R.id.takePhotoBtn).setOnClickListener {
            outputImage = File(externalCacheDir,"output_image.jpg")
            if(outputImage.exists()){
                outputImage.delete()
            }
            outputImage.createNewFile()
            imageUri = if(Build.VERSION.SDK_INT>=Build.VERSION_CODES.N){
                FileProvider.getUriForFile(this,"com.example.cameraandgallery.fileprovider",outputImage)
            }else{
                Uri.fromFile(outputImage)
            }

            //启动相机程序
            val intent = Intent("android.media.action.IMAGE_CAPTURE")
            intent.putExtra(MediaStore.EXTRA_OUTPUT,imageUri)
            startActivityForResult(intent,takePhoto)
        }
        findViewById<Button>(R.id.fromAlbumBtn).setOnClickListener {
            val intent = Intent(Intent.ACTION_OPEN_DOCUMENT)
            intent.addCategory(Intent.CATEGORY_OPENABLE)
            intent.type="image/*"
            startActivityForResult(intent,fromAlbum)
        }
    }

    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?) {
        super.onActivityResult(requestCode, resultCode, data)
        when(requestCode){
            takePhoto->{
                if(resultCode==Activity.RESULT_OK){
                    val bitmap = BitmapFactory.decodeStream(contentResolver.openInputStream(imageUri))
                    findViewById<ImageView>(R.id.imageView).setImageBitmap(rotateIfRequired(bitmap))
                }
            }
            fromAlbum->{
                if(resultCode==Activity.RESULT_OK && data!=null){
                    data.data?.let {
                        val bitmap = getBitmapFromUri(it)
                        findViewById<ImageView>(R.id.imageView).setImageBitmap(bitmap)
                    }
                }
            }
        }
    }

    private fun getBitmapFromUri(uri: Uri) = contentResolver
        .openFileDescriptor(uri, "r")?.use {
            BitmapFactory.decodeFileDescriptor(it.fileDescriptor)
        }

    private fun rotateIfRequired(bitmap: Bitmap): Bitmap {
        val exif = ExifInterface(outputImage.path)
        val orientation = exif.getAttributeInt(ExifInterface.TAG_ORIENTATION,ExifInterface.ORIENTATION_NORMAL)
        return when(orientation){
            ExifInterface.ORIENTATION_ROTATE_90->rotateBitmap(bitmap, 90)
            ExifInterface.ORIENTATION_ROTATE_180->rotateBitmap(bitmap,180)
            ExifInterface.ORIENTATION_ROTATE_270->rotateBitmap(bitmap,270)
            else->bitmap
        }
    }

    private fun rotateBitmap(bitmap: Bitmap, i: Int): Bitmap {
        val matrix = Matrix()
        matrix.postRotate(i.toFloat())
        val rotatedBitmap = Bitmap.createBitmap(bitmap,0,0,bitmap.width,bitmap.height,matrix,true)
        bitmap.recycle()
        return rotatedBitmap
    }
}
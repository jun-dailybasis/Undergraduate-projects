package com.example.jun0_pc.project1_160913;

import android.content.Intent;
import android.content.res.Configuration;
import android.graphics.Bitmap;
import android.graphics.drawable.BitmapDrawable;
import android.graphics.drawable.Drawable;
import android.graphics.drawable.LayerDrawable;
import android.net.Uri;
import android.os.Environment;
import android.provider.MediaStore;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Gallery;
import android.widget.ImageView;
import android.widget.RadioButton;
import android.widget.TextView;

import java.io.File;

import static android.R.attr.bitmap;
import static android.R.attr.textEditNoPasteWindowLayout;

public class MainActivity extends AppCompatActivity {
    private int TAKE_CAMERA = 2;
    private int cnt = 0;
    private String name;
    private String id;
    private String android;
    private int img;
    private Bundle Image;
    static Bitmap bitmap = null;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

    }
    @Override
    protected void onSaveInstanceState(Bundle outState) {
        super.onSaveInstanceState(outState);
        // gallery.getSelectedItemPosition()
        TextView name_view = (TextView) findViewById(R.id.textNAME);
        TextView id_view = (TextView) findViewById(R.id.textid);
        TextView android_view = (TextView) findViewById(R.id.textAndroid);
        ImageView imageview = (ImageView) findViewById(R.id.imageView);
        name = name_view.getText().toString();
        id = id_view.getText().toString();
        android = android_view.getText().toString();
        outState.putString("data_name", name);
        outState.putString("data_id", id);
        outState.putString("data_android", android);
        //if(imageview!=null){
        //    imageview.setImageBitmap(findViewById(R.drawable.profile));
        //}
        //BitmapDrawable drawable = (BitmapDrawable) imageview.getDrawable();
        //Bitmap bitmap = drawable.getBitmap();
        //        //Bitmap bitmap =  Bitmap.createBitmap(drawable.getBitmap());
        //bitmap = ((BitmapDrawable)imageview.getDrawable()).getBitmap();

        outState.putParcelable("data_picture", bitmap);

        super.onSaveInstanceState(outState);
    }

    @Override
    protected void onRestoreInstanceState(Bundle savedInstanceState){
        super.onRestoreInstanceState(savedInstanceState);
        TextView name_view = (TextView) findViewById(R.id.textNAME);
        TextView id_view = (TextView) findViewById(R.id.textid);
        TextView android_view = (TextView) findViewById(R.id.textAndroid);
        ImageView imageview = (ImageView) findViewById(R.id.imageView);
        name = savedInstanceState.getString("data_name");
        id = savedInstanceState.getString("data_id");
        android = savedInstanceState.getString("data_android");
        name_view.setText(name);
        id_view.setText(id);
        android_view.setText(android);
        if(savedInstanceState != null) {
            Bitmap bitmap = savedInstanceState.getParcelable("data_picture");
            imageview.setImageBitmap(bitmap);
        }

    }

    public void onConfigurationChanged(Configuration newConfig) {
        super.onConfigurationChanged(newConfig);

    }




    //EDIT Button click.
    public void onclickEdit(View v) {
        Intent intent = new Intent(this, Activity2.class);
        startActivityForResult(intent, 1);
    }

    public void onClickPic(View v) {
        Intent intent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
        //   // 인텐트 정보에 맞는 액티비티를 실행한다.
        startActivityForResult(intent, TAKE_CAMERA);

    }

    @Override
    public void onActivityResult(int request_code, int result_code, Intent data) {
        TextView name_view = (TextView) findViewById(R.id.textNAME);
        TextView id_view = (TextView) findViewById(R.id.textid);
        TextView android_view = (TextView) findViewById(R.id.textAndroid);
        ImageView imageview = (ImageView) findViewById(R.id.imageView);
        // RadioButton YES = (RadioButton) findViewById(R.id.radioYES);
        // RadioButton NO = (RadioButton) findViewById(R.id.radioNO);
        //TextView digit_view = (TextView)findViewById(R.id.textid);
        // 결과 값이 있고, 액티비티를 시작할 때 0로 설정해둔 결과값인 경우
        if (request_code == 1 && result_code == RESULT_OK) {
            // intent 의 여분 데이터로 저장된 비트맵 이미지를 얻는다.
            name_view.setText(data.getStringExtra("data_name"));
            id_view.setText(data.getStringExtra("data_id"));
            android_view.setText(data.getStringExtra("data_android"));
        } else if (result_code == RESULT_OK && request_code == TAKE_CAMERA) {
            if (data != null) {
                Image = data.getExtras();
                Bitmap ImageBitmap = (Bitmap) Image.get("data");
               // Bitmap tmp = findViewById(R.drawable.profile);
               // ImageBitmap.setWidth(200);
               // ImageBitmap.setHeight(200);
                //imageview.setScaleType(ImageView.ScaleType.MATRIX);
                bitmap = ImageBitmap;
                imageview.setImageBitmap(ImageBitmap);
                //Log.e("Test", "result = " + data);

               // Uri thumbnail = data.getData();

               // if (thumbnail != null) {
               //     ImageView Imageview = (ImageView) findViewById(R.id.imageView);
               //     Imageview.setImageURI(thumbnail);
               // }
            }
        }
    }


}
package com.example.jun0_pc.project1_160913;

import android.content.Intent;
import android.content.res.Configuration;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.webkit.WebView;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.Toast;

public class Activity2 extends AppCompatActivity {
    EditText name_input;
    EditText id_input;
    String android_input;
    RadioButton YES;
    RadioButton NO;
    Button btnSave;
    private int cnt = 0;
    private static final int REQUEST_CODE = 100;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_2);
        //if(getResources().getConfiguration().orientation==Configuration.ORIENTATION_PORTRAIT){
        //    setContentView(R.layout.activity_2);
        //}
        //else if(getResources().getConfiguration().orientation==Configuration.ORIENTATION_LANDSCAPE){
        //    setContentView(R.layout.activity_2_land);
        //}
       if(savedInstanceState != null)
       {
           cnt = savedInstanceState.getInt("num");
       }
        initInstance();
    }
    public void onConfigurationChanged(Configuration newConfig) {
        super.onConfigurationChanged(newConfig);

    }
    public void initInstance() {
        btnSave = (Button) findViewById(R.id.btnSave);
        name_input = (EditText) findViewById(R.id.editNAME);
        id_input = (EditText) findViewById(R.id.editID);
        //YES = (RadioButton) findViewById(R.id.radioYES);
        //NO = (RadioButton) findViewById(R.id.radioNO);
        final RadioGroup rg = (RadioGroup) findViewById(R.id.radioGroup);
        rg.setOnCheckedChangeListener(new RadioGroup.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(RadioGroup group, int checkedId) {
                RadioButton radio_btn = (RadioButton) findViewById(checkedId);
                Toast.makeText(Activity2.this, radio_btn.getText() + "check", Toast.LENGTH_LONG).show();
               // switch (checkedId) {
               //     case R.id.radioYES:
               //         break;
               //     case R.id.radioNO:
               //         break;
               // }
                final RadioButton selectedRdo = (RadioButton)findViewById(rg.getCheckedRadioButtonId());
                android_input = selectedRdo.getText().toString();
            }
        });

        btnSave.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
               Intent intent = getIntent();
                intent.putExtra("data_name",name_input.getText().toString());
                intent.putExtra("data_id",id_input.getText().toString());
                intent.putExtra("data_android", android_input);
                setResult(RESULT_OK,intent);

                finish();
                //intent.getExtras().getString("name", "name");
                //startActivityForResult(intent, REQUEST_CODE);
            }
        });

    }


    public void onClickCancel(View v){
        finish();

    }

}

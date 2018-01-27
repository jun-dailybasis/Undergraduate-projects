package com.example.junyoung.a2017msp_termproject;

import android.app.Service;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.location.LocationManager;
import android.widget.Toast;

public class AlertReceiver extends BroadcastReceiver {
    public String name = "none";
    public String loc = "none";

    public long startTime_playground = 0;
    public long curTime_playground = 0;

    public long startTime_grass = 0;
    public long curTime_grass= 0;

    public long startTime_eng = 0;
    public long curTime_eng = 0;

    public long startTime_dasan = 0;
    public long curTime_dasan = 0;

    @Override
    public void onReceive(Context context, Intent intent) {
        boolean isEntering = intent.getBooleanExtra(LocationManager.KEY_PROXIMITY_ENTERING, false);
        // getBooleanExtra(String name, boolean defaultValue)

        if(isEntering) {
            if(intent.getAction().equals("com.example.junyoung.locationAlert1")) {
                Toast.makeText(context, "운동장", Toast.LENGTH_LONG).show();
                name = "운동장";
            }
            if(intent.getAction().equals("com.example.junyoung.locationAlert2")) {
                Toast.makeText(context, "잔디밭 벤치", Toast.LENGTH_LONG).show();
                name = "잔디밭";
            }
            if(intent.getAction().equals("com.example.junyoung.locationAlert3")) {
                Toast.makeText(context, "4공학관 건물", Toast.LENGTH_LONG).show();
                name = "4공학관";
            }
            if(intent.getAction().equals("com.example.junyoung.locationAlert4")) {
                Toast.makeText(context, "다산정보관", Toast.LENGTH_LONG).show();
                name = "다산정보관";
            }
        }
        else{
            Toast.makeText(context, "목표 지점에서 벗어납니다..", Toast.LENGTH_LONG).show();
            reset_all();
            name = "none";
            loc = "none";
        }
    }



    public void reset_all(){
        startTime_playground = 0;
        curTime_playground = 0;
        startTime_grass = 0;
        curTime_grass= 0;
        startTime_eng = 0;
        curTime_eng = 0;
        startTime_dasan = 0;
        curTime_dasan = 0;
    }

    public void reset_platground(){
        startTime_grass = 0;
        curTime_grass= 0;
        startTime_eng = 0;
        curTime_eng = 0;
        startTime_dasan = 0;
        curTime_dasan = 0;
    }

    public void reset_grass(){
        startTime_playground = 0;
        curTime_playground = 0;
        startTime_eng = 0;
        curTime_eng = 0;
        startTime_dasan = 0;
        curTime_dasan = 0;
    }

    public void reset_eng(){
        startTime_playground = 0;
        curTime_playground = 0;
        startTime_grass = 0;
        curTime_grass= 0;
        startTime_dasan = 0;
        curTime_dasan = 0;
    }

    public void reset_dasan(){
        startTime_playground = 0;
        curTime_playground = 0;
        startTime_grass = 0;
        curTime_grass= 0;
        startTime_eng = 0;
        curTime_eng = 0;
    }
}


package com.pierre.biojoux.project;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

import java.util.ArrayList;

import GarbageBin.GarbageBin;

public class MainActivity extends AppCompatActivity {

    private Button buttonCheckStatus;
    private Button buttonViewMap;
    private Button buttonCheckWeather;
    private Button buttonLogOut;
    private ArrayList<GarbageBin> binList = null;

    IntentFilter filter;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        binList = testData();
        Intent weatherIntent = new Intent(this, BinService.class);
        startService(weatherIntent);
        filter = new IntentFilter();
        filter.addAction("com.pierre.biojoux.project.BROADCAST_BACKGROUND_SERVICE_RESULT");
        registerReceiver(receiver, filter);
        buttonCheckStatus = (Button) findViewById(R.id.buttonCheckStatus);
        buttonCheckStatus.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                checkStatus();
            }
        });

        buttonViewMap = (Button) findViewById(R.id.buttonViewMap);
        buttonViewMap.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                viewMap();
            }
        });

        buttonCheckWeather = (Button) findViewById(R.id.buttonCheckWeather);
        buttonCheckWeather.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                checkWeather();
            }
        });

        buttonLogOut = (Button) findViewById(R.id.buttonLogOut);
        buttonLogOut.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                logOut();
            }
        });

    }

    private void checkStatus() {
        Intent intent = new Intent(this, StatusActivity.class);
        intent.putExtra("binList", binList);
        startActivity(intent);
    }

    private void viewMap() {
        Intent intent = new Intent(this, MapsActivity.class);
        intent.putExtra("binList", binList);
        intent.putExtra("doIt", "ManyGarbageBins");
        startActivity(intent);
    }

    private void checkWeather() {
        Intent intent = new Intent(this, WeatherActivity.class);
        startActivity(intent);
    }


    private void logOut() {
        finish();
    }

    private ArrayList<GarbageBin> testData() {
        GarbageBin B1 = new GarbageBin(1, 37.414, -122.1, "Full");
        GarbageBin B2 = new GarbageBin(2, 37.434, -121.1, "Empty");
        GarbageBin B3 = new GarbageBin(3, 37.424, -122.1, "Medium");
        GarbageBin B4 = new GarbageBin(4, 37.424, -120.1, "Full");
        GarbageBin B5 = new GarbageBin(5, 37.420, -121.1, "Empty");
        GarbageBin B6 = new GarbageBin(6, 37.414, -120.1, "Medium");
        GarbageBin B7 = new GarbageBin(7, 37.414, -120.1, "Full");
        GarbageBin B8 = new GarbageBin(8, 37.404, -121.1, "Empty");
        GarbageBin B9 = new GarbageBin(9, 37.424, -122.1, "Medium");

        ArrayList<GarbageBin> binList = new ArrayList<GarbageBin>();
        binList.add(B1);
        binList.add(B2);
        binList.add(B3);
        binList.add(B4);
        binList.add(B5);
        binList.add(B6);
        binList.add(B7);
        binList.add(B8);
        binList.add(B9);
        return binList;
    }
    private final BroadcastReceiver receiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            String action = intent.getAction();
            if(action.equals("com.pierre.biojoux.project.BROADCAST_BACKGROUND_SERVICE_RESULT")) {
                Toast.makeText(MainActivity.this, "Broadcast received", Toast.LENGTH_LONG).show();
            }
        }
    };
}

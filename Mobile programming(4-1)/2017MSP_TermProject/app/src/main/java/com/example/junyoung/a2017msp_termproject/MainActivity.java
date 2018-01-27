package com.example.junyoung.a2017msp_termproject;

import android.Manifest;
import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.pm.PackageManager;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Locale;

public class MainActivity extends AppCompatActivity {

    private TextView stepsText;
    private TextView longilati;

    //private static final String BROADCAST_ACTION_ACTIVITY = "kr.ac.koreatech.msp.hslocationtracking";

    static private int steps;
    private int gpsStatusLevel;

    private double lon = 0.0;
    private double lat = 0.0;

    long startTime = 0;
    long curTime = 0;

    private String provider = "";
    private String location_inout = "";
    private String location_user = "";
    private String nowtime = "";

    private String listItem_startTime = "";
    private String listItem_endTime = "";
    private String listItem_duringTime = "";
    private String listItem_where = "";
    private String listItem_moveState = "none";
    private String listItem_step = "";

    private String preWhere = "none";
    private String preMove = "none";
    private int presteps = 0;

    private TextView movingText;
    private TextView locationText;


    static private ListViewAdapter adapter1 = new ListViewAdapter();

    private BroadcastReceiver MyMovingReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            if(intent.getAction().equals("com.example.junyoung.MyMovingReceiver")) {
                boolean moving = intent.getBooleanExtra("moving", false);
                if(moving) {
                    movingText.setText("Moving");
                    listItem_moveState = "Moving";
                    Intent intent3 = new Intent(context, StepMonitor.class);
                    startService(intent3);
                } else {
                    movingText.setText("NOT Moving");
                    listItem_moveState = "Stop";
                    stopService(new Intent(context, StepMonitor.class));
                }
                lon = intent.getDoubleExtra("longitude", 0.0);
                lat = intent.getDoubleExtra("latitude", 0.0);
                gpsStatusLevel = intent.getIntExtra("gpsStatusLevel", 0);
                location_inout = intent.getStringExtra("location");
                location_user = intent.getStringExtra("location_user");
                provider = intent.getStringExtra("inout");
                nowtime = intent.getStringExtra("nowtime");
                String strNumber1 = String.format("%.6f", lat);
                String strNumber2 = String.format("%.6f", lon);


                //장소를 정하기 위함
                //이미 n초동안 해당 장소에 있었거나, 멈추거나 이동 했기 때문에 바로 리스트에 추가해도 된다.
                if(location_inout.equals("실내")||location_inout.equals("실외")){
                    if(location_user.equals("운동장")||location_user.equals("잔디밭")||
                            location_user.equals("4공학관")||location_user.equals("다산정보관")){
                        listItem_where = location_user;
                    }
                    else if(!location_user.equals(""))
                        listItem_where = location_inout;
                }
                else listItem_where = "none";

                longilati.setText(provider+"\nlongitude " + strNumber1 + "\nlatitude " + strNumber2+"\n"+preMove+"\n"+listItem_moveState+"\n"+preWhere+"\n"+listItem_where+"\n"+nowtime+"\ngpsStatusLevel : "+gpsStatusLevel);



                if(!listItem_where.equals("none") && !listItem_moveState.equals("none")){
                    //이전의 상태에서 위치 또는 움직임에 변화가 있을때
                    if(!listItem_where.equals(preWhere) || !listItem_moveState.equals(preMove)) {
                        adapter1.notifyDataSetChanged();
                        //걸린 시간을 구하기 위함
                        curTime = System.currentTimeMillis();

                        //끝난 시간을 구하기 위함
                        listItem_endTime = getCurrentTime();

                        //걸린 시간을 분 단위로 만듬
                        int min = (int)(curTime - startTime)/1000;
                        listItem_duringTime = min/60%60+"분";

                        int unitSteps = steps - presteps;
                        listItem_step = unitSteps+"걸음";

                        //리스트 추가
                        adapter1.addItem(listItem_startTime, listItem_endTime, listItem_duringTime, listItem_moveState, listItem_where, listItem_step);

                        //다음 리스트 추가를 위한 시간 등록과 시스템 시간 저장
                        listItem_startTime = getCurrentTime();
                        startTime = System.currentTimeMillis();

                        presteps = steps;

                        //라음 리스트 추가의 여부를 판별할 위치와 움직임 정보 저장
                        preWhere = listItem_where;
                        preMove = listItem_moveState;
                    }
                }
            }
        }
    };

    public String getCurrentTime() {
        SimpleDateFormat formatter = new SimpleDateFormat("HH:mm", Locale.KOREA);
        Date currentTime = new Date();
        String dTime = formatter.format(currentTime);
        return dTime;
    }

    private BroadcastReceiver MyStepReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            if(intent.getAction().equals("com.example.junyoung.a2017msp_termproject")) {
                steps += intent.getIntExtra("steps", 0);
                stepsText.setText("Step_Count: " + steps);
            }
        }
    };

    private BroadcastReceiver MyLCReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            if(intent.getAction().equals("com.example.junyoung.b2017msp_termproject")) {
                lon = intent.getDoubleExtra("longitude", 0);
                lat = intent.getDoubleExtra("latitude", 0);
                //longilati.setText("latitude: "+ lat +", longitude: "+ lon);
            }
        }
    };
    static int totalTime = 0; //상단에 위치한.. 움직인 종합 시간
    static int totalStep = 0; // 상담에 위치한.. 걸음걸이 종합 시간

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        ListView TrackInformationList;

        //상단 텍스트 중 총 움직인 시간
        TextView totalTimeView = (TextView) findViewById(R.id.movingTime);

        longilati = (TextView) findViewById(R.id.loglat);
        stepsText = (TextView) findViewById(R.id.stepCount);
        movingText = (TextView) findViewById(R.id.ismoving);


        TrackInformationList = (ListView) findViewById(R.id.listview);

        TrackInformationList.setAdapter(adapter1);

        //스탭 측정 서비스와 연결을 위한 인텐트
        IntentFilter intentFilter1 = new IntentFilter("com.example.junyoung.a2017msp_termproject");
        registerReceiver(MyStepReceiver, intentFilter1);

        //위치 측정 서비스와 연결을 위한 인텐트
        IntentFilter intentFilter2 = new IntentFilter("com.example.junyoung.b2017msp_termproject");
        registerReceiver(MyLCReceiver, intentFilter2);

        IntentFilter intentFilter3 = new IntentFilter("com.example.junyoung.MyMovingReceiver");
        registerReceiver(MyMovingReceiver, intentFilter3);

        //adapter1.addItem("12:30", "13:00", "30분", "이동","다산", "30걸음");
        //adapter1.addItem("13:00", "14:00", "60분", "정지","다산", "0걸음");
    }

    @Override
    protected void onPause() {
        super.onPause();

        unregisterReceiver(MyStepReceiver);
        unregisterReceiver(MyLCReceiver);
    }




    // Start/Stop 버튼을 눌렀을 때 호출되는 콜백 메소드
    // monitoring을 수행하는 service 시작/종료
    public void onClick(View v) {
        if(v.getId() == R.id.start) {
            /*
            Intent intent1 = new Intent(this, StepMonitor.class);
            startService(intent1);
            Intent intent2 = new Intent(this, LCMonitor.class);
            startService(intent2);*/

            listItem_startTime = getCurrentTime();
            startTime = System.currentTimeMillis();

            Intent intent1 = new Intent(this, HSMonitorService.class);
            startService(intent1);

            Toast.makeText(getApplicationContext(), "[스탭카운트]", Toast.LENGTH_SHORT).show();

        } else if(v.getId() == R.id.stop) {
            /*
            stopService(new Intent(this, StepMonitor.class));
            stopService(new Intent(this, LCMonitor.class));
            */
            stopService(new Intent(this, HSMonitorService.class));
            stepsText.setText("Step_Count: " + 0);
            longilati.setText("latitude: "+ 0 +", longitude: "+ 0);
            Toast.makeText(getApplicationContext(), "스탭카운트 종료.", Toast.LENGTH_SHORT).show();
        }
    }
    @Override
    protected void onResume() {
        super.onResume();

        adapter1.notifyDataSetChanged();

        IntentFilter intentFilter1 = new IntentFilter("com.example.junyoung.a2017msp_termproject");
        registerReceiver(MyStepReceiver, intentFilter1);
/*
        IntentFilter intentFilter2 = new IntentFilter("com.example.junyoung.b2017msp_termproject");
        registerReceiver(MyLCReceiver, intentFilter2);
*/
        IntentFilter intentFilter3 = new IntentFilter("com.example.junyoung.MyMovingReceiver");
        registerReceiver(MyLCReceiver, intentFilter3);

    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        unregisterReceiver(MyStepReceiver);
        unregisterReceiver(MyLCReceiver);
    }
}

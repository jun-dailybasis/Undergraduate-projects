package com.example.junyoung.a2017msp_termproject;


import android.app.AlarmManager;
import android.app.PendingIntent;
import android.app.Service;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;

import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;

import android.os.Bundle;
import android.os.CountDownTimer;
import android.os.IBinder;

import android.os.PowerManager;
import android.os.SystemClock;

import android.util.Log;
import android.widget.Toast;

import java.text.SimpleDateFormat;

import java.util.Date;
import java.util.Locale;

import java.util.Timer;
import java.util.TimerTask;

public class HSMonitorService extends Service {
    private static final String LOGTAG = "HS_Location_Tracking";
    private static final String BROADCAST_ACTION_ACTIVITY = "com.example.junyoung.MyMovingReceiver";
    AlarmManager am;
    PendingIntent pendingIntent;

    private PowerManager.WakeLock wakeLock;
    private CountDownTimer timer;

    //실내인지 실외인지 확인에 쓰기는 타임을 구하기 위함
    long startTime_n = 0;
    long curTime_n = 0;

    long startTime_g = 0;
    long curTime_g = 0;

    private MovingMonitor accelMonitor;
    private long period = 10000;
    private static final long activeTime = 1000;
    private static final long periodForMoving = 5000;
    private static final long periodIncrement = 5000;
    private static final long periodMax = 30000;

    private LocationManager mLocationManager = null;
    private final int MIN_TIME_UPDATES = 5000; // milliseconds
    private final int MIN_DISTANCE_CHANGE_FOR_UPDATES = 5; // meters
    private boolean isRequestRegistered = false;

    String provider;

    //위치 등록을 위함
    PendingIntent proximityIntent1;//운동장
    PendingIntent proximityIntent2;//잔디밭 벤치
    PendingIntent proximityIntent3;//4공 B211
    PendingIntent proximityIntent4;//다산정보관

    AlertReceiver receiver;

    boolean isLocRequested = false;

    private String location_inout;
    private String nowtime;
    private int gpsStatusLevel = 0;
    private double lon = 0.0;
    private double lat = 0.0;

    // Alarm 시간이 되었을 때 안드로이드 시스템이 전송해주는 broadcast를 받을 receiver 정의
    // 움직임 여부에 따라 다음 alarm이 발생하도록 설정한다.
    private BroadcastReceiver AlarmReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            if(intent.getAction().equals("kr.ac.koreatech.msp.hsalarm")) {
                Log.d(LOGTAG, "Alarm fired!!!!");
                //-----------------
                // Alarm receiver에서는 장시간에 걸친 연산을 수행하지 않도록 한다
                // Alarm을 발생할 때 안드로이드 시스템에서 wakelock을 잡기 때문에 CPU를 사용할 수 있지만
                // 그 시간은 제한적이기 때문에 애플리케이션에서 필요하면 wakelock을 잡아서 연산을 수행해야 함
                //-----------------

                PowerManager pm = (PowerManager) context.getSystemService(Context.POWER_SERVICE);
                wakeLock = pm.newWakeLock(PowerManager.PARTIAL_WAKE_LOCK, "HS_Wakelock");
                // ACQUIRE a wakelock here to collect and process accelerometer data and control location updates
                wakeLock.acquire();

                accelMonitor = new MovingMonitor(context);
                accelMonitor.onStart();

                whereareyou(receiver.name);
                inandout(provider);
                nowtime = getCurrentTime();

                timer = new CountDownTimer(activeTime, 1000) {
                    @Override
                    public void onTick(long millisUntilFinished) {
                    }

                    @Override
                    public void onFinish() {
                        Log.d(LOGTAG, "1-second accel data collected!!");
                        // stop the accel data update
                        accelMonitor.onStop();

                        boolean moving = accelMonitor.isMoving();
                        // 움직임 여부에 따라 GPS location update 요청 처리
                        if(moving) {
                            Log.d(LOGTAG, "before calling requestLocation");
                            if(!isRequestRegistered) {
                                requestLocation();
                                in_EB4();
                                Log.d(LOGTAG, "after calling requestLocation");
                            }
                        } else {
                            Log.d(LOGTAG, "before calling cancelLocationRequest");
                            if(isRequestRegistered) {
                                cancelLocationRequest();
                                Log.d(LOGTAG, "after calling cancelLocationRequest");
                            }
                        }
                        // 움직임 여부에 따라 다음 alarm 설정
                        setNextAlarm(moving);

                        // 화면에 위치 데이터를 표시할 수 있도록 브로드캐스트 전송
                        sendDataToActivity(moving);

                        // When you finish your job, RELEASE the wakelock
                        wakeLock.release();
                        wakeLock = null;
                    }
                };
                timer.start();
            }
        }
    };

    private void requestLocation() {


        try {
            if(mLocationManager == null) {
                Log.d(LOGTAG, "mLocMan obtained");
                mLocationManager = (LocationManager)getSystemService(Context.LOCATION_SERVICE);
            }
            if(!isRequestRegistered) {
                // min time과 min distance를 0으로 설정했을 때와 아닌 경우 비교

                /*
                mLocationManager.requestLocationUpdates(LocationManager.GPS_PROVIDER,
                        MIN_TIME_UPDATES,
                        MIN_DISTANCE_CHANGE_FOR_UPDATES,
                        locationListener);
                */
                /*
                mLocationManager.requestLocationUpdates(LocationManager.GPS_PROVIDER,
                        0,
                        0,
                        locationListener);
                */
                mLocationManager.requestLocationUpdates(LocationManager.GPS_PROVIDER,
                        100,
                        0,
                        locationListener);
                mLocationManager.requestLocationUpdates(LocationManager.NETWORK_PROVIDER, // 등록할 위치제공자
                        100, // 통지사이의 최소 시간간격 (miliSecond)
                        1, // 통지사이의 최소 변경거리 (m)
                        locationListener);
                isRequestRegistered = true;
            }
        } catch (SecurityException se) {
            se.printStackTrace();
            Log.e(LOGTAG, "PERMISSION_NOT_GRANTED");
        }
    }

    private void cancelLocationRequest() {
        Log.d(LOGTAG, "Cancel the location update request");
        if(mLocationManager != null) {
            try {
                mLocationManager.removeUpdates(locationListener);

                mLocationManager.removeProximityAlert(proximityIntent1);
                mLocationManager.removeProximityAlert(proximityIntent2);
                mLocationManager.removeProximityAlert(proximityIntent3);
                mLocationManager.removeProximityAlert(proximityIntent4);

            } catch(SecurityException se) {
                se.printStackTrace();
                Log.e(LOGTAG, "PERMISSION_NOT_GRANTED");
            }
        }
        mLocationManager = null;
        isRequestRegistered = false;
    }

    //실내, 실외인지 판단하는 함수
    public void inandout(String str){
        //실내인지 실외인지 파악
        if(str.equals("network") || gpsStatusLevel < 2){
            startTime_g = curTime_g = 0;//gps타이머 초기화
            if(startTime_n == 0)
                startTime_n = System.currentTimeMillis();
            else{
                curTime_n = System.currentTimeMillis();
                //10초 이상 network를 잡는다면 실내 판정
                if((int)(curTime_n/1000 - startTime_n/1000) >= 10){
                    location_inout = "실내";
                }
            }
        }
        else if(str.equals("gps")){
            startTime_n = curTime_n = 0;//net타이머 초기화
            if(startTime_g == 0)
                startTime_g = System.currentTimeMillis();
            else{
                curTime_g = System.currentTimeMillis();
                //10초 이상 gps를 잡는다면 실외 판정
                if((int)(curTime_g/1000 - startTime_g/1000) >= 10){
                    location_inout = "실외";
                }
            }
        }
    }

    LocationListener locationListener = new LocationListener() {
        public void onLocationChanged(Location location) {
            Log.d(LOGTAG, " Time : " + getCurrentTime() + " Longitude : " + location.getLongitude()
                    + " Latitude : " + location.getLatitude() + " Altitude: " + location.getAltitude()
                    + " Accuracy : " + location.getAccuracy());
            lon = location.getLongitude();
            lat = location.getLatitude();
            provider = location.getProvider();
        }

        public void onStatusChanged(String provider, int status, Bundle bundle) {
            Log.d(LOGTAG, "GPS status changed. status code: " + status);
            gpsStatusLevel = status;
            if(status == 2)
                Log.d(LOGTAG, "status: Available");
            else if(status == 1)
                Log.d(LOGTAG, "status: Temporarily unavailable");
            else if(status == 0)
                Log.d(LOGTAG, "status: Out of service");
            //Toast.makeText(getApplicationContext(), "GPS status changed.", Toast.LENGTH_SHORT).show();
        }

        public void onProviderEnabled(String provider) {
            Log.d(LOGTAG, "GPS onProviderEnabled: " + provider);
        }

        public void onProviderDisabled(String provider) {
            Log.d(LOGTAG, "GPS onProviderDisabled: " + provider);
            //Toast.makeText(getApplicationContext(), "GPS is off, please turn on!", Toast.LENGTH_LONG).show();
        }
    };

    public String getCurrentTime() {
        SimpleDateFormat formatter = new SimpleDateFormat("HH:mm", Locale.KOREA);
        Date currentTime = new Date();
        String dTime = formatter.format(currentTime);
        return dTime;
    }

    private void setNextAlarm(boolean moving) {

        // 움직임이면 5초 period로 등록
        // 움직임이 아니면 5초 증가, max 30초로 제한
        if(moving) {
            Log.d(LOGTAG, "MOVING!!");
            period = periodForMoving;
        } else {
            Log.d(LOGTAG, "NOT MOVING!!");
            period = period + periodIncrement;
            if(period >= periodMax) {
                period = periodMax;
            }
        }
        Log.d(LOGTAG, "Next alarm: " + period);

        // 다음 alarm 등록
        Intent in = new Intent("kr.ac.koreatech.msp.hsalarm");
        pendingIntent = PendingIntent.getBroadcast(getApplicationContext(), 0, in, 0);
        am.setExact(AlarmManager.ELAPSED_REALTIME_WAKEUP,
                SystemClock.elapsedRealtime() + period - activeTime, pendingIntent);
    }

    private void sendDataToActivity(boolean moving) {
        // 화면에 정보 표시를 위해 activity의 broadcast receiver가 받을 수 있도록 broadcast 전송
        Intent intent = new Intent(BROADCAST_ACTION_ACTIVITY);

        intent.putExtra("moving", moving);
        intent.putExtra("inout", provider);
        intent.putExtra("longitude", lon);
        intent.putExtra("latitude", lat);
        intent.putExtra("location", location_inout);
        intent.putExtra("location_user", receiver.loc);
        intent.putExtra("nowtime", nowtime);
        intent.putExtra("gpsStatusLevel", gpsStatusLevel);
        // broadcast 전송
        sendBroadcast(intent);
    }

    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    @Override
    public void onCreate() {

        Log.d(LOGTAG, "onCreate");

        // Alarm 발생 시 전송되는 broadcast를 수신할 receiver 등록
        IntentFilter intentFilter = new IntentFilter("kr.ac.koreatech.msp.hsalarm");
        registerReceiver(AlarmReceiver, intentFilter);

        // AlarmManager 객체 얻기
        am = (AlarmManager)getSystemService(ALARM_SERVICE);

        provider = "";
        location_inout = "none";

        receiver = new AlertReceiver();
        IntentFilter filter1 = new IntentFilter("com.example.junyoung.locationAlert1");//운동장
        IntentFilter filter2 = new IntentFilter("com.example.junyoung.locationAlert2");//잔디밭 벤치
        IntentFilter filter3 = new IntentFilter("com.example.junyoung.locationAlert3");//4공 B211
        IntentFilter filter4 = new IntentFilter("com.example.junyoung.locationAlert4");//다산정보관

        registerReceiver(receiver, filter1);
        registerReceiver(receiver, filter2);
        registerReceiver(receiver, filter3);
        registerReceiver(receiver, filter4);

    }

    //정적으로 위치를 직접 넣어줌
    public void in_EB4(){
        // ProximityAlert 등록을 위한 PendingIntent 객체 얻기
        Intent intent1 = new Intent("com.example.junyoung.locationAlert1");
        Intent intent2 = new Intent("com.example.junyoung.locationAlert2");
        Intent intent3 = new Intent("com.example.junyoung.locationAlert3");
        Intent intent4 = new Intent("com.example.junyoung.locationAlert4");

        proximityIntent1 = PendingIntent.getBroadcast(this, 0, intent1, 0);
        try {
            // 근접 경보 등록 메소드
            // void addProximityAlert(double latitude, double longitude, float radius, long expiration, PendingIntent intent)
            // 아래 위도, 경도 값의 위치는 운동장
            //mLocationManager.addProximityAlert(36.762581, 127.284527, 80, -1, proximityIntent1);
            mLocationManager.addProximityAlert(36.761603, 127.279196, 20, -1, proximityIntent1);
        } catch (SecurityException e) {
            e.printStackTrace();
        }

        proximityIntent2 = PendingIntent.getBroadcast(this, 0, intent2, 0);
        try {
            // 근접 경보 등록 메소드
            // void addProximityAlert(double latitude, double longitude, float radius, long expiration, PendingIntent intent)
            // 아래 위도, 경도 값의 위치는 대학본부 잔디광장 앞 벤치
            //mLocationManager.addProximityAlert(36.764215, 127.282173, 50, -1, proximityIntent2);
            mLocationManager.addProximityAlert(36.760829, 127.279828, 20, -1, proximityIntent2);
        } catch (SecurityException e) {
            e.printStackTrace();
        }

        proximityIntent3 = PendingIntent.getBroadcast(this, 0, intent3, 0);
        try {
            mLocationManager.addProximityAlert(36.761724, 127.280312, 10, -1, proximityIntent3);
            // 근접 경보 등록 메소드
            // void addProximityAlert(double latitude, double longitude, float radius, long expiration, PendingIntent intent)
            // 아래 위도, 경도 값의 위치는 운동장36.761447, 127.280181
            //mLocationManager.addProximityAlert(36.762581, 127.284527, 80, -1, proximityIntent);
        } catch (SecurityException e) {
            e.printStackTrace();
        }

        proximityIntent4 = PendingIntent.getBroadcast(this, 0, intent4, 0);
        try {
            mLocationManager.addProximityAlert(36.76357, 127.28043, 12, -1, proximityIntent4);
            // 근접 경보 등록 메소드
            // void addProximityAlert(double latitude, double longitude, float radius, long expiration, PendingIntent intent)
            // 아래 위도, 경도 값의 위치는 다산정보관
            //mLocationManager.addProximityAlert(36.762581, 127.284527, 80, -1, proximityIntent);
        } catch (SecurityException e) {
            e.printStackTrace();
        }
    }

    //4가지 위치 중 어느곳인지 판단하는 함수
    public void whereareyou(String str){
        if(str.equals("운동장")){
            receiver.reset_platground();//그 외 타이머 초기화
            if(receiver.startTime_playground == 0)
                receiver.startTime_playground = System.currentTimeMillis();
            else{
                receiver.curTime_playground = System.currentTimeMillis();
                //10초 이상 운동장을 잡는다면 실내 판정
                if((int)(receiver.curTime_playground/1000 - receiver.startTime_playground/1000) >= 10){
                    receiver.loc = "운동장";
                }
            }
        }
        else if(str.equals("잔디밭")){
            receiver.reset_grass();//그 외 타이머 초기화
            if(receiver.startTime_grass == 0)
                receiver.startTime_grass = System.currentTimeMillis();
            else{
                receiver.curTime_grass = System.currentTimeMillis();
                //10초 이상 잔디밭을 잡는다면 실내 판정
                if((int)(receiver.curTime_grass/1000 - receiver.startTime_grass/1000) >= 10){
                    receiver.loc = "잔디밭";
                }
            }
        }
        else if(str.equals("4공학관")){
            receiver.reset_eng();//그 외 타이머 초기화
            if(receiver.startTime_eng == 0)
                receiver.startTime_eng = System.currentTimeMillis();
            else{
                receiver.curTime_eng = System.currentTimeMillis();
                //10초 이상 4공학관을 잡는다면 실내 판정
                if((int)(receiver.curTime_eng/1000 - receiver.startTime_eng/1000) >= 10){
                    receiver.loc = "4공학관";
                }
            }
        }
        else if(str.equals("다산정보관")){
            receiver.reset_dasan();//그 외 타이머 초기화
            if(receiver.startTime_dasan == 0)
                receiver.startTime_dasan = System.currentTimeMillis();
            else{
                receiver.curTime_dasan = System.currentTimeMillis();
                //10초 이상 다산정보관을 잡는다면 실내 판정
                if((int)(receiver.curTime_dasan/1000 - receiver.startTime_dasan/1000) >= 10){
                    receiver.loc = "다산정보관";
                }
            }
        }
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        // intent: startService() 호출 시 넘기는 intent 객체
        // flags: service start 요청에 대한 부가 정보. 0, START_FLAG_REDELIVERY, START_FLAG_RETRY
        // startId: start 요청을 나타내는 unique integer id

        Log.d(LOGTAG, "onStartCommand");
        Toast.makeText(this, "Activity Monitor 시작", Toast.LENGTH_SHORT).show();

        // Alarm이 발생할 시간이 되었을 때, 안드로이드 시스템에 전송을 요청할 broadcast를 지정
        Intent in = new Intent("kr.ac.koreatech.msp.hsalarm");
        pendingIntent = PendingIntent.getBroadcast(getApplicationContext(), 0, in, 0);

        // Alarm이 발생할 시간 및 alarm 발생시 이용할 pending intent 설정
        // 설정한 시간 (5000-> 5초, 10000->10초) 후 alarm 발생
        am.setExact(AlarmManager.ELAPSED_REALTIME_WAKEUP,
                SystemClock.elapsedRealtime() + period, pendingIntent);

        return super.onStartCommand(intent, flags, startId);
    }

    public void onDestroy() {
        Toast.makeText(this, "Activity Monitor 중지", Toast.LENGTH_SHORT).show();

        try {
            // Alarm 발생 시 전송되는 broadcast 수신 receiver를 해제
            unregisterReceiver(AlarmReceiver);
            unregisterReceiver(receiver);
        } catch(IllegalArgumentException ex) {
            ex.printStackTrace();
        }
        // AlarmManager에 등록한 alarm 취소
        am.cancel(pendingIntent);

        // release all the resources you use
        if(timer != null)
            timer.cancel();
        if(wakeLock != null && wakeLock.isHeld()) {
            wakeLock.release();
            wakeLock = null;
        }
    }
}

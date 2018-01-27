package com.example.junyoung.a2017msp_termproject;

import android.Manifest;
import android.app.AlarmManager;
import android.app.PendingIntent;
import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.pm.PackageManager;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.os.Bundle;
import android.os.IBinder;
import android.os.PowerManager;
import android.os.SystemClock;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.util.Log;
import android.widget.Toast;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;

public class LCMonitor extends Service implements SensorEventListener {
    private static final String LOGTAG = "LCMonitor";

    private double lon = 0.0;
    private double lat = 0.0;

    //위치 등록을 위함
    PendingIntent proximityIntent1;//운동장
    PendingIntent proximityIntent2;//잔디밭 벤치
    PendingIntent proximityIntent3;//4공 B211
    PendingIntent proximityIntent4;//다산정보관

    AlertReceiver receiver;

    //위치 등록을 위함
    boolean isPermitted = false;
    boolean isLocRequested = false;
    boolean isAlertRegistered = false;

    private LocationManager mLocationManager = null;
    private boolean isRequestRegistered = false;

    private PowerManager.WakeLock wakeLock;

    final int MY_PERMISSIONS_REQUEST_ACCESS_FINE_LOCATION = 1;

    @Override
    public IBinder onBind(Intent intent) {return null;}

    @Override
    public void onAccuracyChanged(Sensor sensor, int accuracy) {}
    public void onSensorChanged(SensorEvent event){}

    public void onCreate() {
        super.onCreate();
        // 서비스에서 가장 먼저 호출됨(최초에 한번만)
        Log.d("test", "서비스의 onCreate");
        requestLocation();

    }

    private void requestLocation() {

        receiver = new AlertReceiver();
        IntentFilter filter1 = new IntentFilter("com.example.junyoung.locationAlert1");//운동장
        IntentFilter filter2 = new IntentFilter("com.example.junyoung.locationAlert2");//잔디밭 벤치
        IntentFilter filter3 = new IntentFilter("com.example.junyoung.locationAlert3");//4공 B211
        IntentFilter filter4 = new IntentFilter("com.example.junyoung.locationAlert4");//다산정보관

        registerReceiver(receiver, filter1);
        registerReceiver(receiver, filter2);
        registerReceiver(receiver, filter3);
        registerReceiver(receiver, filter4);

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
                        3000,
                        0,
                        locationListener);

                in_EB4();

                isRequestRegistered = true;
            }
            else mLocationManager.removeUpdates(locationListener);
        } catch (SecurityException se) {

            se.printStackTrace();
            Log.e(LOGTAG, "PERMISSION_NOT_GRANTED");
        }
    }

    private void cancelLocationRequest() {
        Log.d(LOGTAG, "Cancel the location update request");
        if(mLocationManager != null) {
            // 자원 사용 해제
            try {
                if(isLocRequested) {
                    mLocationManager.removeUpdates(locationListener);
                    isLocRequested = false;

                    mLocationManager.removeProximityAlert(proximityIntent1);
                    mLocationManager.removeProximityAlert(proximityIntent2);
                    mLocationManager.removeProximityAlert(proximityIntent3);
                    mLocationManager.removeProximityAlert(proximityIntent4);
                    unregisterReceiver(receiver);
                }

            } catch (SecurityException e) {
                e.printStackTrace();
                Log.e(LOGTAG, "PERMISSION_NOT_GRANTED");
            }
        }
        mLocationManager = null;
        isRequestRegistered = false;
    }


    //시간을 알기 위한 함수
    public String getCurrentTime() {
        SimpleDateFormat formatter = new SimpleDateFormat("yyyy.MM.dd HH:mm:ss", Locale.KOREA);
        Date currentTime = new Date();
        String dTime = formatter.format(currentTime);
        return dTime;
    }

    private void sendDataToActivity() {
        // 화면에 정보 표시를 위해 activity의 broadcast receiver가 받을 수 있도록 broadcast 전송
        Intent intent = new Intent("com.example.junyoung.b2017msp_termproject");
        //intent.putExtra("moving", moving);
        intent.putExtra("longitude", lon);
        intent.putExtra("latitude", lat);
        // broadcast 전송
        sendBroadcast(intent);
    }

    LocationListener locationListener = new LocationListener() {
        public void onLocationChanged(Location location) {
            lon = location.getLongitude();
            lat = location.getLatitude();
            sendDataToActivity();
        }

        public void onStatusChanged(String provider, int status, Bundle bundle) {
        }

        public void onProviderEnabled(String provider) {
        }

        public void onProviderDisabled(String provider) {
            Log.d(LOGTAG, "GPS onProviderDisabled: " + provider);
            //Toast.makeText(getApplicationContext(), "GPS is off, please turn on!", Toast.LENGTH_LONG).show();
        }
    };


    @Override
    public void onDestroy() {
        // handler.removeCallbacks(sendUpdatesToUI);
        super.onDestroy();
        Log.v("STOP_SERVICE", "DONE");
        cancelLocationRequest();
    }

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
            mLocationManager.addProximityAlert(36.762581, 127.284527, 80, -1, proximityIntent1);
        } catch (SecurityException e) {
            e.printStackTrace();
        }

        proximityIntent2 = PendingIntent.getBroadcast(this, 0, intent2, 0);
        try {
            // 근접 경보 등록 메소드
            // void addProximityAlert(double latitude, double longitude, float radius, long expiration, PendingIntent intent)
            // 아래 위도, 경도 값의 위치는 대학본부 잔디광장 앞 벤치
            mLocationManager.addProximityAlert(36.764215, 127.282173, 50, -1, proximityIntent2);
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
    /*
    //사용자 정의 위치 추가
    private void requestRuntimePermission() {
        //*******************************************************************
        // Runtime permission check
        //*******************************************************************
        if (ContextCompat.checkSelfPermission(LCMonitor.this,
                Manifest.permission.ACCESS_FINE_LOCATION)
                != PackageManager.PERMISSION_GRANTED) {

            // Should we show an explanation?
            if (ActivityCompat.shouldShowRequestPermissionRationale(LCMonitor.this,
                    Manifest.permission.ACCESS_FINE_LOCATION)) {

                // Show an expanation to the user *asynchronously* -- don't block
                // this thread waiting for the user's response! After the user
                // sees the explanation, try again to request the permission.

            } else {

                // No explanation needed, we can request the permission.

                ActivityCompat.requestPermissions(LCMonitor.this,
                        new String[]{Manifest.permission.ACCESS_FINE_LOCATION},
                        MY_PERMISSIONS_REQUEST_ACCESS_FINE_LOCATION);
            }
        } else {
            // ACCESS_FINE_LOCATION 권한이 있는 것
            isPermitted = true;
        }
        //*********************************************************************
    }

    //사용자 정의 위치 추가
    @Override
    public void onRequestPermissionsResult(int requestCode,
                                           String permissions[], int[] grantResults) {
        switch (requestCode) {
            case MY_PERMISSIONS_REQUEST_ACCESS_FINE_LOCATION: {
                // If request is cancelled, the result arrays are empty.
                if (grantResults.length > 0
                        && grantResults[0] == PackageManager.PERMISSION_GRANTED) {

                    // permission was granted, yay! Do the
                    // read_external_storage-related task you need to do.

                    // ACCESS_FINE_LOCATION 권한을 얻음
                    isPermitted = true;

                } else {

                    // permission denied, boo! Disable the
                    // functionality that depends on this permission.

                    // 권한을 얻지 못 하였으므로 location 요청 작업을 수행할 수 없다
                    // 적절히 대처한다
                    isPermitted = false;

                }
                return;
            }

            // other 'case' lines to check for other
            // permissions this app might request
        }
    }*/
}

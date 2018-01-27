package com.pierre.biojoux.project;

import android.app.Service;
import android.content.Intent;
import android.os.AsyncTask;
import android.os.Binder;
import android.os.IBinder;
import android.util.Log;

public class BinService extends Service {
    public static final String BROADCAST_BACKGROUND_SERVICE_RESULT = "com.pierre.biojoux.project.BROADCAST_BACKGROUND_SERVICE_RESULT";
    private static final String ERROR = "Error occurred";
    private static final String SUCCESS = "New weather data";
    private static final String LOG = "BinService";
    private boolean started = false;
    private long wait = 30 * 1000; // 30 mins in ms
    private final IBinder mBinder = new MyBinder();

    public BinService() { //Constructor
    }

    @Override
    public void onCreate() {
        super.onCreate();
        Log.d(LOG, "Background service created");
    }
    @Override
    public IBinder onBind(Intent intent){
        return mBinder;
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        if(!started && intent!=null) {
            started = true;
            getData();
        }
        return START_STICKY; // On stop start again
    }

    private void getData(){

        AsyncTask<Object, Object, String> task = new AsyncTask<Object, Object, String>() {
            @Override
            protected String doInBackground(Object[] params) {
                try {
                    Log.d(LOG, "Background service running");
                    stopSelf();
                } catch (Exception e) {
                    e.printStackTrace();
                    return ERROR;
                }
                return SUCCESS;
            }


            @Override
            protected void onPostExecute(String stringResult) {
                super.onPostExecute(stringResult);
                broadcastTaskResult();
                if(started){
                    getData();
                }
            }
        };
        task.execute();
    }

    private void broadcastTaskResult(){
        Intent broadcastIntent = new Intent();
        broadcastIntent.setAction(BROADCAST_BACKGROUND_SERVICE_RESULT);
        broadcastIntent.addFlags(Intent.FLAG_INCLUDE_STOPPED_PACKAGES);
        sendBroadcast(broadcastIntent);
    }

    @Override
    public void onDestroy() {
        started = false;
        super.onDestroy();
    }
    public class MyBinder extends Binder {
        BinService getService(){
            return BinService.this;
        }
    }
}
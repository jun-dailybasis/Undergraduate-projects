package kr.ac.koreatech.seungwoo.msp08encountermonitor;

import android.app.Service;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Environment;
import android.os.IBinder;
import android.os.PowerManager;
import android.os.Vibrator;
import android.util.Log;
import android.widget.Toast;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.Writer;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Timer;
import java.util.TimerTask;

import static android.widget.Toast.LENGTH_SHORT;
public class EncounterMonitor extends Service {
    private static final String TAG = "EncounterMonitor";


    //???? ??? ?? ???
    BluetoothAdapter mBTAdapter;
    Vibrator vib;
    Date startDate;
    //??? ??
    Timer timer = new Timer();
    TimerTask timerTask = null;

    // ????? ???? ????? ?? ??
    String btName;
    String userName;
    //???? ?? ?? ?? ????? true
    boolean isFinding = false;


    //?? ???? ?? ??
    String path = Environment.getExternalStorageDirectory().getAbsolutePath();
    File f = new File(path +"/bloothLog.txt");
    FileInputStream inputStream = null;
    FileOutputStream output = null;
    int count = 1;
    int bloothSearchCount = 0;



    // BT ??? ??? broadcast? ?? BroadcastReceiver ?? ??
    protected BroadcastReceiver mReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            String action = intent.getAction();
            BluetoothDevice device = (BluetoothDevice)intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);
            Log.d("Test", action);
            if(action.equals(BluetoothAdapter.ACTION_DISCOVERY_STARTED)) {
                // discovery 시작됨
                // 아래는 toast 메시지 표시하는 코드
                Toast.makeText(getApplicationContext(), userName + "'s "+btName +" scanning..", LENGTH_SHORT).show();
                Log.d("Test", "Bluetooth scan started..");
                //                if((count==3) && (isConnected == 1)){
//                    saveCurrentTime(BluetoothDevice.ACTION_ACL_DISCONNECTED);
//                    Log.d("Test", "actionStatus.equals(count 3 이다.)");
//                    Log.d("Test", "count" +count);
//                    isConnected = 0;
//                }
//                count++;
                if(isFinding ==true)
                {
                    //장비 검색 횟수 카운트 해준다.
                    bloothSearchCount++;
                    // Toast.makeText(getApplicationContext(), bloothSearchCount , Toast.LENGTH_SHORT).show();

                    // 3번이상 못 찾으면 탐색 종료 시키는 종료문
                    if (bloothSearchCount>3) {

                        //텍스트 파일에 저장하는 구문
                        Date date = new Date();
                        Toast.makeText(getApplication(), userName + "'s "+btName+ "is over to find", Toast.LENGTH_SHORT).show();

                        try {
                            output = new FileOutputStream(f,true);
                            Writer out = new OutputStreamWriter(output, "UTF8");
                            //날짜를 파일에 저장한다.
                            SimpleDateFormat dateFormat = new  SimpleDateFormat("yyyy.MM.dd HH:mm", java.util.Locale.getDefault());
                            String strDate = count + ". " + dateFormat.format(startDate);
                            long distantTime = (date.getTime() - startDate.getTime()) / 1000;
                            distantTime = (distantTime / 60);
                            out.write(strDate + "(" + distantTime + "분)\n"+ "");
                            out.close();
                            //MainActivity의 logText의 내용을 text파일에서 받아와 수정하도록 하였다.
                            inputStream = new FileInputStream(f);
                            byte[] buffer=new byte[inputStream.available()];
                            inputStream.read(buffer);
                            strDate = new String(buffer);
                            MainActivity.logText.setText(strDate);
                            inputStream.close();

                            //검색을 완료했다는 변수를 false로 바꾸면서 장치를 찾은 회수를 증가시키는 count를 1증가시킴
                            isFinding = false;
                            count++;

                        }
                        catch (IOException e) {
                            e.printStackTrace();
                        }

                    }
                }

            }
            else if(action.equals(BluetoothDevice.ACTION_FOUND)) {

                if(isFinding ==true&&btName.equals(device.getName())) {
                    //기존 장비를 찾고있고, 이름이 같다면..
                    vib.vibrate(200);
                    Toast.makeText(getApplicationContext(),  userName + "의 "+btName+" 연결 중",

                            Toast.LENGTH_SHORT).show();
                    //장치를 3번이상 놓치지 않았기에 searchTryCount 를 0으로 초기화
                    bloothSearchCount = 0;
                }
                else if(isFinding ==false&&btName.equals(device.getName())) {
                    //장비를 처음 찾고, 이름이 같다면...

                    Date date = new Date();
                    bloothSearchCount=0;
                    startDate = date;
                    vib.vibrate(200);
                    Toast.makeText(getApplicationContext(), userName + "의 "+btName+"를 찾음.",
                            Toast.LENGTH_SHORT).show();
                    isFinding = true; //isFinding의 변수를 true로 설정하여, 현재 장비를 계속 찾고있음을 저장해둔다.
                }

            }else if (action.equals(BluetoothDevice.ACTION_ACL_CONNECTED)) {
                Log.d("Test", device.getName().toString() +" Device Is Connected!");
            } else if (action.equals(BluetoothDevice.ACTION_ACL_DISCONNECTED)){
                Log.d("Test", device.getName().toString() +" Device Is DISConnected!");
                Toast.makeText(getApplicationContext(),"Device is disconnected!",
                        Toast.LENGTH_SHORT).show();
            }
            if (action.equals(BluetoothAdapter.ACTION_CONNECTION_STATE_CHANGED)){
                Log.d("Test", "ACTION_CONNECTION_STATE_CHANGED");
            }
            if (action.equals(BluetoothAdapter.ACTION_STATE_CHANGED)){
                Log.d("Test", "ACTION_STATE_CHANGED");
            }


        }

    };


    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }



    //??? ??? CPU? ??? ? ????? ????? ? WakeLock ??
    PowerManager pm;
    PowerManager.WakeLock wl;
    @Override
    public void onCreate() {
        Log.d(TAG, "onCreate()");
        //WakeLock ????. ??? ????? CPU? ????? ??????.
        mBTAdapter = BluetoothAdapter.getDefaultAdapter();
        pm = (PowerManager) getSystemService(Context.POWER_SERVICE);
        wl = pm.newWakeLock(PowerManager.PARTIAL_WAKE_LOCK, "wake lock");
        vib = (Vibrator)getSystemService(VIBRATOR_SERVICE);

        // BT ???? ?? ???? ?? ??? broadcast? ?? ??? IntentFilter? ??
        IntentFilter filter = new IntentFilter();
        filter.addAction(BluetoothDevice.ACTION_FOUND);
        filter.addAction(BluetoothAdapter.ACTION_DISCOVERY_STARTED);
        filter.addAction(BluetoothDevice.ACTION_ACL_DISCONNECTED);
        filter.addAction(BluetoothAdapter.ACTION_CONNECTION_STATE_CHANGED);
        filter.addAction(BluetoothAdapter.ACTION_STATE_CHANGED);

        // BroadcastReceiver 등록;
        registerReceiver(mReceiver, filter);
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        // intent: startService() 호출 시 넘기는 intent 객체
        // flags: service start 요청에 대한 부가 정보. 0, START_FLAG_REDELIVERY, START_FLAG_RETRY
        // startId: start 요청을 나타내는 unique integer id

        Toast.makeText(this, "EncounterMonitor 시작", LENGTH_SHORT).show();
        Log.d(TAG, "onStartCommand()");

        // MainActivity에서 Service를 시작할 때 사용한 intent에 담겨진 BT 디바이스와 사용자 이름 얻음
        btName = intent.getStringExtra("BTName");
        userName = intent.getStringExtra("UserName");

        // 주기적으로 BT discovery 수행하기 위한 timer 가동
        startTimerTask();

        return super.onStartCommand(intent, flags, startId);
    }



    private void stopTimerTask() {
        //wskelock를 해제
        wl.release();
        try {

            output = new FileOutputStream(f, true);
            Writer out = new OutputStreamWriter(output, "UTF8");
            SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy.MM.dd HH:mm", java.util.Locale.getDefault());
            Date date = new Date();
            String strDate = "";
            if (isFinding == true) {
                //블루투스를 검색중이었다면 Toast로 검색이 끝났다는 메세지를 날려준다.
                //그 후 검색한 내용을 파일에 저장한 뒤 모니터링 종료를 하였다는 내용을 파일에 쓰라고 하였다.
                isFinding = false;
                Toast.makeText(getApplication(), "검색 종료.", Toast.LENGTH_SHORT).show();
                strDate += count + ". " + dateFormat.format(startDate);
                long distantTime = (date.getTime() - startDate.getTime()) / 1000;
                distantTime = (distantTime / 60);
                out.write(strDate + "(" + distantTime + "분)\n" + "모니터링 종료 - " + dateFormat.format(date) + "\n");
            }
            else {
                //검색 중이 아니었다면 모니터링을 종료하였다는 메세지를 파일에 쓰라고 하였다.
                out.write("모니터링 종료 - " + dateFormat.format(date));
            }
            out.close();
            //MainActivity의 logText의 내용을 text파일에서 받아와 수정하도록 하였다.
            inputStream = new FileInputStream(f);
            byte[] buffer = new byte[inputStream.available()];
            inputStream.read(buffer);
            strDate = new String(buffer);
            MainActivity.logText.setText(strDate);
            inputStream.close();
        }
        catch(IOException e){
            e.printStackTrace();
        }
        //탐지 초기화를 하면서 타이머를 종료켰다.
        bloothSearchCount = 0;
        isFinding = false;
        if(timerTask != null) {
            timerTask.cancel();
            timerTask = null;
        }
    }

    //블루투스 타이머 시작 함수 WakeLock도 같이 시작함.
    private void startTimerTask() {
        // TimerTask 생성한다
        // WakeLock 시작
        wl.acquire();
        timerTask = new TimerTask() {
            @Override
            public void run() {
                mBTAdapter.startDiscovery();
            }
        };

        // TimerTask를 Timer를 통해 실행시킨다
        // 3초 후에 타이머를 구동하고 10초마다 반복한다

        timer.schedule(timerTask, 3000, 10000);

    }
    //블루투스 타이머 종료될 때 호출하는 함수
    public void onDestroy() {

        Toast.makeText(this, "EncounterMonitor 중지", LENGTH_SHORT).show();
        Log.d(TAG, "onDestroy()");

        stopTimerTask();
        unregisterReceiver(mReceiver);
    }

}
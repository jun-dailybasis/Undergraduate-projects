package kr.ac.koreatech.seungwoo.msp08encountermonitor;

import android.app.AlertDialog;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothManager;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Environment;
import android.os.Parcelable;
import android.os.PowerManager;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.Reader;
import java.io.UnsupportedEncodingException;
import java.io.Writer;
import java.nio.charset.StandardCharsets;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;

public class MainActivity extends AppCompatActivity {

    //블루투스를 설정하고 탐색하게 해주는 변수
    BluetoothAdapter mBTAdapter;
    static final int REQUEST_ENABLE_BT = 1;
    static final int REQUEST_ENABLE_DISCOVER = 2;

    boolean isMonitering = false;
//    static TextView logText;
//    String btName ,userName;
//    EditText bt, user;
//    Button regiBtn, startBtn;

    boolean isResistent = false;

    //logText는 EncounterMonitor에서도 뷰를 변경해야하므로 static으로 설정하였다.
    static TextView logText;
    String btName ,userName;
    EditText bt, user;
    Button regiBtn, startBtn;
    String path = Environment.getExternalStorageDirectory().getAbsolutePath();
    File f = new File(path +"/bloothLog.txt");
    //dateformat 선언 하고 양식 설정.
    SimpleDateFormat dateFormat = new  SimpleDateFormat("yyyy.MM.dd HH:mm", java.util.Locale.getDefault());

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        //필요한 컴포넌트 id 받아온다.
        logText = (TextView)findViewById(R.id.logText);
        bt = (EditText)findViewById(R.id.btName);
        user = (EditText)findViewById(R.id.userName);
        regiBtn = (Button)findViewById(R.id.regiBtn);
        startBtn = (Button)findViewById(R.id.startMonitorBtn);

        //블루 투스 adapter로 설정.
        mBTAdapter = BluetoothAdapter.getDefaultAdapter();


        // BT adapter 확인 ===============================//
        // 장치가 블루투스를 지원하지 않는 경우 null 반환
        if(mBTAdapter == null) {
            // 블루투스 지원하지 않기 때문에 블루투스를 이용할 수 없음
            // alert 메세지를 표시하고 사용자 확인 후 종료하도록 함
            // AlertDialog.Builder 이용, set method에 대한 chaining call 가능
            new AlertDialog.Builder(this)
                    .setTitle("Not compatible")
                    .setMessage("Your device does not support Bluetooth")
                    .setPositiveButton("Exit", new DialogInterface.OnClickListener() {
                        @Override
                        public void onClick(DialogInterface dialog, int which) {
                            finish();
                        }
                    })
                    .show();
        } else{
            if(!mBTAdapter.isEnabled()) {
                // 비활성화 상태
                Intent enableBTIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
                startActivityForResult(enableBTIntent, REQUEST_ENABLE_BT);
            }
        }

    }



    @Override
    protected void onActivityResult(int requestCode, int responseCode, Intent data) {
        // 요청 코드에 따라 처리할 루틴을 구분해줌
        switch(requestCode) {
            case REQUEST_ENABLE_BT:
                if(responseCode == RESULT_OK) {
                    // 사용자가 활성화 상태로 변경하는 것을 허용하였음
                } else if(responseCode == RESULT_CANCELED) {
                    // 사용자가 활성화 상태로 변경용할 수 없으므로 애플리케이션 종료
                    finish();//하는 것을 허용하지 않음
                }
                break;
            case REQUEST_ENABLE_DISCOVER:
                if(responseCode == RESULT_CANCELED) {
                    // 사용자가 DISCOVERABLE 허용하지 않음
                    Toast.makeText(this, "사용자가 discoverable을 허용하지 않았습니다.", Toast.LENGTH_SHORT).show();
                }
        }
    }

    //앱을 껐을 때 블루투스 설정을 없애면서 블루투스 탐색 해제
    @Override
    protected void onDestroy() {
        super.onDestroy();
        stopService(new Intent(this, EncounterMonitor.class));
        mBTAdapter = null;
    }





    //버튼 클릭 onClick 함수.
    public void onClick(View view) throws IOException {

        //Register버튼 클릭시
        if(view.getId() == R.id.regiBtn) {
          // 아무것도 입력이 되지 않았을시..
            if(bt.getText().toString().equals("")||user.getText().toString().equals(""))
            {
                Toast.makeText(this, "BT 디바이스와 사용자이름을 작성해주세요", Toast.LENGTH_SHORT).show();
            }
            // 입력 한 값과 디바이스 명이 같으면.. 입력한 정보를 저장해둔다.
            else
            {
                //등록되었다는 것을 알리기 위해 isResistent을 true로 바꾸었다.
                btName = bt.getText().toString();
                userName = user.getText().toString();
                Toast.makeText(this, "장치이름 : " + btName +"\n사용자이름 : " + userName, Toast.LENGTH_SHORT).show();
                isResistent = true;
            }
        }
        else if(view.getId() == R.id.startMonitorBtn) {
            //블루투스 모니터 시작 버튼.
            // isMonitering이 작동중인 값이 있으면 해제 하라는 메세지를 띄우고
            // 등록되지 않았을 시에는 등록하라는 메세지를 띄운다.
            if (isMonitering == true) {
                Toast.makeText(this, "이미 모니터링 중입니다..", Toast.LENGTH_SHORT).show();

            } else if (isResistent == false) {
                Toast.makeText(this, "등록할 장비의 정보를 입력해주세요.", Toast.LENGTH_SHORT).show();
            } else {
                Toast.makeText(this, "모니터링 시작", Toast.LENGTH_SHORT).show();
                isMonitering = true;//모니터링 시작한다는 의미로 true값으로 변환시켜 준다.

                //시작하면 시작하는 시간을 저장하고, 파일 입출력을 통해 시간을 파일에 저장한다..
                Date date = new Date();
                if(f.exists()){
                    Toast.makeText(this, "file 있음", Toast.LENGTH_SHORT).show();
                    try {
                        FileOutputStream output = new FileOutputStream(f, false);
                        Writer out = new OutputStreamWriter(output, "UTF8");
                        String responseString = "모니터링 시작 - " + dateFormat.format(date) + "\n";
                        out.write("모니터링 시작 - " + dateFormat.format(date) + "\n");
                        out.close();
                        logText.setText(responseString);
                        Intent intent = new Intent(this, EncounterMonitor.class);
                        intent.putExtra("UserName", userName);
                        intent.putExtra("BTName", btName);
                        startService(intent);
                    } catch (Exception e) {
                        Toast.makeText(this, "실패:"+path+ ": path", Toast.LENGTH_SHORT).show();
                        // Toast.makeText(this, "파일 입출력 fail", Toast.LENGTH_SHORT).show();
                    }
                }
                else
                    Toast.makeText(this, "file 없음", Toast.LENGTH_SHORT).show();


            }
        }
        else if(view.getId() == R.id.stopMonitorBtn)
        {
            //검색 종료 버튼

            if(isMonitering==false)
            {
                //모니터링하고 있는 디바이스가 없는데 해제하라고 하면..
                Toast.makeText(this, "해제 할 디바이스가 없습니다..", Toast.LENGTH_SHORT).show();
            }
            else {
                //모니터링 중이라면.. 서비스를 종료
                isMonitering = false;
                stopService(new Intent(this, EncounterMonitor.class));
            }
        }
    }
    //블루투스 검색을 시작하는 함수
    public void onClickDiscover(View view) {
        Intent discoverIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_DISCOVERABLE);
        // duration: 초 단위 시간, 0-3600, 0이면 계속 discoverable 상태,
        discoverIntent.putExtra(BluetoothAdapter.EXTRA_DISCOVERABLE_DURATION, 0);
        startActivityForResult(discoverIntent, REQUEST_ENABLE_DISCOVER);
    }
}

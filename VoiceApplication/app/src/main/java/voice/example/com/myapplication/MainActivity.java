package voice.example.com.myapplication;

import android.Manifest;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.SystemClock;
import android.provider.Settings;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Chronometer;
import android.widget.ImageButton;
import android.widget.TextView;
import android.widget.Toast;

import voice.example.com.myapplication.ActivityContract.IActivityPresenter;
import voice.example.com.myapplication.ActivityContract.IActivityView;
import voice.example.com.myapplication.model.RecordItem;
import voice.example.com.myapplication.recordwave.VoiceMicView;

public class MainActivity extends AppCompatActivity implements IActivityView, View.OnClickListener{
    private final int REQUEST_CODE_ASK_MULTIPLE_PERMISSIONS = 11;


    private static final String IP = "192.168.2.1";

    private ImageButton mBtnPlay;
    private ImageButton mBtnNext;
    private ImageButton mBtnReset;
    private VoiceMicView mMicView;
    private TextView mCurRecoderText;
    private TextView mNextRecoderText;
    private Chronometer mRecoderTime;
    private ImageButton mBtnSpeakOnOff;
    private IActivityPresenter mPresenter;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
//
        mBtnNext = findViewById(R.id.btnNext);
        mBtnPlay = findViewById(R.id.btnPlay);
        mBtnReset = findViewById(R.id.btnRemake);
        mBtnSpeakOnOff = findViewById(R.id.btnSpeakOnOff);
        mMicView = findViewById(R.id.micView);
        mCurRecoderText = findViewById(R.id.curRecoder);
        mNextRecoderText = findViewById(R.id.textNextRecoder);
        mRecoderTime = findViewById(R.id.record_time);

        mBtnNext.setOnClickListener(this);
        mBtnReset.setOnClickListener(this);
        mBtnPlay.setOnClickListener(this);
        mBtnSpeakOnOff.setOnClickListener(this);

        mPresenter = new ActivityPresenterImpl(this);
        mPresenter.start();
        checkRecordPermission();

    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        mPresenter.destroy();
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.btnPlay:
                mBtnPlay.setImageResource(android.R.drawable.ic_media_pause);
                mPresenter.playCurRecorder();
                break;
            case R.id.btnNext:
                mBtnNext.setBackgroundResource(R.drawable.gray_circle);
                mBtnNext.setClickable(false);
                mPresenter.next();
                break;
            case R.id.btnRemake:
                mBtnReset.setBackgroundResource(R.drawable.gray_circle);
                mBtnReset.setClickable(false);
                mPresenter.reset();
                break;
            case R.id.btnSpeakOnOff:
                mPresenter.startSpeakOnOff();
                break;
            case R.id.back:
                finish();
                break;
        }
    }
    @Override
    public void onShowRecData(String data) {
        //Toast.makeText(this, "应用出现问题：" + data, Toast.LENGTH_LONG).show();

    }

    @Override
    public void setSpeakIcon(int type) {
        if (type == ActivityContract.SpeakType.START) {
            mBtnSpeakOnOff.setImageResource(android.R.drawable.ic_btn_speak_now);
        } else {
            mBtnSpeakOnOff.setImageResource(android.R.drawable.ic_lock_power_off);
        }
    }

    @Override
    public void onShowNoUSBDialog() {
        new AlertDialog.Builder(this)
                .setPositiveButton("好的", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        finish();
                    }
                })
                .setCancelable(false)
                .setMessage("请插入USB设备")
                .show();
    }

    @Override
    public void onUpdateMicWave() {
        int[] random = {0, 60, 8};
        int randomNum = (int) (Math.random() * random.length - 1);
        mMicView.updateVolume(random[randomNum]);
    }

    @Override
    public void onShowStopView() {
        mMicView.end();
        mRecoderTime.setBase(SystemClock.elapsedRealtime());//计时器清零
        mRecoderTime.stop();
        if (!mBtnReset.isClickable()){
            mBtnReset.setBackgroundResource(R.drawable.default_circle);
            mBtnReset.setClickable(true);
        }
        if (!mBtnNext.isClickable()){
            mBtnNext.setBackgroundResource(R.drawable.default_circle);
            mBtnNext.setClickable(true);
        }
    }

    @Override
    public void onShowStartView() {
        mMicView.start();
        mRecoderTime.setBase(SystemClock.elapsedRealtime());//计时器清零
        int hour = (int) ((SystemClock.elapsedRealtime() - mRecoderTime.getBase()) / 1000 / 60);
        mRecoderTime.setFormat("0"+String.valueOf(hour)+":%s");
        mRecoderTime.start();
    }

    @Override
    public void onPlayFinishedView() {
        mBtnPlay.setImageResource(android.R.drawable.ic_media_play);
    }

    @Override
    public void onShowText(RecordItem curItem, RecordItem nextItem) {
        mCurRecoderText.setText(curItem.getQueryText());
        if (nextItem != null) {
            mNextRecoderText.setText("下一条： " + nextItem.getQueryText());
        } else {
            mNextRecoderText.setText(" ");
        }

    }

    /**
     * 申请权限
     */
    private void checkRecordPermission() {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            if (checkSelfPermission(Manifest.permission.RECORD_AUDIO) != PackageManager.PERMISSION_GRANTED
                    || checkSelfPermission(Manifest.permission.WRITE_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED) {
                requestPermissions(new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE, Manifest.permission.RECORD_AUDIO},
                        REQUEST_CODE_ASK_MULTIPLE_PERMISSIONS);
            } else {
                //startSoundRecord();
            }
        } else {
            //startSoundRecord();
        }
    }
    @Override
    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) {
        switch (requestCode) {
            case REQUEST_CODE_ASK_MULTIPLE_PERMISSIONS: {
                if (grantResults[0] == PackageManager.PERMISSION_GRANTED && grantResults[1] == PackageManager.PERMISSION_GRANTED) {
                   // startSoundRecord();
                } else {
                    Toast.makeText(this, "请在设置中打开权限后继续", Toast.LENGTH_SHORT).show();
                    Intent intent = new Intent();
                    intent.setAction(Settings.ACTION_APPLICATION_DETAILS_SETTINGS);
                    Uri uri = Uri.fromParts("package", getPackageName(), null);
                    intent.setData(uri);
                    startActivityForResult(intent, 200);
                }
            }
            break;
            default:
                super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        }
    }
}

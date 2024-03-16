package com.hw.carctrl;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothGatt;
import android.bluetooth.BluetoothGattCallback;
import android.bluetooth.BluetoothGattCharacteristic;
import android.bluetooth.BluetoothGattDescriptor;
import android.bluetooth.BluetoothGattService;
import android.bluetooth.BluetoothProfile;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.widget.TextView;

import androidx.annotation.Nullable;

import java.util.UUID;

public class CarCtrlActivity extends Activity {
    private static final String TAG = App.getTag(CarCtrlActivity.class);
    private static final String EXTRA_BT_ADDR = "extra_bt_addr";

    /**
    private UUID UUID_S1 = UUID.fromString("00001800-0000-1000-8000-00805f9b34fb");
    private UUID UUID_S1_C1 = UUID.fromString("00002a00-0000-1000-8000-00805f9b34fb"); // BT_NAME hw
    private UUID UUID_S1_C2 = UUID.fromString("00002a01-0000-1000-8000-00805f9b34fb");
    private UUID UUID_S2 = UUID.fromString("00001801-0000-1000-8000-00805f9b34fb");
    private UUID UUID_S2_C1 = UUID.fromString("00002a05-0000-1000-8000-00805f9b34fb");
    private UUID UUID_S2_C1_D1 = UUID.fromString("00002902-0000-1000-8000-00805f9b34fb");
    private UUID UUID_S3 = UUID.fromString("0000180a-0000-1000-8000-00805f9b34fb");
    private UUID UUID_S3_C1 = UUID.fromString("00002a29-0000-1000-8000-00805f9b34fb"); // DX-smart
    private UUID UUID_S3_C2 = UUID.fromString("00002a24-0000-1000-8000-00805f9b34fb"); // DX-BT24
    private UUID UUID_S3_C3 = UUID.fromString("00002a26-0000-1000-8000-00805f9b34fb"); // +VERSION=V2.1.0
    private UUID UUID_S3_C4 = UUID.fromString("00002a28-0000-1000-8000-00805f9b34fb"); // +VERSION=V2.1.0
    private UUID UUID_S3_C5 = UUID.fromString("00002a23-0000-1000-8000-00805f9b34fb"); // DX-smart-BT24
    private UUID UUID_S3_C6 = UUID.fromString("00002a50-0000-1000-8000-00805f9b34fb"); // DX-smart-BT24
    private UUID UUID_NOTIFY_D2 = UUID.fromString("00002901-0000-1000-8000-00805f9b34fb"); // TX & RX
    private UUID UUID_WRITE = UUID.fromString("0000ffe2-0000-1000-8000-00805f9b34fb");
    private UUID UUID_WRITE_D1 = UUID.fromString("00002901-0000-1000-8000-00805f9b34fb"); // TX
    */
    private UUID UUID_SERVICE = UUID.fromString("0000ffe0-0000-1000-8000-00805f9b34fb");
    private UUID UUID_NOTIFY = UUID.fromString("0000ffe1-0000-1000-8000-00805f9b34fb");
    private UUID UUID_NOTIFY_DESCRIPTOR = UUID.fromString("00002902-0000-1000-8000-00805f9b34fb");


    private String mBtAddr;
    private TextView mTxvBtState;
    private TextView mTxvCarState;
    private BluetoothAdapter mBtAdapter;
    private BluetoothDevice mBtDevice;
    private BluetoothGatt mBtGatt;
    private BluetoothGattService mBtService;
    private BluetoothGattCharacteristic mBtChar;

    private TextView mBtnLeft;
    private TextView mBtnRight;
    private TextView mBtnGo;
    private TextView mBtnBack;
    boolean mTurnLeft;
    boolean mTurnRight;
    boolean mGo;
    boolean mBack;

    private static final int TURN_STATE_LEFT = 1;
    private static final int TURN_STATE_RIGHT = 2;
    private static final int TURN_STATE_BACK = 0;
    private static final int MOVE_STATE_GO = 3;
    private static final int MOVE_STATE_BACK = 4;
    private static final int MOVE_STATE_STOP = 5;
    int mTurnState = TURN_STATE_BACK;
    int mMoveState;

    @SuppressLint("MissingPermission")
    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.carctrl_activity);

        mTxvBtState = findViewById(R.id.txv_btstate);
        mTxvBtState.setText("蓝牙连接中...");
        mTxvCarState = findViewById(R.id.txv_carstate);

        mBtAddr = getIntent().getStringExtra(EXTRA_BT_ADDR);
        mBtAdapter = App.getBTAdapter();
        mBtDevice = mBtAdapter.getRemoteDevice(mBtAddr);
        mBtGatt = mBtDevice.connectGatt(this, true, mBTGAttCallback);

        mBtnLeft = findViewById(R.id.btn_left);
        mBtnRight = findViewById(R.id.btn_right);
        mBtnGo = findViewById(R.id.btn_go);
        mBtnBack = findViewById(R.id.btn_back);
        mBtnLeft.setOnTouchListener(mTouchListener);
        mBtnRight.setOnTouchListener(mTouchListener);
        mBtnGo.setOnTouchListener(mTouchListener);
        mBtnBack.setOnTouchListener(mTouchListener);
    }

    @SuppressLint("MissingPermission")
    @Override
    protected void onDestroy() {
        super.onDestroy();
        mBtGatt.disconnect();
    }

    private BluetoothGattCallback mBTGAttCallback = new BluetoothGattCallback() {
        @SuppressLint("MissingPermission")
        @Override
        public void onConnectionStateChange(BluetoothGatt gatt, int status, int newState) {
            super.onConnectionStateChange(gatt, status, newState);
            Log.e(TAG, "onConnectionStateChange status = " + status + " newState = " + newState);
            switch (newState) {
                case BluetoothProfile.STATE_CONNECTED:
                    mTxvBtState.setText("蓝牙已连接");
                    gatt.discoverServices();
                    break;
                case BluetoothProfile.STATE_DISCONNECTED:
                    mTxvBtState.setText("蓝牙断开");
                    break;
                case BluetoothProfile.STATE_CONNECTING:
                    mTxvBtState.setText("蓝牙连接中...");
                    break;
                case BluetoothProfile.STATE_DISCONNECTING:
                    mTxvBtState.setText("蓝牙断开中...");
                    break;
            }
        }

        @Override
        public void onCharacteristicWrite(BluetoothGatt gatt, BluetoothGattCharacteristic characteristic, int status) {
            super.onCharacteristicWrite(gatt, characteristic, status);
            Log.e(TAG, "onCharacteristicWrite");
        }

        @Override
        public void onDescriptorWrite(BluetoothGatt gatt, BluetoothGattDescriptor descriptor, int status) {
            super.onDescriptorWrite(gatt, descriptor, status);
            Log.e(TAG, "onDescriptorWrite");
        }

        @SuppressLint("MissingPermission")
        @Override
        public void onServicesDiscovered(BluetoothGatt gatt, int status) {
            super.onServicesDiscovered(gatt, status);
            Log.e(TAG, "onServiceDiscovered status = " + status);
            mBtService = gatt.getService(UUID_SERVICE);
            mBtChar = mBtService.getCharacteristic(UUID_NOTIFY);
        }
    };

    public static void startActivity(Context context, BluetoothDevice device) {
        Intent intent = new Intent(context, CarCtrlActivity.class);
        intent.putExtra(EXTRA_BT_ADDR, device.getAddress());
        context.startActivity(intent);
    }

    @SuppressLint("MissingPermission")
    private void sendCmd(String cmd) {
        if (mBtChar != null) {
            mBtChar.setValue(cmd);
            mBtGatt.writeCharacteristic(mBtChar);
            Log.e(TAG, "sendCmd done cmd = " + cmd);
        } else {
            Log.e(TAG, "sendCmd mBtChar is null");
        }
    }

    View.OnTouchListener mTouchListener = new View.OnTouchListener() {
        @Override
        public boolean onTouch(View v, MotionEvent event) {
            boolean down = event.getAction() == MotionEvent.ACTION_DOWN || event.getAction() == MotionEvent.ACTION_MOVE;
            boolean checkTurn = false;
            boolean checkMove = false;
            int vid = v.getId();
            if (vid == R.id.btn_left) {
                mTurnLeft = down;
                checkTurn = true;
            } else if (vid == R.id.btn_right) {
                mTurnRight = down;
                checkTurn = true;
            } else if (vid == R.id.btn_go) {
                mGo = down;
                checkMove = true;
            } else if (vid == R.id.btn_back) {
                mBack = down;
                checkMove = true;
            }

            StringBuilder text = new StringBuilder();
            if (mTurnLeft) {
                if (mTurnState != TURN_STATE_LEFT) {
                    sendCmd("1");
                }
                text.append("左转");
                mTurnState = TURN_STATE_LEFT;
            } else if (mTurnRight) {
                if (mTurnState != TURN_STATE_RIGHT) {
                    sendCmd("2");
                }
                text.append("右转");
                mTurnState = TURN_STATE_RIGHT;
            } else if (checkTurn) {
                sendCmd("0");
                mTurnState = TURN_STATE_BACK;
            }

            if (mGo) {
                if (mMoveState != MOVE_STATE_GO) {
                    sendCmd("3");
                }
                text.append("向前");
                mMoveState = MOVE_STATE_GO;
            } else if (mBack) {
                if (mMoveState != MOVE_STATE_BACK) {
                    sendCmd("4");
                }
                text.append("向后");
                mMoveState = MOVE_STATE_BACK;
            } else if (checkMove) {
                sendCmd("5");
                mMoveState = MOVE_STATE_STOP;
            }

            mTxvCarState.setText(text.toString());
            return true;
        }
    };
}

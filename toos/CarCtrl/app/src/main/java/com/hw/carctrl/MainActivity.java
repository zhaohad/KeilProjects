package com.hw.carctrl;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.BaseAdapter;
import android.widget.ListView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import java.util.ArrayList;

public class MainActivity extends Activity {
    private static final String TAG = App.getTag(MainActivity.class);
    private ListView mLsvBt;
    private BtListAdapter mLsvAdapter;

    @SuppressLint("MissingInflatedId")
    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Log.e(TAG, "onCreate");

        PermissionUtils.checkPermissions(this, true);

        setContentView(R.layout.main_activity);

        mLsvAdapter = new BtListAdapter();
        mLsvBt = findViewById(R.id.lsv_bt);
        mLsvBt.setAdapter(mLsvAdapter);
        registerBTReceiver();
        mLsvBt.setOnItemClickListener(mItemClickListener);
    }

    @SuppressLint("MissingPermission")
    @Override
    protected void onResume() {
        super.onResume();
        if (!PermissionUtils.checkPermissions(this, false)) {
            return;
        }

        mLsvAdapter.datas.clear();

        BluetoothAdapter btAdapter = App.getBTAdapter();
        btAdapter.cancelDiscovery();
        Log.e(TAG, "startDiscovery");
        btAdapter.startDiscovery();
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        if (!PermissionUtils.checkPermissions(this, false)) {
            finish();
        }
    }

    private void registerBTReceiver() {
        IntentFilter filter = new IntentFilter();
        filter.addAction(BluetoothAdapter.ACTION_DISCOVERY_STARTED);
        filter.addAction(BluetoothAdapter.ACTION_DISCOVERY_FINISHED);
        filter.addAction(BluetoothDevice.ACTION_FOUND);
        registerReceiver(mBTReceiver, filter);
    }

    private BroadcastReceiver mBTReceiver = new BroadcastReceiver() {
        @SuppressLint("MissingPermission")
        @Override
        public void onReceive(Context context, Intent intent) {
            String action = intent.getAction();
            Log.e(TAG, "onReceive action = " + action);
            switch (action) {
                case BluetoothAdapter.ACTION_DISCOVERY_STARTED:
                    break;
                case BluetoothAdapter.ACTION_DISCOVERY_FINISHED:
                    break;
                case BluetoothDevice.ACTION_FOUND: {
                    Bundle data = intent.getExtras();
                    BluetoothDevice btDevice = (BluetoothDevice) data.get(BluetoothDevice.EXTRA_DEVICE);
                    // BluetoothClass btClass = (BluetoothClass) data.get(BluetoothDevice.EXTRA_CLASS);
                    mLsvAdapter.addItem(btDevice);
                    break;
                }
            }
        }
    };

    private AdapterView.OnItemClickListener mItemClickListener = new AdapterView.OnItemClickListener() {
        @SuppressLint("MissingPermission")
        @Override
        public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
            BluetoothDevice device = mLsvAdapter.getItem(position);
            CarCtrlActivity.startActivity(MainActivity.this, device);
            App.getBTAdapter().cancelDiscovery();
        }
    };

    private class BtListAdapter extends BaseAdapter {
        ArrayList<BluetoothDevice> datas;

        BtListAdapter() {
            datas = new ArrayList<>();
        }

        @SuppressLint("MissingPermission")
        void addItem(BluetoothDevice device) {
            if (TextUtils.isEmpty(device.getName())) {
                return;
            }

            boolean found = false;
            for (BluetoothDevice d : datas) {
                if (d.getAddress().equals(device.getAddress())) {
                    found = true;
                    break;
                }
            }

            if (!found) {
                datas.add(device);
                notifyDataSetChanged();
            }
        }

        @Override
        public int getCount() {
            return datas.size();
        }

        @Override
        public BluetoothDevice getItem(int position) {
            if (position >= datas.size()) {
                return null;
            }
            return datas.get(position);
        }

        @Override
        public long getItemId(int position) {
            return position;
        }

        @SuppressLint("MissingPermission")
        @Override
        public View getView(int position, View convertView, ViewGroup parent) {
            ViewHolder vh;
            BluetoothDevice btDevice;
            if (convertView == null) {
                LayoutInflater inflater = getLayoutInflater();
                convertView = inflater.inflate(R.layout.bt_device_view, mLsvBt, false);
                vh = new ViewHolder();
                vh.txvName = convertView.findViewById(R.id.txv_name);
                vh.txvAddr = convertView.findViewById(R.id.txv_addr);
                convertView.setTag(vh);
            } else {
                vh = (ViewHolder) convertView.getTag();
            }

            btDevice = getItem(position);
            vh.txvName.setText(btDevice.getName());
            vh.txvAddr.setText(btDevice.getAddress());
            return convertView;
        }

        private class ViewHolder {
            TextView txvName;
            TextView txvAddr;
        }
    }
}

package com.led.led;

import android.app.ProgressDialog;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Context;
import android.content.Intent;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import java.io.IOException;
import java.util.UUID;


public class ledControl extends ActionBarActivity implements SensorEventListener {

    Button btnOn3,btnOff3,btnOn4,btnOff4,btnOn5,btnOff5,btnOn6,btnOff6,btnOn7,btnOff7;
    Button btnOn8,btnOff8,btnOn9,btnOff9,btnOn10,btnOff10,btnOn11,btnOff11,btnOn12,btnOff12,btnOn13,btnOff13,btnStart,btnStop;
    Button btnDis;
    //TextView lumn;
    String address = null;
    private ProgressDialog progress;
    BluetoothAdapter myBluetooth = null;
    BluetoothSocket btSocket = null;
    private boolean isBtConnected = false;
    //SPP UUID. Look for it
    static final UUID myUUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");


    //MOTION STARTS
    //private static final String TAG = ledControl.class.getSimpleName();
    private SensorManager mSensorManager;
    private Sensor mAccelerometer;
    TextView title,tv,tv1,tv2, tv3,tv4;
    //RelativeLayout layout;

    int xAxis = 0;
    int yAxis = 0;
    int pwmMax = 255;
    int xR = 5;
    int xMax = 7;
    int yMax = 5;
    int yThreshold = 50;
    int motorLeft = 0;
    int motorRight = 0;
    String commandLeft = "L";		// command symbol for left motor from settings (ñèìâîë êîìàíäû ëåâîãî äâèãàòåëÿ èç íàñòðîåê)
    String commandRight = "R";

    //MOTION ENDS

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        Intent newint = getIntent();
        address = newint.getStringExtra(DeviceList.EXTRA_ADDRESS); //receive the address of the bluetooth device

        //view of the ledControl
        setContentView(R.layout.activity_led_control);

        //call the widgtes
        btnOn3 = (Button) findViewById(R.id.btnOn3);
        btnOff3 = (Button) findViewById(R.id.btnOff3);
        btnOn4 = (Button) findViewById(R.id.btnOn4);
        btnOff4 = (Button) findViewById(R.id.btnOff4);
        btnOn5 = (Button) findViewById(R.id.btnOn5);
        btnOff5 = (Button) findViewById(R.id.btnOff5);
        btnOn6 = (Button) findViewById(R.id.btnOn6);
        btnOff6 = (Button) findViewById(R.id.btnOff6);
        btnOn7 = (Button) findViewById(R.id.btnOn7);
        btnOff7 = (Button) findViewById(R.id.btnOff7);
        btnOn8 = (Button) findViewById(R.id.btnOn8);
        btnOff8 = (Button) findViewById(R.id.btnOff8);
        btnOn9 = (Button) findViewById(R.id.btnOn9);
        btnOff9 = (Button) findViewById(R.id.btnOff9);
        btnOn10 = (Button) findViewById(R.id.btnOn10);
        btnOff10 = (Button) findViewById(R.id.btnOff10);
        btnOn11 = (Button) findViewById(R.id.btnOn11);
        btnOff11 = (Button) findViewById(R.id.btnOff11);
        btnOn12 = (Button) findViewById(R.id.btnOn12);
        btnOff12 = (Button) findViewById(R.id.btnOff12);
        btnOn13 = (Button) findViewById(R.id.btnOn13);
        btnOff13 = (Button) findViewById(R.id.btnOff13);
        btnStart = (Button) findViewById(R.id.btnStart);
        btnStop = (Button) findViewById(R.id.btnStop);
        btnDis = (Button) findViewById(R.id.btnDis);

        //MOTION START
        //get the sensor service

        mSensorManager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);
        //get the accelerometer sensor
        mAccelerometer = mSensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
        //get layout


        //MOTION END


        new ConnectBT().execute(); //Call the class to connect


        btnDis.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Disconnect(); //close connection
            }
        });
        btnOn3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                funOn3(); //close connection
            }
        });
        btnOff3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                funOff3(); //close connection
            }
        });
        btnOn4.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                funOn4(); //close connection
            }
        });
        btnOff4.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                funOff4(); //close connection
            }
        });
        btnOn5.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                funOn5(); //close connection
            }
        });
        btnOff5.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                funOff5(); //close connection
            }
        });
        btnOn6.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                funOn6(); //close connection
            }
        });
        btnOff6.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                funOff6(); //close connection
            }
        });
        btnOn7.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                funOn7(); //close connection
            }
        });
        btnOff7.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                funOff7(); //close connection
            }
        });
        btnOn8.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                funOn8(); //close connection
            }
        });
        btnOff8.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                funOff8(); //close connection
            }
        });
        btnOn9.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                funOn9(); //close connection
            }
        });
        btnOff9.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                funOff9(); //close connection
            }
        });
        btnOn10.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                funOn10(); //close connection
            }
        });
        btnOff10.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                funOff10(); //close connection
            }
        });
        btnOn11.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                funOn11(); //close connection
            }
        });
        btnOff11.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                funOff11(); //close connection
            }
        });
        btnOn12.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                funOn12(); //close connection
            }
        });
        btnOff12.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                funOff12(); //close connection
            }
        });
        btnOn13.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                funOn13(); //close connection
            }
        });
        btnOff13.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                funOff13(); //close connection
            }
        });
        btnStart.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                funStart(); //close connection
            }
        });
        btnStop.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                funStop(); //close connection
            }
        });

    }


    private void Disconnect()
    {
        if (btSocket!=null) //If the btSocket is busy
        {
            try
            {
                btSocket.close(); //close connection
            }
            catch (IOException e)
            { msg("Error");}
        }
        finish(); //return to the first layout

    }



    private void funOn3()
    {
        if (btSocket!=null)
        {
            try
            {
                btSocket.getOutputStream().write("on3:".toString().getBytes());
                Toast.makeText(this,"on3",Toast.LENGTH_LONG).show();
            }
            catch (IOException e)
            {
                msg("Error");
                Toast.makeText(this,"error3",Toast.LENGTH_LONG).show();
            }
        }
    }

    private void funOff3()
    {
        if (btSocket!=null)
        {
            try
            {
                btSocket.getOutputStream().write("off3:".toString().getBytes());
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
    }


    private void funOn4()
    {
        if (btSocket!=null)
        {
            try
            {
                btSocket.getOutputStream().write("on4:".toString().getBytes());
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
    }

    private void funOff4()
    {
        if (btSocket!=null)
        {
            try
            {
                btSocket.getOutputStream().write("off4:".toString().getBytes());
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
    }

    private void funOn5()
    {
        if (btSocket!=null)
        {
            try
            {
                btSocket.getOutputStream().write("on5:".toString().getBytes());
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
    }

    private void funOff5()
    {
        if (btSocket!=null)
        {
            try
            {
                btSocket.getOutputStream().write("off5:".toString().getBytes());
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
    }

    private void funOn6()
    {
        if (btSocket!=null)
        {
            try
            {
                btSocket.getOutputStream().write("on6:".toString().getBytes());
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
    }

    private void funOff6()
    {
        if (btSocket!=null)
        {
            try
            {
                btSocket.getOutputStream().write("off6:".toString().getBytes());
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
    }

    private void funOn7()
    {
        if (btSocket!=null)
        {
            try
            {
                btSocket.getOutputStream().write("on7:".toString().getBytes());
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
    }

    private void funOff7()
    {
        if (btSocket!=null)
        {
            try
            {
                btSocket.getOutputStream().write("off7:".toString().getBytes());
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
    }

    private void funOn8()
    {
        if (btSocket!=null)
        {
            try
            {
                btSocket.getOutputStream().write("on8:".toString().getBytes());
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
    }

    private void funOff8()
    {
        if (btSocket!=null)
        {
            try
            {
                btSocket.getOutputStream().write("off8:".toString().getBytes());
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
    }

    private void funOn9()
    {
        if (btSocket!=null)
        {
            try
            {
                btSocket.getOutputStream().write("on9:".toString().getBytes());
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
    }


    private void funOff9()
    {
        if (btSocket!=null)
        {
            try
            {
                btSocket.getOutputStream().write("off9:".toString().getBytes());
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
    }
    private void funOn10()
    {
        if (btSocket!=null)
        {
            try
            {
                btSocket.getOutputStream().write("on10:".toString().getBytes());
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
    }
    private void funOff10()
    {
        if (btSocket!=null)
        {
            try
            {
                btSocket.getOutputStream().write("off10:".toString().getBytes());
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
    }

    private void funOn11()
    {
        if (btSocket!=null)
        {
            try
            {
                btSocket.getOutputStream().write("on11:".toString().getBytes());
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
    }

    private void funOff11()
    {
        if (btSocket!=null)
        {
            try
            {
                btSocket.getOutputStream().write("off11:".toString().getBytes());
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
    }

    private void funOn12()
    {
        if (btSocket!=null)
        {
            try
            {
                btSocket.getOutputStream().write("on12:".toString().getBytes());
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
    }

    private void funOff12()
    {
        if (btSocket!=null)
        {
            try
            {
                btSocket.getOutputStream().write("off12:".toString().getBytes());
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
    }

    private void funOn13()
    {
        if (btSocket!=null)
        {
            try
            {
                btSocket.getOutputStream().write("on13:".toString().getBytes());
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
    }

    private void funOff13()
    {
        if (btSocket!=null)
        {
            try
            {
                btSocket.getOutputStream().write("off13:".toString().getBytes());
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
    }

    private void funStart()
    {
        if (btSocket!=null)
        {
            try
            {
                btSocket.getOutputStream().write("start:".toString().getBytes());
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
    }

    private void funStop()
    {
        if (btSocket!=null)
        {
            try
            {
                btSocket.getOutputStream().write("stop:".toString().getBytes());
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
    }





    private void sendMotor(String cmdSendLR)
    {
        if (btSocket!=null)
        {
            try
            {
                btSocket.getOutputStream().write(cmdSendLR.getBytes());
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
    }

    // fast way to call Toast
    private void msg(String s)
    {
        Toast.makeText(getApplicationContext(),s,Toast.LENGTH_LONG).show();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_led_control, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }

    private class ConnectBT extends AsyncTask<Void, Void, Void>  // UI thread
    {
        private boolean ConnectSuccess = true; //if it's here, it's almost connected

        @Override
        protected void onPreExecute()
        {
            progress = ProgressDialog.show(ledControl.this, "Connecting...", "Please wait!!!");  //show a progress dialog
        }

        @Override
        protected Void doInBackground(Void... devices) //while the progress dialog is shown, the connection is done in background
        {
            try
            {
                if (btSocket == null || !isBtConnected)
                {
                 myBluetooth = BluetoothAdapter.getDefaultAdapter();//get the mobile bluetooth device
                 BluetoothDevice dispositivo = myBluetooth.getRemoteDevice(address);//connects to the device's address and checks if it's available
                 btSocket = dispositivo.createInsecureRfcommSocketToServiceRecord(myUUID);//create a RFCOMM (SPP) connection
                 BluetoothAdapter.getDefaultAdapter().cancelDiscovery();
                 btSocket.connect();//start connection
                }
            }
            catch (IOException e)
            {
                ConnectSuccess = false;//if the try failed, you can check the exception here
            }
            return null;
        }
        @Override
        protected void onPostExecute(Void result) //after the doInBackground, it checks if everything went fine
        {
            super.onPostExecute(result);

            if (!ConnectSuccess)
            {
                msg("Connection Failed. Is it a SPP Bluetooth? Try again.");
                finish();
            }
            else
            {
                msg("Connected.");
                isBtConnected = true;
            }
            progress.dismiss();
        }
    }

    //MOTION STARTS
    @Override
    public final void onAccuracyChanged(Sensor sensor, int accuracy)
    {
        // Do something here if sensor accuracy changes.
    }

    @Override
    public final void onSensorChanged(SensorEvent event)
    {    /*
        float x, y, z = 0;
        String directionL = "";
        String directionR = "";
        String cmdSendL,cmdSendR;

        WindowManager windowMgr = (WindowManager)this.getSystemService(WINDOW_SERVICE);
        int rotationIndex = windowMgr.getDefaultDisplay().getRotation();
        if (rotationIndex == 1 || rotationIndex == 3){			// detect 90 or 270 degree rotation (îïðåäåëÿåì ïîâîðîò óñòðîéñòâà íà 90 èëè 270 ãðàäóñîâ)
            x = -event.values[1];
            y = event.values[0];
        }
        else{
            x = event.values[0];            //Force x axis in m s-2
            y = event.values[1];      	   //Force y axis in m s-2
        }

        // Many sensors return 3 values, one for each axis.
        tv.setText("X axisz" +"\t\t"+x);
        tv1.setText("Y axis" + "\t\t" +y);
        tv2.setText("Z axis" +"\t\t" +z);

        xAxis = Math.round(x*pwmMax/xR);             //pwmMax = 255      xR = 5
        yAxis = Math.round(y*pwmMax/yMax);           //yMax = 5
        //both equal straight at this point
        if(xAxis > pwmMax) xAxis = pwmMax;           // set max
        else if(xAxis < -pwmMax) xAxis = -pwmMax;      //  and -max values
        if(yAxis > pwmMax) yAxis = pwmMax;              //  dito
        else if(yAxis < -pwmMax) yAxis = -pwmMax;		//  dito       negative - tilt forward
        else if(yAxis >= 0 && yAxis < yThreshold) yAxis = 0;    //Threshold=50  //roughly 20degrees before it moves
        else if(yAxis < 0 && yAxis > -yThreshold) yAxis = 0;

        if(xAxis > 0) {		// if tilt to left, slow down the left engine
            motorRight = yAxis;
            if(Math.abs(Math.round(x)) > xR){       //xR = 5 is 45 degrees
                motorLeft = Math.round((x-xR)*pwmMax/(xMax-xR));
                motorLeft = Math.round(-motorLeft * yAxis/pwmMax);
                //if(motorLeft < -pwmMax) motorLeft = -pwmMax;
            }
            else motorLeft = yAxis - yAxis*xAxis/pwmMax; // tilt less than 45 degrees
        }
        else if(xAxis < 0) {		// tilt to right (íàêëîí âïðàâî)
            motorLeft = yAxis;
            if(Math.abs(Math.round(x)) > xR){
                motorRight = Math.round((Math.abs(x)-xR)*pwmMax/(xMax-xR));
                motorRight = Math.round(-motorRight * yAxis/pwmMax);
                //if(motorRight > -pwmMax) motorRight = -pwmMax;
            }
            else motorRight = yAxis - yAxis*Math.abs(xAxis)/pwmMax;
        }
        else if(xAxis == 0) {       //Straight back/ forwards
            motorLeft = yAxis;
            motorRight = yAxis;
        }

        if(motorLeft > 0) {			// tilt to backward (íàêëîí íàçàä)
            directionL = "-";
        }
        if(motorRight > 0) {		// tilt to backward (íàêëîí íàçàä)
            directionR = "-";
        }
        motorLeft = Math.abs(motorLeft);
        motorRight = Math.abs(motorRight);

        if(motorLeft > pwmMax) motorLeft = pwmMax;
        if(motorRight > pwmMax) motorRight = pwmMax;

        cmdSendL = String.valueOf(commandLeft+directionL+motorLeft+":");
        cmdSendR = String.valueOf(commandRight+directionR+motorRight+":");

        tv3.setText("cmdSendL" +"\t\t" +cmdSendL);
        tv4.setText("cmdSendR" +"\t\t" +cmdSendR);
        if (isBtConnected) {
            sendMotor(cmdSendL);
            sendMotor(cmdSendR);
            try {
                Thread.sleep(50);                 //1000 milliseconds is one second.
            } catch(InterruptedException ex) {
                Thread.currentThread().interrupt();
            }
        }
          */
    }

    protected void onResume() {
        super.onResume();
        mSensorManager.registerListener(this, mAccelerometer, SensorManager.SENSOR_DELAY_NORMAL);
    }
    protected void onPause() {
        super.onPause();
        mSensorManager.unregisterListener(this);
    }
        //MOTION ENDS
}

package bl173214m.m2m.etf.bg.ac.rs.whatsmytemp;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import junit.framework.Test;

import bl173214m.m2m.etf.bg.ac.rs.whatsmytemp.utils.HTTPReqHelperTask;

public class TempDisplay extends AppCompatActivity {

    public static final String TAG = "TempDisplay Activity:";
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Log.d(TAG,"onCreate started");
        setContentView(R.layout.activity_temp_display);
        System.out.print("Hello");
        final Button button = findViewById(R.id.button);
        if (button != null) {
            button.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    final TextView textBox = findViewById(R.id.msg);
                    if(textBox != null) {
                        Log.d(TAG, "clicked");
                        Log.d(TAG, "Starting the Network test.");
                        TestNetworkHelper("http://192.168.1.100:3000/measurements", 8080);

                        textBox.setText("a");

                        Log.d(TAG, "done");
                    }
                }
            });
        }
    }

    private Boolean TestNetworkHelper(String adr, int port) {

        HTTPReqHelperTask t = new HTTPReqHelperTask(adr, port);
        Object res = null;
        try {
            t.execute();
            res = t.get();
        }catch (Exception e) {
            Log.e(TAG, "TestNetworkHelper: Something went wrong!");
        }

        if(res == null) {
            Log.d(TAG, "TestNetworkHelper: Sorry man, couldn't do it.");
            return false;
        }
        else {
            Log.d(TAG, "TestNetworkHelper: SUCCESS! Here's the result:");
            Log.d(TAG, (String)res);
        }
        return true;
    }
}

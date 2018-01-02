package bl173214m.m2m.etf.bg.ac.rs.whatsmytemp;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import junit.framework.Test;

import bl173214m.m2m.etf.bg.ac.rs.whatsmytemp.utils.HTTPReqHelper;

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
                        HTTPReqHelper t = new HTTPReqHelper();
                        t.execute();
                        textBox.setText("a");

                        Log.d(TAG, "done");
                    }
                }
            });
        }
    }
}

package bl173214m.m2m.etf.bg.ac.rs.whatsmytemp;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import com.jjoe64.graphview.GraphView;
import com.jjoe64.graphview.series.DataPoint;
import com.jjoe64.graphview.series.LineGraphSeries;

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
                        Log.d(TAG, "clicked");
                        Log.d(TAG, "Starting the Network test.");
                       // TestNetworkHelper("http://192.168.1.101:3000/measurements");
                        initGraph();
                        Log.d(TAG, "done");
                }
            });
        }
    }

    public void initGraph(){
        GraphView graph = (GraphView) findViewById(R.id.graph);
        LineGraphSeries<DataPoint> series = new LineGraphSeries<>(new DataPoint[] {
                new DataPoint(0, 1),
                new DataPoint(1, 5),
                new DataPoint(2, 3),
                new DataPoint(3, 2),
                new DataPoint(4, 6)
        });
        graph.addSeries(series);
    }

    private Boolean TestNetworkHelper(String adr) {

        HTTPReqHelperTask t = new HTTPReqHelperTask(adr);
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

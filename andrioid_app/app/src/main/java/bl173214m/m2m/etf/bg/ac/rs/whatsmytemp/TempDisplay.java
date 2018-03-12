package bl173214m.m2m.etf.bg.ac.rs.whatsmytemp;

import android.graphics.Color;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.TextView;

import com.github.mikephil.charting.charts.BarChart;
import com.github.mikephil.charting.data.BarData;
import com.github.mikephil.charting.data.BarDataSet;
import com.github.mikephil.charting.data.BarEntry;
import com.github.mikephil.charting.data.Entry;
import com.github.mikephil.charting.data.LineDataSet;
import com.jjoe64.graphview.GraphView;
import com.jjoe64.graphview.helper.DateAsXAxisLabelFormatter;
import com.jjoe64.graphview.series.DataPoint;
import com.jjoe64.graphview.series.LineGraphSeries;
import com.jjoe64.graphview.series.PointsGraphSeries;

import junit.framework.Test;

import org.json.JSONArray;

import java.net.URL;
import java.util.ArrayList;
import java.util.List;

import bl173214m.m2m.etf.bg.ac.rs.whatsmytemp.utils.GraphHelper;
import bl173214m.m2m.etf.bg.ac.rs.whatsmytemp.utils.HTTPReqHelperTask;

public class TempDisplay extends AppCompatActivity {

    protected BarChart m_BarChart;
    protected final String m_Address = "http://checkmytemp.fr.openode.io//measurements";
    public static final String TAG = "TempDisplay Activity:";

    protected void onCreate() {

        super.onCreate(null);
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
                    JSONArray array = getDataFromServer(m_Address);
                    GraphHelper.TempGraphDataPoint[] data =
                            GraphHelper.JSONToCoordinats(array, array.length());
                    PlotGraph(data);
                    Log.d(TAG, "done");
                }
            });
        }
    }

    private JSONArray getDataFromServer(String adr) {
        HTTPReqHelperTask t;
        JSONArray res = null;
        try {
            t = new HTTPReqHelperTask(new URL(adr));
            t.execute();
            res = (JSONArray) t.get();
        }catch (Exception e) {
            Log.e(TAG, "TestNetworkHelper: Something went wrong!");
            return  null;
        }

        if(res == null) {
            Log.d(TAG, "TestNetworkHelper: Sorry man, couldn't do it.");
            return null;
        }
        else {
            Log.d(TAG, "TestNetworkHelper: SUCCESS! Here's the result:");
            Log.d(TAG, ((JSONArray)res).toString());
        }
        return res;
    }

    private void PlotGraph(GraphHelper.TempGraphDataPoint[] aCoordinates) {
        GraphView graph = (GraphView) findViewById(R.id.chart);

        List<BarEntry> entries = new ArrayList<BarEntry>();

        for (GraphHelper.TempGraphDataPoint data: aCoordinates)
            entries.add(new BarEntry(data.x.getTime(),(float) data.y));

        BarDataSet dataSet = new BarDataSet(entries, "Label"); // add entries to dataset
        dataSet.setColor(Color.parseColor("red"));

        BarData lineData = new BarData(dataSet);
        m_BarChart.setData(lineData);
        m_BarChart.invalidate(); // refresh
    }

    /*
    private Boolean TestNetworkHelper(String adr) {

        HTTPReqHelperTask t;
        Object res = null;
        try {
            t = new HTTPReqHelperTask(new URL(adr));
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
*/
}

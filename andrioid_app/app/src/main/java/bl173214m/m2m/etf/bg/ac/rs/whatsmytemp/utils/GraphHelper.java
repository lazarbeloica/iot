package bl173214m.m2m.etf.bg.ac.rs.whatsmytemp.utils;

import android.util.JsonToken;
import android.util.Log;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.lang.reflect.Array;
import java.util.Date;

/**
 * Created by aviator on 1/6/18.
 */

public final class GraphHelper {
    public static String TAG = "GraphHelper";

    public  class TempGraphDataPoint {
        public double y;
        public Date x;

        TempGraphDataPoint(Date aDate, double aTemp) {
            x= aDate;
            y = aTemp;
        }

    }

    public static TempGraphDataPoint[] JSONToCoordinats(JSONArray aInput, int aNum) {

        if (aNum <=0 || aInput == null) {
            Log.e(TAG, "Invalid arguments. ABORTING!");
            return null;
        }

        TempGraphDataPoint[] result = new TempGraphDataPoint[(aInput.length() < aNum) ? aInput.length() : aNum];
        for(int i = 0; i < aInput.length() && i < aNum; i++) {
            JSONObject curr = (JSONObject) aInput.remove(0);
            try {
                Double val = (Double) curr.get("value");
                Log.d(TAG, "Got the value = " + val);
                Date date = (Date) curr.get("Date");
                Log.d(TAG, "Got the date = " + date);
                result[i].x = date;
                result[i].y = val;
            } catch (JSONException e) {
                e.printStackTrace();
                Log.e(TAG, "Something went wrong with parsing JSON!");
                return  null;
            }
        }
        return result;
    }
}





















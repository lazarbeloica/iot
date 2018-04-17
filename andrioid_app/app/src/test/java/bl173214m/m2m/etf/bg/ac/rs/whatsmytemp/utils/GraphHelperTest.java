package bl173214m.m2m.etf.bg.ac.rs.whatsmytemp.utils;

/**
 * Created by aviator on 3/24/18.
 */

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;
import org.junit.Test;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Date;

import static org.junit.Assert.*;


//NOTE: Can't test this; Problem with JSON adn UnitTests
public class GraphHelperTest {

    private SimpleDateFormat format = null;

    public GraphHelperTest() {
        format = new SimpleDateFormat("yyyy-MM-dd'T'hh:mm'Z'");
    }

 //   @Test
//    public void JSONToCoordinatsTest() {
//        //creating the test example
//        JSONArray array = new JSONArray();
//        ArrayList<TempGraphDataPoint> expectedRes = new ArrayList<TempGraphDataPoint>();
//        Date d1 = null;
//        Date d2 = null;
//        Date d3 = null;
//        Date d6 = null;
//        Date d4 = null;
//        Date d5 = null;
//
//        double v1 = -1;
//        double v2 = 0;
//        double v3 = 1;
//        double v4 = 2;
//        double v5 = 1589;
//        double v6 = 35;
//
//        try {
//            d1 = format.parse("2012-03-19T07:22Z");
//            d2 = format.parse("2012-02-19T07:22Z");
//            d3 = format.parse("2012-01-19T07:22Z");
//            d6 = format.parse("2014-03-19T07:22Z");
//            d4 = format.parse("2012-05-19T07:22Z");
//            d5 = format.parse("2017-03-19T07:22Z");
//        } catch (ParseException e) {
//            e.printStackTrace();
//            assertTrue("Something went wrong with the test!", true);
//        }
//
//        expectedRes.add(new TempGraphDataPoint( d1, 1));
//        expectedRes.add(new TempGraphDataPoint( d2, 2));
//        expectedRes.add(new TempGraphDataPoint( d3, 3));
//        expectedRes.add(new TempGraphDataPoint( d6, 4));
//        expectedRes.add(new TempGraphDataPoint( d4, 5));
//        expectedRes.add(new TempGraphDataPoint( d5, 6));
//
//        JSONObject json = null;
//        try {
//            json = new JSONObject();
//            json.put("value", v1);
//            json.put("Created_date", d1);
//            array.put(json);
//
//            json = new JSONObject();
//            json.put("value", v2);
//            json.put("Created_date", d2);
//            array.put(json);
//
//            json = new JSONObject();
//            json.put("value", v3);
//            json.put("Created_date", d3);
//            array.put(json);
//
//            json = new JSONObject();
//            json.put("value", v4);
//            json.put("Created_date", d4);
//            array.put(json);
//
//             json = new JSONObject();
//             json.put("value", v5);
//             json.put("Created_date", d5);
//             array.put(json);
//
//            json = new JSONObject();
//            json.put("value", v6);
//            json.put("Created_date", d6);
//            array.put(json);
//        } catch (JSONException e) {
//            e.printStackTrace();
//            assertTrue("Something went wrong with the test", true);
//        }
//
//        //running the test
//        ArrayList<TempGraphDataPoint> res = GraphHelper.JSONToCoordinats(array);
// //       Arrays.sort(expectedRes);
//   //     assertArrayEquals(expectedRes, res);
//    }

}

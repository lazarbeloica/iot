package bl173214m.m2m.etf.bg.ac.rs.whatsmytemp.utils;

import android.os.AsyncTask;
import android.util.Log;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URI;
import java.net.URL;

/**
 * Created by aviator on 12/27/17.
 */

public class HTTPReqHelperTask extends AsyncTask {

    public static final String TAG = "HTTPReqHelper";

    private String address = null;

    public HTTPReqHelperTask(String address) {
        this.address = address;
    }

    public Object doInBackground(Object [] params) {
        URL url = null;
        URI uri = null;
        InputStream stream = null;
        HttpURLConnection connection = null;
        String response = null;
        JSONArray jArray = null;

        //Connecting to the server
        try {
            url = new URL(address);
            uri = URI.create(address);

            Log.d(TAG, "Establishing connection...");
            connection = (HttpURLConnection) url.openConnection();
            Log.d(TAG, "setReadTimeout = 3000");
            connection.setReadTimeout(3000);
            Log.d(TAG, "setConnectTimeout = 3000");
            connection.setConnectTimeout(3000);
            Log.d(TAG, "Setting request method to GET");
            connection.setRequestMethod("GET");
            Log.d(TAG, "Setting doInput to true");
            connection.setDoInput(true);


            Log.d(TAG, "Connecting...");
            connection.connect();
            Log.d(TAG, "Connected");

            int responseCode = connection.getResponseCode();
            if(responseCode != HttpURLConnection.HTTP_OK){
                Log.e(TAG, "ERROR: Got a bad HTTP code! Got: " + responseCode);
                return null;
            }

            Log.d(TAG, "Getting the input stream...");
            stream = connection.getInputStream();
            Log.d(TAG, "Got the stream!");

            if(stream != null) {
                BufferedReader br = new BufferedReader(new InputStreamReader(stream,"UTF-8"));
                StringBuilder sb = new StringBuilder();

                String line = null;
                while ((line = br.readLine()) != null) {
                    sb.append(line + "\n");
                }

                response = sb.toString();
            }
            else {
                Log.e(TAG, "Could not create a stream!");
                return null;
            }

        } catch (IOException e) {
            e.printStackTrace();
            Log.e(TAG, "An ERROR with the network occurred! Couldn't get the measurements.");
            return null;
        }finally {
            if(stream != null){
                try {
                    stream.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            if(connection != null){
                Log.d(TAG, "Disconnecting...");
                connection.disconnect();
            }
        }

        //Parsing the result
        if (response != null) {
            try {
                Log.d(TAG, "Trying to parse the response...");
                jArray = new JSONArray(response);
                Log.d(TAG, "JSON array extracted.");
            } catch (JSONException e) {
                Log.e(TAG, "Couldn't extract JSON array!");
                e.printStackTrace();
                return  null;
            }
        }

        return jArray ;
    }
}













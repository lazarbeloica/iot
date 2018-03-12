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
import java.net.URI;
import java.net.URL;

/**
 * Created by aviator on 12/27/17.
 */

public class HTTPReqHelperTask extends AsyncTask {

    public static final String TAG = "HTTPReqHelper";
    private final int defaultTimeout = 3000;

    private URL url = null;
    private HttpURLConnection connection = null;

    private InputStream stream = null;

    public HTTPReqHelperTask(URL url)
    {
        this.url = url;
    }

    public HttpURLConnection getConnection()
    {
        return connection;
    }

    public void setConnection(HttpURLConnection connection)
    {
        this.connection = connection;
    }

    private void connectToServer() throws Exception
    {
        URI uri = null;

        Log.d(TAG, "Establishing connection...");
        connection = (HttpURLConnection) url.openConnection();

        Log.d(TAG, "setReadTimeout = " + defaultTimeout);
        connection.setReadTimeout(defaultTimeout);

        Log.d(TAG, "setConnectTimeout = " + defaultTimeout);
        connection.setConnectTimeout(defaultTimeout);

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
            throw new NoConnectionError("Couldnot establish the connection!");
        }
    }

    private void disconnectFromServer()
    {
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
        connection = null;
        stream = null;
    }

    private String getData() throws Exception
    {
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

            return sb.toString();
        }
        else {
            Log.e(TAG, "Could not create a stream!");
            throw new NoDataFromServerError("Couldnot establish the connection!");
        }
    }

    private JSONArray parseResponse(String response)
    {
        //Parsing the result
        JSONArray jArray = null;
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

    public Object doInBackground(Object [] params)
    {
        try {
            connectToServer();
            return parseResponse(getData());

        } catch (Exception e) {
            Log.e(TAG, "An ERROR with the network occurred! Couldn't get the measurements.");
            e.printStackTrace();
            return null;
        }finally {
            disconnectFromServer();
        }
    }
}













package bl173214m.m2m.etf.bg.ac.rs.whatsmytemp.utils;

import android.os.AsyncTask;
import android.util.Log;

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

public class HTTPReqHelper extends AsyncTask {

    public static final String TAG = "HTTPReqHelper";
/*
//    private HttpURLConnection connection = null;

    public HTTPReqHelper(String url) {
        serverUrl = url;
    }

    public void connectToServer(String uri) {
        if (serverUrl == null || uri == null) {
            Log.w(TAG, "Error occured. URL not provided.");
            connection =  null;
        }

        Log.d(TAG, "Connecting to " + serverUrl + uri);

        URL url = null;
        try {
            Log.d(TAG, "Creating URL object for" + serverUrl + uri);
            url = new URL(serverUrl + uri);
        } catch (MalformedURLException e) {
            Log.d(TAG, "Failed to creat URL object");
            e.printStackTrace();
            connection =  null;
        }

        InputStream in;
        HttpURLConnection urlConnection = null;

        try {
            Log.d(TAG, "Establishing the connection...");
            connection = (HttpURLConnection) url.openConnection();
        } catch (IOException e) {
            Log.w(TAG, "Connection failed!");
            e.printStackTrace();
            connection = null;
        }
    }

    public void disconnect() {
        if (connection != null) {
            connection.disconnect();
            Log.d(TAG, "Connection terminated.");
        }
    }
*/
        private String address = "http://192.168.0.100/measurements";
        private int port = 8080;
        private String response = "";
        private String request = "";

        public Object doInBackground(Object [] params) {

            Log.d(TAG, "Invoking GetData");
        URL url = null;
        URI uri = null;
        InputStream stream = null;

        try {
            Log.d(TAG, "Creating URL object...");
            url = new URL(address);
        } catch (MalformedURLException e) {
            Log.e(TAG, "Error creating URL objecr");
            e.printStackTrace();
        }
            Log.d(TAG, "Creating URL object");
        uri = URI.create(address);

        HttpURLConnection connection = null;

        try {
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
                Log.e(TAG, "ERROR: Got a bad HTTP code!");
                throw new IOException();
            }

            Log.d(TAG, "Getting the input stream...");
            stream = connection.getInputStream();
            Log.d(TAG, "Got the stream!");
            if(stream != null){

                Log.d(TAG, "Creating a nerw input stream reader...");
                InputStreamReader reader = new InputStreamReader(stream,"UTF-8");
                Log.d(TAG, "Done!");
                char[] buffer = new char[500]; // Vrlo verovatno ce morati da se menja velicina niza

                int numChars = 0;
                int readSize = 0;

                while(numChars < 500 && readSize != -1 ){

                    numChars += readSize;
                    int pct = (100 * numChars) / 500;
                    readSize = reader.read(buffer,numChars,buffer.length - numChars);

                }

                if(numChars != -1){

                    numChars = Math.min(numChars,10000);
                    response = new String(buffer, 0 ,numChars);

                }

            }

        } catch (IOException e) {
            e.printStackTrace();
        }finally {
            if(stream != null){
                try {
                    stream.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            if(connection != null){

                connection.disconnect();

            }
        }
        return null;

    }

    public String getServerUrl() {
        return serverUrl;
    }

    public void setServerUrl(String serverUrl) {
        this.serverUrl = serverUrl;
    }

    private String serverUrl = null;

    public void Test() {
        Log.d(TAG, "Started Test");
        final String testServer =  "http://192.168.0.100";
        final String testURI = "/measurements";
        Log.d(TAG, "Setting server url to " + testServer);
   //     setServerUrl(testServer);
  //      connectToServer(testURI);
        //Log.d(TAG, "Posting GET to " + testServer + testURI);
         //   getData();
  //      Log.d(TAG, in.toString());
        Log.d(TAG, "Finished Test");
        //disconnect();
    }
}













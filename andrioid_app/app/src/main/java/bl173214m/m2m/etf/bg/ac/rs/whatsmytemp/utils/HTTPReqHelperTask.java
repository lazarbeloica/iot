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

public class HTTPReqHelperTask extends AsyncTask {

    public static final String TAG = "HTTPReqHelper";

    private String address = null;
    private int port;
    private String response = null;

    public HTTPReqHelperTask(String address, int port) {
        this.address = address;
        this.port = port;
    }

    public Object doInBackground(Object [] params) {

        Log.d(TAG, "Invoking GetData");
        URL url = null;
        URI uri = null;
        InputStream stream = null;

        try {
            Log.d(TAG, "Creating URL object...");
            url = new URL(address);
        } catch (MalformedURLException e) {
            Log.e(TAG, "Error creating URL object");
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
                Log.e(TAG, "ERROR: Got a bad HTTP code! Got: " + responseCode);
                throw new IOException();
            }

            Log.d(TAG, "Getting the input stream...");
            stream = connection.getInputStream();
            Log.d(TAG, "Got the stream!");
            if(stream != null) {
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
            else {
                Log.e(TAG, "Could not create a stream!");
                throw new IOException();
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
                Log.d(TAG, "Disconnecting...");
                connection.disconnect();
            }
        }
        return response;
    }
}













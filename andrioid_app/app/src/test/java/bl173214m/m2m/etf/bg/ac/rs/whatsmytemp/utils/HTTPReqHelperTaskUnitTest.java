package bl173214m.m2m.etf.bg.ac.rs.whatsmytemp.utils;

import android.net.Network;
import android.util.Log;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.Mock;
import org.mockito.runners.MockitoJUnitRunner;

import java.io.IOException;
import java.net.HttpURLConnection;
import java.net.URL;

import bl173214m.m2m.etf.bg.ac.rs.whatsmytemp.utils.HTTPReqHelperTask;
import bl173214m.m2m.etf.bg.ac.rs.whatsmytemp.utils.NoConnectionError;

import static org.junit.Assert.*;
import static org.mockito.Mockito.mock;
import static org.mockito.Mockito.when;

/**
 * Created by aviator on 3/6/18.
 */

@RunWith(MockitoJUnitRunner.class)
public class HTTPReqHelperTaskUnitTest {

    public static final String TAG = "HTTPReqHelperTaskUnitTest";

    @Test
    public void testBadAddress()
    {
    }
}

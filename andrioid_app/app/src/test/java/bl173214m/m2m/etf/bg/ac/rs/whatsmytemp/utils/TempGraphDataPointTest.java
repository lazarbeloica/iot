package bl173214m.m2m.etf.bg.ac.rs.whatsmytemp.utils;

import org.junit.Test;
import static org.junit.Assert.*;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;

/**
 * Created by aviator on 3/24/18.
 */

public class TempGraphDataPointTest {

    private SimpleDateFormat format;

    public TempGraphDataPointTest() {
        format = new SimpleDateFormat("yyyy-MM-dd'T'hh:mm:ss.sss'Z'");
    }

    @Test
    public void compareTempGraphDataPoint_first_is_grater() {

        Date date1 = null;
        Date date2 = null;
        try {
            date1 = format.parse("2018-01-16T09:18:37.574Z");
            date2 = format.parse("2017-01-16T09:18:37.574Z");
        } catch (ParseException e) {
            e.printStackTrace();
            assertTrue("Something went wrong wit the test", true);
        }

        TempGraphDataPoint first = new TempGraphDataPoint(date1, 1);
        TempGraphDataPoint second = new TempGraphDataPoint(date2, 1);

        assertTrue(first.compareTo(second) > 0);
    }

    @Test
    public void compareTempGraphDataPoint_second_is_grater() {

        Date date1 = null;
        Date date2 = null;
        try {
            date1 = format.parse("2017-01-16T09:18:37.574Z");
            date2 = format.parse("2018-01-16T09:18:37.574Z");
        } catch (ParseException e) {
            e.printStackTrace();
            assertTrue("Something went wrong wit the test", true);
        }

        TempGraphDataPoint first = new TempGraphDataPoint(date1, 1);
        TempGraphDataPoint second = new TempGraphDataPoint(date2, 1);

        assertTrue(first.compareTo(second) < 0);
    }

    @Test
    public void compareTempGraphDataPoint_first_is_grater1() {

        Date date1 = null;
        Date date2 = null;
        try {
            date1 = format.parse("2018-01-16T09:18:37.574Z");
            date2 = format.parse("2017-01-16T09:18:37.574Z");
        } catch (ParseException e) {
            e.printStackTrace();
            assertTrue("Something went wrong wit the test", true);
        }

        TempGraphDataPoint first = new TempGraphDataPoint(date1, -1);
        TempGraphDataPoint second = new TempGraphDataPoint(date2, 1);

        assertTrue(first.compareTo(second) > 0);
    }

    @Test
    public void compareTempGraphDataPoint_second_is_grater1() {

        Date date1 = null;
        Date date2 = null;
        try {
            date1 = format.parse("2017-01-16T09:18:37.574Z");
            date2 = format.parse("2018-01-16T09:18:37.574Z");
        } catch (ParseException e) {
            e.printStackTrace();
            assertTrue("Something went wrong wit the test", true);
        }

        TempGraphDataPoint first = new TempGraphDataPoint(date1, 1);
        TempGraphDataPoint second = new TempGraphDataPoint(date2, -1);

        assertTrue(first.compareTo(second) < 0);
    }

    @Test
    public void compareTempGraphDataPoint_equal() {

        Date date1 = null;
        Date date2 = null;
        try {
            date1 = format.parse("2018-01-16T09:18:37.574Z");
            date2 = format.parse("2018-01-16T09:18:37.574Z");
        } catch (ParseException e) {
            e.printStackTrace();
            assertTrue("Something went wrong wit the test", true);
        }

        TempGraphDataPoint first = new TempGraphDataPoint(date1, 1);
        TempGraphDataPoint second = new TempGraphDataPoint(date2, 1);

        assertTrue(first.compareTo(second) == 0);
    }

    @Test
    public void compareTempGraphDataPoint_equalDates_first_greater() {

        Date date1 = null;
        Date date2 = null;
        try {
            date1 = format.parse("2018-01-16T09:18:37.574Z");
            date2 = format.parse("2018-01-16T09:18:37.574Z");
        } catch (ParseException e) {
            e.printStackTrace();
            assertTrue("Something went wrong wit the test", true);
        }

        TempGraphDataPoint first = new TempGraphDataPoint(date1, 2);
        TempGraphDataPoint second = new TempGraphDataPoint(date2, -1);

        assertTrue(first.compareTo(second) > 0);
    }

    @Test
    public void compareTempGraphDataPoint_equalDates_second_greater() {

        Date date1 = null;
        Date date2 = null;
        try {
            date1 = format.parse("2018-01-16T09:18:37.574Z");
            date2 = format.parse("2018-01-16T09:18:37.574Z");
        } catch (ParseException e) {
            e.printStackTrace();
            assertTrue("Something went wrong wit the test", true);
        }

        TempGraphDataPoint first = new TempGraphDataPoint(date1, -1);
        TempGraphDataPoint second = new TempGraphDataPoint(date2, 12);

        assertTrue(first.compareTo(second) < 0);
    }
}

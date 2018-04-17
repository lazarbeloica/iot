package bl173214m.m2m.etf.bg.ac.rs.whatsmytemp.utils;

import android.support.annotation.NonNull;

import java.util.Date;

/**
 * Created by aviator on 1/6/18.
 */

public  class TempGraphDataPoint implements Comparable<TempGraphDataPoint> {
    public double y;
    public Date x;

    TempGraphDataPoint(Date aDate, double aTemp) {
        x= aDate;
        y = aTemp;
    }

    @Override
    public int compareTo(@NonNull TempGraphDataPoint o) {
        int res = this.x.compareTo(o.x);
        if (res == 0) {
            return (this.y < o.y) ? -1 : (this.y == o.y ? 0 : 1);
        }
        return res;
    }
}

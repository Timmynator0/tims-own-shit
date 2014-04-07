package com.eindopdracht.aws.data;

import android.content.Context;
import android.content.res.Resources;

import com.eindopdracht.aws.R;

public class DataSources {
    public static final int NUMBER_OF_DATA_SOURCES = 6;

    public static final int AIR_PRESSURE_INDEX = 0;
    public static final int HUMIDITY_INDEX = 1;
    public static final int RAIN_RATE_INDEX = 2;
    public static final int TEMPERATURE_INDEX = 3;
    public static final int WIND_DIRECTION_INDEX = 4;
    public static final int WIND_SPEED_INDEX = 5;

    private static final String AIR_PRESSURE_ID = "airpressure";
    private static final String HUMIDITY_ID = "hum";
    private static final String RAIN_RATE_ID = "rainrate";
    private static final String TEMPERATURE_ID = "temp";
    private static final String WIND_DIRECTION_ID = "winddir";
    private static final String WIND_SPEED_ID = "windspeed";

    public static String getUrlTitleFromIndex(final int index) {
        switch(index) {
            case AIR_PRESSURE_INDEX:
                return AIR_PRESSURE_ID;
            case HUMIDITY_INDEX:
                return HUMIDITY_ID;
            case RAIN_RATE_INDEX:
                return RAIN_RATE_ID;
            case TEMPERATURE_INDEX:
                return TEMPERATURE_ID;
            case WIND_DIRECTION_INDEX:
                return WIND_DIRECTION_ID;
            case WIND_SPEED_INDEX:
                return WIND_SPEED_ID;
        }
        return "";
    }

    public static String getNameFromIndex(final Context context, final int index) {
        final Resources res = context.getResources();
        switch(index) {
            case AIR_PRESSURE_INDEX:
                return res.getString(R.string.air_pressure);
            case HUMIDITY_INDEX:
                return res.getString(R.string.humidity);
            case RAIN_RATE_INDEX:
                return res.getString(R.string.rain_rate);
            case TEMPERATURE_INDEX:
                return res.getString(R.string.temperature);
            case WIND_DIRECTION_INDEX:
                return res.getString(R.string.wind_direction);
            case WIND_SPEED_INDEX:
                return res.getString(R.string.wind_speed);
        }
        return res.getString(R.string.unknown);
    }
}

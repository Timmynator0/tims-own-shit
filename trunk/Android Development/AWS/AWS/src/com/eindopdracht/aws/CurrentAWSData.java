package com.eindopdracht.aws;

public class CurrentAWSData {
    public final float airPressure;
    public final int hudidity;
    public final float rainRate;
    public final float temperature;
    public final int windDirection;
    public final float windSpeed;

    public CurrentAWSData(float airPressure, int hudidity, float rainRate, float temperature, int windDirection,
                          float windSpeed) {
        this.airPressure = airPressure;
        this.hudidity = hudidity;
        this.rainRate = rainRate;
        this.temperature = temperature;
        this.windDirection = windDirection;
        this.windSpeed = windSpeed;
    }
}

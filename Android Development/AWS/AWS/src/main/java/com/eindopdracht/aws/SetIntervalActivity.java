package com.eindopdracht.aws;

import android.app.Activity;
import android.content.Context;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Spinner;
import android.widget.TextView;


public class SetIntervalActivity extends Activity implements Spinner.OnItemSelectedListener{
    SharedPreferences sp;
  //  private SharedPreferences sp;
    private String[] intervalValues;
    private String[] intervalRange;
    private String[] intervalForHttp;
    private boolean shouldset = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_set_interval);

        Spinner intervals = (Spinner) findViewById(R.id.intervals);
        ArrayAdapter<CharSequence> adapter = ArrayAdapter.createFromResource(this, R.array.interval_range, android.R.layout.simple_spinner_dropdown_item);
        intervals.setAdapter(adapter);

        intervals.setOnItemSelectedListener(this);
         sp = PreferenceManager.getDefaultSharedPreferences(this.getApplicationContext());
       // sp = getSharedPreferences("AWS", Context.MODE_PRIVATE);
        intervalValues = getResources().getStringArray(R.array.interval_values);
        intervalRange = getResources().getStringArray(R.array.interval_range);
        intervalForHttp = getResources().getStringArray(R.array.interval_range_httpStyle);
        shouldset = false;
        setCurrentInterval();
    }

    private void setCurrentInterval(){
        TextView current = (TextView) findViewById(R.id.current_interval);
        String currentInterval ;
       // if(sp.contains("interval"))
            currentInterval = sp.getString("interval", "Not Set");

        for(int i = 0; i < intervalValues.length; i++){
            if(intervalValues[i].equals(currentInterval))
                currentInterval = intervalRange[i];
        }

        current.setText("current interval = " + currentInterval);
    }

    @Override
    public void onItemSelected(AdapterView<?> adapterView, View view, int i, long l) {
       // SharedPreferences.Editor editor = sp.edit();
        if(shouldset)
        {
            sp.edit().putString("interval", intervalValues[i]).apply();
            sp.edit().putString("range", intervalForHttp[i]).apply();
            sp.edit().commit();
        }
        shouldset = true;
        setCurrentInterval();
    }


    @Override
    public void onNothingSelected(AdapterView<?> arg0) {
        // do nothing
    }
}

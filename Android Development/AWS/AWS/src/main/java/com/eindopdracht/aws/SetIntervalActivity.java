package com.eindopdracht.aws;

import android.app.Activity;
import android.content.Context;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Spinner;
import android.widget.TextView;


public class SetIntervalActivity extends Activity implements Spinner.OnItemSelectedListener{

    private SharedPreferences sp;
    private String[] intervalValues;
    private String[] intervalRange;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_set_interval);

        Spinner intervals = (Spinner) findViewById(R.id.intervals);
        ArrayAdapter<CharSequence> adapter = ArrayAdapter.createFromResource(this, R.array.interval_range, android.R.layout.simple_spinner_dropdown_item);
        intervals.setAdapter(adapter);

        intervals.setOnItemSelectedListener(this);

        sp = getSharedPreferences("AWS", Context.MODE_PRIVATE);
        intervalValues = getResources().getStringArray(R.array.interval_values);
        intervalRange = getResources().getStringArray(R.array.interval_range);

        setCurrentInterval();
    }

    private void setCurrentInterval(){
        TextView current = (TextView) findViewById(R.id.current_interval);
        String currentInterval = "not set";
        if(sp.contains("interval"))
            currentInterval = sp.getString("interval", "");

        for(int i = 0; i < intervalValues.length; i++){
            if(intervalValues[i].equals(currentInterval))
                currentInterval = intervalRange[i];
        }

        current.setText(current.getText() + currentInterval);
    }

    @Override
    public void onItemSelected(AdapterView<?> adapterView, View view, int i, long l) {
        SharedPreferences.Editor editor = sp.edit();
        editor.putString("interval", intervalValues[i]);
        editor.commit();
    }

    @Override
    public void onNothingSelected(AdapterView<?> arg0) {
        // do nothing
    }
}

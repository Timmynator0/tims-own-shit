package com.eindopdracht.aws;

import android.app.Activity;
import android.content.Context;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Spinner;


public class SetIntervalActivity extends Activity implements Spinner.OnItemSelectedListener{

    private SharedPreferences sp;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_set_interval);

        Spinner intervals = (Spinner) findViewById(R.id.intervals);
        ArrayAdapter<CharSequence> adapter = ArrayAdapter.createFromResource(this, R.array.interval_range, android.R.layout.simple_spinner_dropdown_item);
        intervals.setAdapter(adapter);

        intervals.setOnItemSelectedListener(this);

        sp = getSharedPreferences("AWS", Context.MODE_PRIVATE);
    }

    @Override
    public void onItemSelected(AdapterView<?> adapterView, View view, int i, long l) {
        String[] intervalValues = getResources().getStringArray(R.array.interval_values);

        SharedPreferences.Editor editor = sp.edit();
        editor.putString("interval", intervalValues[i]);
        editor.commit();

        System.out.println("Interval value -> " + intervalValues[i]);
    }

    @Override
    public void onNothingSelected(AdapterView<?> arg0) {
        // do nothing
    }
}

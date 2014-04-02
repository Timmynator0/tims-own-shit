package com.eindopdracht.aws;

import android.app.Activity;
import android.app.Fragment;
import android.app.FragmentTransaction;
import android.content.Intent;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;

import  com.eindopdracht.aws.fragment.GraphViewFragment;
import com.eindopdracht.aws.data.DataSources;



public class MainActivity extends Activity {


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);


        // Add graph fragment on tablets
        Bundle data = new Bundle();
        data.putInt("index", DataSources.TEMPERATURE_INDEX);

        if(getResources().getBoolean(R.bool.isTablet)) {
            // Add Fragment
           Fragment graphFragment = new GraphViewFragment();
            graphFragment.setArguments(data);
            FragmentTransaction transaction = getFragmentManager().beginTransaction();
           transaction.replace(R.id.main_graph_container, graphFragment);
            transaction.commit();
        }

        setupActionBar();
    }

    /**
     * Set up the {@link android.app.ActionBar}.
     */
    private void setupActionBar() {
        getActionBar().setDisplayHomeAsUpEnabled(false);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case R.id.action_interval:
                Intent intervalIntent = new Intent(this, SetIntervalActivity.class);
                startActivity(intervalIntent);
                break;
        }

        return super.onOptionsItemSelected(item);
    }
}

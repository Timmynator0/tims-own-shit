package com.eindopdracht.aws;

import android.app.Activity;
import android.app.Fragment;
import android.app.FragmentTransaction;
import android.os.Bundle;
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
    }


}

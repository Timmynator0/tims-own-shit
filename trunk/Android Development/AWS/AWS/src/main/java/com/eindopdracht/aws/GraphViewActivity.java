package com.eindopdracht.aws;

import android.app.Activity;
import android.app.Fragment;
import android.app.FragmentTransaction;
import android.os.Bundle;

import com.eindopdracht.aws.fragment.GraphViewFragment;


public class GraphViewActivity extends Activity {
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_graph);

        // Pass the arguments fo this activity to the fragment
        Fragment graphFragment = new GraphViewFragment();
        graphFragment.setArguments(getIntent().getExtras());

        FragmentTransaction transaction = getFragmentManager().beginTransaction();
        transaction.add(R.id.activity_graph_container, graphFragment);
        transaction.commit();
    }
}


package com.eindopdracht.aws.fragment;

import android.app.Fragment;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import com.eindopdracht.aws.R;



public class GraphViewFragment extends Fragment {


    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setRetainInstance(false);
    }

    public View onCreateView(LayoutInflater inflater, ViewGroup parent, Bundle instanceState) {
        final View mainLayout = inflater.inflate(R.layout.fragment_graph, parent, false);

        return mainLayout;
    }

    @Override
    public void onResume() {
        super.onResume();
    }




}





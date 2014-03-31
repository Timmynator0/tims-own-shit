package com.eindopdracht.aws.fragment;

import android.app.Fragment;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;
import com.eindopdracht.aws.R;
import com.jjoe64.graphview.BarGraphView;
import com.jjoe64.graphview.GraphView;
import com.jjoe64.graphview.GraphView.GraphViewData;
import com.jjoe64.graphview.GraphViewSeries;
import com.jjoe64.graphview.LineGraphView;

public class GraphViewFragment extends Fragment {


    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setRetainInstance(false);


    }

    public View onCreateView(LayoutInflater inflater, ViewGroup parent, Bundle instanceState) {
        final View mainLayout = inflater.inflate(R.layout.fragment_graph, parent, false);


        // init example series data
        GraphViewSeries exampleSeries = new GraphViewSeries(new GraphViewData[] {
                new GraphViewData(1, 2.0d)
                , new GraphViewData(2, 1.5d)
                , new GraphViewData(3, 2.5d)
                , new GraphViewData(4, 1.0d)
        });

        GraphView graphView = new LineGraphView(
                this.getActivity() // context
                , "GraphViewDemo" // heading
        );
        graphView.addSeries(exampleSeries); // data

        LinearLayout layout = (LinearLayout) this.getActivity().findViewById(R.id.chart);
        layout.addView(graphView);





        return mainLayout;
    }


    @Override
    public void onResume() {
        super.onResume();
    }




}





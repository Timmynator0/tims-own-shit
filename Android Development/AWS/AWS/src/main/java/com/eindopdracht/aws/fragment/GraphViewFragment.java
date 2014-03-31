package com.eindopdracht.aws.fragment;

import android.app.Activity;
import android.app.Fragment;
import android.content.Loader;
import android.content.res.Resources;
import android.os.AsyncTask;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.LinearLayout;
import android.widget.ProgressBar;

import com.eindopdracht.aws.R;
import com.eindopdracht.aws.data.DataSources;
import com.jjoe64.graphview.GraphView;
import com.jjoe64.graphview.GraphView.GraphViewData;
import com.jjoe64.graphview.GraphViewSeries;
import com.jjoe64.graphview.LineGraphView;

import org.apache.http.HttpResponse;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.client.methods.HttpUriRequest;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.util.EntityUtils;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import static com.eindopdracht.aws.data.Constants.*;

import java.io.IOException;

public class GraphViewFragment extends Fragment implements AdapterView.OnItemSelectedListener{

   // private GraphicalView chart;
    private GraphView chart;
    private JSONArray historicaldata;
    private boolean dataDone = false;
    private LinearLayout layout;
    private ProgressBar loader;
    private int lastSelection = -1;
    private int datastreamIndex;
    private GraphViewData[] graphViewArray = new GraphViewData[800];
    private GraphViewSeries graphSeries;

    public GraphViewFragment() {
    }

    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setRetainInstance(false);
    }

    public View onCreateView(LayoutInflater inflater, ViewGroup parent, Bundle instanceState) {
        final View mainLayout = inflater.inflate(R.layout.fragment_graph, parent, false);

        loader = (ProgressBar)mainLayout.findViewById(R.id.loader);

        // init example series data
//        graphSeries = new GraphViewSeries(graphViewArray);
//
//        chart = new LineGraphView(
//                this.getActivity() // context
//                , "GraphViewDemo" // heading
//        );
//        chart.addSeries(graphSeries); // data
//
//        layout = (LinearLayout) mainLayout.findViewById(R.id.chart);
//        layout.addView(chart);

        final Bundle arguments = getArguments();
        final Activity activity = getActivity();
        if(arguments != null && mainLayout != null && activity != null) {
            datastreamIndex = arguments.getInt("index", 0);

            layout = (LinearLayout) mainLayout.findViewById(R.id.chart);
        }

        return mainLayout;
    }

    private void onDataLoaded() {
        if(dataDone) {
            final Activity activity = getActivity();
            if(activity != null) {
                if(chart != null) {
                    // Remove the old chart, add a new one to fix scaling issues
                    layout.removeView(chart);
                }
                // Add view
//                chart.addSeries(graphSeries); // data
//                layout.addView(chart);
                graphSeries = new GraphViewSeries(graphViewArray);

                chart = new LineGraphView(
                        this.getActivity() // context
                        , "GraphViewDemo" // heading
                );
                chart.addSeries(graphSeries); // data

                layout = (LinearLayout) getActivity().findViewById(R.id.chart);
                layout.addView(chart);
            }
        }
        loader.setVisibility(View.GONE);
    }

    @Override
    public void onResume() {
        super.onResume();
    }


    @Override
    public void onItemSelected(final AdapterView<?> parent, final View view, final int position, final long id) {
        if(lastSelection != position) {
            new HistoricalDataFetchingTask().execute(datastreamIndex, position);
            lastSelection = position;
        }
    }

    @Override
    public void onNothingSelected(AdapterView<?> adapterView) {
        //Do nothing
    }

    public class HistoricalDataFetchingTask extends AsyncTask<Integer, Integer, Void> {
        @Override
        protected void onPreExecute() {
            if(loader != null)
                loader.setVisibility(View.VISIBLE);
        }

        @Override
        protected Void doInBackground(Integer... params) {
            getHistoricalData(params[0], params[1]);
            addData();
            return null;
        }

        private void getHistoricalData(int datastreamIndex, int durationIndex) {
            final Activity activity = getActivity();
            if(activity != null) {
                final Resources resources = activity.getResources();

                final String title = DataSources.getUrlTitleFromIndex(datastreamIndex);

                final String interval = resources.getStringArray(R.array.interval_id)[durationIndex];
                final String duration = resources.getStringArray(R.array.duration_id)[durationIndex];

                HttpClient httpClient = new DefaultHttpClient();
                //Prepare a request object
                //
                String uri = XIVELY_DATASTREAM_GRAPH_BASE_URL + title + ".json?duration=" + duration +
                        "&interval=" + interval;

                HttpUriRequest httpUriRequest = new HttpGet(uri);
                httpUriRequest.addHeader(XIVELY_HEADER_API_KEY, XIVELY_API_KEY);
                try {
                    HttpResponse response = httpClient.execute(httpUriRequest);
                    JSONObject jsonObject = new JSONObject(EntityUtils.toString(response.getEntity()));
                    historicaldata = jsonObject.getJSONArray(DATAPOINTS);
                    Log.d("fetching", "done");
                } catch(IOException e) {
                    Log.d("fetching", e.getMessage());
                } catch(JSONException e) {
                    Log.d("fetching", e.getMessage());
                }
            }
        }

        private void addData() {
            if(historicaldata != null) {
                for(int i = 0; i < historicaldata.length(); i++) {
                    try {
                        //currentSeries.add(i, Double.parseDouble(historicaldata.getJSONObject(i).getString("value")));
                        graphViewArray[i] = new GraphViewData(i, Double.parseDouble(historicaldata.getJSONObject(i).getString("value")));
                        dataDone = true;
                    } catch(JSONException e) {
                        Log.d(getClass().getSimpleName(), e.getMessage(), e);
                    }
                }
            }
        }

        @Override
        protected void onPostExecute(Void result) {
            onDataLoaded();
        }
    }
}





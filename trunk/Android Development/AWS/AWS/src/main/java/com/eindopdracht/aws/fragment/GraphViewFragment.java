package com.eindopdracht.aws.fragment;

import android.app.Activity;
import android.app.Fragment;
import android.content.Context;
import android.content.SharedPreferences;
import android.content.res.Resources;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Handler;
import android.preference.PreferenceManager;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;
import android.widget.ProgressBar;

import com.eindopdracht.aws.R;
import com.eindopdracht.aws.data.Constants;
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

import java.io.IOException;

import static com.eindopdracht.aws.data.Constants.DATAPOINTS;
import static com.eindopdracht.aws.data.Constants.XIVELY_API_KEY;
import static com.eindopdracht.aws.data.Constants.XIVELY_DATASTREAM_GRAPH_BASE_URL;
import static com.eindopdracht.aws.data.Constants.XIVELY_HEADER_API_KEY;
import com.eindopdracht.aws.fragment.MainFragment;
public class GraphViewFragment extends Fragment {//implements AdapterView.OnItemSelectedListener{

   // private GraphicalView chart;
    private GraphView chart;
    private JSONArray historicaldata;
    private boolean dataDone = false;
    private LinearLayout layout;
    private ProgressBar loader;
    private int lastSelection = -1;
    private int datastreamIndex;
    private GraphViewData[] graphViewArray; // = new GraphViewData[800];
    private GraphViewSeries graphSeries;
    public Handler graphHandler;

    public final Runnable handlerRunnable = new Runnable() {
        @Override
        public void run() {
            // Update the data

            new HistoricalDataFetchingTask().execute(datastreamIndex, datastreamIndex);

            // Schedule the next update in a minute
          //  graphHandler.post(handlerRunnable);
        }
    };

   // private int arraysize;
    public GraphViewFragment() {
    }

    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setRetainInstance(false);
    }

    public View onCreateView(LayoutInflater inflater, ViewGroup parent, Bundle instanceState) {
        final View mainLayout = inflater.inflate(R.layout.fragment_graph, parent, false);

        loader = (ProgressBar)mainLayout.findViewById(R.id.loader);
        //sp
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

         //   new HistoricalDataFetchingTask().execute(datastreamIndex, datastreamIndex);

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

       // if(getResources().getBoolean(R.bool.isTablet)) {
           graphHandler = new Handler();
           graphHandler.post(handlerRunnable);
       // }
    }


//    @Override
//    public void onItemSelected(final AdapterView<?> parent, final View view, final int position, final long id) {
//        if(lastSelection != position) {
//            new HistoricalDataFetchingTask().execute(datastreamIndex, position);
//            lastSelection = position;
//        }
//    }
//
//    @Override
//    public void onNothingSelected(AdapterView<?> adapterView) {
//        //Do nothing
//    }

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

                SharedPreferences  sp = PreferenceManager.getDefaultSharedPreferences(getActivity().getApplicationContext());

                final String interval = sp.getString("interval", "300"); //gets the interval, 300 as a default if not set
                final String duration = sp.getString("range", "5days"); // gets the range, 500 corresponding the 300 interval

                HttpClient httpClient = new DefaultHttpClient();
                //Prepare a request object

                String uri = XIVELY_DATASTREAM_GRAPH_BASE_URL + title + ".json?duration=" + duration +
                        "&interval=" + interval;

                HttpUriRequest httpUriRequest = new HttpGet(uri);
                httpUriRequest.addHeader(XIVELY_HEADER_API_KEY, XIVELY_API_KEY);
                try {
                    HttpResponse response = httpClient.execute(httpUriRequest);
                    JSONObject jsonObject = new JSONObject(EntityUtils.toString(response.getEntity()));
                    historicaldata = jsonObject.getJSONArray(DATAPOINTS);
                  //int  arraysize == historicaldata.length();
                    graphViewArray =  new GraphViewData[historicaldata.length()];
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





package com.eindopdracht.aws.fragment;

import android.app.Activity;
import android.app.Fragment;
import android.app.FragmentTransaction;
import android.content.Intent;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ListView;
import android.widget.ProgressBar;
import android.widget.Toast;

import com.eindopdracht.aws.CurrentAWSData;
import com.eindopdracht.aws.GraphViewActivity;
import com.eindopdracht.aws.ListViewAdapter;
import com.eindopdracht.aws.MainActivity;
import com.eindopdracht.aws.R;
import com.eindopdracht.aws.data.Constants;

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



import static com.eindopdracht.aws.data.Constants.CURRENT_VALUE;
import static com.eindopdracht.aws.data.Constants.DATASTREAMS;
import static com.eindopdracht.aws.data.Constants.MAX_DEGREES;
import static com.eindopdracht.aws.data.Constants.XIVELY_API_KEY;
import static com.eindopdracht.aws.data.Constants.XIVELY_DATASTREAM_URL;
import static com.eindopdracht.aws.data.Constants.XIVELY_HEADER_API_KEY;
import static com.eindopdracht.aws.data.DataSources.AIR_PRESSURE_INDEX;
import static com.eindopdracht.aws.data.DataSources.HUMIDITY_INDEX;
import static com.eindopdracht.aws.data.DataSources.RAIN_RATE_INDEX;
import static com.eindopdracht.aws.data.DataSources.TEMPERATURE_INDEX;
import static com.eindopdracht.aws.data.DataSources.WIND_DIRECTION_INDEX;
import static com.eindopdracht.aws.data.DataSources.WIND_SPEED_INDEX;

public class MainFragment extends Fragment implements AdapterView.OnItemClickListener {
//    PullToRefreshAttacher.OnRefreshListener {
    private CurrentAWSData currentAWSData;
//    private PullToRefreshAttacher pullToRefreshAttacher;
    private boolean isPullToRefreshAttacherSet = false;
    private boolean isTablet;
    private ListView listView;
    private ProgressBar loader;
    private Handler handler;

    private final Runnable handlerRunnable = new Runnable() {
        @Override
        public void run() {
            // Update the data
            new DataFetchingTask().execute();
            // Schedule the next update in a minute
            handler.postDelayed(this, Constants.ONE_MINUTE);
        }
    };

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Override
    public void onActivityCreated(Bundle data) {
        super.onActivityCreated(data);

        final Activity activity = getActivity();
        if(activity != null && activity instanceof MainActivity) {
            final MainActivity mainActivity = (MainActivity) activity;

        }
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup parent, Bundle instanceState) {
        final View mainLayout = inflater.inflate(R.layout.fragment_main, parent, false);
        listView = (ListView) mainLayout.findViewById(R.id.listView);
        loader = (ProgressBar) mainLayout.findViewById(R.id.fragment_main_loader);

        listView.setOnItemClickListener(this);

        isTablet = getResources().getBoolean(R.bool.isTablet);

        // initial data fetch
        new DataFetchingTask().execute();

        // Start timer after 60 seconds, fetch updated data
        handler = new Handler();
        handler.postDelayed(handlerRunnable, 1000 * 60);

        return mainLayout;
    }

    @Override
    public void onPause() {
        super.onPause();

        handler.removeCallbacks(handlerRunnable);
    }

    @Override
    public void onResume() {
        super.onResume();

        handler.post(handlerRunnable);
    }



    @Override
    public void onItemClick(final AdapterView<?> parent, final View view, final int position, final long id) {
        Bundle data = new Bundle();
        data.putInt("index", position);
        Toast toast = Toast.makeText(this.getActivity(), "Under Construction", Toast.LENGTH_SHORT);
        toast.show();
        if(isTablet) {
            // Add Fragment
            Fragment graphFragment = new GraphViewFragment();
            graphFragment.setArguments(data);
            FragmentTransaction transaction = getFragmentManager().beginTransaction();
            transaction.replace(R.id.main_graph_container, graphFragment);
            transaction.commit();
        } else {
            Intent intent = new Intent(getActivity(), GraphViewActivity.class);
            intent.putExtras(data);
            startActivity(intent);
        }
    }

    public class DataFetchingTask extends AsyncTask<Void, Void, Void> {

        @Override
        protected void onPreExecute() {
            if(loader != null)
                loader.setVisibility(View.VISIBLE);
        }

        @Override
        protected Void doInBackground(Void... voids) {
            updateData();
            return null;
        }

        private void updateData() {
            final HttpClient httpClient = new DefaultHttpClient();
            //Prepare a request object
            final HttpUriRequest httpUriRequest = new HttpGet(XIVELY_DATASTREAM_URL);
            httpUriRequest.addHeader(XIVELY_HEADER_API_KEY, XIVELY_API_KEY);
            try {
                final HttpResponse response = httpClient.execute(httpUriRequest);
                final JSONObject jsonObject = new JSONObject(EntityUtils.toString(response.getEntity()));
                final JSONArray dataStreams = jsonObject.getJSONArray(DATASTREAMS);
                String currentValue;

                // Parse air pressure
                currentValue = dataStreams.getJSONObject(AIR_PRESSURE_INDEX).getString(CURRENT_VALUE);
                float airPressure = Float.parseFloat(currentValue);

                // Parse humidity
                currentValue = dataStreams.getJSONObject(HUMIDITY_INDEX).getString(CURRENT_VALUE);
                int humidity = Integer.parseInt(currentValue);

                // Parse rain rate
                currentValue = dataStreams.getJSONObject(RAIN_RATE_INDEX).getString(CURRENT_VALUE);
                float rainRate = Float.parseFloat(currentValue);

                // Parse temperature
                currentValue = dataStreams.getJSONObject(TEMPERATURE_INDEX).getString(CURRENT_VALUE);
                float temperature = Float.parseFloat(currentValue);

                // Parse wind direction
                currentValue = dataStreams.getJSONObject(WIND_DIRECTION_INDEX).getString(CURRENT_VALUE);
                int windDirection = Integer.parseInt(currentValue) % MAX_DEGREES;

                // Parse wind speed
                currentValue = dataStreams.getJSONObject(WIND_SPEED_INDEX).getString(CURRENT_VALUE);
                float windSpeed = Float.parseFloat(currentValue);

                // Create a new CurrentAWSData object form the values
                currentAWSData = new CurrentAWSData(airPressure, humidity, rainRate, temperature, windDirection,
                        windSpeed);
            } catch(IOException e) {
                Log.e(getClass().getSimpleName(), e.getMessage(), e);
            } catch(JSONException e) {
                Log.e(getClass().getSimpleName(), e.getMessage(), e);
            }
        }

        @Override
        protected void onPostExecute(Void result) {


            if(listView != null) {
                final Activity activity = getActivity();
                if(activity != null) {
                    final ListViewAdapter listViewAdapter = new ListViewAdapter(currentAWSData, activity);
                    listView.setAdapter(listViewAdapter);
                }

                loader.setVisibility(View.GONE);
            }

        }
    }
}
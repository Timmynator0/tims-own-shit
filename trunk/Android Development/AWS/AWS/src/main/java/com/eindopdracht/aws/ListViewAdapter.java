package com.eindopdracht.aws;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.animation.Animation;
import android.view.animation.RotateAnimation;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.TextView;

import com.eindopdracht.aws.data.DataSources;

import static com.eindopdracht.aws.data.DataSources.AIR_PRESSURE_INDEX;
import static com.eindopdracht.aws.data.DataSources.HUMIDITY_INDEX;
import static com.eindopdracht.aws.data.DataSources.NUMBER_OF_DATA_SOURCES;
import static com.eindopdracht.aws.data.DataSources.RAIN_RATE_INDEX;
import static com.eindopdracht.aws.data.DataSources.TEMPERATURE_INDEX;
import static com.eindopdracht.aws.data.DataSources.WIND_DIRECTION_INDEX;
import static com.eindopdracht.aws.data.DataSources.WIND_SPEED_INDEX;

public class ListViewAdapter extends BaseAdapter {

    private final CurrentAWSData currentData;
    private final LayoutInflater inflater;
    private final Context context;

    public ListViewAdapter(com.eindopdracht.aws.CurrentAWSData data, Context context) {
        this.context = context;
        currentData = data;
        inflater = LayoutInflater.from(context);
    }

    @Override
    public int getCount() {
        return NUMBER_OF_DATA_SOURCES;
    }

    @Override
    public Object getItem(int i) {
        return null;
    }

    @Override
    public long getItemId(int i) {
        return 0;
    }

    @Override
    public View getView(int position, View view, ViewGroup viewGroup) {
        // for fancypoints: point the arrow in the direction of the wind...
        if(position == WIND_DIRECTION_INDEX) {
            // Show the view for the Wind Direction index
            view = inflater.inflate(R.layout.list_item_image, null, false);
            view.setTag(WIND_DIRECTION_INDEX);

            final ImageView image = (ImageView) view.findViewById(R.id.image);
            final TextView title = (TextView) view.findViewById(R.id.title);

            // Set title
            final String titleString = DataSources.getNameFromIndex(context, position);
            title.setText(titleString);

            // Set animation
            RotateAnimation animation = new RotateAnimation(0, currentData.windDirection,
                    Animation.RELATIVE_TO_SELF, 0.5f, Animation.RELATIVE_TO_SELF, 0.5f);
            animation.setStartOffset(500);
            animation.setDuration(2000);
            animation.setFillAfter(true);
            animation.setRepeatCount(0);
            image.startAnimation(animation);
        } else {
            // Show the 'normal' view
            // Note: We're using setTag()/getTag() to make sure the View is 'valid' for the current position,
            // since the Wind direction uses another View than the others
            if(view == null || view.getTag() == Integer.valueOf(WIND_DIRECTION_INDEX)) {
                view = inflater.inflate(R.layout.list_item, viewGroup, false);
                view.setTag(position);
            }

            final TextView title = (TextView) view.findViewById(R.id.title);
            final TextView value = (TextView) view.findViewById(R.id.value);

            // Set title
            final String titleString = DataSources.getNameFromIndex(context, position);
            title.setText(titleString);

            // Set value
            switch(position) {
                case AIR_PRESSURE_INDEX:
                    value.setText(String.valueOf(currentData.airPressure));
                    break;
                case HUMIDITY_INDEX:
                    value.setText(String.valueOf(currentData.hudidity));
                    break;
                case RAIN_RATE_INDEX:
                    value.setText(String.valueOf(currentData.rainRate));
                    break;
                case TEMPERATURE_INDEX:
                    value.setText(String.valueOf(currentData.temperature));
                    break;
                case WIND_SPEED_INDEX:
                    value.setText(String.valueOf(currentData.windSpeed));
                    break;
            }
        }
        return view;
    }
}

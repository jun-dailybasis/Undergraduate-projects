package com.pierre.biojoux.project;


import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.drawable.BitmapDrawable;
import android.graphics.drawable.Drawable;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.InputStream;
import java.net.URL;

import Weather.JSONWeatherParser;
import Weather.Model.Weather;
import Weather.Utils;
import Weather.WeatherHttpClient;


/*
https://stackoverflow.com/questions/8423987/download-image-for-imageview-on-android
https://www.youtube.com/watch?v=UuGIAomlU1I
https://github.com/RobertCMonahan/contemplative_brick_weather_app
 */

public class WeatherActivity extends AppCompatActivity{

    private TextView celsius;
    private TextView description;
    private TextView city;
    private TextView timestamp;
    private ImageView imageWeather;
    private TextView humidity;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_weather);
        celsius = (TextView) findViewById(R.id.celsius);
        description = (TextView) findViewById(R.id.description);
        city = (TextView) findViewById(R.id.city);
        timestamp = (TextView) findViewById(R.id.timestamp);
        humidity = (TextView) findViewById(R.id.humidity);
        imageWeather = (ImageView) findViewById(R.id.imageWeather);


        renderWeatherData("Aarhus,DK");

    }



    private void renderWeatherData(String city){
        WeatherTask weatherTask = new WeatherTask();
        weatherTask.execute(city);

    }

    //Download Image
    public class DownloadImage extends AsyncTask<String, Integer, Drawable>{

        @Override
        protected Drawable doInBackground(String... arg0) {
            //This is done in a background thread
            return downloadImage(arg0[0]);
        }

        //Called after the image has been downloaded
        protected void onPostExecute(Drawable image)
        {
            imageWeather.setImageDrawable(image);
        }

        //download the image from the url
        private Drawable downloadImage(String _url){
            URL url;
            BufferedOutputStream bufferedOutputStream;
            InputStream inputStream;
            BufferedInputStream bufferedInputStream;

            try {
                url = new URL(_url);
                inputStream = url.openStream();

                // Read the inputstream
                bufferedInputStream = new BufferedInputStream(inputStream);

                // Convert the BufferedInputStream to a Bitmap
                Bitmap bMap = BitmapFactory.decodeStream(bufferedInputStream);
                if (inputStream != null) {
                    inputStream.close();
                }
                if (bufferedInputStream != null) {
                    bufferedInputStream.close();
                }

                return new BitmapDrawable(bMap);

            } catch (Exception e) {
                Log.e("Error reading file", e.toString());
            }
            return null;
        }
    }

    private class WeatherTask extends AsyncTask<String, Void, Weather>{

        @Override
        protected Weather doInBackground(String... params) {
            String data = ((new WeatherHttpClient()).getWeatherData(params[0]));
            Weather weather = JSONWeatherParser.getWeather(data);
            return weather;
        }

        @Override
        protected void onPostExecute(Weather weather) {
            super.onPostExecute(weather);


            //Convert times into readable formats
            //get unix times and multiply by 1000 to get proper length since it converts down to milliseconds
            long unixUpdated = weather.getTimestamp()*1000;
            //do the conversion
            java.util.Date updatedDate = new java.util.Date(unixUpdated);
            String updatedTime = String.valueOf(android.text.format.DateFormat.format("kk:mm:ss", updatedDate));

            //Set text for all items
            city.setText(weather.getCity()+" in "+weather.sys.getCountry());
            celsius.setText(weather.main.getTemp() + "°C");
            description.setText("Condition: " + weather.currentCondition.getMain() + "\n(" + weather.currentCondition.getDescription() + ")");
            timestamp.setText("Last Updated: " + updatedTime);
            humidity.setText("Humidity: " + weather.main.getHumidity() + " %");

            //Set imageWeather in the XML file
            new DownloadImage().execute(Utils.ICON_URL + weather.currentCondition.getIcon() +".png");
        }
    }


    //Quit the weather activity
    public void quit (View view){
        finish();
    }
}
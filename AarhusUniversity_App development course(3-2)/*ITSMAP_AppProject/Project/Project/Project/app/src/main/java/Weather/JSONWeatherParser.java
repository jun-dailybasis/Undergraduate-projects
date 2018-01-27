package Weather;

import android.util.Log;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import Weather.Model.Weather;

import static Weather.Utils.getDouble;
import static Weather.Utils.getInt;
import static Weather.Utils.getLong;
import static Weather.Utils.getObject;
import static Weather.Utils.getString;

/*
https://www.youtube.com/watch?v=UuGIAomlU1I
*/
public class JSONWeatherParser {

    public static Weather getWeather(String data){

        Weather weather = new Weather();
        //create JsonObject from data
        try {
            JSONObject jsonObject = new JSONObject(data);

            //Get the sys
            JSONObject sysObj = getObject("sys", jsonObject);
            weather.sys.setCountry(getString("country", sysObj));

            //Get other info
            weather.setTimestamp(getLong("dt", jsonObject));
            weather.setCity(getString("name", jsonObject));

            //Get the main
            JSONObject mainObj = getObject("main", jsonObject);
            weather.main.setTemp(getDouble("temp", mainObj));
            weather.main.setHumidity(getInt("humidity", mainObj));

            //Get weather array
            JSONArray jsonArray = jsonObject.getJSONArray("weather");
            JSONObject jsonWeather = jsonArray.getJSONObject(0);
            weather.currentCondition.setDescription(Utils.getString("description", jsonWeather));
            weather.currentCondition.setMain(getString("main", jsonWeather));
            Log.v("--Icon text", "setIcon Start");
            weather.currentCondition.setIcon(Utils.getString("icon", jsonWeather));
            Log.v("--Icon text", "setIcon End");
            Log.v("--Icon text", String.valueOf(weather.currentCondition.getIcon()));

            return weather;

        } catch (JSONException e) {
            e.printStackTrace();
        }

        return null;
    }
}

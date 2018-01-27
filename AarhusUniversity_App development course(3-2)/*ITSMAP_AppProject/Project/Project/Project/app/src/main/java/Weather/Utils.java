package Weather;

import org.json.JSONException;
import org.json.JSONObject;

/*
https://www.youtube.com/watch?v=UuGIAomlU1I
*/

public class Utils {
    public static final String BASE_URL = "http://api.openweathermap.org/data/2.5/weather?q=";
    public static final String METRIC_URL = "&units=metric";
    public static final String APP_ID = "&APPID=50b3e841741f20820afb8b2e706984a0";
    public static final String ICON_URL = "http://openweathermap.org/img/w/";

    public static JSONObject getObject(String tagName, JSONObject jsonObject) throws JSONException {
        return jsonObject.getJSONObject(tagName);
    }

    public static String getString(String tagName, JSONObject jsonObject) throws JSONException {
        return jsonObject.getString(tagName);
    }

    public static float getFloat(String tagName, JSONObject jsonObject) throws JSONException {
        return (float) jsonObject.getDouble(tagName);
    }

    public static double getDouble(String tagName, JSONObject jsonObject) throws JSONException {
        return jsonObject.getDouble(tagName);
    }

    public static int getInt(String tagName, JSONObject jsonObject) throws JSONException {
        return jsonObject.getInt(tagName);
    }

    public static long getLong(String tagName, JSONObject jsonObject) throws JSONException{
        return jsonObject.getLong(tagName);
    }

}

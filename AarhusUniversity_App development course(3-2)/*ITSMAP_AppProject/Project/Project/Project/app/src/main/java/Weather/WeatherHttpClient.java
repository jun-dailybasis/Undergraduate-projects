package Weather;

/*
https://www.youtube.com/watch?v=UuGIAomlU1I
*/

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;

import static Weather.Utils.APP_ID;
import static Weather.Utils.BASE_URL;
import static Weather.Utils.METRIC_URL;

public class WeatherHttpClient {
    public String getWeatherData(String place){
        HttpURLConnection connection;
        InputStream inputStream;

        try {
            connection = (HttpURLConnection) (new URL(BASE_URL + place + APP_ID + METRIC_URL)).openConnection();
            connection.setRequestMethod("GET");
            connection.setDoInput(true);
            connection.setDoInput(true);
            connection.connect();

            //Read the response
            StringBuffer stringBuffer = new StringBuffer();
            inputStream = connection.getInputStream();
            BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(inputStream));
            String line = null;

            while((line = bufferedReader.readLine()) != null){
                stringBuffer.append(line + "\r\n");
            }

            inputStream.close();
            connection.disconnect();
            return stringBuffer.toString();

        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }


}
package Weather.Model;

/*
https://www.youtube.com/watch?v=UuGIAomlU1I
*/

public class Weather {
    public final Main main = new Main();
    public final CurrentCondition currentCondition = new CurrentCondition();
    public final Sys sys = new Sys();
    private long timestamp;
    private String city;

    public long getTimestamp() {
        return timestamp;
    }

    public void setTimestamp(long timestamp) {
        this.timestamp = timestamp;
    }

    public String getCity() {
        return city;
    }

    public void setCity(String city) {
        this.city = city;
    }
}

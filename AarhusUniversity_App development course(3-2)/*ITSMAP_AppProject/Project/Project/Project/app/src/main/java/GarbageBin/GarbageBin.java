package GarbageBin;

import java.io.Serializable;

public class GarbageBin implements Serializable{
    private long ID;
    private double lat;
    private double lon;
    private String status;
    private String emptied;

    public GarbageBin(long ID, double lat, double lon, String status){
        this.ID = ID;
        this.lat = lat;
        this.lon = lon;
        this.status = status;
        this.emptied = "Never";}
    //Getters & setters
    public void setID(long ID) {this.ID = ID;}
    public void setLon(double lat){this.lat = lat;}
    public void setLat(double lon){this.lon = lon;}
    public void setStatus(String status){this.status = status;}
    public void setEmptied(String emptied){this.emptied = emptied;}

    public long getID(){return ID;}
    public double getLat(){return lat;}
    public double getLon(){return lon;}
    public String getStatus(){return status;}
    public String getEmptied(){return emptied;}
    public String getCoord() { return lat + "," + lon;}
    //Methods

}

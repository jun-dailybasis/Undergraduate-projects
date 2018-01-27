package com.example.junyoung.a2017msp_termproject;

/**
 * Created by LSG on 2017-06-13.
 */

public class TrackInformation {
    private String timeStart;
    private String timeEnd;
    private String timePeriod;
    private String isMove;
    private String place;
    private String step;

    public void setTimeStart(String timeStart) {
        this.timeStart = timeStart;
    }

    public void setTimeEnd(String timeEnd) {
        this.timeEnd = timeEnd;
    }

    public void setTimePeriod(String timePeriod) {
        this.timePeriod = timePeriod;
    }

    public void setIsMove(String isMove) {
        this.isMove = isMove;
    }

    public void setPlace(String place) {
        this.place = place;
    }

    public void setStep(String step) {
        this.step = step;
    }


    public String getTimeStart() { return timeStart; }

    public String getTimeEnd() {
        return timeEnd;
    }

    public String getTimePeriod() {
        return timePeriod;
    }

    public String getIsMove() {
        return isMove;
    }

    public String getPlace() {
        return place;
    }

    public String getStep() {
        return step;
    }

    public TrackInformation(String timeStart, String timeEnd, String timePeriod, String isMove, String place, String step) {
        this.timeStart = timeStart;
        this.timeEnd = timeEnd;
        this.timePeriod = timePeriod;
        this.isMove = isMove;
        this.place = place;
        this.step = step;
    }



}

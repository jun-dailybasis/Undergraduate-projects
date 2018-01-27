package com.example.junyoung.a2017msp_termproject;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.TextView;

import java.util.ArrayList;

/**
 * Created by LSG on 2017-06-13.
 */

public class ListViewAdapter  extends BaseAdapter {

    // Adapter에 추가된 데이터를 저장하기 위한 ArrayList
    public ArrayList<TrackInformation> listViewItemList = new ArrayList<TrackInformation>() ;

    // ListViewAdapter의 생성자
    public ListViewAdapter() {

    }

    // Adapter에 사용되는 데이터의 개수를 리턴. : 필수 구현
    @Override
    public int getCount() {
        return listViewItemList.size() ;
    }

    // position에 위치한 데이터를 화면에 출력하는데 사용될 View를 리턴. : 필수 구현
    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        final int pos = position;
        final Context context = parent.getContext();
        // "listview_item" Layout을 inflate하여 convertView 참조 획득.
        if (convertView == null) {
            LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
            convertView = inflater.inflate(R.layout.item_list, parent, false);
        }

        // 화면에 표시될 View(Layout이 inflate된)으로부터 위젯에 대한 참조 획득
        //ListView ListViewItem = (ListView) convertView.findViewById(R.id.listview);
        TextView timeStart = (TextView) convertView.findViewById(R.id.timeStart);
        TextView timeEnd = (TextView) convertView.findViewById(R.id.timeEnd);
        TextView period = (TextView) convertView.findViewById(R.id.period);
        TextView move = (TextView) convertView.findViewById(R.id.move);
        TextView place = (TextView) convertView.findViewById(R.id.place);
        TextView step = (TextView) convertView.findViewById(R.id.step);


        // Data Set(listViewItemList)에서 position에 위치한 데이터 참조 획득
        TrackInformation listViewItem = listViewItemList.get(position);
        // 아이템 내 각 위젯에 데이터 반영
        timeStart.setText(listViewItem.getTimeStart());
        timeEnd.setText(listViewItem.getTimeEnd());
        period.setText(listViewItem.getTimePeriod());
        move.setText(listViewItem.getIsMove());
        place.setText(listViewItem.getPlace());
        step.setText(listViewItem.getStep());
        return convertView;
    }

    // 지정한 위치(position)에 있는 데이터와 관계된 아이템(row)의 ID를 리턴. : 필수 구현
    @Override
    public long getItemId(int position) {
        return position ;
    }

    // 지정한 위치(position)에 있는 데이터 리턴 : 필수 구현
    @Override
    public Object getItem(int position) {
        return listViewItemList.get(position) ;
    }
    // 아이템 데이터 추가를 위한 함수. 개발자가 원하는대로 작성 가능.
    public void addItem(String timeStart, String timeEnd, String period, String isMove, String place, String step) {
        TrackInformation item = new TrackInformation(timeStart, timeEnd, period, isMove, place, step);


        listViewItemList.add(item);
    }

}

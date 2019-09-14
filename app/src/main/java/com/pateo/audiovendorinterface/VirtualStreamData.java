package com.pateo.audiovendorinterface;

import java.util.ArrayList;
import java.util.Arrays;

public class VirtualStreamData {
    private byte[] data;
    private long mTimeStampUs;
    private VirtualStreamDataHeader head;

    public VirtualStreamData(){

    }

    public VirtualStreamData(byte[] data, long mTimeStampUs, VirtualStreamDataHeader head) {
        this.data = data;
        this.mTimeStampUs = mTimeStampUs;
        this.head = head;
    }

    public byte[] getData() {
        return data;
    }

    public void setData(byte[] data) {
        this.data = data;
    }

    public long getmTimeStampUs() {
        return mTimeStampUs;
    }

    public void setmTimeStampUs(long mTimeStampUs) {
        this.mTimeStampUs = mTimeStampUs;
    }

    public VirtualStreamDataHeader getHead() {
        return head;
    }

    public void setHead(VirtualStreamDataHeader head) {
        this.head = head;
    }

    @Override
    public String toString() {
        return "VirtualStreamData{" +
                "data=" + Arrays.toString(data) +
                ", mTimeStampUs=" + mTimeStampUs +
                ", head=" + head +
                '}';
    }
}

class VirtualStreamDataHeader{
    private int type;
    private int length;
    private ArrayList<Integer> reserved;

    public VirtualStreamDataHeader(){

    }

    public VirtualStreamDataHeader(int type, int length, ArrayList<Integer> reserved) {
        this.type = type;
        this.length = length;
        this.reserved = reserved;
    }

    public int getType() {
        return type;
    }

    public void setType(int type) {
        this.type = type;
    }

    public int getLength() {
        return length;
    }

    public void setLength(int length) {
        this.length = length;
    }

    public ArrayList<Integer> getReserved() {
        return reserved;
    }

    public void setReserved(ArrayList<Integer> reserved) {
        this.reserved = reserved;
    }

    @Override
    public String toString() {
        return "VirtualStreamDataHeader{" +
                "type=" + type +
                ", length=" + length +
                ", reserved=" + reserved +
                '}';
    }
}

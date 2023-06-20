package com.zyl.yuvlib.util;

public class YuvUtils {
    static {
        System.loadLibrary("yuvlib");
    }
    public static native void NV21ToI420(byte[] input, byte[] output, int width, int height);
    public static native void RotateI420(byte[] input, byte[] output, int width, int height, int rotation);
    public static native void NV21ToI420andRotate90Clockwise(byte[] input, byte[] output, int width, int height);
    public static native void pushRTMPStream(String pushUrl, byte[] input);
}

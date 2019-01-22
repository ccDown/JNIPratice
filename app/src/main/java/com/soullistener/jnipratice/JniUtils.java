package com.soullistener.jnipratice;

/**
 * @author kuan
 * Created on 2019/1/17.
 * @description
 */
public class JniUtils {

    public static void init() {
        System.loadLibrary("native-lib");
    }

    /**
     * 进行加密操作
     * @param byteKey
     * @param data
     * @return
     */
    public static native byte[] enCode(byte[] byteKey,byte[] data) ;

    /**
     * 进行解密操作
     * @param byteKey
     * @param data
     * @return
     */
    public static native byte[] deCode(byte[] byteKey, byte[] data) throws IllegalArgumentException;

}

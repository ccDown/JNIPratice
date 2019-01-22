package com.soullistener.jnipratice;

import android.annotation.SuppressLint;

/**
 * @author kuan
 * Created on 2019/1/22.
 * @description
 */
public class Utils {

    // 十六进制字符串转字节数组
    public static byte[] parseHexStr2Byte(String hexStr) {
        if (hexStr.length() < 1) {
            return null;
        }
        byte[] result = new byte[hexStr.length() / 2];
        for (int i = 0; i < hexStr.length() / 2; i++) {
            int high = Integer.parseInt(hexStr.substring(i * 2, i * 2 + 1), 16);
            int low = Integer.parseInt(hexStr.substring(i * 2 + 1, i * 2 + 2),
                    16);
            result[i] = (byte) (high * 16 + low);
        }
        return result;
    }

    // 字节数组转十六进制字符串
    @SuppressLint("DefaultLocale")
    public static String parseByte2HexStr(byte buf[]) {
        StringBuffer sb = new StringBuffer();
        for (int i = 0; i < buf.length; i++) {
            String hex = Integer.toHexString(buf[i] & 0xFF);
            if (hex.length() == 1) {
                hex = '0' + hex;
            }
            sb.append(hex.toUpperCase());
        }
        return sb.toString();
    }

    // 数据补位
    public static String dataFill(String dataStr) {
        int len = dataStr.length();
        if (len%16 != 0) {
            dataStr += "80";
            len = dataStr.length();
        }
        while (len%16 != 0) {
            dataStr += "0";
            len ++;
        }
        return dataStr;
    }

}

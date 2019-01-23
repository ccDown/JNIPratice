package com.soullistener.jnipratice;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;

import com.soullistener.com.soullistener.jnipratice.R;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        JniUtils.init();

        findViewById(R.id.sample_text).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                // 测试加密
                String keyStr = "11223344556677881122334455667788";
                String dataStr = "12345";
                dataStr = Utils.dataFill(dataStr);
                Log.e("dataStr",dataStr);
                String enResultStr = Utils.parseByte2HexStr(JniUtils.enCode(Utils.parseHexStr2Byte(keyStr),Utils.parseHexStr2Byte(dataStr)));
                Log.e("enResultStr",enResultStr);

                // 测试解密
                String deResultStr = Utils.parseByte2HexStr(JniUtils.deCode(Utils.parseHexStr2Byte(keyStr),Utils.parseHexStr2Byte(enResultStr)));
                Log.e("deResultStr",deResultStr);

            }
        });

    }

}

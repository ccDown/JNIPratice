#include <jni.h>
#include <string>

#include <stdio.h>
#include <stdlib.h>

#include<android/log.h>
#include <cstring>

#ifndef LOG_TAG
#define LOG_TAG "JniUtils的Log"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG ,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG ,__VA_ARGS__) // 定义LOGI类型
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,LOG_TAG ,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG ,__VA_ARGS__) // 定义LOGE类型
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,LOG_TAG ,__VA_ARGS__) // 定义LOGF类型
#endif


#include <iostream>
#include <csignal>
#include <setjmp.h>

static jmp_buf jumpflg;
JNIEnv* penv = NULL;

/**
 * @author 宽
 * 加解密操作
 */


/**
 * 3Des ECB模式加密
 */
extern "C"
JNIEXPORT jbyteArray JNICALL
Java_com_soullistener_jnipratice_JniUtils_enCode(JNIEnv *env, jclass type, jbyteArray byteKey_,
                                                 jbyteArray data_) {
    LOGE("开始加密");
    jbyte *byteKey = env->GetByteArrayElements(byteKey_, NULL);
    jbyte *data = env->GetByteArrayElements(data_, NULL);

    jbyteArray en_key =  env->NewByteArray(24);

    int byteKeySize = env->GetArrayLength(byteKey_);
    jclass system = env->FindClass("java/lang/System");
    jmethodID  systemId = env->GetStaticMethodID(system,"arraycopy","(Ljava/lang/Object;ILjava/lang/Object;II)V");


    if (byteKeySize == 16){
        env->CallStaticVoidMethod(system,systemId,byteKey_,0,en_key,0,16);
        env->CallStaticVoidMethod(system,systemId,byteKey_,0,en_key,16,8);

    } else if (byteKeySize == 8){
        env->CallStaticVoidMethod(system,systemId,byteKey_,0,en_key,0,8);
        env->CallStaticVoidMethod(system,systemId,byteKey_,0,en_key,8,8);
        env->CallStaticVoidMethod(system,systemId,byteKey_,0,en_key,16,8);
    } else {
        en_key = byteKey_;
    }

    jclass SecretKeySpec = env->FindClass("javax/crypto/spec/SecretKeySpec");
    jmethodID  SecretKeySpecId = env->GetMethodID(SecretKeySpec,"<init>","([BLjava/lang/String;)V");


    jstring algorithm = env->NewStringUTF("DESede");
    jobject spcretKeySpec = env->NewObject(SecretKeySpec,SecretKeySpecId,en_key,algorithm);


    jclass Cipher = env->FindClass("javax/crypto/Cipher");
    jmethodID  CipherId = env->GetStaticMethodID(Cipher,"getInstance","(Ljava/lang/String;)Ljavax/crypto/Cipher;");

    jstring transformation = env->NewStringUTF("DESede/ECB/NoPadding");
    jobject cipher = env->CallStaticObjectMethod(Cipher,CipherId,transformation);
    jmethodID  cipherInitId = env->GetMethodID(Cipher,"init","(ILjava/security/Key;)V");

    //Cipher.ENCRYPT_MODE
    env->CallVoidMethod(cipher,cipherInitId,1,spcretKeySpec);

    jmethodID cipherDoFinalId = env->GetMethodID(Cipher,"doFinal","([B)[B");
    jbyteArray en_data = static_cast<jbyteArray>(env->CallObjectMethod(cipher, cipherDoFinalId, data_));

    env->ReleaseByteArrayElements(byteKey_, byteKey, 0);
    env->DeleteLocalRef(system);
    env->DeleteLocalRef(spcretKeySpec);
    env->DeleteLocalRef(cipher);
    env->ReleaseByteArrayElements(data_, data, 0);
    env->DeleteLocalRef(algorithm);
    env->DeleteLocalRef(transformation);
    LOGE("加密完成");

    return en_data;

}

/**
 * 3Des ECB解密
 */
extern "C"
JNIEXPORT jbyteArray JNICALL
Java_com_soullistener_jnipratice_JniUtils_deCode(JNIEnv *env, jclass type, jbyteArray byteKey_,
                                                 jbyteArray data_) {
    LOGE("开始解密");

    jbyte *byteKey = env->GetByteArrayElements(byteKey_, NULL);
    jbyte *data = env->GetByteArrayElements(data_, NULL);

    jbyteArray en_key =  env->NewByteArray(24);

    int byteKeySize = env->GetArrayLength(byteKey_);
    jclass system = env->FindClass("java/lang/System");
    jmethodID  systemId = env->GetStaticMethodID(system,"arraycopy","(Ljava/lang/Object;ILjava/lang/Object;II)V");


    if (byteKeySize == 16){
        env->CallStaticVoidMethod(system,systemId,byteKey_,0,en_key,0,16);
        env->CallStaticVoidMethod(system,systemId,byteKey_,0,en_key,16,8);

    } else if (byteKeySize == 8){
        env->CallStaticVoidMethod(system,systemId,byteKey_,0,en_key,0,8);
        env->CallStaticVoidMethod(system,systemId,byteKey_,0,en_key,8,8);
        env->CallStaticVoidMethod(system,systemId,byteKey_,0,en_key,16,8);
    } else {
        en_key = byteKey_;
    }

    jclass SecretKeySpec = env->FindClass("javax/crypto/spec/SecretKeySpec");
    jmethodID  SecretKeySpecId = env->GetMethodID(SecretKeySpec,"<init>","([BLjava/lang/String;)V");

    jstring algorithm = env->NewStringUTF("DESede");
    jobject spcretKeySpec = env->NewObject(SecretKeySpec,SecretKeySpecId,en_key,algorithm);


    jclass Cipher = env->FindClass("javax/crypto/Cipher");
    jmethodID  CipherId = env->GetStaticMethodID(Cipher,"getInstance","(Ljava/lang/String;)Ljavax/crypto/Cipher;");

    jstring transformation = env->NewStringUTF("DESede/ECB/NoPadding");
    jobject cipher = env->CallStaticObjectMethod(Cipher,CipherId,transformation);
    jmethodID  cipherInitId = env->GetMethodID(Cipher,"init","(ILjava/security/Key;)V");

    //Cipher.DECRYPT_MODE
    env->CallVoidMethod(cipher,cipherInitId,2,spcretKeySpec);

    jmethodID cipherDoFinalId = env->GetMethodID(Cipher,"doFinal","([B)[B");
    jbyteArray de_data = static_cast<jbyteArray>(env->CallObjectMethod(cipher, cipherDoFinalId, data_));

    env->ReleaseByteArrayElements(byteKey_, byteKey, 0);
    env->DeleteLocalRef(system);
    env->DeleteLocalRef(spcretKeySpec);
    env->DeleteLocalRef(cipher);
    env->ReleaseByteArrayElements(data_, data, 0);
    env->DeleteLocalRef(algorithm);
    env->DeleteLocalRef(transformation);
    LOGE("解密完成");

    return de_data;
}


JNIEXPORT void throwJNIException(JNIEnv* pEnv) {
    //注意JNIException的路径
    jclass lClass = pEnv->FindClass("com/soullistener/jnipratice/JNIException");
    if (lClass != NULL) {
        pEnv->ThrowNew(lClass, "Throw JNIException");
        //如果我们长时间不再需要引用这个异常类时，可以使用DeleteLocalRef()来解除它。
        pEnv->DeleteLocalRef(lClass);
    }
}

void handler(int sig) {
    //解除绑定到信号上的方法
    signal(sig, SIG_DFL);
    throwJNIException(penv);
    longjmp (jumpflg, 1);
}

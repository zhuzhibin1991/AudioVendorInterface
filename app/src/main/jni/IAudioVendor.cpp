//
// Created by zhibinzhu on 2019/9/12.
//
#include <string>
#include "pch.h"
#include "com_pateo_audiovendorinterface_IAudioVendor.h"
#include "VirtualAudioType.h"
#include "VirtualStreamData.h"

#ifndef NELEM
# define NELEM(x) ((int) (sizeof(x) / sizeof((x)[0])))
#endif

using namespace std;
using namespace Dmsdp;

JNIEnv *env = NULL;
static const char *const kClassIAudioVendor =
        "com/pateo/audiovendorinterface/IAudioVendor";
static const char *const kClassAudioCapability =
        "com/pateo/audiovendorinterface/AudioCapability";
static const char *const kClassAudioProfile =
        "com/pateo/audiovendorinterface/AudioProfile";
static const char *const kClassVirtualStreamData =
        "com/pateo/audiovendorinterface/VirtualStreamData";
static const char *const kClassVirtualStreamDataHeader =
        "com/pateo/audiovendorinterface/VirtualStreamDataHeader";

void printVector(vector<AudioCapability> vector) {
    for (int i = 0; i < vector.size(); i++) {
        LOGI("zhibinzhu vector[%d]:\n", i);
        LOGI("zhibinzhu serviceId:%s\n", vector[i].serviceId.c_str());
        LOGI("zhibinzhu type:%d\n", vector[i].type);
        std::vector<AudioProfile> _profiles;
        _profiles.assign(vector[i].profiles.begin(), vector[i].profiles.end());
        for (int j = 0; j < _profiles.size(); j++) {
            LOGI("zhibinzhu profiles[%d]:\n", j);
            LOGI("zhibinzhu sampleRates[%d]:%d\n", j, _profiles[j].sampleRates);
            LOGI("zhibinzhu channelMask[%d]:%d\n", j, _profiles[j].channelMask);
            LOGI("zhibinzhu format[%d]:%d\n", j, _profiles[j].format);
        }
        std::vector<AudioCodec> _codecs;
        _codecs.assign(vector[i].codecs.begin(), vector[i].codecs.end());
        for (int k = 0; k < _codecs.size(); k++) {
            LOGI("zhibinzhu codecs[%d]:%d\n", k, _codecs[k]);
        }
        LOGI("zhibinzhu -----AudioCapability-----\n");
    }
}

/**
 * 获取音频设备能力
 * @return vector<AudioCapability> 音频设备能力集合
 */
std::vector<AudioCapability> _GetAudioCapability() {
    vector<AudioCapability> mAudioCapabilityVector = vector<AudioCapability>();
    if (env == NULL) {
        LOGI("zhibinzhu JNIEnv is NULL");
        return mAudioCapabilityVector;
    }

    jobject audioVendor;
    //IAudioVendor
    jclass cIAudioVendor = env->FindClass(kClassIAudioVendor);
    jmethodID _constructMid = env->GetMethodID(cIAudioVendor, "<init>", "()V");
    if (_constructMid != 0) {
        audioVendor = env->NewObject(cIAudioVendor, _constructMid);
        LOGI("zhibinzhu IAudioVendor CLASS init ok.\n");
    } else {
        LOGI("zhibinzhu IAudioVendor CLASS init fail...\n");
    }
    jmethodID _getAudioCapabilityMid = env->GetMethodID(cIAudioVendor, "GetAudioCapability",
                                                        "()Ljava/util/ArrayList;");

    //AudioCapability
    jclass cAudioCapability = env->FindClass(kClassAudioCapability);
    jmethodID _getServiceIdMid = env->GetMethodID(cAudioCapability, "getServiceId",
                                                  "()Ljava/lang/String;");
    jmethodID _getTypeMid = env->GetMethodID(cAudioCapability, "getType", "()I");
    jmethodID _getProfilesMid = env->GetMethodID(cAudioCapability, "getProfiles",
                                                 "()Ljava/util/ArrayList;");
    jmethodID _getCodecsMid = env->GetMethodID(cAudioCapability, "getCodecs",
                                               "()Ljava/util/ArrayList;");

    //AudioProfile
    jclass cAudioProfile = env->FindClass(kClassAudioProfile);
    jmethodID _getSampleRatesMid = env->GetMethodID(cAudioProfile, "getSampleRates", "()I");
    jmethodID _getChannelMaskMid = env->GetMethodID(cAudioProfile, "getChannelMask", "()I");
    jmethodID _getFormatMid = env->GetMethodID(cAudioProfile, "getFormat", "()I");

    jobject listObj = env->CallObjectMethod(audioVendor, _getAudioCapabilityMid);
    jclass cArrayList = env->GetObjectClass(listObj);       //定义ArrayList类对象
    jmethodID _listget = env->GetMethodID(cArrayList, "get", "(I)Ljava/lang/Object;");
    jmethodID _listsize = env->GetMethodID(cArrayList, "size", "()I");
    jint listObjSize = env->CallIntMethod(listObj, _listsize);

    for (int i = 0; i < listObjSize; i++) {
        AudioCapability audioCapability;
        jobject audioCapabilityObj = env->CallObjectMethod(listObj, _listget, i);
        jstring _serviceId = (jstring) env->CallObjectMethod(audioCapabilityObj, _getServiceIdMid);
        const char *_serviceIdStr = env->GetStringUTFChars(_serviceId, JNI_FALSE);
        string serviceId = _serviceIdStr;
        //释放资源，否则会导致JVM内存泄露
        env->ReleaseStringUTFChars(_serviceId, _serviceIdStr);
        audioCapability.serviceId = serviceId;

        jint _type = env->CallIntMethod(audioCapabilityObj, _getTypeMid);
        //强制类型转换
        audioCapability.type = static_cast<AudioDevice>(_type);

        jobject _profiles = env->CallObjectMethod(audioCapabilityObj, _getProfilesMid);
        jint listProfilesSize = env->CallIntMethod(_profiles, _listsize);
        vector<AudioProfile> mAudioProfileVector;
        for (int j = 0; j < listProfilesSize; j++) {
            AudioProfile audioProfile;
            jobject audioProfileObj = env->CallObjectMethod(_profiles, _listget, j);
            jint _sampleRates = env->CallIntMethod(audioProfileObj, _getSampleRatesMid);
            jint _channelMask = env->CallIntMethod(audioProfileObj, _getChannelMaskMid);
            jint _format = env->CallIntMethod(audioProfileObj, _getFormatMid);
            audioProfile.sampleRates = static_cast<AudioSampleRates>(_sampleRates);
            audioProfile.channelMask = static_cast<AudioChannelMasks>(_channelMask);
            audioProfile.format = static_cast<AudioFormats>(_format);
            mAudioProfileVector.push_back(audioProfile);
        }
        audioCapability.profiles.assign(mAudioProfileVector.begin(), mAudioProfileVector.end());

        jobject _codecs = env->CallObjectMethod(audioCapabilityObj, _getCodecsMid);
        jint listCodecsSize = env->CallIntMethod(_codecs, _listsize);
        vector<AudioCodec> mAudioCodecVector;
        for (int k = 0; k < listCodecsSize; k++) {
            AudioCodec audioCodec;
            jobject _codec = env->CallObjectMethod(_codecs, _listget, k);
            jclass cInteger = env->GetObjectClass(_codec);
            jmethodID _intValueMid = env->GetMethodID(cInteger, "intValue", "()I");
            jint codec = env->CallIntMethod(_codec, _intValueMid);
            LOGI("zhibinzhu 111 codec = %d", codec);
            audioCodec = static_cast<AudioCodec>(codec);
            //及时回收内存
            env->DeleteLocalRef(_codec);
            mAudioCodecVector.push_back(audioCodec);
        }
        audioCapability.codecs.assign(mAudioCodecVector.begin(), mAudioCodecVector.end());
        mAudioCapabilityVector.push_back(audioCapability);
    }
    printVector(mAudioCapabilityVector);
    return mAudioCapabilityVector;
}

jstring StringToJString(JNIEnv *env, const std::string &nativeString) {
    return env->NewStringUTF(nativeString.c_str());
}

// 获取系统的当前时间，单位微秒(us)
int64_t GetSysTimeMicros() {
#ifdef _WIN32
    // 从1601年1月1日0:0:0:000到1970年1月1日0:0:0:000的时间(单位100ns)
#define EPOCHFILETIME   (116444736000000000UL)
    FILETIME ft;
    LARGE_INTEGER li;
    int64_t tt = 0;
    GetSystemTimeAsFileTime(&ft);
    li.LowPart = ft.dwLowDateTime;
    li.HighPart = ft.dwHighDateTime;
    // 从1970年1月1日0:0:0:000到现在的微秒数(UTC时间)
    tt = (li.QuadPart - EPOCHFILETIME) /10;
    return tt;
#else
    timeval tv;
    gettimeofday(&tv, 0);
    return (int64_t) tv.tv_sec * 1000000 + (int64_t) tv.tv_usec;
#endif // _WIN32
    return 0;
}

/**
 * 播放音频数据
 * @param serviceId 音频设备Id
 * @param sessionId 会话ID
 * @param data 音频数据
 * @return 播放音频字节数
 */
int _WriteStreamBuffer(string serviceId, int sessionId, VirtualStreamData data) {
    if (env == NULL) {
        LOGI("zhibinzhu JNIEnv is NULL");
        return -1;
    }

    //IAudioVendor
    jclass cIAudioVendor = env->FindClass(kClassIAudioVendor);
    jmethodID _constructMid = env->GetMethodID(cIAudioVendor, "<init>", "()V");
    jmethodID _writeStreamBufferMid = env->GetMethodID(cIAudioVendor, "WriteStreamBuffer",
                                                       "(Ljava/lang/String;ILcom/pateo/audiovendorinterface/VirtualStreamData;)I");
    jobject audioVendor;
    if (_constructMid != 0) {
        audioVendor = env->NewObject(cIAudioVendor, _constructMid);
        LOGI("zhibinzhu IAudioVendor CLASS init ok.\n");
    } else {
        LOGI("zhibinzhu IAudioVendor CLASS init fail...\n");
    }
    //Java ArrayList
    jclass cArrayList = env->FindClass("java/util/ArrayList");       //定义ArrayList类对象
    jmethodID _listconstruct = env->GetMethodID(cArrayList, "<init>", "()V");
    jmethodID _listadd = env->GetMethodID(cArrayList, "add", "(Ljava/lang/Object;)Z");
    //Java Integer
    jclass cInteger = env->FindClass("java/lang/Integer");
    jmethodID _integerIntConstructMid = env->GetMethodID(cInteger, "<init>", "(I)V");
    //VirtualStreamDataHeader
    jclass cVirtualStreamDataHeader = env->FindClass(kClassVirtualStreamDataHeader);
    jmethodID _constructDataHeaderMid = env->GetMethodID(cVirtualStreamDataHeader, "<init>", "()V");
    jmethodID _setTypeMid = env->GetMethodID(cVirtualStreamDataHeader, "setType", "(I)V");
    jmethodID _setLengthMid = env->GetMethodID(cVirtualStreamDataHeader, "setLength", "(I)V");
    jmethodID _setReservedMid = env->GetMethodID(cVirtualStreamDataHeader, "setReserved",
                                                 "(Ljava/util/ArrayList;)V");

    //convert native VirtualStreamData to Java VirtualStreamData
    jobject virtualStreamDataHeader;
    if (_constructDataHeaderMid != 0) {
        virtualStreamDataHeader = env->NewObject(cVirtualStreamDataHeader, _constructDataHeaderMid);
        LOGI("zhibinzhu VirtualStreamDataHeader CLASS init ok.\n");
    } else {
        LOGI("zhibinzhu VirtualStreamDataHeader CLASS init fail...\n");
    }
    //VirtualStreamDataHeader::type
    env->CallVoidMethod(virtualStreamDataHeader, _setTypeMid, (jint) data.head->type);
    //VirtualStreamDataHeader::length
    env->CallVoidMethod(virtualStreamDataHeader, _setLengthMid, (jint) data.head->length);
//    list<int> _reserved(data.head->reserved);
    list<int>::iterator iter;
    jobject reservedListObj = env->NewObject(cArrayList, _listconstruct);
    for (iter = data.head->reserved.begin(); iter != data.head->reserved.end(); iter++) {
        int tmp = *iter;
        LOGI("zhibinzhu native jni reserved:%d", tmp);
        jobject tmpIntegerObj = env->NewObject(cInteger, _integerIntConstructMid, tmp);
        jboolean ret = env->CallBooleanMethod(reservedListObj, _listadd, tmpIntegerObj);
        env->DeleteLocalRef(tmpIntegerObj);
    }
    //VirtualStreamDataHeader::reserved
    env->CallVoidMethod(virtualStreamDataHeader, _setReservedMid, reservedListObj);

    //VirtualStreamData
    jclass cVirtualStreamData = env->FindClass(kClassVirtualStreamData);
    jmethodID _constructDataMid = env->GetMethodID(cVirtualStreamData, "<init>", "()V");
    jmethodID _setDataMid = env->GetMethodID(cVirtualStreamData, "setData", "([B)V");
    jmethodID _setmTimeStampUsMid = env->GetMethodID(cVirtualStreamData, "setmTimeStampUs", "(J)V");
    jmethodID _setHeadMid = env->GetMethodID(cVirtualStreamData, "setHead",
                                             "(Lcom/pateo/audiovendorinterface/VirtualStreamDataHeader;)V");
    jobject virtualStreamData;
    if (_constructDataMid != 0) {
        virtualStreamData = env->NewObject(cVirtualStreamData, _constructDataMid);
        LOGI("zhibinzhu VirtualStreamData CLASS init ok.\n");
    } else {
        LOGI("zhibinzhu VirtualStreamData CLASS init fail...\n");
    }
    //VirtualStreamData::data
    jbyteArray dataJava = env->NewByteArray(data.head->length);
    //此处无符号转有符号有待确认
    env->SetByteArrayRegion(dataJava, 0, data.head->length, (const jbyte *) data.data);
    env->CallVoidMethod(virtualStreamData, _setDataMid, dataJava);
    //VirtualStreamData::mTimeStampUs
    env->CallVoidMethod(virtualStreamData, _setmTimeStampUsMid, (jlong) data.mTimeStampUs);
    //VirtualStreamData::head
    env->CallVoidMethod(virtualStreamData, _setHeadMid, virtualStreamDataHeader);

    //convert native serviceId to Java serviceId
    jstring serviceIdJava = StringToJString(env, serviceId);
    //convert native sessionId to Java sessionId
    jint sessionIdJava = (jint) sessionId;

    //Call the "WriteStreamBuffer" method of the Java(IAudioVendor) object
    int dataSize = (int) env->CallIntMethod(audioVendor, _writeStreamBufferMid, serviceIdJava,
                                            sessionIdJava, virtualStreamData);
    LOGI("zhibinzhu native jni _WriteStreamBuffer dataSize=%d", dataSize);
    return dataSize;
}

jstring com_pateo_audiovendorinterface_IAudioVendor_test
        (JNIEnv *env, jobject audioVendor) {
    _GetAudioCapability();

    VirtualStreamData virtualStreamData;
    uint8_t *data = (uint8_t *) "I like Cpp";
    virtualStreamData.data = data;
    virtualStreamData.mTimeStampUs = GetSysTimeMicros();
    VirtualStreamDataHeader header = VirtualStreamDataHeader();
    header.type = 5;
    header.length = 10;
    header.reserved = list<int>(4, 100);
    virtualStreamData.head = &header;
    LOGI("zhibinzhu com_pateo_audiovendorinterface_IAudioVendor_test");
    _WriteStreamBuffer("speaker1", 100, virtualStreamData);
    /*//IAudioVendor
    jclass cIAudioVendor=env->FindClass(kClassIAudioVendor);
    jmethodID _getAudioCapability = env->GetMethodID(cIAudioVendor,"GetAudioCapability","()Ljava/util/ArrayList;");

    //AudioCapability
    jclass cAudioCapability=env->FindClass(kClassAudioCapability);
    jmethodID _getServiceIdMid=env->GetMethodID(cAudioCapability,"getServiceId","()Ljava/lang/String;");
    jmethodID _getTypeMid=env->GetMethodID(cAudioCapability,"getType","()I");
    jmethodID _getProfilesMid=env->GetMethodID(cAudioCapability,"getProfiles","()Ljava/util/ArrayList;");
    jmethodID _getCodecsMid=env->GetMethodID(cAudioCapability,"getCodecs","()Ljava/util/ArrayList;");

    //AudioProfile
    jclass cAudioProfile=env->FindClass(kClassAudioProfile);
    jmethodID _getSampleRatesMid=env->GetMethodID(cAudioProfile,"getSampleRates","()I");
    jmethodID _getChannelMaskMid=env->GetMethodID(cAudioProfile,"getChannelMask","()I");
    jmethodID _getFormatMid=env->GetMethodID(cAudioProfile,"getFormat","()I");

    jobject listObj=env->CallObjectMethod(audioVendor,_getAudioCapability);
    jclass cArrayList=env->GetObjectClass(listObj);       //定义ArrayList类对象
    jmethodID _listget=env->GetMethodID(cArrayList,"get","(I)Ljava/lang/Object;");
    jmethodID _listsize = env->GetMethodID(cArrayList,"size","()I");
    jint listObjSize = env->CallIntMethod(listObj,_listsize);

    vector<AudioCapability> mAudioCapabilityVector;

    for(int i=0;i<listObjSize;i++)
    {
        AudioCapability audioCapability;
        jobject audioCapabilityObj=env->CallObjectMethod(listObj,_listget,i);
        jstring _serviceId=(jstring)env->CallObjectMethod(audioCapabilityObj,_getServiceIdMid);
        const char* _serviceIdStr = env->GetStringUTFChars(_serviceId, JNI_FALSE);
        string serviceId=_serviceIdStr;
        //释放资源，否则会导致JVM内存泄露
        env->ReleaseStringUTFChars(_serviceId, _serviceIdStr);
        audioCapability.serviceId=serviceId;

        jint _type=env->CallIntMethod(audioCapabilityObj,_getTypeMid);
        //强制类型转换
        audioCapability.type=static_cast<AudioDevice>(_type);

        jobject _profiles=env->CallObjectMethod(audioCapabilityObj,_getProfilesMid);
        jint listProfilesSize = env->CallIntMethod(_profiles,_listsize);
        vector<AudioProfile> mAudioProfileVector;
        for(int j=0;j<listProfilesSize;j++){
            AudioProfile audioProfile;
            jobject audioProfileObj=env->CallObjectMethod(_profiles,_listget,j);
            jint _sampleRates = env->CallIntMethod(audioProfileObj,_getSampleRatesMid);
            jint _channelMask = env->CallIntMethod(audioProfileObj,_getChannelMaskMid);
            jint _format = env->CallIntMethod(audioProfileObj,_getFormatMid);
            audioProfile.sampleRates=static_cast<AudioSampleRates>(_sampleRates);
            audioProfile.channelMask=static_cast<AudioChannelMasks>(_channelMask);
            audioProfile.format=static_cast<AudioFormats>(_format);
            mAudioProfileVector.push_back(audioProfile);
        }
        audioCapability.profiles.assign(mAudioProfileVector.begin(),mAudioProfileVector.end());

        jobject _codecs=env->CallObjectMethod(audioCapabilityObj,_getCodecsMid);
        jint listCodecsSize = env->CallIntMethod(_codecs,_listsize);
        vector<AudioCodec> mAudioCodecVector;
        for(int k=0;k<listCodecsSize;k++){
            AudioCodec audioCodec;
            jobject _codec = env->CallObjectMethod(_codecs,_listget,k);
            jclass cInteger=env->GetObjectClass(_codec);
            jmethodID _intValueMid = env->GetMethodID(cInteger, "intValue", "()I");
            jint codec=env->CallIntMethod(_codec, _intValueMid);
            LOGI("zhibinzhu 111 codec = %d",codec);
            audioCodec=static_cast<AudioCodec>(codec);
            //及时回收内存
            env->DeleteLocalRef(_codec);
            mAudioCodecVector.push_back(audioCodec);
        }
        audioCapability.codecs.assign(mAudioCodecVector.begin(),mAudioCodecVector.end());
        mAudioCapabilityVector.push_back(audioCapability);
    }
    printVector(mAudioCapabilityVector);*/
    return (env)->NewStringUTF("This is aaaabbbbccc NDK Demo.");
}

JNINativeMethod gMethods[] = {
        {"test", "()Ljava/lang/String;", (void *) com_pateo_audiovendorinterface_IAudioVendor_test}
};

jint registerJNINativeMethods(JNIEnv *env) {
    jclass clazz = env->FindClass(kClassIAudioVendor);
    return env->RegisterNatives(clazz, gMethods, NELEM(gMethods));
}

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    LOGI("+++++JNI_OnLoad+++++");
//    JNIEnv* env = NULL;
    jint result = -1;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_4) == JNI_OK) {
        if (NULL != env && registerJNINativeMethods(env) == JNI_OK) {
            result = JNI_VERSION_1_4;
        }
    }
    return result;
}

//JNIEXPORT jstring JNICALL Java_com_pateo_audiovendorinterface_IAudioVendor_test
//        (JNIEnv *env, jobject audioVendor) {
////    jclass _IAudioVendor=env->FindClass(kClassIAudioVendor);
////    jmethodID _test = env->GetMethodID(_IAudioVendor,"test","()Ljava/lang/String;");
////    return (jstring)env->CallObjectMethod(audioVendor,_test);
//    return (env)->NewStringUTF( "This is aaaaa NDK Demo.");
//}


//std::vector<AudioCapability> _GetAudioCapability(){
//
//}
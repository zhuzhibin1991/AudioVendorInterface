package com.pateo.audiovendorinterface;

import android.util.Log;

import java.util.ArrayList;

public class IAudioVendor {
    private static final String TAG="IAudioVendor";

    static {
        System.loadLibrary("AudioVendorInterface");
    }

    /**
     * 获取音频设备能力
     * @return ArrayList<AudioCapability> 音频设备能力集合
     */
    public ArrayList<AudioCapability> GetAudioCapability() {
        ArrayList<AudioCapability> audioCapabilities = new ArrayList();
        AudioCapability audioCapability=new AudioCapability();
        audioCapability.setServiceId(AudioServiceId.OUT_SPEAKER);
        audioCapability.setType(AudioDevice.AUDIO_DEVICE_TYPE_SPEAKER);
        ArrayList<AudioProfile> profiles=new ArrayList();
        profiles.add(new AudioProfile(AudioSampleRates.AUDIO_SAMPLE_RATE_44_1K,AudioChannelMasks.AUDIO_CHANNEL_OUT_STEREO,AudioCodec.FORMAT_PCM));
        audioCapability.setProfiles(profiles);
        ArrayList<Integer> codecs=new ArrayList();
        codecs.add(AudioCodec.FORMAT_PCM);
        audioCapability.setCodecs(codecs);
        audioCapabilities.add(audioCapability);
        return audioCapabilities;
    }

    /**
     * 播放音频数据
     * @param serviceId 音频设备Id
     * @param sessionId 会话ID
     * @param data 音频数据
     * @return 播放音频字节数
     */
    public int WriteStreamBuffer(String serviceId, int sessionId, VirtualStreamData data){
        Log.d(TAG,"WriteStreamBuffer");
        Log.d(TAG,"serviceId:"+serviceId);
        Log.d(TAG,"sessionId:"+sessionId);
        Log.d(TAG,"data:"+data.toString());
        return data.getData().length;
    }

    public native String test();

}

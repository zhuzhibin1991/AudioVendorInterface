package com.pateo.audiovendorinterface;

import java.util.ArrayList;
import java.lang.Integer;

public class AudioCapability {
    private String serviceId;
    private int type;
    private ArrayList<AudioProfile> profiles;
    private ArrayList<Integer> codecs;

    public AudioCapability() {
    }

    public AudioCapability(String serviceId, int type, ArrayList<AudioProfile> profiles, ArrayList<Integer> codecs) {
        this.serviceId = serviceId;
        this.type = type;
        this.profiles = profiles;
        this.codecs = codecs;
    }

    public String getServiceId() {
        return serviceId;
    }

    public void setServiceId(String serviceId) {
        this.serviceId = serviceId;
    }

    public int getType() {
        return type;
    }

    public void setType(int type) {
        this.type = type;
    }

    public ArrayList<AudioProfile> getProfiles() {
        return profiles;
    }

    public void setProfiles(ArrayList<AudioProfile> profiles) {
        this.profiles = profiles;
    }

    public ArrayList<Integer> getCodecs() {
        return codecs;
    }

    public void setCodecs(ArrayList<Integer> codecs) {
        this.codecs = codecs;
    }
}

class AudioDevice {
    public static final int AUDIO_DEVICE_TYPE_SPEAKER = 0;
    public static final int AUDIO_DEVICE_TYPE_MIC = 1;
}

class AudioSampleRates {
    public static final int AUDIO_SAMPLE_RATE_8K = 8000;
    public static final int AUDIO_SAMPLE_RATE_16K = 16000;
    public static final int AUDIO_SAMPLE_RATE_32K = 32000;
    public static final int AUDIO_SAMPLE_RATE_44_1K = 44100;
    public static final int AUDIO_SAMPLE_RATE_48K = 48000;

}

class AudioChannelMasks {
    public static final int AUDIO_CHANNEL_OUT_MONO = 0x1;
    public static final int AUDIO_CHANNEL_OUT_STEREO = 0x3;
    public static final int AUDIO_CHANNEL_IN_MONO = 0x10;
    public static final int AUDIO_CHANNEL_IN_STEREO = 0xC;
}

class AudioFormats {
    public static final int AUDIO_FORMAT_PCM_16_BIT = 0x1;
    public static final int AUDIO_FORMAT_PCM_8_BIT = 0x2;
    public static final int AUDIO_FORMAT_PCM_32_BIT = 0x3;
    public static final int AUDIO_FORMAT_PCM_8_24_BIT = 0x4;
}

class AudioStatus {
    public static final int AUDIO_STATUS_NORMAL = 0x1;
    public static final int AUDIO_STATUS_BUSY = 0x2;
    public static final int AUDIO_STATUS_ABNORMAL = 0x3;
}

class AudioCodec {
    public static final int FORMAT_AAC = 0;
    public static final int FORMAT_PCM = 1;
}

class AudioStreamType {
    public static final int AUDIO_STREAM_VOICE_CALL = 0;
    public static final int AUDIO_STREAM_SYSTEM = 1;
    public static final int AUDIO_STREAM_RING = 2;
    public static final int AUDIO_STREAM_MUSIC = 3;
    public static final int AUDIO_STREAM_ALARM = 4;
    public static final int AUDIO_STREAM_NOTIFICATION = 5;
    public static final int AUDIO_STREAM_BLUETOOTH_SCO = 6;
    public static final int AUDIO_STREAM_ENFORCED_AUDIBLE = 7;
    public static final int AUDIO_STREAM_DTMF = 8;
    public static final int AUDIO_STREAM_TTS = 9;
    public static final int AUDIO_STREAM_ACCESSIBILITY = 10;
}

class AudioSource {
    public static final int AUDIO_SOURCE_MIC = 1;
    public static final int AUDIO_SOURCE_VOICE_UPLINK = 2;
    public static final int AUDIO_SOURCE_VOICE_DOWNLINK = 3;
    public static final int AUDIO_SOURCE_VOICE_CALL = 4;
    public static final int AUDIO_SOURCE_CAMCORDER = 5;
    public static final int AUDIO_SOURCE_VOICE_RECOGNITION = 6;
    public static final int AUDIO_SOURCE_VOICE_COMMUNICATION = 7;
    public static final int AUDIO_SOURCE_REMOTE_SUBMIX = 8;
    public static final int AUDIO_SOURCE_UNPROCESSED = 9;
    public static final int AUDIO_SOURCE_FM_TUNER = 1998;
}

class AudioServiceId {
    public static final String OUT_SPEAKER = "speaker";
    public static final String IN_SPEAKER_MIC = "speaker-mic";
}

class AudioProfile {
    private int sampleRates;
    private int channelMask;
    private int format;

    public AudioProfile(int sampleRates, int channelMask, int format) {
        this.sampleRates = sampleRates;
        this.channelMask = channelMask;
        this.format = format;
    }

    public int getSampleRates() {
        return sampleRates;
    }

    public void setSampleRates(int sampleRates) {
        this.sampleRates = sampleRates;
    }

    public int getChannelMask() {
        return channelMask;
    }

    public void setChannelMask(int channelMask) {
        this.channelMask = channelMask;
    }

    public int getFormat() {
        return format;
    }

    public void setFormat(int format) {
        this.format = format;
    }
}
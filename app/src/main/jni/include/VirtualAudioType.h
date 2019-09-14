/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2019-2019. All rights reserved.
 * Description: virtual audio type
 * Author: gongqinghua
 * Create: 2019-04-13
 */
#ifndef VIRTUAL_AUDIO_TYPE_H
#define VIRTUAL_AUDIO_TYPE_H

#include <vector>
#include <string>

namespace Dmsdp {
    enum AudioDevice{
        AUDIO_DEVICE_TYPE_SPEAKER = 0u,
        AUDIO_DEVICE_TYPE_MIC = 1u
    };

    enum AudioSampleRates{
        AUDIO_SAMPLE_RATE_8K = 8000u,
        AUDIO_SAMPLE_RATE_16K = 16000u,
        AUDIO_SAMPLE_RATE_32K = 32000u,
        AUDIO_SAMPLE_RATE_44_1K = 44100u,
        AUDIO_SAMPLE_RATE_48K = 48000u
    };

    enum AudioChannelMasks{
        AUDIO_CHANNEL_OUT_MONO = 0x1u,
        AUDIO_CHANNEL_OUT_STEREO = 0x3u,
        AUDIO_CHANNEL_IN_MONO = 0x10u,
        AUDIO_CHANNEL_IN_STEREO = 0xCu
    };

    enum AudioFormats{
        AUDIO_FORMAT_PCM_16_BIT = 0x1u,
        AUDIO_FORMAT_PCM_8_BIT = 0x2u,
        AUDIO_FORMAT_PCM_32_BIT = 0x3u,
        AUDIO_FORMAT_PCM_8_24_BIT = 0x4u
    };

    enum AudioStatus{
        AUDIO_STATUS_NORMAL = 0x1u,
        AUDIO_STATUS_BUSY = 0x2u,
        AUDIO_STATUS_ABNORMAL = 0x3u
    };

    enum AudioCodec{
        FORMAT_AAC = 0,
        FORMAT_PCM = 1
    };

    enum AudioStreamType{
        AUDIO_STREAM_VOICE_CALL = 0,
        AUDIO_STREAM_SYSTEM = 1,
        AUDIO_STREAM_RING = 2,
        AUDIO_STREAM_MUSIC = 3,
        AUDIO_STREAM_ALARM = 4,
        AUDIO_STREAM_NOTIFICATION = 5,
        AUDIO_STREAM_BLUETOOTH_SCO = 6,
        AUDIO_STREAM_ENFORCED_AUDIBLE = 7,
        AUDIO_STREAM_DTMF = 8,
        AUDIO_STREAM_TTS = 9,
        AUDIO_STREAM_ACCESSIBILITY = 10
    };

    enum AudioSource {
        AUDIO_SOURCE_MIC = 1,
        AUDIO_SOURCE_VOICE_UPLINK = 2,
        AUDIO_SOURCE_VOICE_DOWNLINK = 3,
        AUDIO_SOURCE_VOICE_CALL = 4,
        AUDIO_SOURCE_CAMCORDER = 5,
        AUDIO_SOURCE_VOICE_RECOGNITION = 6,
        AUDIO_SOURCE_VOICE_COMMUNICATION = 7,
        AUDIO_SOURCE_REMOTE_SUBMIX = 8,
        AUDIO_SOURCE_UNPROCESSED = 9,
        AUDIO_SOURCE_FM_TUNER = 1998
    };

    struct AudioProfile
    {
        AudioSampleRates sampleRates;
        AudioChannelMasks channelMask;
        AudioFormats format;
    };

    struct AudioCapability
    {
        std::string serviceId;
        AudioDevice type;
		std::vector<AudioProfile> profiles;
        std::vector<AudioCodec> codecs;
    };
}

#endif
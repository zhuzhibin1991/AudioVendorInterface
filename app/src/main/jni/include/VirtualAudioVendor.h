/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2019-2019. All rights reserved.
 * Description: virtual audio
 * Author: gongqinghua
 * Create: 2019-07-08
 */

#ifndef VIRTUAL_AUDIO_VENDOR_H
#define VIRTUAL_AUDIO_VENDOR_H
#include <map>
#include <vector>
#include <string>
#include "VirtualStreamData.h"
#include "VirtualAudioType.h"

namespace Dmsdp {
    class VirtualAudioVendor {

    public:
        virtual ~VirtualAudioVendor() {};

        /*
         * get audio device capacity
         * capabilities: audio capacity struct
         */
        virtual std::vector<AudioCapability> GetAudioCapability()= 0;

        /*
         * set audio track proile
         * serviceId: speaker id
         * sessionId: transport session id
         * profiles keys:"channel"、"format"、"sampleRate"、"codec"
         */
        virtual int SetAudioParameter(string serviceId, int sessionId, map<string, int> profiles)= 0;

        /*
         * open audio track and write track data
         * serviceId: speaker id
         * sessionId: transport session id
         * data:audio datas struct 
         */
        virtual int WriteStreamBuffer(string serviceId, int sessionId, VirtualStreamData data)= 0;

        /*
         * close audio track
         * sessionId: transport session id
         */
        virtual int CloseAudioTrack(int sessionId)= 0;

        /*
         * open audio record
         * serviceId: mic id
         * sessionId: transport session id
         * inputSource: the recording source
         * profiles keys:"channel"、"format"、"sampleRate"、"codec"
         */
        virtual int OpenAudioRecord(string serviceId, int sessionId, int inputSource, map<string, int> profiles)= 0;

        /*
         * read audio record data
         * serviceId: speaker id
         * sessionId: transport session id
         * data:audio datas struct 
         */
        virtual int ReadStreamBuffer(string serviceId, int sessionId, VirtualStreamData data)= 0;

        /*
         * close audio record
         * sessionId: transport session id
         */
        virtual int CloseAudioRecord(int sessionId)= 0;

    };
   
    /*
     *  VirtualAudioVendor object pointer for operater native audio by manufacturer implemented so
     */
    extern "C" int32_t CreateNativeAudioHandle(VirtualAudioVendor *&client);
}
#endif
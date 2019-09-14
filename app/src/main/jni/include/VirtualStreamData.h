/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2019-2019. All rights reserved.
 * Description: virtual audio header
 * Author: gongqinghua
 * Create: 2019-04-13
 */
#ifndef AUDIO_VIRTUALSTREAMDATA_H
#define AUDIO_VIRTUALSTREAMDATA_H

#include <string>
#include <list>
using namespace std;

struct VirtualStreamDataHeader {
	int type;
    int length;
    list<int> reserved;
	explicit VirtualStreamDataHeader(): type(0), length(0)
    {
    }
	explicit VirtualStreamDataHeader(int streamType, int size) : type(streamType), length(size)
	{
    }
};

struct VirtualStreamData {
	uint8_t *data;
    int64_t mTimeStampUs;
    VirtualStreamDataHeader *head;
	explicit VirtualStreamData(): data(nullptr), mTimeStampUs(0), head(nullptr)
	{
	}

	explicit VirtualStreamData(VirtualStreamDataHeader *header, uint8_t *streamData)
		: data(streamData), mTimeStampUs(0), head(header)
	{
	}
};

#endif
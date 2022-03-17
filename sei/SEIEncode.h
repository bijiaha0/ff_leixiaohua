#pragma once
#ifndef SEIENCODE_H
#define SEIENCODE_H

#include "Encode.h"
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>
#include "libavutil/dict.h"

class SEIEncode
        :public OriginalEncode
{
public:
    SEIEncode();
    virtual int EncodeVideo(AVFrame* frame);
    virtual int FlushVideo();
};

#endif
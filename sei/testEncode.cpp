#pragma once

#include "EvHeade.h"
#include "Encode.h"
#include "SEIEncode.h"
#include "exterlFunction.h"

//file = "../1.yuv"
int testEncode(const char * infile,const char * outfile)
{
    int in_w = 480, in_h = 272;                              //Input data's width and height


    SEIEncode encode;
    int ret = encode.Open(outfile);
    if (ret != 0)
    {
        return -1;
    }
    int frameRate = 5;
    ret = encode.NewVideoStream(in_w, in_h, AV_PIX_FMT_YUV420P, frameRate);
    if (ret != 0)
    {
        return -1;
    }
    ret = encode.WriteHeader();
    if (ret != 0)
    {
        //写头失败
        return -1;
    }

    FILE *in_file = fopen(infile, "rb");   //Input raw YUV data

    int framenum = 100;                                   //Frames to encode

    AVStream * stream = encode.GetVideoStream();
    AVCodecContext * codecContext = encode.GetVideoContext();

    AVFrame * frame = av_frame_alloc();
    int picture_size = GetPictureSize(codecContext->pix_fmt, codecContext->width, codecContext->height);
    uint8_t * picture_buf = (uint8_t *)av_malloc(picture_size);
#ifdef USE_NEW_API
    av_image_fill_arrays(frame->data,frame->linesize, picture_buf, codecContext->pix_fmt, codecContext->width, codecContext->height,1);
#else
    avpicture_fill((AVPicture *)frame, picture_buf, codecContext->pix_fmt, codecContext->width, codecContext->height);
#endif
    int y_size = codecContext->width * codecContext->height;

    for (int i = 0; i < framenum; i++)
    {
        //Read raw YUV data
        if (fread(picture_buf, 1, y_size * 3 / 2, in_file) <= 0) {
            printf("Failed to read raw data! \n");
            break;
        }
        else if (feof(in_file)) {
            break;
        }

        frame->data[0] = picture_buf;					// Y
        frame->data[1] = picture_buf + y_size;			// U
        frame->data[2] = picture_buf + y_size * 5 / 4;  // V
        frame->width = codecContext->width;
        frame->height = codecContext->height;
        frame->format = codecContext->pix_fmt;
        //PTS
        //pFrame->pts=i;
        float time = (1 / (frameRate * 1.0));
        frame->pts = (int64_t)(i * time / (av_q2d(stream->time_base)));
        /*frame->pts = i * av_q2d(codecContext->time_base) / av_q2d(stream->time_base);
        frame->pts = av_rescale_q(i,
            codecContext->time_base,
            stream->time_base);*/

        encode.EncodeVideo(frame);
    }

    encode.FlushVideo();

    encode.WriteTrailer();
    encode.Close();


    av_free(picture_buf);
    picture_buf = NULL;
    av_frame_free(&frame);
    return  0;
}
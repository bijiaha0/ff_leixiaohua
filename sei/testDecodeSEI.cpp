#include <sys/time.h>
#include "EvHeade.h"
#include "Encode.h"
#include "SEIEncode.h"
#include "exterlFunction.h"
#include "ImageFile.h"

unsigned long GetTickCount()
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}

//"../Vid0616000023.mp4"
int testDecodeSEI(const char * file)
{
    avcodec_register_all();

    EvoMediaSource source;

    //file += "gopro.mp4";
    EvoMediaSourceConfig config = { false,false };
    int ret = source.Open(file, &config);
    if (ret != 0)
    {
        return -1;
    }

    AVStream * stream = source.GetVideoStream();

    VideoDecoder *decoder = NULL;
    AVCodecContext	*codecContext = NULL;
    bool newContext = true;
    if (newContext) {
        AVCodec *codec = avcodec_find_decoder(AV_CODEC_ID_H264);
        if (!codec) return -1;
        codecContext = avcodec_alloc_context3(codec);

        uint8_t extData[64];
        int size = source.GetExtData(extData, 64);
        codecContext->extradata = extData;
        codecContext->extradata_size = size;

        int rate = source.GetFrameRate();
        int duration = source.GetDuration();

        if (avcodec_open2(codecContext, codec, NULL) < 0)
        {
            return -1;
        }
        decoder = new VideoDecoder(codecContext);
    }
    else
    {
#ifndef USE_NEW_API
        AVCodecContext * sourceContext = stream->codec;
		if (sourceContext != NULL && sourceContext->codec != NULL)
		{
			printf("Stream DECODE:%s\n", sourceContext->codec->name);
		}
		//使用自身解码器解码
		AVCodec *codec = (AVCodec*)sourceContext->codec;
		if (codec == NULL) codec = avcodec_find_decoder(sourceContext->codec_id);

		if (avcodec_open2(sourceContext, codec, NULL) < 0)
		{
			return -1;
		}

		decoder = new VideoDecoder(sourceContext);
#endif
    }

    EvoVideoConvert convert;
    struct EvoVideoInfo info;
    info.Width = 0;
    info.Height = 0;
    info.Format = AV_PIX_FMT_NONE;

    struct EvoVideoInfo des = info;
    des.Width = 3040;
    des.Height = 1520;
    des.Format = AV_PIX_FMT_BGR24;
    convert.Initialize(info, des);
    decoder->Attach(&convert);

#ifndef USE_NEW_API
    AVBitStreamFilterContext *bsfc = av_bitstream_filter_init("h264_mp4toannexb");
#endif
    int index = 0;
    while (true)
    {
        EvoFrame *out = NULL;
        ret = source.ReadFrame(&out);
        if (out != NULL)
        {
            index++;
            uint8_t * buffer = NULL;
            uint32_t count = 0;
            int ret = get_sei_content(out->data, out->size, IMU_UUID, &buffer, &count);
            printf("get_sei_content:%d data:%p size:%d pkt.size:%d\n", ret, buffer, count, out->size);
            if (buffer != NULL)
            {
                if (index == 318)
                {
                    printf("");
                }
                float * imu = (float*)buffer;
                printf("pts:%lld dts:%lld imu:%f  %f  %f  %f  %f  %f  %f  %f  %f\n", out->pts, out->dts, imu[0], imu[1], imu[2], imu[3], imu[4], imu[5], imu[6], imu[7], imu[8]);
                free_sei_content(&buffer);
            }
            else {
                uint8_t* filter_buffer = (uint8_t*)av_malloc(out->size);
                int filter_size = out->size;
                memcpy(filter_buffer, out->data, out->size);
                filter_buffer[0] = 0;
                filter_buffer[1] = 0;
                filter_buffer[2] = 0;
                filter_buffer[3] = 1;
                uint8_t * buffer = NULL;
                uint32_t count = 0;
                int ret = get_sei_content(filter_buffer, filter_size, IMU_UUID, &buffer, &count);
                av_free(filter_buffer);
                printf("get_sei_content:%d data:%p size:%d pkt.size:%d\n", ret, buffer, count, out->size);
                if (buffer != NULL)
                {
                    float * imu = (float*)buffer;
                    printf("pts:%lld dts:%lld imu:%f %f %f %f %f %f %f %f %f\n", out->pts, out->dts, imu[0], imu[1], imu[2], imu[3], imu[4], imu[5], imu[6], imu[7], imu[8]);
                    free_sei_content(&buffer);
                }
                else {
                    printf("no find sei.\n");
                    printf("pts:%lld dts:%lld\n", out->pts, out->dts);
                }
            }


            AVFrame *outFrame = NULL;

            printf("Decode begin:%lld\n", av_gettime() / 1000);
            decoder->DecodeFrame(out, &outFrame);
            printf("Decode end:%lld Success:%d\n", av_gettime() / 1000, (outFrame != NULL));

            if (outFrame != NULL)
            {
                printf("Decode pts:%lld %lld\n", outFrame->pts,outFrame->pkt_dts);
                printf("width:%d height:%d\n", outFrame->width, outFrame->height);
#ifdef _WIN32
                SaveAsBMP(outFrame, outFrame->width, outFrame->height, index, 24);
#endif
                FreeAVFrame(&outFrame);
            }

            EvoFreeFrame(&out);
        }
        if (ret == AVERROR_EOF)
        {
            break;
        }
    }


    AVPacket* empty_packet = av_packet_alloc();
    av_new_packet(empty_packet,0);

    unsigned long time = GetTickCount();

    while (true)
    {
        AVFrame *outFrame = NULL;

        printf("Decode begin:%lld\n", av_gettime() / 1000);
        decoder->Decode(empty_packet, &outFrame);
        printf("Decode end:%lld Success:%d\n", av_gettime() / 1000, (outFrame != NULL));

        if (outFrame != NULL)
        {
            printf("Decode pts:%lld %lld\n", outFrame->pts, outFrame->pkt_dts);
            FreeAVFrame(&outFrame);
        }
        else
        {
            if(GetTickCount() - time > 5000)
            {
                break;
            }
        }
    }
    av_packet_free(&empty_packet);

#ifndef USE_NEW_API
    av_bitstream_filter_close(bsfc);
#endif

    if (decoder != NULL)
    {
        delete decoder;
        decoder = NULL;
    }

    if (codecContext != NULL)
    {
        codecContext->extradata = NULL;
        codecContext->extradata_size = 0;
        avcodec_close(codecContext);
        avcodec_free_context(&codecContext);
    }

    return 0;
}
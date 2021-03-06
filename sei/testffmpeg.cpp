#include "EvHeade.h"
#include "exterlFunction.h"
#include "ImageFile.h"

//file="../1.mp4"
int testFFmpeg(const char * file)
{
    av_register_all();

    AVFormatContext * formatContext = avOpenFile(file);
    if (formatContext == NULL)
    {
        return -1;
    }
    int videoIndex = getStreamId(formatContext);

    if (videoIndex == -1)
    {
        avformat_close_input(&formatContext);
        return -1;
    }

    AVCodecContext * codecContext = openCodecContext(formatContext->streams[videoIndex]);
    if (codecContext == NULL)
    {
        avformat_close_input(&formatContext);
        return -1;
    }

    AVPacket * packet = av_packet_alloc();
    AVPacket * pkt = av_packet_alloc();
    AVFrame * frame = av_frame_alloc();

    while (true)
    {
        int ret = av_read_frame(formatContext, packet);
        if (ret == 0)
        {
            if (packet->stream_index == videoIndex)
            {
                //修改包裹
                //resetPacket(packet, pkt);
                //解码
                ret = decodeVideo(codecContext, packet, frame);
                if (ret == 1)
                {
                    FILE * fp = fopen("../tmp.yuv","wb");
                    void * ptr = frame->data[0];
                    int len = frame->height*frame->width * 3 / 2;
                    size_t ret = fwrite(ptr, len,1,fp);
                    printf("%lld %d\n",ret,errno);
                    //fflush(fp);
                    fclose(fp);
                    av_frame_unref(frame);
                }
                //取出自定义数据
                uint8_t *selfPacket = NULL;
                uint32_t count = 0;
                ret = get_sei_content(packet->data, packet->size, TIME_STAMP_UUID, &selfPacket, &count);
                if (selfPacket != NULL)
                {
                    printf("sei: %s\n", selfPacket);
                    free_sei_content(&selfPacket);
                }

                av_packet_unref(pkt);
            }
        }
        else if (ret == AVERROR_EOF)
        {
            break;
        }
        av_packet_unref(packet);
    }


    av_frame_free(&frame);
    av_packet_free(&packet);
    av_packet_free(&pkt);

    avcodec_close(codecContext);
#ifdef USE_NEW_API
    avcodec_free_context(&codecContext);
#endif
    avformat_close_input(&formatContext);
    return 0;
}
#include <iostream>
#include <fstream>

#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavdevice/avdevice.h"
#include "libavfilter/avfilter.h"

AVCodecContext * CreateContext()
{
    const AVCodec *codec = avcodec_find_decoder(AV_CODEC_ID_AAC);
    AVCodecContext *avCtx = avcodec_alloc_context3(codec);
    return avCtx;
}

int32_t DecodeBuffer(std::ostream &output, uint8_t *pInput, uint32_t cbInputSize, AVCodecContext * pAVContext)
{
    int32_t cbDecoded = 0;

    AVPacket avPacket;
    av_init_packet(&avPacket);

    avPacket.size = cbInputSize;
    avPacket.data = pInput;

    AVFrame * pDecodedFrame = av_frame_alloc();

    int nGotFrame = 0;

    cbDecoded = avcodec_decode_audio4(    pAVContext,
                                          pDecodedFrame,
                                          & nGotFrame,
                                          & avPacket);

    int data_size = av_samples_get_buffer_size( NULL,
                                                pAVContext->ch_layout.nb_channels,
                                                pDecodedFrame->nb_samples,
                                                pAVContext->sample_fmt,
                                                1);

    output.write((const char*)pDecodedFrame->data[0],data_size);


    av_frame_free(&pDecodedFrame);

    return cbDecoded;
}


uint8_t * ReceiveBuffer( uint32_t * cbBufferSize)
{
    // TODO implement

    return NULL;
}
//https://stackoverflow.com/questions/24218527/how-to-decode-one-aac-frame-at-a-time-using-c
int main(int argc, char *argv[])
{
    int nResult = 0;
    AVCodecContext * pAVContext = CreateContext();
    std::ofstream myOutputFile("audio.pcm",std::ios::binary);

    while(1)
    {
        uint32_t cbBufferSize = 0;
        uint8_t *pCompressedAudio = ReceiveBuffer( &cbBufferSize);

        if(cbBufferSize && pCompressedAudio)
        {
            DecodeBuffer(myOutputFile,pCompressedAudio,cbBufferSize, pAVContext);
        }
        else
        {
            break;
        }
    }

    avcodec_close(pAVContext);
    av_free(pAVContext);

    return nResult;
}
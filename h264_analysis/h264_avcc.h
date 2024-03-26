#ifndef _H264_AVCC_H
#define _H264_AVCC_H        1

#include <stdint.h>
#include <assert.h>

#include "bs.h"
#include "h264_stream.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
   AVC decoder configuration record, ISO/IEC 14496-15:2004(E), Section 5.2.4.1
   Seen in seen in mp4 files as 'avcC' atom 
   Seen in flv files as AVCVIDEOPACKET with AVCPacketType == 0
*/
typedef struct
{
    //8   version ( always 0x01 )
    int configurationVersion; // = 1
    //8   avc profile ( sps[0][1] )
    int AVCProfileIndication;
    //8   avc compatibility ( sps[0][2] )
    int profile_compatibility;
    //8   avc level ( sps[0][3] )
    int AVCLevelIndication;
    //reserved
    // bit(6) reserved = '111111'b;
    //NALULengthSizeMinusOne  这个值是（前缀长度-1），值如果是3，那前缀就是4，因为4-1=3
    int lengthSizeMinusOne;
    //reserved
    // bit(3) reserved = '111'b;

    //5   number of SPS NALUs (usually 1)
    int numOfSequenceParameterSets;

    sps_t** sps_table;
    //8   number of PPS NALUs (usually 1)
    int numOfPictureParameterSets;

    pps_t** pps_table;
} avcc_t;

avcc_t* avcc_new();
void avcc_free(avcc_t* avcc);
int read_avcc(avcc_t* avcc, h264_stream_t* h, bs_t* b);
int write_avcc(avcc_t* avcc, h264_stream_t* h, bs_t* b);
void debug_avcc(avcc_t* avcc);

#ifdef __cplusplus
}
#endif

#endif
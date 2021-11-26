#include <stdio.h>
#include <string.h>

//Important!
#pragma pack(1)

#define TAG_TYPE_SCRIPT 18
#define TAG_TYPE_AUDIO  8
#define TAG_TYPE_VIDEO  9

typedef unsigned char byte;
typedef unsigned int uint;

typedef struct {
    //文件标识，3字节
    byte Signature[3];
    //版本 1字节
    byte Version;
    // Flags 1字节，
    // 前5位保留，必须位0。
    // 第6位表示是否存在音频Tag。
    // 第7位保留，必须为0。
    // 第8位表示是否存在视频Tag。
    byte Flags;
    // Headersize(4字节，无符号整型是4个字节)为从File Header开始到File Body开始的字节数，版本1中总为9。
    uint DataOffset;
} FLV_HEADER;

typedef struct {
    // Type(1字节)表示Tag类型，
    // 包括音频(0x08)，
    // 视频(0x09)，
    // script data(0x12)，其他类型值被保留
    byte TagType;
    //DataSize(3字节)表示该Tag Data部分的大小
    byte DataSize[3];
    //Timestamp(3字节)表示该Tag的时间戳
    byte Timestamp[3];
    //无符号整型(4个字节) = Timestampe_ex(1个字节，表示时间戳的扩展字节) + Stream(3个字节，表示stream id)
    uint Reserved;
} TAG_HEADER;

//reverse_bytes - turn a BigEndian byte array into a LittleEndian integer
//将大端数据转成值(value)
//https://www.ruanyifeng.com/blog/2016/11/byte-order.html
uint reverse_bytes(byte *p, char c) {
    int r = 0;
    int i;
    for (i = 0; i < c; i++)
        r |= (*(p + i) << (((c - 1) * 8) - 8 * i));
    return r;
}

int simplest_flv_parser(char *url) {
    int output_a = 1;
    int output_v = 1;
    FILE *ifh = NULL, *vfh = NULL, *afh = NULL;

    //FILE *myout=fopen("output_log.txt","wb+");
    FILE *myout = stdout;

    FLV_HEADER flv;
    TAG_HEADER tagheader;
    uint previoustagsize, previoustagsize_z = 0;
    uint ts = 0, ts_new = 0;

    ifh = fopen(url, "rb+");
    if (ifh == NULL) {
        printf("Failed to open files!");
        return -1;
    }

    //FLV file header
    fread((char *) &flv, 1, sizeof(FLV_HEADER), ifh);

    fprintf(myout, "============== FLV Header ==============\n");
    fprintf(myout, "Signature:  0x %c %c %c\n", flv.Signature[0], flv.Signature[1], flv.Signature[2]);
    fprintf(myout, "Version:    0x %X\n", flv.Version);
    fprintf(myout, "Flags  :    0x %X\n", flv.Flags);
    //计算出正确的值
    fprintf(myout, "HeaderSize: 0x %X\n", reverse_bytes((byte *) &flv.DataOffset, sizeof(flv.DataOffset)));
    fprintf(myout, "========================================\n");

    //move the file pointer to the end of the header
    //fseek()函数可以移动文件的读写指针到指定的位置
    //SEEK_SET：表示文件的相对起始位置
    fseek(ifh, reverse_bytes((byte *) &flv.DataOffset, sizeof(flv.DataOffset)), SEEK_SET);

    //process each tag
    do {
        //Previous Tag Size(4字节) 表示前一个Tag的长度。
        //getw()函数用于从流中取一整数。
        previoustagsize = getw(ifh);

        fread((void *) &tagheader, sizeof(TAG_HEADER), 1, ifh);

        //大端转为值
        int tagheader_datasize = tagheader.DataSize[0] * 65536 + tagheader.DataSize[1] * 256 + tagheader.DataSize[2];
        int tagheader_timestamp =
                tagheader.Timestamp[0] * 65536 + tagheader.Timestamp[1] * 256 + tagheader.Timestamp[2];

        char tagtype_str[10];
        switch (tagheader.TagType) {
            case TAG_TYPE_AUDIO:
                sprintf(tagtype_str, "AUDIO");
                break;
            case TAG_TYPE_VIDEO:
                sprintf(tagtype_str, "VIDEO");
                break;
            case TAG_TYPE_SCRIPT:
                sprintf(tagtype_str, "SCRIPT");
                break;
            default:
                sprintf(tagtype_str, "UNKNOWN");
                break;
        }
        fprintf(myout, "[%6s] %6d %6d |", tagtype_str, tagheader_datasize, tagheader_timestamp);

        //if we are not past the end of file, process the tag
        if (feof(ifh)) {
            break;
        }

        //process tag by type
        switch (tagheader.TagType) {
            //Tag类型为audio
            case TAG_TYPE_AUDIO: {
                char audiotag_str[100] = {0};
                strcat(audiotag_str, "| ");
                char tagdata_first_byte;
                //音频Tag开始的第1个字节包含了音频数据的参数信息，从第2个字节开始为音频流数据。
                tagdata_first_byte = fgetc(ifh);
                //0xF0表示11110000
                //第1个字节的前4位的数值表示了音频编码类型。
                int x = tagdata_first_byte & 0xF0;
                x = x >> 4;
                switch (x) {
                    case 0:
                        strcat(audiotag_str, "Linear PCM, platform endian");
                        break;
                    case 1:
                        strcat(audiotag_str, "ADPCM");
                        break;
                    case 2:
                        strcat(audiotag_str, "MP3");
                        break;
                    case 3:
                        strcat(audiotag_str, "Linear PCM, little endian");
                        break;
                    case 4:
                        strcat(audiotag_str, "Nellymoser 16-kHz mono");
                        break;
                    case 5:
                        strcat(audiotag_str, "Nellymoser 8-kHz mono");
                        break;
                    case 6:
                        strcat(audiotag_str, "Nellymoser");
                        break;
                    case 7:
                        strcat(audiotag_str, "G.711 A-law logarithmic PCM");
                        break;
                    case 8:
                        strcat(audiotag_str, "G.711 mu-law logarithmic PCM");
                        break;
                    case 9:
                        strcat(audiotag_str, "reserved");
                        break;
                    case 10:
                        strcat(audiotag_str, "AAC");
                        break;
                    case 11:
                        strcat(audiotag_str, "Speex");
                        break;
                    case 14:
                        strcat(audiotag_str, "MP3 8-Khz");
                        break;
                    case 15:
                        strcat(audiotag_str, "Device-specific sound");
                        break;
                    default:
                        strcat(audiotag_str, "UNKNOWN");
                        break;
                }
                strcat(audiotag_str, "| ");
                //0x0C=00001100
                //第1个字节的第5-6位的数值表示音频采样率。
                x = tagdata_first_byte & 0x0C;
                x = x >> 2;
                switch (x) {
                    case 0:
                        strcat(audiotag_str, "5.5-kHz");
                        break;
                    case 1:
                        strcat(audiotag_str, "1-kHz");
                        break;
                    case 2:
                        strcat(audiotag_str, "22-kHz");
                        break;
                    case 3:
                        strcat(audiotag_str, "44-kHz");
                        break;
                    default:
                        strcat(audiotag_str, "UNKNOWN");
                        break;
                }
                strcat(audiotag_str, "| ");
                //0x02=00000010
                //第1个字节的第7位表示音频采样精度。
                x = tagdata_first_byte & 0x02;
                x = x >> 1;
                switch (x) {
                    case 0:
                        strcat(audiotag_str, "8Bit");
                        break;
                    case 1:
                        strcat(audiotag_str, "16Bit");
                        break;
                    default:
                        strcat(audiotag_str, "UNKNOWN");
                        break;
                }
                strcat(audiotag_str, "| ");
                //第1个字节的第8位表示音频类型。
                x = tagdata_first_byte & 0x01;
                switch (x) {
                    case 0:
                        strcat(audiotag_str, "Mono");
                        break;
                    case 1:
                        strcat(audiotag_str, "Stereo");
                        break;
                    default:
                        strcat(audiotag_str, "UNKNOWN");
                        break;
                }
                fprintf(myout, "%s", audiotag_str);

                //if the output file hasn't been opened, open it.
                if (output_a != 0 && afh == NULL) {
                    afh = fopen("output.mp3", "wb");
                }

                //TagData - First Byte Data
                int data_size = reverse_bytes((byte *) &tagheader.DataSize, sizeof(tagheader.DataSize)) - 1;
                if (output_a != 0) {
                    //TagData+1
                    for (int i = 0; i < data_size; i++)
                        //将一指定字符写入文件流中
                        fputc(fgetc(ifh), afh);

                } else {
                    for (int i = 0; i < data_size; i++)
                        fgetc(ifh);
                }
                break;
            }
            //Tag类型为video
            case TAG_TYPE_VIDEO: {
                char videotag_str[100] = {0};
                //strcat() 函数用来将两个字符串连接（拼接）起来。
                strcat(videotag_str, "| ");
                //视频Tag也用开始的第1个字节包含视频数据的参数信息，从第2个字节为视频流数据。
                char tagdata_first_byte;
                tagdata_first_byte = fgetc(ifh);

                //第1个字节的前4位的数值表示帧类型
                int x = tagdata_first_byte & 0xF0;
                x = x >> 4;
                switch (x) {
                    case 1:
                        strcat(videotag_str, "key frame  ");
                        break;
                    case 2:
                        strcat(videotag_str, "inter frame");
                        break;
                    case 3:
                        strcat(videotag_str, "disposable inter frame");
                        break;
                    case 4:
                        strcat(videotag_str, "generated keyframe");
                        break;
                    case 5:
                        strcat(videotag_str, "video info/command frame");
                        break;
                    default:
                        strcat(videotag_str, "UNKNOWN");
                        break;
                }

                strcat(videotag_str, "| ");
                //第1个字节的后4位的数值表示视频编码类型
                x = tagdata_first_byte & 0x0F;
                switch (x) {
                    case 1:
                        strcat(videotag_str, "JPEG (currently unused)");
                        break;
                    case 2:
                        strcat(videotag_str, "Sorenson H.263");
                        break;
                    case 3:
                        strcat(videotag_str, "Screen video");
                        break;
                    case 4:
                        strcat(videotag_str, "On2 VP6");
                        break;
                    case 5:
                        strcat(videotag_str, "On2 VP6 with alpha channel");
                        break;
                    case 6:
                        strcat(videotag_str, "Screen video version 2");
                        break;
                    case 7:
                        strcat(videotag_str, "AVC");
                        break;
                    default:
                        strcat(videotag_str, "UNKNOWN");
                        break;
                }
                fprintf(myout, "%s", videotag_str);

                fseek(ifh, -1, SEEK_CUR);
                //if the output file hasn't been opened, open it.
                if (vfh == NULL && output_v != 0) {
                    //write the flv header (reuse the original file's hdr) and first previoustagsize
                    vfh = fopen("output.flv", "wb");
                    fwrite((char *) &flv, 1, sizeof(flv), vfh);
                    fwrite((char *) &previoustagsize_z, 1, sizeof(previoustagsize_z), vfh);
                }
#if 0
                //Change Timestamp

                //Get Timestamp
                ts = reverse_bytes((byte *)&tagheader.Timestamp, sizeof(tagheader.Timestamp));
                ts= ts*2;

                //Writeback Timestamp
                ts_new = reverse_bytes((byte *)&ts, sizeof(ts));
                memcpy(&tagheader.Timestamp, ((char *)&ts_new) + 1, sizeof(tagheader.Timestamp));
#endif

                //TagData + Previous Tag Size
                int data_size = reverse_bytes((byte *) &tagheader.DataSize, sizeof(tagheader.DataSize)) + 4;
                if (output_v != 0) {
                    //TagHeader
                    fwrite((char *) &tagheader, 1, sizeof(tagheader), vfh);
                    //TagData
                    for (int i = 0; i < data_size; i++)
                        fputc(fgetc(ifh), vfh);
                } else {
                    for (int i = 0; i < data_size; i++)
                        fgetc(ifh);
                }
                //rewind 4 bytes, because we need to read the previoustagsize again for the loop's sake
                fseek(ifh, -4, SEEK_CUR);

                break;
            }

            default:
                //skip the data of this tag
                //SEEK_CUR：表示文件的相对当前位置
                fseek(ifh, reverse_bytes((byte *) &tagheader.DataSize, sizeof(tagheader.DataSize)), SEEK_CUR);
        }

        //换行
        fprintf(myout, "\n");
    } while (!feof(ifh));

    fclose(ifh);
    fclose(vfh);
    fclose(afh);

    return 0;
}


#include <string>

int testDecodeSEI(const char * file);
int testEncode(const char * infile, const char * outfile);
int testEncode2(const char * infile, const char * outfile);
int testEncode3(const char * infile, const char * outfile);

#include <strings.h>

#include <stdlib.h>
#include "sei_packet.h"

int testIMU()
{
    float imu[9] = {
            0.999047,
            0.031128,
            0.030595,
            -0.031389,
            0.999474,
            0.008097,
            -0.030327,
            -0.009049,
            0.999499
    };

    uint32_t annexbType = 1;
    uint32_t len = get_sei_packet_size((const uint8_t*)imu,sizeof(float)*9, annexbType);
    uint8_t * buffer = (uint8_t*)malloc(len);

    fill_sei_packet(buffer, annexbType,IMU_UUID, (const uint8_t*)imu, sizeof(float) * 9);

    uint8_t * data = NULL;
    uint32_t size = 0;
    get_sei_content(buffer,len,IMU_UUID,&data,&size);
    if (data != NULL)
    {
        FILE * fp = fopen("imu.data","wb");
        fwrite(buffer,len,1,fp);
        fclose(fp);
        float * fData = (float*)data;
        printf("%f  %f  %f  %f  %f  %f  %f  %f  %f\n",fData[0], fData[1], fData[2], fData[3], fData[4], fData[5], fData[6], fData[7], fData[8]);
    }
    free_sei_content(&data);
    free(buffer);
    return 0;
}

int testSEI() {
    uint8_t source[9] = { 0};
    uint32_t source_len = 9;

    uint32_t annexbType = 1;
    uint32_t len = get_sei_packet_size((const uint8_t*)source, source_len, annexbType);
    uint8_t * buffer = (uint8_t*)malloc(len);

    fill_sei_packet(buffer, annexbType, IMU_UUID, (const uint8_t*)source, source_len);

    uint8_t * data = NULL;
    uint32_t size = 0;
    get_sei_content(buffer, len, IMU_UUID, &data, &size);
    if (data != NULL)
    {
        printf("%d",memcmp(data, source, source_len));

        free_sei_content(&data);
    }
    free(buffer);
    return 0;

}

#include <string.h>

int main(int argv ,char* argc[])
{
    char * type = NULL;
    if (argv > 1)
    {
        type = argc[1];
    }
    else {
        return -1;
    }

    char * infile = "../video.mp4";
    char * infile_yuv = "../video.yuv";
    char * infile_sei_mp4 = "../video_sei.mp4";
    char * outfile = "../1.mp4";

    if (strcasecmp(type, "sei") == 0)
    {
        return testDecodeSEI(infile_sei_mp4);
    }
    else if (strcasecmp(type, "encode") == 0)
    {
        return testEncode(infile_yuv, outfile);
    }
    else if (strcasecmp(type, "encode2") == 0)
    {
        return testEncode2(infile, outfile);
    }
    else if (strcasecmp(type, "encode3") == 0)
    {
        return testEncode3(infile, outfile);
    }
    else if (strcasecmp(type, "sei_test") == 0)
    {
        testSEI();
        //testIMU();
    }
    else
    {
        printf("not found type %s\n",type);
    }
    return 0;
}
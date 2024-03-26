#include "EvHeade.h"
#include "Encode.h"

//"../Vid0616000023.mp4"
int TestHeader(const char *file)
{
    EvoMediaSource source;
    printf("测试开始! %lld\n", av_gettime() / 1000);
    source.SetVideoCodecName("h264");
    int ret = source.Open(file);
    if (ret != 0)
    {
        return -1;
    }
    printf("测试结束! %lld\n", av_gettime() / 1000);
    return 1;
}
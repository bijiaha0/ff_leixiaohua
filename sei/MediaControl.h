//
// Created by jephy on 7/13/17.
//

#ifndef MEDIACONTROLLERDEMO_MEDIACONTROL_H
#define MEDIACONTROLLERDEMO_MEDIACONTROL_H

#include "EvoMediaSource.h"
#include "VideoDecoder.h"
#include "EvoVideoConvert.h"
#include <pthread.h>

class MediaControl {
public:
    MediaControl();
    ~MediaControl();
    int Open(const char * file);
    int Close();
    int Play();
    int Pause();
    int Seek(int second);
    void Run();
    bool CheckIsEnd() { return IsEnd; }
protected:
    virtual void AttachThread() {};
    virtual void DetachThread() {};
    virtual void SendPacket(int64_t timestamp,AVFrame *frame);
private:
    EvoMediaSource source;
    EvoVideoConvert convert;
    VideoDecoder *decoder;
    AVCodecContext *codecContext;
    uint8_t *extraData_;

    int64_t timestamp_now;
    int64_t timestamp_last;
    int64_t time_last;
    AVFrame *frame_last;
    bool bStop;
    bool bPause;
    bool IsEnd;
#ifdef _WIN32
    std::mutex lock;
	HANDLE thread;
#else
    pthread_mutex_t lock;
    pthread_t thread;
#endif
};


#endif //MEDIACONTROLLERDEMO_MEDIACONTROL_H
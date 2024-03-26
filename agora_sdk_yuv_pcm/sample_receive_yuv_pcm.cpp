#include <csignal>
#include <cstring>
#include <sstream>
#include <string>
#include <thread>

#include "AgoraRefCountedObject.h"
#include "IAgoraService.h"
#include "NGIAgoraRtcConnection.h"

#include "../agora_sdk_common/helper.h"
#include "../agora_sdk_common/log.h"
#include "../agora_sdk_common/opt_parser.h"
#include "../agora_sdk_common/sample_common.h"
#include "../agora_sdk_common/sample_connection_observer.h"
#include "../agora_sdk_common/sample_local_user_observer.h"

#include "NGIAgoraAudioTrack.h"
#include "NGIAgoraLocalUser.h"
#include "NGIAgoraMediaNodeFactory.h"
#include "NGIAgoraMediaNode.h"
#include "NGIAgoraVideoTrack.h"
#include<iostream>
#include<cstdlib>
#include<unistd.h>
#include<pthread.h>
#include<ctime>
#include<deque>
#include<algorithm>
#include<iterator>

using namespace std;

#define DEFAULT_CONNECT_TIMEOUT_MS (3000)
#define DEFAULT_SAMPLE_RATE (16000)
#define DEFAULT_NUM_OF_CHANNELS (1)
#define DEFAULT_TARGET_BITRATE (1 * 1000 * 1000)
#define DEFAULT_VIDEO_WIDTH (352)
#define DEFAULT_VIDEO_HEIGHT (288)
#define DEFAULT_FRAME_RATE (15)

#define STREAM_TYPE_HIGH "high"
#define STREAM_TYPE_LOW "low"

#define DEFAULT_CONNECT_TIMEOUT_MS (3000)
#define DEFAULT_SAMPLE_RATE (16000)
#define DEFAULT_NUM_OF_CHANNELS (1)
#define DEFAULT_TARGET_BITRATE (1 * 1000 * 1000)

static bool exitFlag = false;

struct pcst {
    pthread_mutex_t mutex;
    pthread_cond_t not_full;
    pthread_cond_t not_empty;
};

pcst shared1 = {PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER, PTHREAD_COND_INITIALIZER};
pcst shared2 = {PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER, PTHREAD_COND_INITIALIZER};

struct SampleOptions {
    std::string appId;
    std::string channelId;
    std::string userId;
    std::string remoteUserId;
    std::string streamType = STREAM_TYPE_HIGH;

    int video_resend = 3;
    int audio_resend = 3;

    struct {
        int sampleRate = DEFAULT_SAMPLE_RATE;
        int numOfChannels = DEFAULT_NUM_OF_CHANNELS;
    } audio;
    struct {
        int targetBitrate = DEFAULT_TARGET_BITRATE;
        int width = DEFAULT_VIDEO_WIDTH;
        int height = DEFAULT_VIDEO_HEIGHT;
        int frameRate = DEFAULT_FRAME_RATE;
    } video;
};

deque<agora::media::base::VideoFrame> videoFrame_dt;
deque<agora::media::IAudioFrameObserverBase::AudioFrame> audioFrame_dt;

void audioFrame_deep_copy(agora::media::IAudioFrameObserverBase::AudioFrame &desAudioFrame, agora::media::IAudioFrameObserverBase::AudioFrame &srcAudioFrame) {
    desAudioFrame.type = srcAudioFrame.type;
    desAudioFrame.samplesPerChannel = srcAudioFrame.samplesPerChannel;
    desAudioFrame.bytesPerSample = srcAudioFrame.bytesPerSample;
    desAudioFrame.channels = srcAudioFrame.channels;
    desAudioFrame.samplesPerSec = srcAudioFrame.samplesPerSec;

    desAudioFrame.renderTimeMs = srcAudioFrame.renderTimeMs;
    desAudioFrame.captureTimeMs = srcAudioFrame.captureTimeMs;
    desAudioFrame.avsync_type = srcAudioFrame.avsync_type;

    size_t writeBytes = srcAudioFrame.samplesPerChannel * srcAudioFrame.channels * sizeof(int16_t);
    desAudioFrame.buffer = (uint8_t *) malloc(writeBytes);
    memcpy(desAudioFrame.buffer, srcAudioFrame.buffer, writeBytes);

}

void free_audioFrame(agora::media::IAudioFrameObserverBase::AudioFrame* audioFrame) {
    free(audioFrame->buffer);
}

void videoFrame_deep_copy(agora::media::base::VideoFrame &desVideoFrame, const agora::media::base::VideoFrame *srcVideoFrame) {
    desVideoFrame.type = srcVideoFrame->type;
    desVideoFrame.width = srcVideoFrame->width;
    desVideoFrame.height = srcVideoFrame->height;
    desVideoFrame.yStride = srcVideoFrame->yStride;
    desVideoFrame.uStride = srcVideoFrame->uStride;
    desVideoFrame.vStride = srcVideoFrame->vStride;

    desVideoFrame.rotation = srcVideoFrame->rotation;
    desVideoFrame.renderTimeMs = srcVideoFrame->renderTimeMs;
    desVideoFrame.avsync_type = srcVideoFrame->avsync_type;

    desVideoFrame.metadata_size = srcVideoFrame->metadata_size;

    //if (videoFrame_tmp.metadata_size > 0) {
    //    AG_LOG(INFO, "metadata_buffer ...,%s", videoFrame_tmp.metadata_buffer);
    //}

    desVideoFrame.textureId = srcVideoFrame->textureId;

    size_t writeBytes = srcVideoFrame->yStride * srcVideoFrame->height;
    desVideoFrame.yBuffer = (uint8_t *) malloc(writeBytes);
    memcpy(desVideoFrame.yBuffer, srcVideoFrame->yBuffer, writeBytes);
    desVideoFrame.uBuffer = (uint8_t *) malloc(writeBytes / 4);
    memcpy(desVideoFrame.uBuffer, srcVideoFrame->uBuffer, writeBytes/4);
    desVideoFrame.vBuffer = (uint8_t *) malloc(writeBytes / 4);
    memcpy(desVideoFrame.vBuffer, srcVideoFrame->vBuffer, writeBytes/4);
    desVideoFrame.metadata_buffer = (uint8_t *) malloc(srcVideoFrame->metadata_size);
    memcpy(desVideoFrame.metadata_buffer, srcVideoFrame->metadata_buffer, srcVideoFrame->metadata_size);
}

void free_videoFrame(agora::media::base::VideoFrame *videoFrame) {
    free(videoFrame->yBuffer);
    free(videoFrame->uBuffer);
    free(videoFrame->vBuffer);
    if (videoFrame->metadata_size > 0){
        free(videoFrame->metadata_buffer);
    }
}

void sendOnePcmFrame(
        const SampleOptions &options,
        agora::agora_refptr<agora::rtc::IAudioPcmDataSender> audioPcmDataSender,
        agora::media::IAudioFrameObserverBase::AudioFrame &audioFrame_tmp) {

    size_t writeBytes = audioFrame_tmp.samplesPerChannel * audioFrame_tmp.channels * sizeof(int16_t);

    uint8_t frameBuf[writeBytes];
    memcpy(&frameBuf, audioFrame_tmp.buffer, writeBytes);

    if (audioPcmDataSender->sendAudioPcmData(
            frameBuf, 0, audioFrame_tmp.samplesPerChannel, agora::rtc::TWO_BYTES_PER_SAMPLE,
            audioFrame_tmp.channels, audioFrame_tmp.samplesPerSec) < 0) {
        AG_LOG(ERROR, "failed to send audio frame!");
    }

}

void sendOneYuvFrame(
        const SampleOptions &options,
        agora::agora_refptr<agora::rtc::IVideoFrameSender> videoFrameSender,
        agora::media::base::VideoFrame &videoFrame_tmp) {

    int sendBytes = videoFrame_tmp.yStride * videoFrame_tmp.height;
    uint8_t frameBuf[sendBytes * 3/2];
    memcpy(frameBuf, videoFrame_tmp.yBuffer, sendBytes);
    memcpy(frameBuf + sendBytes, videoFrame_tmp.uBuffer, sendBytes / 4);
    memcpy(frameBuf + sendBytes * 5 / 4, videoFrame_tmp.vBuffer, sendBytes / 4);

    for(int j =0; j < sendBytes; j++){
        uint8_t value = frameBuf[j]/2;
        frameBuf[j] = value;
    }

    agora::media::base::ExternalVideoFrame videoFrame;
    videoFrame.type = agora::media::base::ExternalVideoFrame::VIDEO_BUFFER_RAW_DATA;
    videoFrame.format = agora::media::base::VIDEO_PIXEL_I420;
    videoFrame.buffer = frameBuf;
    videoFrame.stride = options.video.width;
    videoFrame.height = options.video.height;
    videoFrame.cropLeft = 0;
    videoFrame.cropTop = 0;
    videoFrame.cropRight = 0;
    videoFrame.cropBottom = 0;
    videoFrame.rotation = 0;
    videoFrame.timestamp = 0;

    if (videoFrameSender->sendVideoFrame(videoFrame) < 0) {
        AG_LOG(ERROR, "Failed to send video frame!");
    }

}

class PcmFrameObserver : public agora::media::IAudioFrameObserverBase {
public:
    PcmFrameObserver()
            : fileCount(0), fileSize_(0) {}

    bool onPlaybackAudioFrame(const char *channelId, AudioFrame &audioFrame) override { return true; };

    bool onRecordAudioFrame(const char *channelId, AudioFrame &audioFrame) override { return true; };

    bool onMixedAudioFrame(const char *channelId, AudioFrame &audioFrame) override { return true; };

    bool onPlaybackAudioFrameBeforeMixing(const char *channelId, agora::media::base::user_id_t userId,
                                          AudioFrame &audioFrame) override;

    bool onEarMonitoringAudioFrame(AudioFrame &audioFrame) { return true; };

    int fileCount;
    int fileSize_;
};

bool PcmFrameObserver::onPlaybackAudioFrameBeforeMixing(const char *channelId, agora::media::base::user_id_t userId, AudioFrame &audioFrame) {
    PcmFrameObserver::AudioFrame audioFrame_tmp;
    audioFrame_deep_copy(audioFrame_tmp, audioFrame);

    pthread_mutex_lock(&shared1.mutex);
    audioFrame_dt.push_back(audioFrame_tmp);

    AG_LOG(INFO, "receive pcm frame ...,%ld", audioFrame_dt.size());
    pthread_cond_signal(&shared1.not_empty);
    pthread_mutex_unlock(&shared1.mutex);

    return true;
}

class YuvFrameObserver : public agora::rtc::IVideoFrameObserver2 {
public:
    YuvFrameObserver()
            : fileCount(0), fileSize_(0) {}

    void
    onFrame(const char *channelId, agora::user_id_t remoteUid, const agora::media::base::VideoFrame *frame) override;

    virtual ~YuvFrameObserver() = default;

    int fileCount;
    int fileSize_;
};

void YuvFrameObserver::onFrame(const char *channelId, agora::user_id_t remoteUid, const agora::media::base::VideoFrame *videoFrame) {
    agora::media::base::VideoFrame videoFrame_tmp;
    videoFrame_deep_copy(videoFrame_tmp, videoFrame);

    pthread_mutex_lock(&shared2.mutex);
    videoFrame_dt.push_back(videoFrame_tmp);

    AG_LOG(INFO, "receive yuv frame ...,%ld", videoFrame_dt.size());
    pthread_cond_signal(&shared2.not_empty);
    pthread_mutex_unlock(&shared2.mutex);

    return;
};

static void SignalHandler(int sigNo) { exitFlag = true; }

void SampleSendAudioTask(
        const SampleOptions &options,
        agora::agora_refptr<agora::rtc::IAudioPcmDataSender> audioPcmDataSender,
        bool &exitFlag) {

    PacerInfo pacer = {0, 10, 0, std::chrono::steady_clock::now()};

    while (!exitFlag) {
        pthread_mutex_lock(&shared1.mutex);
        if (audioFrame_dt.empty()) {
            pthread_cond_wait(&shared1.not_empty, &shared1.mutex);
            pthread_mutex_unlock(&shared1.mutex);
        }
        while (!audioFrame_dt.empty()) {
            auto audioFrame = audioFrame_dt.front();
            AG_LOG(INFO, "send pcm frame ....%ld",audioFrame_dt.size());
            sendOnePcmFrame(options, audioPcmDataSender, audioFrame);
            audioFrame_dt.pop_front();
            free_audioFrame(&audioFrame);
            waitBeforeNextSend(pacer);  // sleep for a while before sending next frame
        }
        pthread_cond_signal(&shared1.not_full);
        pthread_mutex_unlock(&shared1.mutex);
    }
}

void SampleSendVideoTask(
        const SampleOptions &options,
        agora::agora_refptr<agora::rtc::IVideoFrameSender> videoFrameSender,
        bool &exitFlag) {
    PacerInfo pacer = {0, 1000 / options.video.frameRate, 0,
                       std::chrono::steady_clock::now()};

    while (!exitFlag) {
        pthread_mutex_lock(&shared2.mutex);
        if (videoFrame_dt.empty()) {
            pthread_cond_wait(&shared2.not_empty, &shared2.mutex);
            pthread_mutex_unlock(&shared2.mutex);
        }
        while (!videoFrame_dt.empty()) {
            auto videoFrame = videoFrame_dt.front();
            AG_LOG(INFO, "send video frame ...,%ld",videoFrame_dt.size());
            sendOneYuvFrame(options, videoFrameSender, videoFrame);
            videoFrame_dt.pop_front();
            free_videoFrame(&videoFrame);
            waitBeforeNextSend(pacer);  // sleep for a while before sending next frame
        }
        pthread_cond_signal(&shared2.not_full);
        pthread_mutex_unlock(&shared2.mutex);
    }
}

int main(int argc, char *argv[]) {
    SampleOptions options;
    opt_parser optParser;

    optParser.add_long_opt("token", &options.appId, "The token for authentication / must");
    optParser.add_long_opt("channelId", &options.channelId, "Channel Id / must");
    optParser.add_long_opt("userId", &options.userId, "User Id / default is 0");
    optParser.add_long_opt("sampleRate", &options.audio.sampleRate, "Sample rate for the PCM file to be sent");
    optParser.add_long_opt("numOfChannels", &options.audio.numOfChannels, "Number of channels for the PCM file to be sent");
    optParser.add_long_opt("fps", &options.video.frameRate, "Target frame rate for sending the video stream");
    optParser.add_long_opt("width", &options.video.width, "Image width for the YUV file to be sent");
    optParser.add_long_opt("height", &options.video.height, "Image height for the YUV file to be sent");
    optParser.add_long_opt("bitrate", &options.video.targetBitrate, "Target bitrate (bps) for encoding the YUV stream");

    if ((argc <= 1) || !optParser.parse_opts(argc, argv)) {
        std::ostringstream strStream;
        optParser.print_usage(argv[0], strStream);
        std::cout << strStream.str() << std::endl;
        return -1;
    }

    if (options.appId.empty()) {
        AG_LOG(ERROR, "Must provide appId!");
        return -1;
    }

    if (options.channelId.empty()) {
        AG_LOG(ERROR, "Must provide channelId!");
        return -1;
    }

    std::signal(SIGQUIT, SignalHandler);
    std::signal(SIGABRT, SignalHandler);
    std::signal(SIGINT, SignalHandler);

    agora::base::IAgoraService* service1 = nullptr;
    // Create Agora service
    service1 = createAndInitAgoraService(false, true, true, false, true);
    if (!service1) {
        AG_LOG(ERROR, "Failed to creating Agora service!");
    }

    // Create Agora connection
    agora::rtc::RtcConnectionConfiguration ccfg1;
    ccfg1.autoSubscribeAudio = false;
    ccfg1.autoSubscribeVideo = false;
    ccfg1.clientRoleType = agora::rtc::CLIENT_ROLE_BROADCASTER;

    agora::agora_refptr<agora::rtc::IRtcConnection> connection1 = service1->createRtcConnection(ccfg1);
    if (!connection1) {
        AG_LOG(ERROR, "Failed to creating Agora connection!");
        return -1;
    }

    int ret = connection1->getLocalUser()->setAudioScenario(agora::rtc::AUDIO_SCENARIO_TYPE::AUDIO_SCENARIO_CHORUS);
    if (!ret) {
        AG_LOG(
                INFO,
                "[Low Delay] setAudioScenario : AUDIO_SCENARIO_CHORUS successfully!");
    } else {
        AG_LOG(INFO,
               "[Low Delay] setAudioScenario : AUDIO_SCENARIO_CHORUS fail! The "
               "err num is %d",
               ret);
    }

    auto s = connection1->getAgoraParameter();
    // ret = s->setParameters("{\"rtc.video.uplink_max_retry_times\": 3}");
    ret = s->setUInt("rtc.video.uplink_max_retry_times",options.audio_resend);
    if (!ret) {
        AG_LOG(INFO, "[Low Delay] set the max video resend times %d successfully!",options.video_resend);
    } else {
        AG_LOG(INFO,
               "[Low Delay] close video resend  fail! The "
               "err num is %d",
               ret);
    }

    // ret = s->setParameters("{\"rtc.audio.uplink_max_retry_times\": 3}");
    ret = s->setUInt("rtc.audio.uplink_max_retry_times",options.audio_resend);
    if (!ret) {
        AG_LOG(INFO, "[Low Delay] set the max audio resend times %d successfully!",options.audio_resend);
    } else {
        AG_LOG(INFO,
               "[Low Delay] close audio resend fail! The "
               "err num is %d",
               ret);
    }
    ret = s->setParameters("{\"rtc.paced_sender_enabled\": 0}");
    if (!ret) {
        AG_LOG(
                INFO,
                "[Low Delay] close the send pacer successfully!");
    } else {
        AG_LOG(INFO,
               "[Low Delay] close the send pacer fail! The "
               "err num is %d",
               ret);
    }

    // Register connection observer to monitor connection event
    auto connObserver1 = std::make_shared<SampleConnectionObserver>();
    connection1->registerObserver(connObserver1.get());

    // Connect to Agora channel
    if (connection1->connect(options.appId.c_str(), options.channelId.c_str(),options.userId.c_str())) {
        AG_LOG(ERROR, "Failed to connect to Agora channel!");
        return -1;
    }

    // Create media node factory
    agora::agora_refptr<agora::rtc::IMediaNodeFactory> factory1 = service1->createMediaNodeFactory();
    if (!factory1) {
        AG_LOG(ERROR, "Failed to create media node factory!");
    }

    // Create audio data sender
    agora::agora_refptr<agora::rtc::IAudioPcmDataSender> audioPcmDataSender1 = factory1->createAudioPcmDataSender();
    if (!audioPcmDataSender1) {
        AG_LOG(ERROR, "Failed to create audio data sender!");
        return -1;
    }

    // Create audio track
    agora::agora_refptr<agora::rtc::ILocalAudioTrack> customAudioTrack1 = service1->createCustomAudioTrack(audioPcmDataSender1);
    if (!customAudioTrack1) {
        AG_LOG(ERROR, "Failed to create audio track!");
        return -1;
    }

    // Create video frame sender
    agora::agora_refptr<agora::rtc::IVideoFrameSender> videoFrameSender1 = factory1->createVideoFrameSender();
    if (!videoFrameSender1) {
        AG_LOG(ERROR, "Failed to create video frame sender!");
        return -1;
    }

    // Create video track
    agora::agora_refptr<agora::rtc::ILocalVideoTrack> customVideoTrack1 = service1->createCustomVideoTrack(videoFrameSender1);
    if (!customVideoTrack1) {
        AG_LOG(ERROR, "Failed to create video track!");
        return -1;
    }

    // Configure video encoder
    agora::rtc::VideoEncoderConfiguration encoderConfig1;
    encoderConfig1.codecType = agora::rtc::VIDEO_CODEC_H264;
    encoderConfig1.dimensions.width = options.video.width;
    encoderConfig1.dimensions.height = options.video.height;
    encoderConfig1.frameRate = options.video.frameRate;
    encoderConfig1.bitrate = options.video.targetBitrate;

    customVideoTrack1->setVideoEncoderConfiguration(encoderConfig1);

    // Publish audio & video track
    customAudioTrack1->setEnabled(true);
    connection1->getLocalUser()->publishAudio(customAudioTrack1);
    customVideoTrack1->setEnabled(true);
    connection1->getLocalUser()->publishVideo(customVideoTrack1);

    // Wait until connected before sending media stream
    connObserver1->waitUntilConnected(DEFAULT_CONNECT_TIMEOUT_MS);

    // Start sending media data
    AG_LOG(INFO, "Start sending audio & video data ...");

    std::thread sendAudioThread1(SampleSendAudioTask, options, audioPcmDataSender1, std::ref(exitFlag));
    std::thread sendVideoThread1(SampleSendVideoTask, options, videoFrameSender1, std::ref(exitFlag));

    //################################################################################
    // Create Agora service
    auto service2 = createAndInitAgoraService(false, true, true);
    if (!service2) {
        AG_LOG(ERROR, "Failed to creating Agora service!");
    }

    // Create Agora connection
    agora::rtc::AudioSubscriptionOptions audioSubOpt2;
    audioSubOpt2.bytesPerSample = sizeof(int16_t) * options.audio.numOfChannels;
    audioSubOpt2.numberOfChannels = options.audio.numOfChannels;
    audioSubOpt2.sampleRateHz = options.audio.sampleRate;

    agora::rtc::RtcConnectionConfiguration ccfg2;
    ccfg2.clientRoleType = agora::rtc::CLIENT_ROLE_AUDIENCE;
    ccfg2.audioSubscriptionOptions = audioSubOpt2;
    ccfg2.autoSubscribeAudio = false;
    ccfg2.autoSubscribeVideo = false;
    ccfg2.enableAudioRecordingOrPlayout = false;  // Subscribe audio but without playback

    agora::agora_refptr<agora::rtc::IRtcConnection> connection2 = service2->createRtcConnection(ccfg2);
    if (!connection2) {
        AG_LOG(ERROR, "Failed to creating Agora connection!");
        return -1;
    }

    // Subcribe streams from all remote users or specific remote user
    agora::rtc::VideoSubscriptionOptions subscriptionOptions2;
    if (options.streamType == STREAM_TYPE_HIGH) {
        subscriptionOptions2.type = agora::rtc::VIDEO_STREAM_HIGH;
    } else if(options.streamType==STREAM_TYPE_LOW){
        subscriptionOptions2.type = agora::rtc::VIDEO_STREAM_LOW;
    } else{
        AG_LOG(ERROR, "It is a error stream type");
        return -1;
    }
    if (options.remoteUserId.empty()) {
        AG_LOG(INFO, "Subscribe streams from all remote users");
        connection2->getLocalUser()->subscribeAllAudio();
        connection2->getLocalUser()->subscribeAllVideo(subscriptionOptions2);

    } else {
        connection2->getLocalUser()->subscribeAudio(options.remoteUserId.c_str());
        connection2->getLocalUser()->subscribeVideo(options.remoteUserId.c_str(), subscriptionOptions2);
    }
    // Register connection observer to monitor connection event
    auto connObserver2 = std::make_shared<SampleConnectionObserver>();
    connection2->registerObserver(connObserver2.get());

    // Create local user observer
    auto localUserObserver2 = std::make_shared<SampleLocalUserObserver>(connection2->getLocalUser());

    // Register audio frame observer to receive audio stream
    auto pcmFrameObserver2 = std::make_shared<PcmFrameObserver>();
    if (connection2->getLocalUser()->setPlaybackAudioFrameBeforeMixingParameters(options.audio.numOfChannels, options.audio.sampleRate)) {
        AG_LOG(ERROR, "Failed to set audio frame parameters!");
        return -1;
    }
    localUserObserver2->setAudioFrameObserver(pcmFrameObserver2.get());

    // Register video frame observer to receive video stream
    std::shared_ptr<YuvFrameObserver> yuvFrameObserver2 = std::make_shared<YuvFrameObserver>();
    localUserObserver2->setVideoFrameObserver(yuvFrameObserver2.get());

    // Connect to Agora channel
    if (connection2->connect(options.appId.c_str(), options.channelId.c_str(), options.userId.c_str())) {
        AG_LOG(ERROR, "Failed to connect to Agora channel!");
        return -1;
    }

    // Start receiving incoming media data
    AG_LOG(INFO, "Start receiving audio & video data ...");

    sendAudioThread1.join();
    sendVideoThread1.join();

    // Unregister audio & video frame observers
    localUserObserver2->unsetAudioFrameObserver();
    localUserObserver2->unsetVideoFrameObserver();

    // Unregister connection observer
    connection2->unregisterObserver(connObserver2.get());

    // Disconnect from Agora channel
    if (connection2->disconnect()) {
        AG_LOG(ERROR, "Failed to disconnect from Agora channel!");
        return -1;
    }
    AG_LOG(INFO, "Disconnected from Agora channel successfully");

    // Destroy Agora connection and related resources
    localUserObserver2.reset();
    pcmFrameObserver2.reset();
    yuvFrameObserver2.reset();
    connection2 = nullptr;

    // Destroy Agora Service
    service2->release();
    service2 = nullptr;

    //#####################################################################
    // Unpublish audio & video track
    connection1->getLocalUser()->unpublishAudio(customAudioTrack1);
    connection1->getLocalUser()->unpublishVideo(customVideoTrack1);

    // Unregister connection observer
    connection1->unregisterObserver(connObserver1.get());

    // Disconnect from Agora channel
    if (connection1->disconnect()) {
        AG_LOG(ERROR, "Failed to disconnect from Agora channel!");
        return -1;
    }
    AG_LOG(INFO, "Disconnected from Agora channel successfully");

    // Destroy Agora connection and related resources
    connObserver1.reset();
    audioPcmDataSender1 = nullptr;
    videoFrameSender1 = nullptr;
    customAudioTrack1 = nullptr;
    customVideoTrack1 = nullptr;
    factory1 = nullptr;
    connection1 = nullptr;

    // Destroy Agora Service
    service1->release();
    service1 = nullptr;

    return 0;
}
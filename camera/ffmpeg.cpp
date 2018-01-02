#include "ffmpeg.h"
#include <QDebug>
#include <QImage>
#include <QMutex>
#include <iostream>

using namespace std;

static QMutex mutex;
static bool ffmpeg_init = false;

FFmpeg::FFmpeg() {
    started = false;
    restart = false;
    opened = false;
    stoped = false;
}

FFmpeg::~FFmpeg() {

}

QString FFmpeg::getUrl() {
    return url;
}

bool FFmpeg::prepare() {
    mutex.lock();
    if(!ffmpeg_init) {
        av_register_all();
        avformat_network_init();
        av_log_set_level(AV_LOG_WARNING);
        ffmpeg_init = true;
    }
    mutex.unlock();
    return true;
}

bool FFmpeg::open()
{
    pAVFormatContext = avformat_alloc_context();
    pAVFrame = av_frame_alloc();
    AVDictionary *opts = NULL;
    av_dict_set(&opts, "stimeout", "6000000", 0);
    int result = avformat_open_input(&pAVFormatContext, url.toStdString().c_str(), NULL, &opts);
    if (result < 0){
        qDebug()<<"avformat_open_input < 0";
        avformat_free_context(pAVFormatContext);
        av_frame_free(&pAVFrame);
        return false;
    }

    result = avformat_find_stream_info(pAVFormatContext, NULL);
    if (result < 0){
        qDebug()<<"avformat_find_stream_info < 0";
        avformat_free_context(pAVFormatContext);
        av_frame_free(&pAVFrame);
        return false;
    }

    videoStreamIndex = -1;
    for (uint i = 0; i < pAVFormatContext->nb_streams; i++) {
        if (AVMEDIA_TYPE_VIDEO == pAVFormatContext->streams[i]->codec->codec_type) {
            videoStreamIndex = i;
            break;
        }
    }

    if (-1 == videoStreamIndex){
        qDebug()<<"-1 == videoStreamIndex";
        avformat_free_context(pAVFormatContext);
        av_frame_free(&pAVFrame);
        return false;
    }

    pAVCodecContext = pAVFormatContext->streams[videoStreamIndex]->codec;
    videoWidth = pAVCodecContext->width;
    videoHeight = pAVCodecContext->height;

    avpicture_alloc(&pAVPicture, AV_PIX_FMT_RGB24, videoWidth, videoHeight);

    AVCodec *pAVCodec;

    pAVCodec = avcodec_find_decoder(pAVCodecContext->codec_id);
    pSwsContext = sws_getContext(videoWidth, videoHeight, AV_PIX_FMT_YUV420P,
                                 videoWidth, videoHeight, AV_PIX_FMT_RGB24,
                                 SWS_BICUBIC, 0, 0, 0);

    result = avcodec_open2(pAVCodecContext, pAVCodec, NULL);
    if (result<0){
        qDebug()<<"avcodec_open2 < 0";
        avformat_free_context(pAVFormatContext);
        av_frame_free(&pAVFrame);
        sws_freeContext(pSwsContext);
        avpicture_free(&pAVPicture);
        return false;
    }

    qDebug()<<"open success";
    return true;
}

void FFmpeg::close() {
    if(opened) {
        avformat_free_context(pAVFormatContext);
        av_frame_free(&pAVFrame);
        sws_freeContext(pSwsContext);
        avpicture_free(&pAVPicture);
        opened = false;
    }
}

void FFmpeg::play(QString url, int index) {
    if(url.count() < 4) {
        return;
    }
    if(!started) {
        started = true;
        this->url = url;
        this->index = index;
        start();
    }
    if(0 != this->url.compare(url) && this->index == index) {
        this->url = url;
        restart = true;
    }
    stoped = false;
}

void FFmpeg::stop() {
    stoped = true;
}

void FFmpeg::run() {
    prepare();
    int frameFinished = 0;
    QDateTime time0 = QDateTime::currentDateTime();
    int reconnectcount = 0;
    while (true){
        if(stoped) {
            sleep(5);
            continue;
        }
        if(!opened) {
            qDebug()<<"opening rtsp stream "<<url;
            opened = open();
            frameFinished = 0;
            sleep(1);
            continue;
        } else if(restart) {
            close();
            sleep(1);
            restart = false;
            continue;
        }
        if (av_read_frame(pAVFormatContext, &pAVPacket) >= 0){
            if(pAVPacket.stream_index == videoStreamIndex){
                avcodec_decode_video2(pAVCodecContext, pAVFrame, &frameFinished, &pAVPacket);
                if (frameFinished){
                    sws_scale(pSwsContext,(const uint8_t* const *)pAVFrame->data,pAVFrame->linesize,0,videoHeight,pAVPicture.data,pAVPicture.linesize);

                    QImage image(pAVPicture.data[0],videoWidth,videoHeight,QImage::Format_RGB888);
                    emit GetImage(image, index);
                    time0 = QDateTime::currentDateTime().addSecs(5);
                }
            }
        } else {;
            if(QDateTime::currentDateTime().secsTo(time0) < 0) {
                restart = true;
                ++reconnectcount;
            }
            qDebug()<<"av_read_frame < 0"<<"reconnectcount "<<reconnectcount;
            usleep(1000);
        }
        av_free_packet(&pAVPacket);
    }
    close();
}



#ifndef QFFMPEG_H
#define QFFMPEG_H

#include <QObject>
#include <QThread>
#include <QDateTime>

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavfilter/avfilter.h>
#include <libswscale/swscale.h>
#include <libavutil/frame.h>
}

class FFmpeg : public QThread
{
    Q_OBJECT
public:
    explicit FFmpeg();
    ~FFmpeg();
    void play(QString url, int index);
    void run();
    QString getUrl();
    void stop();

signals:
    void GetImage(const QImage &image, const int index);

public slots:
private:
    int index;
    AVPicture  pAVPicture;
    AVFormatContext *pAVFormatContext;
    AVCodecContext *pAVCodecContext;
    AVFrame *pAVFrame;
    SwsContext * pSwsContext;
    AVPacket pAVPacket;

    QString url;
    int videoWidth;
    int videoHeight;
    int videoStreamIndex;
    bool started;
    bool restart;
    bool opened;
    bool stoped;

    bool prepare();
    bool open();
    void close();
};

#endif // QFFMPEG_H

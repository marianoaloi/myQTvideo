#ifndef MVIDEO_H
#define MVIDEO_H

#include <QWidget>
#include <string>
#include <component/rangeslider.h>
#include <QFileDialog>
#include <iostream>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QVideoWidget>


QT_BEGIN_NAMESPACE
class QMediaPlayer;
QT_END_NAMESPACE

using namespace std;

namespace Ui
{
    class MVideo;
}

class MVideo : public QWidget
{
    Q_OBJECT

public slots:
    void openVideo();

public:
    explicit MVideo(QWidget *parent = nullptr);
    ~MVideo();

private:
    Ui::MVideo *ui;
    QString directory = nullptr;
    RangeSlider *slider = nullptr;
    QMediaPlayer *m_player = nullptr;
    QMediaPlaylist *m_playlist = nullptr;
    QVideoWidget *m_videoWidget = nullptr;
};

#endif // MVIDEO_H

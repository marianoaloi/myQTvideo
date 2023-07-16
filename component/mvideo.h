#ifndef MVIDEO_H
#define MVIDEO_H

#include <string>
#include <iostream>

#include <component/rangeslider.h>

#include <QWidget>
#include <QFileDialog>
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

private slots:

    // void playlistPositionChanged(int);

public:
    explicit MVideo(QWidget *parent = nullptr);
    ~MVideo();

private:
    Ui::MVideo *ui;
    int duration = 0;
    QString directory = nullptr;
    RangeSlider *slider = nullptr;
    QMediaPlayer *m_player = nullptr;
    QMediaPlaylist *m_playlist = nullptr;
    QVideoWidget *m_videoWidget = nullptr;

    //Methods
    void setPossition(int);
    int getPossition();
    void mediastateChanged(int);
    void positionChanged(int);
    void durationChanged(int);
    // void metaDataChanged();
    // void playlistPositionChanged();
    // void bufferingProgress();
    // void videoAvailableChanged();
    // void displayErrorMessage();
    // void stateChanged();


    // HistogramWidget *m_videoHistogram = nullptr;
    // HistogramWidget *m_audioHistogram = nullptr;
    // PlaylistModel *m_playlistModel = nullptr;
    // QAbstractItemView *m_playlistView = nullptr;


    // void clearHistogram();

    void openVideo(QString);
};

#endif // MVIDEO_H

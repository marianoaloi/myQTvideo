#include "mvideo.h"
#include "ui_mvideo.h"

#include <QMediaService>
#include <QMediaPlaylist>
#include <QVideoProbe>
#include <QAudioProbe>
#include <QMediaMetaData>

MVideo::MVideo(QWidget *parent) : QWidget(parent),
                                  ui(new Ui::MVideo)
{
    ui->setupUi(this);

    //! [create-objs]
    m_player = new QMediaPlayer(this, QMediaPlayer::VideoSurface);
    m_player->setAudioRole(QAudio::VideoRole);
    qInfo() << "Supported audio roles:";
    for (QAudio::Role role : m_player->supportedAudioRoles())
        qInfo() << "    " << role;
    // owned by PlaylistModel
    m_playlist = new QMediaPlaylist();
    m_player->setPlaylist(m_playlist);

    connect(m_player, &QMediaPlayer::positionChanged, this, &MVideo::setPossition);
    connect(m_player, &QMediaPlayer::durationChanged, this, &MVideo::durationChanged);
    connect(m_player, &QMediaPlayer::mediaStatusChanged, this, &MVideo::mediastateChanged);
    // connect(m_player, QOverload<>::of(&QMediaPlayer::metaDataChanged), this, &MVideo::metaDataChanged);
    // connect(m_playlist, &QMediaPlaylist::currentIndexChanged, this, &MVideo::playlistPositionChanged);
    // connect(m_player, &QMediaPlayer::bufferStatusChanged, this, &MVideo::bufferingProgress);
    // connect(m_player, &QMediaPlayer::videoAvailableChanged, this, &MVideo::videoAvailableChanged);
    // connect(m_player, QOverload<QMediaPlayer::Error>::of(&QMediaPlayer::error), this, &MVideo::displayErrorMessage);
    // connect(m_player, &QMediaPlayer::stateChanged, this, &MVideo::stateChanged);

    // connect(m_playlist, &QMediaPlaylist::currentIndexChanged, this, &MVideo::playlistPositionChanged);
    //! [create-objs]

    slider = new RangeSlider(this);
    slider->setOrientation(Qt::Orientation::Horizontal);
    slider->setObjectName("slider");
    slider->setRange(0, 0);
    slider->setMinimum(0);
    // slider.sliderMoved(e)
    connect(slider, &RangeSlider::sliderMoved, this, &MVideo::setPossition);
    connect(slider, &RangeSlider::sliderMovedMaloi, this, &MVideo::setPossition);
    ui->sliderPanel->addWidget(slider);

    m_player->setVideoOutput(ui->videoWidget);
    ui->videoWidget->show();
}

MVideo::~MVideo()
{
    delete ui;
}

void MVideo::openVideo()
{
    QFileDialog filename(this);
    filename.setFileMode(QFileDialog::FileMode::Directory);
    // filename.setDirectory(QStandardPaths::standardLocations(QStandardPaths::MoviesLocation).value(0, QDir::homePath()));
    directory = filename.getExistingDirectory(this, "Open Video", directory, QFileDialog::Option::ShowDirsOnly);
    if (!directory.isEmpty())
    {
        cout << directory.toStdString() << "\n";
        QDir qdirectory(directory);
        QFileInfoList images = qdirectory.entryInfoList(QStringList() << "*.mp4"
                                                                      << "*.JPG",
                                                        QDir::Files);
        foreach (QFileInfo entry, images)
        {
            cout << entry.filePath().toStdString() << "\n"
                 << endl;
            this->openVideo(entry.filePath());
        }
    }
}

void MVideo::openVideo(QString path)
{
    m_player->setMedia(QMediaContent(QUrl().fromLocalFile(path)));
    m_player->play();
}

void MVideo::setPossition(int possition)
{
    this->m_player->setPosition(possition);
}
int MVideo::getPossition()
{
    return this->m_player->position();
}

void MVideo::durationChanged(int durationInt)
{
    durationInt = durationInt - 100;
    slider->activeSlider(0);
    slider->setMaximum(durationInt);
    this->duration = durationInt;
}
void MVideo::positionChanged(int possition)
{
    this->slider->setValue(possition);
}
void MVideo::mediastateChanged(int possition)
{
}

// void MVideo::playlistPositionChanged(int currentItem)
// {
//     clearHistogram();
//     m_playlistView->setCurrentIndex(m_playlistModel->index(currentItem, 0));
// }

// void MVideo::clearHistogram()
// {
//     QMetaObject::invokeMethod(m_videoHistogram, "processFrame", Qt::QueuedConnection, Q_ARG(QVideoFrame, QVideoFrame()));
//     QMetaObject::invokeMethod(m_audioHistogram, "processBuffer", Qt::QueuedConnection, Q_ARG(QAudioBuffer, QAudioBuffer()));
// }
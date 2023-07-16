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

    // connect(m_playlist, &QMediaPlaylist::currentIndexChanged, this, &MVideo::playlistPositionChanged);
    //! [create-objs]

    RangeSlider *slider = new RangeSlider(this);
    slider->setOrientation(Qt::Orientation::Horizontal);
    slider->setObjectName("slider");
    slider->setRange(0, 0);
    // slider.sliderMoved(e)
    // connect(slider, &RangeSlider);
    ui->sliderPanel->addWidget(slider);

    QVBoxLayout vbox(this);
    m_videoWidget = new QVideoWidget(this);
    m_player->setVideoOutput(m_videoWidget);
    m_videoWidget->show();
    vbox.addWidget(m_videoWidget);
    ui->videoWidget->setLayout(&vbox);
}

MVideo::~MVideo()
{
    delete ui;
}

void MVideo::openVideo()
{
    QFileDialog filename(this);
    filename.setFileMode(QFileDialog::FileMode::Directory);
    directory = filename.getExistingDirectory(this, "Open Video", directory, QFileDialog::Option::ShowDirsOnly);
    if (!directory.isEmpty())
    {
        cout << directory.toStdString() << "\n";
        QDir qdirectory(directory);
        QStringList images = qdirectory.entryList(QStringList() << "*.mp4" << "*.JPG",QDir::Files);
        foreach(QString entry, images) 
        {
            cout << entry.toStdString() << "\n"<< endl;
            m_player->setMedia(QMediaContent(QUrl().fromLocalFile(entry)));
            m_player->play();
        }
    }
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
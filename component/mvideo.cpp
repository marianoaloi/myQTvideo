#include "mvideo.h"
#include "ui_mvideo.h"

#include <QMediaService>
#include <QMediaPlaylist>
#include <QVideoProbe>
#include <QAudioProbe>
#include <QMediaMetaData>

MVideo::MVideo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MVideo)
{
    ui->setupUi(this);

    //! [create-objs]
    m_player = new QMediaPlayer(this);
    m_player->setAudioRole(QAudio::VideoRole);
    qInfo() << "Supported audio roles:";
    for (QAudio::Role role : m_player->supportedAudioRoles())
        qInfo() << "    " << role;
    // owned by PlaylistModel
    m_playlist = new QMediaPlaylist();
    m_player->setPlaylist(m_playlist);
//! [create-objs]

    RangeSlider *slider = new RangeSlider(this);
    slider->setOrientation(Qt::Orientation::Horizontal);
    slider->setObjectName("slider");
    slider->setRange(0,0);
    // slider.sliderMoved(e)
    // connect(slider, &RangeSlider);
    // ui->sliderPanel->addWidget(slider);
}

MVideo::~MVideo()
{
    delete ui;
}

void MVideo::openVideo(){
    QFileDialog filename(this);
    filename.setFileMode(QFileDialog::FileMode::Directory);
    directory = filename.getExistingDirectory(this,"Open Video", directory,QFileDialog::Option::ShowDirsOnly);
    if(!directory.isEmpty()){
    cout << directory.toStdString() << "\n";
    }
}
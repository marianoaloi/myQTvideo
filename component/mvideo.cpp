#include "mvideo.h"
#include "ui_mvideo.h"

MVideo::MVideo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MVideo)
{
    ui->setupUi(this);

    RangeSlider slider;
    ui->sliderPanel->addWidget(&slider);
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
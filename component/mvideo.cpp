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

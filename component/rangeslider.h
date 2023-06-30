#ifndef RANGESLIDER_H
#define RANGESLIDER_H

#include <QSlider>
#include <QStyle>
#include <QWidget>
#include <QPainter>
#include <QStyleOptionSlider>

class RangeSlider : public QSlider
{

    void paintEvent(QPaintEvent *ev);

public:
    RangeSlider();

private:
    QStyle::SubControl pressed_control;
    int tick_interval;
    QSlider::TickPosition tick_position;
    QStyle::SubControl hover_control;
    int click_offset;
};

#endif // RANGESLIDER_H

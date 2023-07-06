#ifndef RANGESLIDER_H
#define RANGESLIDER_H

#include <QSlider>
#include <QStyle>
#include <QWidget>
#include <QPainter>
#include <QStyleOptionSlider>
#include <QApplication>
#include <algorithm>

using namespace std;

class RangeSlider : public QSlider
{

  virtual  void paintEvent(QPaintEvent *ev);

public:
    RangeSlider();
    int low();
    void setLow(int low);
    int high();
    void setHigh(int high);

private:
    QStyle::SubControl pressed_control;
    QSlider::TickPosition tick_position;
    QStyle::SubControl hover_control;
    int _low;
    int _high;
    int tick_interval;
    int click_offset;
    int active_slider;
    int RangeSlider::pick(QPoint pt);
};

#endif // RANGESLIDER_H

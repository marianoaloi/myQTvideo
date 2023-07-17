#ifndef RANGESLIDER_H
#define RANGESLIDER_H

#include <QSlider>
#include <QWidget>
#include <QStyle>
#include <QWidget>
#include <QMouseEvent>

using namespace std;

class RangeSlider : public QSlider
{

  Q_OBJECT

  virtual void paintEvent(QPaintEvent *ev) override;
  virtual void mouseMoveEvent(QMouseEvent *ev);
  virtual void mousePressEvent(QMouseEvent *ev);

public:
  explicit RangeSlider(QWidget *parent = nullptr);
  int low();
  void setLow(int low);
  int high();
  void setHigh(int high);
  void activeSlider(int);
  int activeSlider();

private:
  QStyle::SubControl pressed_control;
  QSlider::TickPosition tick_position;
  QStyle::SubControl hover_control;
  int _low=0;
  int _high=0;
  int tick_interval=0;
  int click_offset=0;
  int active_slider=0;
  int pick(QPoint pt);
  int pixelPosToRangeValue(int pos);

signals:
  void sliderMovedMaloi(int pos);
  void sliderMovedDouble(int low, int high);
};

#endif // RANGESLIDER_H

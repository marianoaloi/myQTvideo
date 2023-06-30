#include "rangeslider.h"

int _low,_hight;
RangeSlider::RangeSlider()
{
    _low=this->minimum();
    _hight=this->maximum();

    this->pressed_control = QStyle::SC_None;
    this->tick_interval = 0;
    this->tick_position = QSlider::NoTicks;
    this->hover_control = QStyle::SC_None;
    this->click_offset = 0;


}



void RangeSlider::paintEvent(QPaintEvent *ev) {
    QPainter painter;
//    QStyle style = ;
    QStyleOptionSlider opt;
}

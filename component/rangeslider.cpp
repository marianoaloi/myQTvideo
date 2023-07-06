#include "rangeslider.h"

int _low, _hight;
RangeSlider::RangeSlider() // Add superclass dependnece
{

    this->_low = this->minimum();
    this->_high = this->maximum();

    this->pressed_control = QStyle::SC_None;
    this->tick_interval = 0;
    this->tick_position = QSlider::NoTicks;
    this->hover_control = QStyle::SC_None;
    this->click_offset = 0;

    this->active_slider = 0;
}

int RangeSlider::low()
{
    return this->_low;
}

void RangeSlider::setLow(int low)
{
    this->_low = low;
    this->update();
}

int RangeSlider::high()
{
    return this->_high;
}

void RangeSlider::setHigh(int high)
{
    this->_high = high;
    this->update();
}

void RangeSlider::paintEvent(QPaintEvent *ev)
{
    QPainter painter;
    QStyle *styleSlide = QApplication::style();
    QStyleOptionSlider opt;
    this->initStyleOption(&opt);
    opt.sliderValue = 0;
    opt.sliderPosition = 0;
    opt.subControls = QStyle::SC_SliderGroove;

    if (this->tickPosition() != this->NoTicks)
    {
        opt.subControls |= QStyle::SC_SliderTickmarks;
    }
    styleSlide->drawComplexControl(QStyle::CC_Slider, &opt, &painter, this);
    QRect groove = styleSlide->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderGroove, this);

    initStyleOption(&opt);
    opt.subControls = QStyle::SC_SliderGroove;
    opt.sliderValue = 0;

    opt.sliderPosition = this->_low;
    QRect low_rect = styleSlide->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, this);
    opt.sliderPosition = this->_high;
    QRect high_rect = styleSlide->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, this);

    int low_pos = pick(low_rect.center());
    int high_pos = pick(high_rect.center());

    int min_pos = min(low_pos, high_pos);
    int max_pos = max(low_pos, high_pos);

    QPoint c = QRect(low_rect.center(),high_rect.center()).center();
}

int RangeSlider::pick(QPoint pt)
{
    if (this->orientation() == Qt::Horizontal)
    {
        return pt.x();
    }
    else
    {
        return pt.y();
    }
}
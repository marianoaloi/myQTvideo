#include "rangeslider.h"


#include <QPainter>
#include <QStyleOptionSlider>
#include <QApplication>
#include <QPalette>
#include <algorithm>

int _low, _hight;
RangeSlider::RangeSlider(QWidget *parent)
:QSlider(parent)
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

    QPoint c = QRect(low_rect.center(), high_rect.center()).center();

    QRect span_rect;
    if (opt.orientation == Qt::Horizontal)
    {
        span_rect = QRect(QPoint(min_pos, c.y() - 2), QPoint(max_pos, c.y() + 1));
    }
    else
    {

        span_rect = QRect(QPoint(c.x() - 2, min_pos), QPoint(c.x() + 1, max_pos));
    }

    if (opt.orientation == Qt::Horizontal)
        groove.adjust(0, 0, -1, 0);
    else
        groove.adjust(0, 0, 0, -1);

    QColor highlight = palette().color(QPalette::Highlight);
    painter.setBrush(QBrush(highlight));
    painter.setPen(QPen(highlight, 0));
    painter.drawRect(span_rect.intersected(groove));

    for (int value = _low; value < _high; value++)
    {

        QStyleOptionSlider opt;
        this->initStyleOption(&opt);

        opt.subControls = QStyle::SC_SliderHandle;

        if (this->tickPosition() != this->NoTicks)
        {
            opt.subControls |= QStyle::SC_SliderTickmarks;
        }

        if (this->pressed_control)
        {
            opt.activeSubControls = pressed_control;
        }
        else
        {
            opt.activeSubControls = hover_control;
        }
        opt.sliderPosition = value;
        opt.sliderValue = value;
        styleSlide->drawComplexControl(QStyle::CC_Slider, &opt, &painter, this);
    }
}

void RangeSlider::mousePressEvent(QMouseEvent *ev)
{
    ev->accept();
    QStyle *styleSlide = QApplication::style();
    Qt::MouseButton button = ev->button();

    if (button != 0L)
    {

        QStyleOptionSlider opt;
        this->initStyleOption(&opt);
        active_slider = -1;
        for (int value = _low; value < _high; value++)
        {

            opt.sliderPosition = value;
            QStyle::SubControl hit = styleSlide->hitTestComplexControl(QStyle::CC_Slider, &opt, ev->pos(), this);
            if (hit == styleSlide->SC_SliderHandle)
            {
                active_slider = value - _low;
                pressed_control = hit;

                triggerAction(SliderMove);
                setRepeatAction(SliderNoAction);
                setSliderDown(true);
                break;
            }
        }
        if (active_slider < 0)
        {
            pressed_control = QStyle::SC_SliderHandle;
            click_offset = pixelPosToRangeValue(pick(ev->pos()));
            triggerAction(SliderMove);
            setRepeatAction(SliderNoAction);
        }
    }
    else
    {
        ev->ignore();
    }
}
void RangeSlider::mouseMoveEvent(QMouseEvent *ev)
{
    if (pressed_control != QStyle::SC_SliderHandle)
    {
        ev->ignore();
        return;
    }

    ev->accept();
    int new_pos = pixelPosToRangeValue(pick(ev->pos()));
    QStyleOptionSlider opt;
    this->initStyleOption(&opt);

    if (active_slider < 0)
    {
        int offset = new_pos - click_offset;
        _high += offset;
        _low += offset;
        if (_low < minimum())
        {
            int diff = minimum() - _low;
            _low += diff;
            _high += diff;
        }
        if (_high > maximum()){
            int diff = minimum() - _high;
            _low += diff;
            _high += diff;
        }
    }
    else if (active_slider == 0)
    {
        if (new_pos >= _high)
            new_pos = _high - 1;
        _low = new_pos;
    }
    else
    {
        if (new_pos <= _low)
            new_pos = _low + 1;
        _high = new_pos;
    }

    click_offset = new_pos;

    this->update();

    emit sliderMovedMaloi(new_pos);
    emit sliderMovedDouble(_low,_high);
}

int RangeSlider::pixelPosToRangeValue(int pos)
{
    QStyle *styleSlide = QApplication::style();
    QStyleOptionSlider opt;
    this->initStyleOption(&opt);

    QRect gr = styleSlide->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderGroove, this);
    QRect sr = styleSlide->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, this);

    int slider_length;
    int slider_min;
    int slider_max;

    if (opt.orientation == Qt::Horizontal)
    {
        slider_length = sr.width();
        slider_min = gr.x();
        slider_max = gr.right() - slider_length + 1;
    }
    else
    {
        slider_length = sr.height();
        slider_min = gr.y();
        slider_max = gr.bottom() - slider_length + 1;
    }
    return styleSlide->sliderValueFromPosition(minimum(), maximum(), pos - slider_min, slider_max - slider_min, opt.upsideDown);
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
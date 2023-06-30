#ifndef MVIDEO_H
#define MVIDEO_H

#include <QWidget>
#include <component/rangeslider.h>

namespace Ui {
class MVideo;
}

class MVideo : public QWidget
{
    Q_OBJECT

public:
    explicit MVideo(QWidget *parent = nullptr);
    ~MVideo();

private:
    Ui::MVideo *ui;
};

#endif // MVIDEO_H

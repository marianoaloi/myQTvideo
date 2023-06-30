#ifndef MVIDEO_H
#define MVIDEO_H

#include <QWidget>
#include <string>
#include <component/rangeslider.h>
#include <QFileDialog>
#include <iostream>

using namespace std;

namespace Ui
{
    class MVideo;
}

class MVideo : public QWidget
{
    Q_OBJECT

public slots:
    void openVideo();

public:
    explicit MVideo(QWidget *parent = nullptr);
    ~MVideo();

private:
    Ui::MVideo *ui;
    QString directory;
};

#endif // MVIDEO_H

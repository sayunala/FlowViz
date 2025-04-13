#ifndef IGWCAMERATOOLBAR_H
#define IGWCAMERATOOLBAR_H

#include <QWidget>
#include <QToolBar>
namespace Ui {
class igwCameraToolBar;
}

class igwCameraToolBar : public QToolBar
{
    Q_OBJECT

public:
    explicit igwCameraToolBar(QWidget *parent = nullptr);
    ~igwCameraToolBar();

private:
    Ui::igwCameraToolBar *ui;
};

#endif // IGWCAMERATOOLBAR_H

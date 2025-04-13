#ifndef IGWVCRTOOLBAR_H
#define IGWVCRTOOLBAR_H

#include <QWidget>
#include <QToolBar>
class igwVCRControl;
namespace Ui {
class igwVCRToolBar;
}

class igwVCRToolBar : public QToolBar
{
    Q_OBJECT

public:
    explicit igwVCRToolBar(QWidget *parent = nullptr);
    ~igwVCRToolBar();

protected Q_SLOTS:
    void onPlaying(bool, bool);
private:
    Ui::igwVCRToolBar *ui;

    igwVCRControl* Controller;

};

#endif // IGWVCRTOOLBAR_H

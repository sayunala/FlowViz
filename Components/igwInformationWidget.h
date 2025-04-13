#ifndef IGWINFORMATIONWIDGET_H
#define IGWINFORMATIONWIDGET_H

#include <QWidget>

namespace Ui {
class igwInformationWidget;
}

class igwInformationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit igwInformationWidget(QWidget *parent = nullptr);
    ~igwInformationWidget();

private:
    Ui::igwInformationWidget *ui;
};

#endif // IGWINFORMATIONWIDGET_H

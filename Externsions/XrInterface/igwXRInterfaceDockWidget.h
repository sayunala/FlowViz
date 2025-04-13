#ifndef IGWXRINTERFACEDOCKWIDGET_H
#define IGWXRINTERFACEDOCKWIDGET_H

#include <QDockWidget>
#include <QScopedPointer>

namespace Ui {
class igwXRInterfaceDockWidget;
}

class igwXRInterfaceDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit igwXRInterfaceDockWidget(QWidget *parent = nullptr);
    ~igwXRInterfaceDockWidget();


private slots:
    void on_SendToXRBtn_clicked();

    void on_ShowViewBtn_clicked();

private:

    void Init();
    Ui::igwXRInterfaceDockWidget *ui;
    struct igwInternals;
    QScopedPointer<igwInternals> Internals;
};

#endif // IGWXRINTERFACEDOCKWIDGET_H

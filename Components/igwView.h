#ifndef IGWVIEW_H
#define IGWVIEW_H

#include <QObject>
#include <QPointer>
#include <QWidget>
#include "vtkView.h"
#include "vtkSmartPointer.h"
class igwView : public QObject
{
    Q_OBJECT
public:
    explicit igwView(vtkView* view, QObject *parent = nullptr);
    virtual ~igwView() override;

    virtual QWidget* createWidget() = 0;
    QWidget *widget();

    vtkView *getVtkView();


public Q_SLOTS:
    virtual void render();

    virtual void forceRender();
protected:
    QPointer<QWidget> Widget;
    bool WidgetCreated = false;
    vtkSmartPointer<vtkView> View;
};

#endif // IGWVIEW_H

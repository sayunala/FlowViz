#ifndef IGWVTKWIDGET_H
#define IGWVTKWIDGET_H

#include <QWidget>

#include "vtkView.h"
#include "vtkSmartPointer.h"
class vtkRenderer;
class vtkGenericOpenGLRenderWindow;
namespace Ui {
class igwVtkWidget;
}


class igwVtkWidget : public QWidget
{
    Q_OBJECT

public:
    explicit igwVtkWidget(QWidget *parent = nullptr);
    ~igwVtkWidget();

    void setView(vtkView* view);


private:
    Ui::igwVtkWidget *ui;
    vtkSmartPointer<vtkView> View;
    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow;

};

#endif // IGWVTKWIDGET_H

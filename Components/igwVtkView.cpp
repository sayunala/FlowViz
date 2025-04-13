#include "igwVtkView.h"
#include "igwVtkWidget.h"
#include "Representation/igwRenderView.h"
igwVtkView::igwVtkView(vtkView* view, QObject* parent)
    :Superclass(view, parent)
{

}

igwVtkView::igwVtkView(QObject *parent)
    :Superclass(vtkSmartPointer<igwRenderView>::New(), parent)
{

}

igwVtkView::~igwVtkView()
{
    std::cout << "delete igwvtkview" << std::endl;
}

QWidget *igwVtkView::createWidget()
{
    igwVtkWidget* widget = new igwVtkWidget();
    widget->setView(this->getVtkView());
    return widget;
}

void igwVtkView::render()
{
    this->Superclass::render();
}

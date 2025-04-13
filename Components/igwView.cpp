#include "igwView.h"
#include "vtkView.h"
#include "igwVtkWidget.h"
#include "Representation/igwRenderView.h".h"
igwView::igwView(vtkView* view, QObject *parent)
    :QObject(parent)
{
    View = view;
}

igwView::~igwView()
{

}

QWidget *igwView::widget()
{
    if(this->WidgetCreated == false)
    {
        this->Widget = this->createWidget();
        this->WidgetCreated = true;
    }
    return this->Widget;
}

vtkView *igwView::getVtkView()
{
    return this->View;
}

void igwView::render()
{
    this->forceRender();
}

void igwView::forceRender()
{
    igwVtkWidget* vtkWidget = qobject_cast<igwVtkWidget*>(this->widget());
    if(vtkWidget !=nullptr && !vtkWidget->isVisible())
    {
        return;
    }
    vtkView* view = this->getVtkView();
    view->Update();
    igwRenderView* rView = igwRenderView::SafeDownCast(view);
    if(rView != nullptr)
        rView->Render();
}

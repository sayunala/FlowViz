#include "igwVtkWidget.h"

#include "ui_igwVtkWidget.h"

#include <QSurfaceFormat>
#include <vtkCallbackCommand.h>

#include "vtkGenericOpenGLRenderWindow.h"
#include "vtkNamedColors.h"
#include "vtkRenderer.h"
#include "igwView.h"
#include "igwVtkView.h"
#include "Representation/igwRenderViewBase.h"
#include "Representation/igwRenderView.h"

void CallbackFunction(vtkObject* caller, long unsigned int eventId,
                      void* clientData, void* callData)
{
    vtkRenderer* renderer = static_cast<vtkRenderer*>(caller);

    double timeInSeconds = renderer->GetLastRenderTimeInSeconds();
    double fps = 1.0 / timeInSeconds;
//    std::cout << "FPS: " << fps << std::endl;
//    std::cout << "FPS: " << timeInSeconds << std::endl;
//    std::cout << "Callback" << std::endl;
}
igwVtkWidget::igwVtkWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::igwVtkWidget)
{
    ui->setupUi(this);
    QSurfaceFormat::setDefaultFormat(QVTKOpenGLNativeWidget::defaultFormat());
    vtkNew<vtkNamedColors> colors;

    // 初始化VTK窗口
    renderer = vtkSmartPointer<vtkRenderer>::New();

//    renderer->SetBackground(colors->GetColor3d("SteelBlue").GetData());
//    renderer->SetGradientBackground(true);
    renderer->SetBackground(1,1,1);
//    renderer->SetBackground2(75.0/255.0,75.0/255.0,75.0/255.0);

    renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();


    renderWindow->AddRenderer(renderer);
    renderWindow->SetWindowName("RenderWindowNoUIFile");
    ui->vtkWidget->setRenderWindow(renderWindow);

    vtkNew<vtkCallbackCommand> callback;

    callback->SetCallback(CallbackFunction);
    renderer->AddObserver(vtkCommand::EndEvent, callback);

}

igwVtkWidget::~igwVtkWidget()
{
    delete ui;
}

void igwVtkWidget::setView(vtkView *view)
{
    if(view != this->View)
    {
        this->View = view;
        view->Print(std::cout);
        this->View->Print(std::cout);
        igwRenderView* renderView = igwRenderView::SafeDownCast(this->View);
        renderView->SetRenderWindow(renderWindow);
        renderView->SetRenderer(renderer);
    }

}

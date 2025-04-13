#include "igwRenderView.h"
#include "igwrenderviewbase.h"
#include "vtkCommand.h"
#include "vtkObjectFactory.h"

#include "vtkDataRepresentation.h"

#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkGenericOpenGLRenderWindow.h"
#include "igwRenderedRepresentation.h"

#include "vtkRenderWindowInteractor.h"
#include "vtkInteractorStyleRubberBandZoom.h"
#include "vtkInteractorStyleRubberBand2D.h"
#include "vtkInteractorStyleRubberBand3D.h"
#include "vtkInteractorStyle3D.h"
#include "vtkInteractorStyleTrackballCamera.h"

#include "vtkViewTheme.h"
#include "vtkOrientationMarkerWidget.h"
#include "vtkAxesActor.h"
#include "vtkCamera.h"
#include "Externsions/Sources/vtkLidarGridActor.h"


vtkStandardNewMacro(igwRenderView);

igwRenderView::igwRenderView()
{
    this->RenderWindow->AddObserver(vtkCommand::EndEvent, this->GetObserver());

    vtkRenderWindowInteractor* iren = this->RenderWindow->GetInteractor();
    this->SetInteractor(iren);


    this->RubberBandZoom = vtkInteractorStyleRubberBandZoom::New();
    this->RubberBandZoom->SetLockAspectToViewport(true);
    this->RubberBandZoom->SetUseDollyForPerspectiveProjection(false);
    this->RubberBandZoom->SetAutoAdjustCameraClippingRange(true);
    this->RubberBand2D = vtkInteractorStyleRubberBand2D::New();
    this->RubberBand3D = vtkInteractorStyleRubberBand3D::New();

    this->TrackballCamera = vtkInteractorStyleTrackballCamera::New();

    // construct Axes
    AxesActor = vtkSmartPointer<vtkAxesActor>::New();
    AxesWidget = vtkSmartPointer<vtkOrientationMarkerWidget>::New();
    AxesWidget->SetOrientationMarker(AxesActor);

    this->LidarGridActor = vtkSmartPointer<vtkLidarGridActor>::New();


}

igwRenderView::~igwRenderView()
{
    if(this->RubberBandZoom)
    {
        this->RubberBandZoom->Delete();
        this->RubberBandZoom = nullptr;
    }
    if(this->RubberBand3D)
    {
        this->RubberBand3D->Delete();
        this->RubberBand3D = nullptr;
    }
    if(this->RubberBand2D)
    {
        this->RubberBand2D->Delete();
        this->RubberBand2D = nullptr;
    }
    if(this->TrackballCamera)
    {
        this->TrackballCamera->Delete();
        this->TrackballCamera = nullptr;
    }

}
void igwRenderView::PrintSelf(std::ostream &os, vtkIndent indent)
{
    
}

void igwRenderView::SetInteractor(vtkRenderWindowInteractor *interactor)
{
    if (!interactor)
    {
      vtkErrorMacro(<< "SetInteractor called with a null interactor pointer."
                    << " That can't be right.");
      return;
    }

    if (this->GetInteractor())
    {
        this->GetInteractor()->RemoveObserver(this->GetObserver());
    }


    interactor->EnableRenderOff();
    interactor->AddObserver(vtkCommand::RenderEvent, this->GetObserver());
    interactor->AddObserver(vtkCommand::StartInteractionEvent, this->GetObserver());
    interactor->AddObserver(vtkCommand::EndInteractionEvent, this->GetObserver());
    //Call RenderViewBase SetInteractor
    this->Superclass::SetInteractor(interactor);


}

void igwRenderView::SetInteractorStyle(vtkInteractorObserver *style)
{
    if (!style)
    {
        vtkErrorMacro("Interactor style must not be null.");
        return;
    }
    vtkInteractorObserver* oldStyle = this->GetInteractorStyle();
    if (style != oldStyle)
    {
      if (oldStyle)
      {
        oldStyle->RemoveObserver(this->GetObserver());
      }
      this->RenderWindow->GetInteractor()->SetInteractorStyle(style);
      style->AddObserver(vtkCommand::SelectionChangedEvent, this->GetObserver());
      vtkInteractorStyleRubberBand2D* style2D = vtkInteractorStyleRubberBand2D::SafeDownCast(style);
      vtkInteractorStyleRubberBand3D* style3D = vtkInteractorStyleRubberBand3D::SafeDownCast(style);
      vtkInteractorStyleRubberBandZoom* styleZoom  =  vtkInteractorStyleRubberBandZoom::SafeDownCast(style);
      if (style2D)
      {
//        style2D->SetRenderOnMouseMove(this->GetRenderOnMouseMove());
        this->InteractionMode = InteractionModes::INTERACTION_MODE_2D;
      }
      else if (style3D)
      {
//        style3D->SetRenderOnMouseMove(this->GetRenderOnMouseMove());
        this->InteractionMode = InteractionModes::INTERACTION_MODE_3D;
      }
      else if(styleZoom)
      {
        this->InteractionMode = InteractionModes::INTERACTION_MODE_ZOOM;
      }
      else
      {
          this->InteractionMode = InteractionModes::INTERACTION_MODE_UNINTIALIZED;
      }
    }
}

void igwRenderView::SetInteractorMode(InteractionModes mode)
{
    this->InteractionMode = mode;
    switch (this->InteractionMode) {
    case InteractionModes::INTERACTION_MODE_ZOOM:
        this->SetInteractorStyle(this->RubberBandZoom);
        break;
    case InteractionModes::INTERACTION_MODE_3D:
        this->SetInteractorStyle(this->TrackballCamera);
    case InteractionModes::INTERACTION_MODE_UNINTIALIZED:
//        this->SetInteractorStyle(this->InteractorStyle3D);
        break;
    }
}

vtkInteractorObserver *igwRenderView::GetInteractorStyle()
{
    if (this->GetInteractor())
    {
        return this->GetInteractor()->GetInteractorStyle();
    }
    return nullptr;
}

void igwRenderView::SetRenderWindow(vtkGenericOpenGLRenderWindow *win)
{
    vtkSmartPointer<vtkRenderWindowInteractor> irenOld = this->GetInteractor();
    this->Superclass::SetRenderWindow(win);
    vtkRenderWindowInteractor* irenNew = this->GetInteractor();
    if (irenOld != irenNew)
    {
      if (irenOld)
      {
        irenOld->RemoveObserver(this->GetObserver());
      }
      if (irenNew)
      {
        this->SetInteractor(irenNew);
      }
    }
}

void igwRenderView::Render()
{
    this->PrepareForRendering();
    this->Renderer->ResetCameraClippingRange();
    this->RenderWindow->Render();
}

void igwRenderView::ApplyViewTheme(vtkViewTheme *theme)
{
    this->Renderer->SetBackground(theme->GetBackgroundColor());
    this->Renderer->SetBackground2(theme->GetBackgroundColor2());
    this->Renderer->SetGradientBackground(true);
    for(int i = 0; i < this->GetNumberOfRepresentations(); ++i)
    {
        this->GetRepresentation(i)->ApplyViewTheme(theme);
    }
}

void igwRenderView::InvokeEvent(unsigned int Event, void *callData)
{
    this->GetInteractor()->InvokeEvent(Event, callData);
}

void igwRenderView::ResetActiveCameraToDirection(const double &look_x, const double &look_y, const double &look_z, const double &up_x, const double &up_y, const double &up_z)
{
    if (vtkCamera* cam = this->GetRenderer()->GetActiveCamera())
    {
      cam->SetPosition(0, 0, 0);
      cam->SetFocalPoint(look_x, look_y, look_z);
      cam->SetViewUp(up_x, up_y, up_z);

    }
    this->GetRenderer()->ResetCamera();
    this->GetInteractor()->Render();
}


void igwRenderView::ResetViewDirectionToPositiveX()
{
    this->ResetActiveCameraToDirection(1, 0, 0, 0, 0, 1);
    std::cout << "to POS X " << std::endl;
}

void igwRenderView::ResetViewDirectionToPositiveY()
{
    this->ResetActiveCameraToDirection(0, 1, 0, 0, 0, 1);
}

void igwRenderView::ResetViewDirectionToPositiveZ()
{
    this->ResetActiveCameraToDirection(0, 0, 1, 0, 1, 0);
}

void igwRenderView::ResetViewDirectionToNegativeX()
{
    this->ResetActiveCameraToDirection(-1, 0, 0, 0, 0, 1);
}

void igwRenderView::ResetViewDirectionToNegativeY()
{
    this->ResetActiveCameraToDirection(0, -1, 0, 0, 0, 1);
}

void igwRenderView::ResetViewDirectionToNegativeZ()
{
    this->ResetActiveCameraToDirection(0, 0, -1, 0, 1, 0);
}

void igwRenderView::ZoomIn()
{
    this->GetRenderer()->GetActiveCamera()->Zoom(2);
    this->GetInteractor()->Render();
}

void igwRenderView::ZoomOut()
{
    this->GetRenderer()->GetActiveCamera()->Zoom(0.5);
    this->GetInteractor()->Render();
}

void igwRenderView::AdjustRoll(double angle)
{
    this->GetRenderer()->GetActiveCamera()->Roll(angle);
    this->Render();
}

void igwRenderView::ShowAxes(bool value)
{
    this->AxesWidget->SetEnabled(value);
    this->GetRenderWindow()->Render();
}

void igwRenderView::SetBackGroundColor(double color[3])
{
    this->GetRenderer()->SetBackground(color);
    this->GetInteractor()->Render();
}


void igwRenderView::PrepareForRendering()
{
    this->Update();
    for(int i = 0; i < this->GetNumberOfRepresentations(); ++i)
    {
        igwRenderedRepresentation* rep = igwRenderedRepresentation::SafeDownCast(this->GetRepresentation(i));
        if(rep)
        {
            rep->PrepareForRendering(this);
        }
    }
    vtkRenderWindowInteractor* iren = this->GetInteractor();

    AxesWidget->SetInteractor(iren);
//    AxesWidget->SetViewport(0.0, 0.0, 0.4, 0.4);
    AxesWidget->SetEnabled(1);
    AxesWidget->InteractiveOff();



}

void igwRenderView::ProcessEvents(vtkObject *caller, unsigned long eventId, void *calLData)
{
    if( caller == this->GetInteractor() && eventId == vtkCommand::RenderEvent)
    {

        this->Render();
    }
    else if (vtkDataRepresentation::SafeDownCast(caller) && eventId == vtkCommand::UpdateDataEvent)
    {
        vtkDebugMacro("push pipeline causing a render event.");
        this->Render();
    }
    this->Superclass::ProcessEvents(caller, eventId, calLData);

}


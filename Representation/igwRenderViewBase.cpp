#include "igwrenderviewbase.h"
#include "vtkCamera.h"
#include "vtkGenericRenderWindowInteractor.h"
#include "vtkInteractorObserver.h"
#include "vtkObjectFactory.h"
#include "vtkRendererCollection.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkGenericOpenGLRenderWindow.h"

#include <QVTKInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
vtkStandardNewMacro(igwRenderViewBase);
igwRenderViewBase::igwRenderViewBase()
{
    this->Renderer = vtkSmartPointer<vtkRenderer>::New();
    this->RenderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    this->RenderWindow->AddRenderer(this->Renderer);

    vtkNew<QVTKInteractor> iren;
    iren->Initialize();
    vtkNew<vtkInteractorStyleTrackballCamera> style;
    iren->SetInteractorStyle(style);
    this->RenderWindow->SetInteractor(iren);

}

igwRenderViewBase::igwRenderViewBase(vtkGenericOpenGLRenderWindow *win)
{
    if(!win)
    this->RenderWindow = win;
    this->RenderWindow->AddRenderer(this->Renderer);
}

void igwRenderViewBase::PrepareForRendering()
{

}
igwRenderViewBase::~igwRenderViewBase() = default;

void igwRenderViewBase::SetRenderer(vtkRenderer* newren)
{
  vtkRendererCollection* rens = this->RenderWindow->GetRenderers();
  vtkCollectionSimpleIterator cookie;
  rens->InitTraversal(cookie);
  while(vtkRenderer *ren = rens->GetNextRenderer(cookie))
  {
    if (ren->GetLayer()<2)
    {
      ren->SetRenderWindow(nullptr);
      this->RenderWindow->RemoveRenderer(ren);
    }
  }

  this->RenderWindow->AddRenderer(newren);
  this->Renderer = newren;
}

vtkRenderer* igwRenderViewBase::GetRenderer()
{
    return this->Renderer;
}

vtkRenderWindow* igwRenderViewBase::GetRenderWindow()
{
    return this->RenderWindow;
}

void igwRenderViewBase::SetRenderWindow(vtkGenericOpenGLRenderWindow *win)
{
    if (!win)
     {
       vtkErrorMacro(<< "SetRenderWindow called with a null window pointer."
                     << " That can't be right.");
       return;
     }
    // move renderers to new window
    vtkRendererCollection* rens = this->RenderWindow->GetRenderers();
    while(rens->GetNumberOfItems())
    {
      vtkRenderer* ren = rens->GetFirstRenderer();
      ren->SetRenderWindow(nullptr);
      win->AddRenderer(ren);
      this->RenderWindow->RemoveRenderer(ren);
    }
    vtkSmartPointer<vtkInteractorObserver> style = this->GetInteractor()?
            this->GetInteractor()->GetInteractorStyle() : nullptr;
    this->RenderWindow = win;
    if (this->GetInteractor())
    {
        this->GetInteractor()->SetInteractorStyle(style);
    }

}

vtkRenderWindowInteractor *igwRenderViewBase::GetInteractor()
{
    return this->RenderWindow->GetInteractor();
}

void igwRenderViewBase::SetInteractor(vtkRenderWindowInteractor * interactor)
{
    if (interactor == this->GetInteractor())
    {
        return;
    }

    vtkSmartPointer<vtkInteractorObserver> style = this->GetInteractor() ?
           this->GetInteractor()->GetInteractorStyle() : nullptr;
     this->RenderWindow->SetInteractor(interactor);
    if (this->GetInteractor())
    {
        this->GetInteractor()->SetInteractorStyle(style);
    }

}

void igwRenderViewBase::Render()
{
    this->PrepareForRendering();
    this->Renderer->Render();
}

void igwRenderViewBase::ResetCamera()
{
//    this->PrepareForRendering();
    this->Renderer->ResetCamera();
    this->GetInteractor()->Render();
}

void igwRenderViewBase::ResetCameraClippingRange()
{
    this->PrepareForRendering();
    this->Renderer->ResetCameraClippingRange();
}
void igwRenderViewBase::PrintSelf(ostream& os, vtkIndent indent){
    this->Superclass::PrintSelf(os, indent);
     os << indent << "RenderWindow: ";
     if (this->RenderWindow)
     {
       os << "\n";
       this->RenderWindow->PrintSelf(os, indent.GetNextIndent());
     }
     else
     {
       os << "(none)\n";
     }
     os << indent << "Renderer: ";
     if (this->Renderer)
     {
       os << "\n";
       this->Renderer->PrintSelf(os, indent.GetNextIndent());
     }
     else
     {
       os << "(none)\n";
     }

}

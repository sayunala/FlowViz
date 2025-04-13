#include "igwOutLineRepresentation.h"
#include "vtkObjectFactory.h"
#include "vtkMapper.h"
#include "vtkOutlineFilter.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "igwRenderView.h"
#include "vtkRenderer.h"
vtkStandardNewMacro(igwOutLineRepresentation)
igwOutLineRepresentation::igwOutLineRepresentation()
{
    this->OutlineFilter = vtkOutlineFilter::New();

    this->Mapper = vtkPolyDataMapper::New();
    this->Actor->SetMapper(this->Mapper);
    this->Mapper->SetInputConnection(this->OutlineFilter->GetOutputPort());

}

igwOutLineRepresentation::~igwOutLineRepresentation()
{
    this->Mapper->Delete();
    this->OutlineFilter->Delete();
}

int igwOutLineRepresentation::RequestData(vtkInformation *request, vtkInformationVector **inputVector, vtkInformationVector *outputVector)
{
    this->OutlineFilter->SetInputConnection(this->GetInternalOutputPort());
    return this->Superclass::RequestData(request, inputVector, outputVector);
}

bool igwOutLineRepresentation::AddToView(vtkView *view)
{
    igwRenderView* rv = igwRenderView::SafeDownCast(view);
      if (!rv)
      {
        vtkErrorMacro("Can only add to a subclass of igwRenderView.");
        return false;
      }
      rv->GetRenderer()->AddActor(this->Actor);

      return true;
}

bool igwOutLineRepresentation::RemoveFromView(vtkView *view)
{
    igwRenderView* rv = igwRenderView::SafeDownCast(view);
     if (rv)
     {
       rv->GetRenderer()->RemoveActor(this->Actor);
       return this->Superclass::RemoveFromView(view);
     }

     return false;
}

void igwOutLineRepresentation::PrintSelf(std::ostream &os, vtkIndent indent)
{

}

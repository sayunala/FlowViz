#include "igwRenderedSurfaceRepresentation.h"
#include "vtkPolyDataMapper.h"
#include "vtkGeometryFilter.h"
#include "vtkActor.h"
#include "vtkObjectFactory.h"
#include "vtkRenderer.h"
#include "vtkApplyColors.h"
#include "vtkUnstructuredGridGeometryFilter.h"
#include "igwRenderView.h"

#include <vtkInformation.h>
#include <vtkInformationVector.h>

vtkStandardNewMacro(igwRenderedSurfaceRepresentation)

void igwRenderedSurfaceRepresentation::PrintSelf(std::ostream &os, vtkIndent indent)
{

}

void igwRenderedSurfaceRepresentation::SetLookupTable(vtkScalarsToColors *val)
{
    this->Superclass::SetLookupTable(val);
    this->Mapper->SetLookupTable(val);

}

void igwRenderedSurfaceRepresentation::SetInputArrayToProcess(int idx, int port, int connection, int fieldAssociation, const char *name)
{
    this->Superclass::SetInputArrayToProcess(idx, port, connection, fieldAssociation, name);

    if (idx == 1)
    {
        return ;
    }

    this->Mapper->SetInputArrayToProcess(idx, port, connection, fieldAssociation, name);


    if(name && name[0])
    {
        this->Mapper->SetScalarVisibility(1);
        this->Mapper->SelectColorArray(name);
        this->Mapper->SetUseLookupTableScalarRange(1);

    }
    else
    {
        this->Mapper->SetScalarVisibility(0);
        this->Mapper->SelectColorArray(static_cast<const char*>(NULL));
    }

    switch (fieldAssociation)
    {
      case vtkDataObject::FIELD_ASSOCIATION_CELLS:
        this->Mapper->SetScalarMode(VTK_SCALAR_MODE_USE_CELL_FIELD_DATA);
        break;

      case vtkDataObject::FIELD_ASSOCIATION_POINTS:
      default:
        this->Mapper->SetScalarMode(VTK_SCALAR_MODE_USE_POINT_FIELD_DATA);
        break;
    }
}

void igwRenderedSurfaceRepresentation::SetPointColorArrayName(const char *arrayName)
{
    this->Superclass::SetPointColorArrayName(arrayName);
    this->Mapper->SetScalarModeToUsePointFieldData();
    this->Mapper->SelectColorArray(arrayName);
}

igwRenderedSurfaceRepresentation::igwRenderedSurfaceRepresentation()
{
    this->Mapper = vtkPolyDataMapper::New();
    this->ApplyColors = vtkApplyColors::New();
    this->GeometryFilter = vtkGeometryFilter::New();
//    this->GeometryFilter->SetUseOutline(0);
    this->CompositeDataGeometryFilter = vtkCompositeDataGeometryFilter::New();
    this->ExtractSurface = vtkDataSetSurfaceFilter::New();


//    this->Mapper->SetInputConnection(this->GeometryFilter->GetOutputPort());
    this->Actor->SetMapper(this->Mapper);


    this->PointColorArrayNameInternal = nullptr;
//    this->SetOpacity(0.3);
}

igwRenderedSurfaceRepresentation::~igwRenderedSurfaceRepresentation()
{
    this->Mapper->Delete();
    this->GeometryFilter->Delete();
    this->CompositeDataGeometryFilter->Delete();
    this->ExtractSurface->Delete();
}

int igwRenderedSurfaceRepresentation::RequestData(vtkInformation *request, vtkInformationVector **inputVector, vtkInformationVector *outputVector)
{

    vtkInformation* inInfo = inputVector[0]->GetInformationObject(0);
    vtkDataSet* data = vtkDataSet::SafeDownCast(inInfo->Get(vtkDataObject::DATA_OBJECT()));
    if(data != nullptr)
    {
        this->GeometryFilter->SetInputConnection(this->GetInternalOutputPort());
        this->Mapper->SetInputConnection(this->GeometryFilter->GetOutputPort());
    }
    else
    {
        this->CompositeDataGeometryFilter->SetInputConnection(this->GetInternalOutputPort());
        this->Mapper->SetInputConnection(this->CompositeDataGeometryFilter->GetOutputPort());
    }
//    this->SetOpacity(0.5);



//    this->ExtractSurface->SetInputConnection(this->GetInternalOutputPort());

    return this->Superclass::RequestData(request, inputVector, outputVector);
}

bool igwRenderedSurfaceRepresentation::AddToView(vtkView *view)
{
    igwRenderView* rv = igwRenderView::SafeDownCast(view);
      if (!rv)
      {
        vtkErrorMacro("Can only add to a subclass of igwRenderView.");
        return false;
      }
      rv->GetRenderer()->AddActor(this->Actor);
      this->Superclass::AddToView(view);
      return true;
}

bool igwRenderedSurfaceRepresentation::RemoveFromView(vtkView *view)
{
    igwRenderView* rv = igwRenderView::SafeDownCast(view);
     if (rv)
     {
       rv->GetRenderer()->RemoveActor(this->Actor);
       return this->Superclass::RemoveFromView(view);
     }

     return false;
}

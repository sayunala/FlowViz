#include "igwIsoSurfaceRepresentation.h"
#include "vtkSmartPointer.h"
#include "vtkNew.h"
#include "vtkObjectFactory.h"
#include "vtkTransformFilter.h"
#include "vtkContourFilter.h"
#include "vtkView.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkApplyColors.h"
#include "vtkActor.h"

#include "igwRenderView.h"
#include "vtkRenderer.h"
#include "vtkPolyData.h"
#include "vtkArrayCalculator.h"
#include "vtkRenderedRepresentation.h"
#include "igwRenderView.h"
#include "ColorMap/igwColorMapManager.h"

#include "igwRenderRepObserver.h"

#include <vtkPointData.h>

vtkStandardNewMacro(igwIsoSurfaceRepresentation);

igwIsoSurfaceRepresentation::igwIsoSurfaceRepresentation()
{
    this->TransformFilter = vtkTransformFilter::New();
    this->ApplyColors = vtkApplyColors::New();// 待定

    this->Mapper = vtkPolyDataMapper::New();
    this->ContourFilter = vtkContourFilter::New();
    this->NumberOfContours = 10;

    this->Actor->SetMapper(Mapper);
    this->Mapper->SetInputConnection(ContourFilter->GetOutputPort());
    this->ColorArrayName = nullptr;
    ArrayCalculator = vtkSmartPointer<vtkArrayCalculator>::New();
}

igwIsoSurfaceRepresentation::~igwIsoSurfaceRepresentation()
{
    this->TransformFilter->Delete();
    this->ApplyColors->Delete();
    this->ContourFilter->Delete();
    this->Mapper->Delete();
    this->ColorArrayName = nullptr;
}

void igwIsoSurfaceRepresentation::PrintSelf(std::ostream &os, vtkIndent indent)
{
    this->Superclass::PrintSelf(os, indent);
}

void igwIsoSurfaceRepresentation::SetValue(int i, double value)
{
    this->ContourFilter->SetValue(i, value);


}

void igwIsoSurfaceRepresentation::SetPointColorArrayName(const char *arrayName)
{
    this->Superclass::SetPointColorArrayName(arrayName);
    this->Mapper->SetScalarModeToUsePointFieldData();
    this->Mapper->SelectColorArray(arrayName);

    this->ContourFilter->SetInputArrayToProcess(
                0, 0, 0, vtkDataObject::FIELD_ASSOCIATION_POINTS, arrayName);

}

void igwIsoSurfaceRepresentation::SetLookupTable(vtkScalarsToColors *val)
{
    this->Mapper->SetLookupTable(val);
}

void igwIsoSurfaceRepresentation::SetNumberOfContoursApi(int num)
{
    this->SetNumberOfContours(num);
    this->ContourFilter->SetNumberOfContours(num);
}

double *igwIsoSurfaceRepresentation::GetValues()
{
    return this->ContourFilter->GetValues();
}

double igwIsoSurfaceRepresentation::GetValue(int idx)
{
    return this->ContourFilter->GetValue(idx);
}

void igwIsoSurfaceRepresentation::GenerateValues(int numberOfContours, double range[])
{
    this->NumberOfContours = numberOfContours;
    this->ContourFilter->GenerateValues(numberOfContours, range);
}

void igwIsoSurfaceRepresentation::SetInputArrayToProcess(int idx, int port, int connection, int fieldAssociation, const char *name)
{


    if (idx == 1)
    {
        return ;
    }
    vtkPointData* pointData =  this->DataSet->GetPointData();
    vtkDataArray* array =  pointData->GetArray(name);
    int numberOfComponents = array->GetNumberOfComponents();
    int i = 0;
//    while(numberOfComponents != 1 && i < pointData->GetNumberOfArrays())
//    {
//        array = pointData->GetArray(i);
//        name = array->GetName();
//        ++i;
//    }
    if(numberOfComponents != 1)
    {

    }


    this->Superclass::SetInputArrayToProcess(idx, port, connection, fieldAssociation, name);
    this->Mapper->GetLookupTable()->SetRange(this->GetArrayRange(fieldAssociation, name));

    this->Mapper->SetInputArrayToProcess(idx, port, connection, fieldAssociation, name);

    this->ContourFilter->SetInputArrayToProcess(idx, port, connection, fieldAssociation, name);

    if(name && name[0])
    {
        this->Mapper->SetScalarVisibility(1);
        this->Mapper->SelectColorArray(name);
        this->Mapper->SetUseLookupTableScalarRange(1);
        this->ArrayCalculator->AddVectorArrayName("Velocity");
        this->ArrayCalculator->SetResultArrayName("Velocity");
        this->ArrayCalculator->SetFunction("mag(Velocity)");
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

void igwIsoSurfaceRepresentation::SetDataSet(vtkDataSet* dataSet)
{
    this->Superclass::SetDataSet(dataSet);
    this->ContourFilter->GenerateValues(NumberOfContours, dataSet->GetScalarRange());
}


int igwIsoSurfaceRepresentation::RequestData(vtkInformation *request, vtkInformationVector **inputVector, vtkInformationVector *outputVector)
{
    this->ContourFilter->SetInputConnection(0, this->GetInternalOutputPort());

    return this->Superclass::RequestData(request, inputVector, outputVector);
}

void igwIsoSurfaceRepresentation::PrepareForRendering(igwRenderView *view)
{
    this->Superclass::PrepareForRendering(view);

}

bool igwIsoSurfaceRepresentation::AddToView(vtkView *view)
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

bool igwIsoSurfaceRepresentation::RemoveFromView(vtkView *view)
{
    igwRenderView* rv = igwRenderView::SafeDownCast(view);
     if (rv)
     {
       rv->GetRenderer()->RemoveActor(this->Actor);
       return this->Superclass::RemoveFromView(view);
     }

     return false;
}

vtkSelection *igwIsoSurfaceRepresentation::ConvertSelection(vtkView *view, vtkSelection *selection)
{
    return nullptr;
}

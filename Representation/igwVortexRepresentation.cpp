#include "igwVortexRepresentation.h"
#include "vtkGradientFilter.h"
#include "vtkContourFilter.h"
#include "vtkActor.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderer.h"
#include "vtkProperty.h"
#include "vtkVortexCore.h"
#include "igwRenderView.h"

vtkStandardNewMacro(igwVortexRepresentation);

igwVortexRepresentation::igwVortexRepresentation()
{
    //this->GradientFilterArrayName = "velocity";
    QCriterion = 0.0;
    // Set the default QCriterionName;
    this->QCriterionArrayName = const_cast<char*>("QCriterion");
    this->VelocityArrayName = const_cast<char*>("velocity");

    this->GradientFilter = vtkGradientFilter::New();
    this->GradientFilter->SetComputeQCriterion(true);

    this->GradientFilter->SetQCriterionArrayName(QCriterionArrayName);
    this->GradientFilter->SetInputArrayToProcess(0,0,0,vtkDataObject::FIELD_ASSOCIATION_POINTS, VelocityArrayName);

    this->ContourFilter = vtkContourFilter::New();
    this->ContourFilter->SetInputConnection(this->GradientFilter->GetOutputPort());

    this->ContourFilter->SetInputArrayToProcess(0,0,0,vtkDataObject::FIELD_ASSOCIATION_POINTS,
                                                QCriterionArrayName);

    this->ContourFilter->SetValue(0, QCriterion);
    this->ContourFilter->ComputeScalarsOn();
    this->ContourFilter->ComputeNormalsOn();

    VortexCore = vtkVortexCore::New();
    this->Mapper = vtkPolyDataMapper::New();
    this->Actor->SetMapper(Mapper);
    this->SetOpacity(0.5);
    this->Mapper->SetInputConnection(this->ContourFilter->GetOutputPort());

}

igwVortexRepresentation::~igwVortexRepresentation()
{
    this->GradientFilter->Delete();
    this->ContourFilter->Delete();
    this->Mapper->Delete();
    this->VortexCore->Delete();
}
void igwVortexRepresentation::PrintSelf(std::ostream &os, vtkIndent indent)
{
//    this->TransformFilter->Delete();
//    this->ApplyColors->Delete();
    this->GradientFilter->Delete();
    this->ContourFilter->Delete();
    this->Mapper->Delete();
    this->Actor->Delete();
    QCriterion = 0.0;
    this->SetQCriterionArrayName(nullptr);
    this->SetVelocityArrayName(nullptr);

}

void igwVortexRepresentation::SetPointVelocityArrayName(const char *arrayName)
{
    this->SetVelocityArrayName(arrayName);
    this->GradientFilter->SetInputArrayToProcess(0,0,0,vtkDataObject::FIELD_ASSOCIATION_POINTS, VelocityArrayName);
}

void igwVortexRepresentation::SetPointQCriterionArrayName(const char *arrayName)
{
    this->SetQCriterionArrayName(arrayName);
    this->GradientFilter->SetQCriterionArrayName(arrayName);
    this->ContourFilter->SetInputArrayToProcess(0, 0, 0, vtkDataObject::FIELD_ASSOCIATION_POINTS, QCriterionArrayName);
}

void igwVortexRepresentation::SetQCriterionValue(double value)
{
    this->SetQCriterion(value);
    this->ContourFilter->SetValue(0, this->QCriterion);
}

void igwVortexRepresentation::SetLookupTable(vtkScalarsToColors *val)
{
    this->Mapper->SetLookupTable(val);
}

void igwVortexRepresentation::SetInputArrayToProcess(int idx, int port, int connection, int fieldAssociation, const char *name)
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
        this->VortexCore->SetInputArrayToProcess(idx, port, connection, fieldAssociation, name);
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

void igwVortexRepresentation::SetPointColorArrayName(const char *arrayName)
{
    this->Superclass::SetPointColorArrayName(arrayName);
    this->Mapper->SetScalarModeToUsePointFieldData();
    this->Mapper->SelectColorArray(arrayName);
}

int igwVortexRepresentation::RequestData(vtkInformation *request, vtkInformationVector **inputVector, vtkInformationVector *outputVector)
{
    this->GradientFilter->SetInputConnection(0, this->GetInternalOutputPort());
//this->VortexCore->SetInputConnection(0, this->GetInternalOutputPort());
//    this->GradientFilter->SetInputArrayToProcess(0,0,0,vtkDataObject::FIELD_ASSOCIATION_POINTS, VelocityArrayName);
//    this->GradientFilter->SetQCriterionArrayName(QCriterionArrayName);
//    this->GradientFilter->SetInputArrayToProcess(0,0,0,vtkDataObject::FIELD_ASSOCIATION_POINTS, VelocityArrayName);
//    this->ContourFilter->SetInputArrayToProcess(0,0,0,vtkDataObject::FIELD_ASSOCIATION_POINTS,
//                                                QCriterionArrayName);

    return this->Superclass::RequestData(request, inputVector, outputVector);
}

void igwVortexRepresentation::PrepareForRendering(igwRenderView *view)
{
    this->Superclass::PrepareForRendering(view);
}

bool igwVortexRepresentation::AddToView(vtkView *view)
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

bool igwVortexRepresentation::RemoveFromView(vtkView *view)
{
     igwRenderView* rv = igwRenderView::SafeDownCast(view);
     if (rv)
     {
       rv->GetRenderer()->RemoveActor(this->Actor);
       return this->Superclass::RemoveFromView(view);
     }

     return false;
}

vtkSelection *igwVortexRepresentation::ConvertSelection(vtkView *view, vtkSelection *selection)
{
    return nullptr;
}

#include "igwVolumeRepresentation.h"
#include "vtkSmartPointer.h"
#include "vtkNew.h"
#include "vtkObjectFactory.h"
#include "vtkTransformFilter.h"

#include "vtkView.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkApplyColors.h"
#include "vtkActor.h"

#include "vtkLODProp3D.h"
#include "vtkGPUVolumeRayCastMapper.h"
#include "vtkVolumeProperty.h"
#include "vtkResampleToImage.h"
#include "vtkArrayCalculator.h"

#include "igwRenderView.h"
#include "vtkRenderer.h"
#include "vtkPolyData.h"
#include "vtkRenderedRepresentation.h"
#include "igwRenderView.h"
#include "ColorMap/igwColorMapManager.h"
vtkStandardNewMacro(igwVolumeRepresentation);
void igwVolumeRepresentation::PrintSelf(std::ostream &os, vtkIndent indent)
{
    this->Superclass::PrintSelf(os, indent);
}

void igwVolumeRepresentation::SetPointColorArrayName(const char *arrayName)
{
    this->Superclass::SetPointColorArrayName(arrayName);

}

void igwVolumeRepresentation::SetLookupTable(vtkScalarsToColors *val)
{
    this->VolumeProperty->SetColor(vtkColorTransferFunction::SafeDownCast(val));
    this->Mapper->SetLookupTable(val);
}

void igwVolumeRepresentation::SetInputArrayToProcess(int idx, int port, int connection, int fieldAssociation, const char *name)
{
    this->Superclass::SetInputArrayToProcess(idx, port, connection, fieldAssociation, name);

    if (idx == 1)
    {
        return ;
    }

    this->VolumeMapper->SetInputArrayToProcess(idx, port, connection, fieldAssociation, name);
    this->Mapper->SetInputArrayToProcess(idx, port, connection, fieldAssociation, name);
    if(name && name[0])
    {

        this->VolumeMapper->SelectScalarArray(name);
        this->ArrayCalculator->AddVectorArrayName("Velocity");
        this->ArrayCalculator->SetResultArrayName("Velocity");
        this->ArrayCalculator->SetFunction("mag(Velocity)");

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
        this->VolumeMapper->SetScalarMode(VTK_SCALAR_MODE_USE_CELL_FIELD_DATA);
        this->Mapper->SetScalarMode(VTK_SCALAR_MODE_USE_CELL_FIELD_DATA);
        break;

      case vtkDataObject::FIELD_ASSOCIATION_POINTS:
      default:
        this->VolumeMapper->SetScalarMode(VTK_SCALAR_MODE_USE_POINT_FIELD_DATA);
        this->Mapper->SetScalarMode(VTK_SCALAR_MODE_USE_POINT_FIELD_DATA);
        break;
    }
}

void igwVolumeRepresentation::SetDataSet(vtkDataSet* dataSet)
{
    this->Superclass::SetDataSet(dataSet);
    //this->ContourFilter->GenerateValues(NumberOfContours, dataSet->GetScalarRange());
}

void igwVolumeRepresentation::SetSamplingDimensions(int xdim, int ydim, int zdim)
{
    this->ResampleToImage->SetSamplingDimensions(xdim, ydim, zdim);
}

void igwVolumeRepresentation::SetOrientation(double x, double y, double z)
{
    this->LODProp3D->SetOrientation(x, y, z);
}

void igwVolumeRepresentation::SetPickable(int val)
{
    this->LODProp3D->SetPickable(val);
}

void igwVolumeRepresentation::SetScale(double x, double y, double z)
{
//    this->LODProp3D-SetScale(x, y , z);
}

void igwVolumeRepresentation::SetPosition(double x, double y, double z)
{
    this->LODProp3D->SetPosition(x, y , z);
}

void igwVolumeRepresentation::SetOrigin(double x, double y, double z)
{
    this->LODProp3D->SetOrigin(x, y, z);
}


void igwVolumeRepresentation::SetInterpolationType(int val)
{
    this->VolumeProperty->SetInterpolationType(val);
}

void igwVolumeRepresentation::SetScalarOpacity(vtkPiecewiseFunction *pwf)
{
    this->VolumeProperty->SetScalarOpacity(pwf);
}

void igwVolumeRepresentation::SetScalarOpacityUnitDistance(double val)
{
    this->VolumeProperty->SetScalarOpacityUnitDistance(val);
}

igwVolumeRepresentation::igwVolumeRepresentation()
{
    this->ApplyColors = vtkApplyColors::New();// 待定
    this->ColorArrayName = nullptr;
    Mapper = vtkPolyDataMapper::New();

    ArrayCalculator = vtkSmartPointer<vtkArrayCalculator>::New();

    // 重采样为ImageData
    this->ResampleToImage = vtkSmartPointer<vtkResampleToImage>::New();
    this->ResampleToImage->SetSamplingDimensions(128, 128, 128);
    this->Origin[0] = this->Origin[1] = this->Origin[2] = 0.0;
    this->Spacing[0] = this->Spacing[1] = this->Spacing[2] = 0.0;
    this->WholeExtent[0] = this->WholeExtent[2] = this->WholeExtent[4] = 0;
    this->WholeExtent[1] = this->WholeExtent[3] = this->WholeExtent[5] = -1;
    this->ResampleToImage->UseInputBoundsOn();

    this->VolumeMapper = vtkSmartPointer<vtkGPUVolumeRayCastMapper>::New();
    this->VolumeMapper->SetInputConnection(this->ResampleToImage->GetOutputPort());
    this->VolumeProperty = vtkSmartPointer<vtkVolumeProperty>::New();
    this->LODProp3D = vtkSmartPointer<vtkLODProp3D>::New();
    this->LODProp3D->AddLOD(this->VolumeMapper, this->VolumeProperty, 0);

}

igwVolumeRepresentation::~igwVolumeRepresentation()
{

    this->ColorArrayName = nullptr;
    this->Mapper->Delete();
}

int igwVolumeRepresentation::RequestData(vtkInformation *request, vtkInformationVector **inputVector, vtkInformationVector *outputVector)
{
    this->ArrayCalculator->SetInputConnection(this->GetInternalOutputPort());
    this->ArrayCalculator->Update();

    this->ResampleToImage->SetInputConnection(0, this->ArrayCalculator->GetOutputPort());
    return this->Superclass::RequestData(request, inputVector, outputVector);
}

void igwVolumeRepresentation::PrepareForRendering(igwRenderView *view)
{
    this->Superclass::PrepareForRendering(view);

}

bool igwVolumeRepresentation::AddToView(vtkView *view)
{
    igwRenderView* rv = igwRenderView::SafeDownCast(view);
      if (!rv)
      {
        vtkErrorMacro("Can only add to a subclass of igwRenderView.");
        return false;
      }
//      rv->GetRenderer()->AddActor(this->Actor);
      rv->GetRenderer()->AddVolume(this->LODProp3D);
      this->Superclass::AddToView(view);
      return true;
}

bool igwVolumeRepresentation::RemoveFromView(vtkView *view)
{
    igwRenderView* rv = igwRenderView::SafeDownCast(view);
     if (rv)
     {
//       rv->GetRenderer()->RemoveActor(this->Actor);
       rv->GetRenderer()->RemoveVolume(this->LODProp3D);
       return this->Superclass::RemoveFromView(view);
     }

     return false;
}

vtkSelection *igwVolumeRepresentation::ConvertSelection(vtkView *view, vtkSelection *selection)
{
    return nullptr;
}

#include "igwTextureRepresentation.h"

#include "vtkCompositeDataDisplayAttributes.h"
#include "vtkInformation.h"
#include "vtkInformationRequestKey.h"
#include "vtkObjectFactory.h"

#include "igwRenderView.h"
#include "vtkRenderer.h"

#include "vtkRenderedRepresentation.h"
#include "igwRenderView.h"

#include "vtkGeometryFilter.h"
#include "vtkCompositeSurfaceLICMapper.h"
#include "vtkSurfaceLICInterface.h"
#include "vtkActor.h"
#include "igwRenderRepObserver.h"
#include "ColorMap/igwColorMapManager.h"

vtkStandardNewMacro(igwTextureRepresentation)

igwTextureRepresentation::igwTextureRepresentation()
{
    this->GeometryFilter = vtkSmartPointer<vtkGeometryFilter>::New();

    this->SurfaceLICMapper = vtkSmartPointer<vtkCompositeSurfaceLICMapper>::New();

    this->SurfaceLICMapper->SetInputConnection(this->GeometryFilter->GetOutputPort());

    this->Actor->SetMapper(this->SurfaceLICMapper);

    // 初始化Observer

}

igwTextureRepresentation::~igwTextureRepresentation()
{

}

void igwTextureRepresentation::PrintSelf(ostream& os, vtkIndent indent)
{
    this->Superclass::PrintSelf(os, indent);
}

vtkSurfaceLICInterface *igwTextureRepresentation::GetLICInterface()
{
    return this->SurfaceLICMapper->GetLICInterface();
}
void igwTextureRepresentation::SetLookupTable(vtkScalarsToColors *val)
{
    this->SurfaceLICMapper->SetLookupTable(val);
}

void igwTextureRepresentation::SetInputArrayToProcess(int idx, int port, int connection, int fieldAssociation, const char *name)
{
    this->Superclass::SetInputArrayToProcess(idx, port, connection, fieldAssociation, name);

    if (idx == 1)
    {
        return ;
    }

    this->SurfaceLICMapper->GetLookupTable()->SetRange(this->GetArrayRange(fieldAssociation, name));

    this->SurfaceLICMapper->SetInputArrayToProcess(idx, port, connection, fieldAssociation, name);

    //this->ContourFilter->SetInputArrayToProcess(idx, port, connection, fieldAssociation, name);

    if(name && name[0])
    {
        this->SurfaceLICMapper->SetScalarVisibility(1);
        this->SurfaceLICMapper->SelectColorArray(name);
        this->SurfaceLICMapper->SetUseLookupTableScalarRange(1);

    }
    else
    {
        this->SurfaceLICMapper->SetScalarVisibility(0);
        this->SurfaceLICMapper->SelectColorArray(static_cast<const char*>(NULL));
    }

    switch (fieldAssociation)
    {
      case vtkDataObject::FIELD_ASSOCIATION_CELLS:
        this->SurfaceLICMapper->SetScalarMode(VTK_SCALAR_MODE_USE_CELL_FIELD_DATA);
        break;

      case vtkDataObject::FIELD_ASSOCIATION_POINTS:
      default:
        this->SurfaceLICMapper->SetScalarMode(VTK_SCALAR_MODE_USE_POINT_FIELD_DATA);
        break;
    }
}

void igwTextureRepresentation::SetDataSet(vtkDataSet* dataSet)
{
    this->Superclass::SetDataSet(dataSet);
    //    this->ContourFilter->GenerateValues(NumberOfContours, dataSet->GetScalarRange());
}


#define igwTextureRepresentationPassParameterWithLODMacro(_name, _type)                           \
  void igwTextureRepresentation::Set##_name(_type val)                                            \
  {                                                                                               \
    this->SurfaceLICMapper->GetLICInterface()->Set##_name(val);                                   \
                                                                                                  \
  }

#if !defined(igwTextureRepresentationFASTLOD)
  igwTextureRepresentationPassParameterWithLODMacro(
    StepSize, double) igwTextureRepresentationPassParameterWithLODMacro(NumberOfSteps,
    int) igwTextureRepresentationPassParameterWithLODMacro(EnhancedLIC,
    int) igwTextureRepresentationPassParameterWithLODMacro(EnhanceContrast,
    int) igwTextureRepresentationPassParameterWithLODMacro(LowLICContrastEnhancementFactor,
    double) igwTextureRepresentationPassParameterWithLODMacro(HighLICContrastEnhancementFactor,
    double) igwTextureRepresentationPassParameterWithLODMacro(LowColorContrastEnhancementFactor,
    double) igwTextureRepresentationPassParameterWithLODMacro(HighColorContrastEnhancementFactor,
    double) igwTextureRepresentationPassParameterWithLODMacro(AntiAlias, int)
#endif
    igwTextureRepresentationPassParameterWithLODMacro(
      NormalizeVectors, int) igwTextureRepresentationPassParameterWithLODMacro(ColorMode,
      int) igwTextureRepresentationPassParameterWithLODMacro(MapModeBias, double)
      igwTextureRepresentationPassParameterWithLODMacro(LICIntensity, double)
        igwTextureRepresentationPassParameterWithLODMacro(MaskOnSurface, int)
          igwTextureRepresentationPassParameterWithLODMacro(MaskThreshold, double)
            igwTextureRepresentationPassParameterWithLODMacro(MaskColor, double*)
              igwTextureRepresentationPassParameterWithLODMacro(MaskIntensity, double)
                igwTextureRepresentationPassParameterWithLODMacro(GenerateNoiseTexture, int)
                  igwTextureRepresentationPassParameterWithLODMacro(NoiseType, int)
                    igwTextureRepresentationPassParameterWithLODMacro(NoiseTextureSize, int)
                      igwTextureRepresentationPassParameterWithLODMacro(MinNoiseValue, double)
                        igwTextureRepresentationPassParameterWithLODMacro(MaxNoiseValue, double)
                          igwTextureRepresentationPassParameterWithLODMacro(NoiseGrainSize, int)
                            igwTextureRepresentationPassParameterWithLODMacro(
                              NumberOfNoiseLevels, int)
                              igwTextureRepresentationPassParameterWithLODMacro(
                                ImpulseNoiseProbability, double)
                                igwTextureRepresentationPassParameterWithLODMacro(
                                  ImpulseNoiseBackgroundValue, double)
                                  igwTextureRepresentationPassParameterWithLODMacro(
                                    NoiseGeneratorSeed, int)
                                    igwTextureRepresentationPassParameterWithLODMacro(
                                      CompositeStrategy, int)

int igwTextureRepresentation::RequestData(vtkInformation *request, vtkInformationVector **inputVector, vtkInformationVector *outputVector)
{
  this->GeometryFilter->SetInputConnection(0, this->GetInternalOutputPort());

  return this->Superclass::RequestData(request, inputVector, outputVector);
}

void igwTextureRepresentation::PrepareForRendering(igwRenderView *view)
{
  this->Superclass::PrepareForRendering(view);

}

bool igwTextureRepresentation::AddToView(vtkView *view)
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

bool igwTextureRepresentation::RemoveFromView(vtkView *view)
{
  igwRenderView* rv = igwRenderView::SafeDownCast(view);
   if (rv)
   {
     rv->GetRenderer()->RemoveActor(this->Actor);
     return this->Superclass::RemoveFromView(view);
   }

   return false;
}


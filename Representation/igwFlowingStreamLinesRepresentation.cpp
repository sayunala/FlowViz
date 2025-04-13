#include "igwFlowingStreamLinesRepresentation.h"
#include "vtkObjectFactory.h"
#include "vtkProperty.h"
#include "vtkActor.h"
#include "vtkStreamLinesMapper.h"
#include "igwRenderView.h"
#include "vtkRenderer.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderWindow.h"
#include "igwRenderRepObserver.h"
#include "ColorMap/igwColorMapManager.h"
class igwFlowingStreamLinesRepresentation::igwFlowingStreamLinesObserver : public vtkCommand
{
public:

  static igwFlowingStreamLinesObserver* New()
  {
    return new igwFlowingStreamLinesObserver;
  }

  void Execute(vtkObject* caller, unsigned long eventId,
               void* vtkNotUsed(callData)) override
  {
      vtkRenderWindowInteractor* iren =
          static_cast<vtkRenderWindowInteractor*>(caller);
      switch (eventId) {
      case vtkCommand::TimerEvent:
          iren->Render();

          break;
      case vtkCommand::KeyPressEvent:
          break;
      default:
          break;
      }
  }

};

vtkStandardNewMacro(igwFlowingStreamLinesRepresentation)
igwFlowingStreamLinesRepresentation::igwFlowingStreamLinesRepresentation()
{
    this->Mapper = vtkStreamLinesMapper::New();
    this->FlowingStreamLinesObserver = vtkSmartPointer<igwFlowingStreamLinesObserver>::New();

    InitParameters();
    this->Actor->SetMapper(this->Mapper);



}

igwFlowingStreamLinesRepresentation::~igwFlowingStreamLinesRepresentation()
{
    this->Mapper->Delete();
}

void igwFlowingStreamLinesRepresentation::SetAlpha(double val)
{
    this->Alpha = val;
    this->Mapper->SetAlpha(val);

}

void igwFlowingStreamLinesRepresentation::SetStepLength(double val)
{
    this->StepLength = val;
    this->Mapper->SetStepLength(val);
}

void igwFlowingStreamLinesRepresentation::SetNumberOfParticles(int val)
{
    this->NumberOfParticles = val;
    this->Mapper->SetNumberOfParticles(val);
}

void igwFlowingStreamLinesRepresentation::SetMaxTimeToLive(int val)
{
    this->MaxTimeToLive = val;
    this->Mapper->SetMaxTimeToLive(val);
}

void igwFlowingStreamLinesRepresentation::SetNumberOfAnimationSteps(int val)
{

    this->Mapper->SetNumberOfAnimationSteps(val);
}

void igwFlowingStreamLinesRepresentation::SetInputerVectors(
        int vtkNotUsed(idx), int port, int connection, int attributeMode, const char *name)
{
    this->Mapper->SetInputArrayToProcess(1, port, connection, attributeMode, name);
}

void igwFlowingStreamLinesRepresentation::SetInterpolateScalarsBeforeMapping(int val)
{
    this->Mapper->SetInterpolateScalarsBeforeMapping(val);
}
void igwFlowingStreamLinesRepresentation::SetAnimate(bool val)
{

    this->Mapper->SetAnimate(val);
}

void igwFlowingStreamLinesRepresentation::SetLookupTable(vtkScalarsToColors *val)
{
    this->Superclass::SetLookupTable(val);
    this->Mapper->SetLookupTable(val);
}

void igwFlowingStreamLinesRepresentation::SetPointColorArrayName(const char *arrayName)
{
//    this->Mapper->SetScalarVisibility(1);
    this->Superclass::SetPointColorArrayName(arrayName);
    this->Mapper->SetScalarModeToUsePointFieldData();
    this->Mapper->SelectColorArray(arrayName);
    this->Mapper->SetUseLookupTableScalarRange(1);
}

void igwFlowingStreamLinesRepresentation::SetInputArrayToProcess(int idx, int port, int connection, int fieldAssociation, const char *name)
{
    this->Superclass::SetInputArrayToProcess(idx, port, connection, fieldAssociation, name);

    if (idx == 1)
    {
        return ;
    }

    this->Mapper->GetLookupTable()->SetRange(this->GetArrayRange(fieldAssociation ,name));
    this->Mapper->SetInputArrayToProcess(0, port, connection, fieldAssociation, name);
    this->Mapper->SetInputArrayToProcess(1, port, connection, fieldAssociation, name);

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


int igwFlowingStreamLinesRepresentation::RequestData(vtkInformation *request, vtkInformationVector **inputVector, vtkInformationVector *outputVector)
{

    this->Mapper->SetInputConnection(this->GetInternalOutputPort());
    return this->Superclass::RequestData(request, inputVector, outputVector);
}

void igwFlowingStreamLinesRepresentation::PrepareForRendering(igwRenderView *view)
{

    this->Superclass::PrepareForRendering(view);
}

bool igwFlowingStreamLinesRepresentation::AddToView(vtkView *view)
{
    igwRenderView* rv = igwRenderView::SafeDownCast(view);
    if (!rv)
    {
        vtkErrorMacro("Can only add to a subclass of igwRenderView.");
        return false;
    }
    rv->GetRenderer()->AddActor(this->Actor);
    this->Superclass::AddToView(view);
    vtkRenderWindowInteractor* interactor = rv->GetInteractor();
    interactor->AddObserver(vtkCommand::TimerEvent, this->FlowingStreamLinesObserver);
    interactor->CreateRepeatingTimer(1000 / 60);

    return true;
}

bool igwFlowingStreamLinesRepresentation::RemoveFromView(vtkView *view)
{
    igwRenderView* rv = igwRenderView::SafeDownCast(view);
     if (rv)
     {
       rv->GetRenderer()->RemoveActor(this->Actor);
       return this->Superclass::RemoveFromView(view);
     }

     return false;
}

void igwFlowingStreamLinesRepresentation::InitParameters()
{
    Alpha = 0.1;
    StepLength = 0.05;
    MaxTimeToLive = 600;
    NumberOfParticles = 100;

    this->SetAlpha(this->Alpha);
    this->SetStepLength(this->StepLength);
    this->SetMaxTimeToLive(this->MaxTimeToLive);
    this->SetNumberOfParticles(this->NumberOfParticles);
}


void igwFlowingStreamLinesRepresentation::PrintSelf(std::ostream &os, vtkIndent indent)
{

}

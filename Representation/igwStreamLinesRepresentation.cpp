#include "igwStreamLinesRepresentation.h"

#include "vtkObjectFactory.h"
#include "vtkActor.h"
#include "vtkPolyDataMapper.h"
#include "vtkStreamTracer.h"
#include "vtkStreamSurface.h"
#include "vtkCallbackCommand.h"
#include "vtkLineWidget.h"
#include "vtkPlaneWidget.h"
#include "vtkPlaneSource.h"
#include "vtkRenderWindow.h"
#include "vtkRibbonFilter.h"
#include "igwRenderView.h"
#include "vtkRenderer.h"
#include "vtkPolyData.h"
#include "vtkPlane.h"
#include "vtkScalarBarActor.h"
#include "vtkProperty.h"
#include "vtkTubeFilter.h"
#include "ColorMap/igwColorMapManager.h"
class igwStreamLinesRepresentation::EnableActorCallback: public vtkCallbackCommand
{
public:
    static EnableActorCallback* New()
    {
      return new EnableActorCallback;
    }
    void Execute(vtkObject* /*caller*/, unsigned long, void*) override
    {
      this->actor->VisibilityOn();
    }
    EnableActorCallback() : actor(nullptr)
    {
    }
    vtkActor* actor;
};

class igwStreamLinesRepresentation::LWCallback : public vtkCallbackCommand
{
public:
    static LWCallback* New()
    {
      return new LWCallback;
    }
    void Execute(vtkObject* caller, unsigned long, void*) override
    {
        std::cout << "linemove" << std::endl;
      vtkLineWidget* lineWidget = reinterpret_cast<vtkLineWidget*>(caller);
      lineWidget->GetPolyData(this->polyData);
      this->renWin->Render();
    }
    LWCallback() : polyData(nullptr), renWin(nullptr)
    {
    }
    vtkPolyData* polyData;
    vtkRenderWindow* renWin;
};
/**
 * @brief The igwStreamLinesRepresentation::PWCallback class:
 */
class igwStreamLinesRepresentation::PWCallback : public vtkCallbackCommand
{
public:
    static PWCallback* New()
    {
      return new PWCallback;
    }
    void Execute(vtkObject* caller, unsigned long, void*) override
    {
      vtkPlaneWidget* planeWidget = reinterpret_cast<vtkPlaneWidget*>(caller);
      planeWidget->GetPolyData(this->polyData);
      this->renWin->Render();
    }
    PWCallback() : polyData(nullptr), renWin(nullptr)
    {
    }
    vtkPolyData* polyData;
    vtkRenderWindow* renWin;
};

vtkStandardNewMacro(igwStreamLinesRepresentation)
igwStreamLinesRepresentation::igwStreamLinesRepresentation()
{

    this->Mapper = vtkPolyDataMapper::New();
    //this->StreamTracer = vtkStreamSurface::New();
    //this->StreamSurface = vtkStreamSurface::New();

    this->Actor->SetMapper(this->Mapper);
    this->Actor->GetProperty()->SetOpacity(0.5);
//     this->Property->SetRepresentationToWireframe();
    this->LineWidget = vtkLineWidget::New();
    this->LineVisibility = true;
    this->PlaneWidget = vtkPlaneWidget::New();
    this->PlaneVisibility = true;

    this->Seeds = vtkPolyData::New();

    InitStreamTracer();

    InitCallback();

    InitStreamTube();
    InitStreamRibbon();
    InitStreamSurface();
    this->Mapper->SetInputConnection(this->StreamTracer->GetOutputPort());
}

igwStreamLinesRepresentation::~igwStreamLinesRepresentation()
{
    this->StreamTracer->Delete();
    //this->StreamSurface->Delete();
    this->Mapper->Delete();
    this->Seeds->Delete();
//    this->LineWidget->Delete();

}
void igwStreamLinesRepresentation::PrintSelf(std::ostream &os, vtkIndent indent)
{

}

void igwStreamLinesRepresentation::SetSourceConnection(vtkAlgorithmOutput* algOutput)
{
    this->StreamTracer->SetSourceConnection(algOutput);
}

void igwStreamLinesRepresentation::SetSourceData(vtkDataSet *source)
{
    this->StreamTracer->SetSourceData(source);
}

void igwStreamLinesRepresentation::SetResolutionToUpdate(int resolution)
{
    this->SetResolution(resolution);
    switch (SeedWidgetType) {
    case USE_LINE_WIDGET:
        this->LineWidget->SetResolution(resolution);
        break;
    case USE_PLANE_WIDGET:
        this->PlaneWidget->SetResolution(resolution);
    default:
        break;
    }
    this->StreamTracer->Update();
}

void igwStreamLinesRepresentation::SetStreamLineType(StreamLinesType type)
{
    this->Type = type;
    switch (type) {
    case STREAM_LINE:
        this->Mapper->SetInputConnection(this->StreamTracer->GetOutputPort());
        break;

    case STREAM_TUBE:
        this->Mapper->SetInputConnection(this->TubeFilter->GetOutputPort());
        break;

    case STREAM_RIBBON:
        this->Mapper->SetInputConnection(this->RibbonFilter->GetOutputPort());
        break;

    case STREAM_SURFACE:
        this->Mapper->SetInputConnection(this->StreamSurface->GetOutputPort());
        break;
    default:
        break;
    }

}

void igwStreamLinesRepresentation::SetStreamLineDirection(int d)
{
    this->Direction = d;
    this->StreamTracer->SetIntegrationDirection(d);
    this->StreamSurface->SetIntegrationDirection(d);
}

void igwStreamLinesRepresentation::SetWidth(double w)
{
    this->SetStreamLineWidth(w);
    this->RibbonFilter->SetWidth(w);
    this->TubeFilter->SetRadius(w);

}

void igwStreamLinesRepresentation::SetLength(int l)
{
    this->SetMaxPropagation(l);
    this->StreamTracer->SetMaximumPropagation(l);
//    this->StreamTracer->Update();
//    this->StreamSurface->Update();
}

void igwStreamLinesRepresentation::SetLineSeedResolution(int r)
{
    // 更新种子点数量
    this->SetResolution(r);
    this->LineWidget->SetResolution(r);
//    this->LineWidget->PlaceWidget();
    this->LineWidget->GetPolyData(this->Seeds);
}

void igwStreamLinesRepresentation::SetPlaneSeedXResolution(int x)
{
    this->SetNumberOfXResolution(x);
    vtkPlaneSource* planeSource = vtkPlaneSource::SafeDownCast(this->PlaneWidget->GetPolyDataAlgorithm());
    planeSource->SetXResolution(NumberOfXResolution);

//    this->PlaneWidget->PlaceWidget();
    this->PlaneWidget->GetPolyData(this->Seeds);


}

void igwStreamLinesRepresentation::SetPlaneSeedYResolution(int y)
{
    this->SetNumberOfYResolution(y);
    vtkPlaneSource* planeSource = vtkPlaneSource::SafeDownCast(this->PlaneWidget->GetPolyDataAlgorithm());
    planeSource->SetYResolution(NumberOfYResolution);

//    this->PlaneWidget->PlaceWidget();
    this->PlaneWidget->GetPolyData(this->Seeds);

}

void igwStreamLinesRepresentation::GenerateEntropySeeds()
{
    float interval = 0.5;
    int k = 20;
    std::vector<float> vecEntropyVect;


}

void igwStreamLinesRepresentation::LineWidgetOn()
{
    this->LineWidget->On();
}

void igwStreamLinesRepresentation::LineWidgetOff()
{
    this->LineWidget->Off();
}

vtkLineWidget *igwStreamLinesRepresentation::GetLineWidget()
{
    return this->LineWidget;
}

void igwStreamLinesRepresentation::PlaneWidgetOn()
{
    this->PlaneWidget->On();
}

void igwStreamLinesRepresentation::PlaneWidgetOff()
{
    this->PlaneWidget->Off();
}

vtkPlaneWidget *igwStreamLinesRepresentation::GetPlaneWidget()
{
    return this->PlaneWidget;
}

vtkPlane* igwStreamLinesRepresentation::GetPlane()
{
    vtkPlane* plane = vtkPlane::New();

    //    this->PlaneWidget->GetNormal();
    this->PlaneWidget->GetPlane(plane);
    return plane;
}

void igwStreamLinesRepresentation::SetPlaneNormalToXAxis()
{
    this->PlaneWidget->SetNormalToXAxis(1);
    this->PlaneWidget->SetNormal(1, 0, 0);
}

void igwStreamLinesRepresentation::SetPlaneNormalToYAxis()
{

    this->PlaneWidget->SetNormal(0, 1, 0);
}

void igwStreamLinesRepresentation::SetPlaneNormalToZAxis()
{
    this->PlaneWidget->SetNormalToZAxis(1);
    this->PlaneWidget->SetNormal(0, 0, 1);
}

void igwStreamLinesRepresentation::SetPlaneNormal(double x, double y, double z)
{
    this->PlaneWidget->SetNormal(x, y, z);
}

void igwStreamLinesRepresentation::SetPlaneNormal(double normal[])
{
    this->PlaneWidget->SetNormal(normal);
}

double *igwStreamLinesRepresentation::GetPlaneNormal()
{
    return this->PlaneWidget->GetNormal();
}

void igwStreamLinesRepresentation::SetPlaneOrigin(double x, double y, double z)
{
    this->PlaneWidget->SetOrigin(x, y, z);
}

void igwStreamLinesRepresentation::SetPlaneOrigin(double origin[])
{
    this->PlaneWidget->SetOrigin(origin);
}

double *igwStreamLinesRepresentation::GetPlaneOrigin()
{
    return this->PlaneWidget->GetOrigin();
}

void igwStreamLinesRepresentation::SetSeedType(SeedWidget type)
{
    this->SeedWidgetType = type;
    switch (this->SeedWidgetType) {
    case USE_LINE_WIDGET:
        this->LineWidgetOn();
        this->LineWidget->GetPolyData(this->Seeds);
        this->PlaneWidgetOff();
        break;
    case USE_PLANE_WIDGET:
        this->PlaneWidgetOn();
        this->PlaneWidget->GetPolyData(this->Seeds);
        this->LineWidgetOff();

    default:
        break;
    }
}

int igwStreamLinesRepresentation::GetSeedType()
{
    switch (this->SeedWidgetType) {
    case USE_LINE_WIDGET:
        return 1;

    case USE_PLANE_WIDGET:
        return 0;
    default:
        break;
    }
}

void igwStreamLinesRepresentation::UpdateSeed()
{
    switch (this->SeedWidgetType) {
    case USE_LINE_WIDGET:
        this->LineWidget->InvokeEvent(vtkCommand::EndInteractionEvent);
        this->LineWidget->InvokeEvent(vtkCommand::EndInteractionEvent);
        break;
    case USE_PLANE_WIDGET:
        this->PlaneWidget->InvokeEvent(vtkCommand::EndInteractionEvent);
        this->PlaneWidget->InvokeEvent(vtkCommand::EndInteractionEvent);
    default:
        break;
    }
//    this->StreamTracer->Update();
//    this->StreamSurface->Update();

}

void igwStreamLinesRepresentation::SetPointColorArrayName(const char *arrayName)
{
    this->Superclass::SetPointColorArrayName(arrayName);
    this->Mapper->SetScalarModeToUsePointFieldData();
    this->Mapper->SelectColorArray(arrayName);

}


int igwStreamLinesRepresentation::RequestData(vtkInformation *request, vtkInformationVector **inputVector, vtkInformationVector *outputVector)
{

    this->StreamTracer->SetInputConnection(this->GetInternalOutputPort());
    this->StreamTracer->SetSourceData(this->Seeds);
    this->StreamSurface->SetInputConnection(this->GetInternalOutputPort());
    this->StreamSurface->SetSourceData(this->Seeds);
    this->Mapper->SetInputConnection(this->StreamTracer->GetOutputPort());

    this->ConstructLineWidget();
    this->ConstructPlaneWidget();


    this->LineWidget->SetInputConnection(this->GetInternalOutputPort());
    this->PlaneWidget->SetInputConnection(this->GetInternalOutputPort());
//    this->SetStreamLineType(this->Type);

    return this->Superclass::RequestData(request, inputVector, outputVector);
}

void igwStreamLinesRepresentation::PrepareForRendering(igwRenderView *view)
{
    this->Superclass::PrepareForRendering(view);
}

bool igwStreamLinesRepresentation::AddToView(vtkView *view)
{
    igwRenderView* rv = igwRenderView::SafeDownCast(view);
    if (!rv)
    {
        vtkErrorMacro("Can only add to a subclass of igwRenderView.");
        return false;
    }
    rv->GetRenderer()->AddActor(this->Actor);
    this->Superclass::AddToView(view);
    this->LineWidget->SetInteractor(rv->GetInteractor());
    this->PlaneWidget->SetInteractor(rv->GetInteractor());
    switch (this->SeedWidgetType) {
    case USE_LINE_WIDGET:

        this->LineWidgetOn();
        break;
    case USE_PLANE_WIDGET:

        this->PlaneWidgetOn();
    default:
        break;
    }



    this->GenerateStreamLines->renWin = rv->GetRenderWindow();
    this->PlaneWidgetCallback->renWin = rv->GetRenderWindow();

    return true;
}

bool igwStreamLinesRepresentation::RemoveFromView(vtkView *view)
{
    igwRenderView* rv = igwRenderView::SafeDownCast(view);
    if (rv)
    {
        rv->GetRenderer()->RemoveActor(this->Actor);
        return this->Superclass::RemoveFromView(view);
    }
    return false;
}

void igwStreamLinesRepresentation::SetLookupTable(vtkScalarsToColors *val)
{
    this->Mapper->SetLookupTable(val);
}

void igwStreamLinesRepresentation::SetInputArrayToProcess(int idx, int port, int connection, int fieldAssociation, const char *name)
{
    this->Superclass::SetInputArrayToProcess(idx, port, connection, fieldAssociation, name);

    if (idx == 1)
    {
        return ;
    }

//    this->Mapper->GetLookupTable()->SetRange(this->GetArrayRange(name));
    this->Mapper->SetInputArrayToProcess(idx, port, connection, fieldAssociation, name);
    this->StreamSurface->SetInputArrayToProcess(idx, port, connection, fieldAssociation, name);
    this->StreamTracer->SetInputArrayToProcess(idx, port, connection, fieldAssociation, name);
    this->TubeFilter->SetInputArrayToProcess(idx, port, connection, fieldAssociation, name);
    this->RibbonFilter->SetInputArrayToProcess(idx, port, connection, fieldAssociation, name);
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

int igwStreamLinesRepresentation::GetStreamLineType()
{
    switch (Type) {
    case STREAM_LINE:
        return 0;
        break;

    case STREAM_TUBE:
        return 1;
        break;

    case STREAM_RIBBON:
        return 2;

    case STREAM_SURFACE:
        return 3;
    }
}

void igwStreamLinesRepresentation::InitStreamTracer()
{
    InitParameters();
    this->StreamTracer = vtkStreamTracer::New();
    this->StreamTracer->SetMaximumPropagation(MaxPropagation);
    //设置 vtkStreamTracer参数
    this->StreamTracer->SetIntegratorTypeToRungeKutta4();
    this->StreamTracer->SetIntegrationDirectionToBoth();
    this->StreamTracer->SetMaximumIntegrationStep(MaxPropagation);
    this->StreamTracer->SetInitialIntegrationStep(InitStep);
    this->StreamTracer->SetMinimumIntegrationStep(MinStep);
    this->StreamTracer->SetMaximumIntegrationStep(MaxStep);



}

void igwStreamLinesRepresentation::InitStreamTube()
{
    this->TubeFilter = vtkSmartPointer<vtkTubeFilter>::New();
    this->TubeFilter->SetInputConnection(this->StreamTracer->GetOutputPort());
//    this->TubeFilter->SetRadius(StreamLineWidth);
    this->TubeFilter->SetVaryRadiusToVaryRadiusByVector();

}

void igwStreamLinesRepresentation::InitStreamRibbon()
{
    this->RibbonFilter = vtkSmartPointer<vtkRibbonFilter>::New();
    this->RibbonFilter->SetInputConnection(this->StreamTracer->GetOutputPort());
    this->RibbonFilter->SetWidth(StreamLineWidth);
}

void igwStreamLinesRepresentation::InitStreamSurface()
{
    this->StreamSurface = vtkSmartPointer<vtkStreamSurface>::New();

    this->StreamSurface->SetMaximumPropagation(MaxPropagation);
    //设置 vtkStreamTracer参数
    this->StreamTracer->SetIntegratorTypeToRungeKutta4();
    this->StreamTracer->SetIntegrationDirectionToBoth();
    this->StreamTracer->SetMaximumPropagation(MaxPropagation);
    this->StreamTracer->SetInitialIntegrationStep(InitStep);
    this->StreamTracer->SetMinimumIntegrationStep(MinStep);
    this->StreamTracer->SetMaximumIntegrationStep(MaxStep);
}

void igwStreamLinesRepresentation::InitParameters()
{
    SeedWidgetType = USE_LINE_WIDGET;
    MaxPropagation = 10000;
    Resolution = 50;
    MaxStep = 10.0;
    MinStep = 0.01;
    InitStep = 0.5;

    // plane Resolution
    NumberOfXResolution = 5;
    NumberOfYResolution = 5;

    StreamLineWidth = 1;

    Direction = 2;// 插值方向 Both
    Type = STREAM_LINE;


}

void igwStreamLinesRepresentation::InitCallback()
{
    this->GenerateStreamLines = vtkSmartPointer<LWCallback>::New();
    this->GenerateStreamLines->polyData = this->Seeds;
    this->PlaneWidgetCallback = vtkSmartPointer<PWCallback>::New();
    this->PlaneWidgetCallback->polyData = this->Seeds;
//    this->PlaneWidget->GetPolyData(this->Seeds);
    this->PlaneWidget->AddObserver(vtkCommand::EndInteractionEvent, this->PlaneWidgetCallback);
    this->LineWidget->AddObserver(vtkCommand::EndInteractionEvent, this->GenerateStreamLines);
}

void igwStreamLinesRepresentation::ConstructLineWidget()
{
    this->LineWidget->SetResolution(this->Resolution);
    this->LineWidget->ClampToBoundsOn();
    this->LineWidget->SetAlignToYAxis();
    double* bounds;
    this->DataSet->GetBounds(bounds);
//    this->LineWidget->PlaceWidget(bounds[0], bounds[1], bounds[2] / 20,
//            bounds[3] / 20, bounds[4], bounds[5]);
    if(!isLinePlaced)
    {
        this->LineWidget->PlaceWidget(this->DataSet->GetBounds());
        isLinePlaced = true;
    }

    if(this->SeedWidgetType == USE_LINE_WIDGET)
    {

        this->LineWidget->GetPolyData(this->Seeds);

    }
}

void igwStreamLinesRepresentation::ConstructPlaneWidget()
{

    vtkPlaneSource* planeSource = vtkPlaneSource::SafeDownCast(this->PlaneWidget->GetPolyDataAlgorithm());
    planeSource->SetXResolution(NumberOfXResolution);
    planeSource->SetYResolution(NumberOfYResolution);

    if(!isPlanePlaced)
    {
         this->PlaneWidget->PlaceWidget(this->DataSet->GetBounds());
        isPlanePlaced = true;
    }


    this->PlaneWidget->SetNormalToZAxis(true);
    this->PlaneWidget->SetHandleSize(0.1);
//    this->PlaneWidget->GetHandleProperty()->set;
    if (this->SeedWidgetType == USE_PLANE_WIDGET)
        this->PlaneWidget->GetPolyData(this->Seeds);
}

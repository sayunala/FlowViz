#include "igwCloudMapRepresentation.h"
#include "vtkObjectFactory.h"
#include "vtkActor.h"
#include "vtkPolyDataMapper.h"
#include "vtkPlane.h"
#include "vtkCutter.h"
#include "vtkCommand.h"
#include "vtkDataObject.h"
#include "vtkOutlineFilter.h"
#include "igwRenderView.h"
#include "vtkRenderer.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkImplicitPlaneWidget.h"
#include "vtkProperty.h"
#include "vtkApplyColors.h"
#include "vtkDataSetSurfaceFilter.h"
#include "vtkInformation.h"
//#include "igwRenderRepObserver.h"

#include <ColorMap/igwColorMapManager.h>

#include <vtkInformationVector.h>
class igwCloudMapRepresentation::igwCMCallback : public vtkCommand
{
public:
  static igwCMCallback* New()
  {
    return new igwCMCallback;
  }

  virtual void Execute(vtkObject* caller, unsigned long, void*)
  {
    vtkImplicitPlaneWidget* planeWidget =
        reinterpret_cast<vtkImplicitPlaneWidget*>(caller);

    planeWidget->GetPlane(this->plane);


  }

  igwCMCallback() = default;

  vtkPlane* plane{nullptr};
};



vtkStandardNewMacro(igwCloudMapRepresentation);

igwCloudMapRepresentation::igwCloudMapRepresentation()
{
    this->DataSetSurfaceFilter = vtkSmartPointer<vtkDataSetSurfaceFilter>::New();
    this->Plane = vtkPlane::New();
    this->Cutter = vtkCutter::New();
    this->Cutter->SetCutFunction(this->Plane);

    this->CallBack = igwCMCallback::New();
    this->CallBack->plane = this->Plane;

    this->ImplicitPlaneWidget = vtkImplicitPlaneWidget::New();

    this->ImplicitPlaneWidget->SetPlaceFactor(1.2);
    this->ImplicitPlaneWidget->SetNormalToZAxis(1);
    this->ImplicitPlaneWidget->GetPlaneProperty()->SetOpacity(0.3);

    this->ImplicitPlaneWidget->SetOriginTranslation(false);

    this->ImplicitPlaneWidget->ScaleEnabledOff();
    this->ImplicitPlaneWidget->OutlineTranslationOff();
    this->ImplicitPlaneWidget->SetDiagonalRatio(0);


    this->Mapper = vtkPolyDataMapper::New();

    this->Actor->SetMapper(Mapper);

//    this->SetPlaneVisibility(false);

    // 默认三维数据
    this->Type = THREE_D;

    // 初始化Observer

}

igwCloudMapRepresentation::~igwCloudMapRepresentation()
{
    this->Plane->Delete();
    this->CallBack->Delete();

    this->Cutter->Delete();
    this->Mapper->Delete();

}
void igwCloudMapRepresentation::PrintSelf(std::ostream &os, vtkIndent indent)
{

}

void igwCloudMapRepresentation::SetDataSet(vtkDataSet *dataSet)
{
    this->Superclass::SetDataSet(dataSet);

}

void igwCloudMapRepresentation::SetNormalToXAxis()
{
    this->ImplicitPlaneWidget->SetNormalToXAxis(1);
    this->ImplicitPlaneWidget->PlaceWidget();
}

void igwCloudMapRepresentation::SetNormalToYAxis()
{
    this->ImplicitPlaneWidget->NormalToYAxisOn();
    this->ImplicitPlaneWidget->PlaceWidget();
}

void igwCloudMapRepresentation::SetNormalToZAxis()
{
    this->ImplicitPlaneWidget->NormalToZAxisOn();
    this->ImplicitPlaneWidget->PlaceWidget();
}

void igwCloudMapRepresentation::SetPlaneNormal(double normal[])
{
    this->ImplicitPlaneWidget->SetNormal(normal);
}

void igwCloudMapRepresentation::SetPlaneNormal(double x, double y, double z)
{
    this->ImplicitPlaneWidget->SetNormal(x, y, z);
}

double *igwCloudMapRepresentation::GetPlaneNormal()
{
    return this->ImplicitPlaneWidget->GetNormal();
}


void igwCloudMapRepresentation::SetPlaneOrigin(double origin[])
{
    this->ImplicitPlaneWidget->SetOrigin(origin);
}

void igwCloudMapRepresentation::SetPlaneOrigin(double x, double y, double z)
{
    this->ImplicitPlaneWidget->SetOrigin(x, y, z);
}

double *igwCloudMapRepresentation::GetPlaneOrigin()
{
    return this->ImplicitPlaneWidget->GetOrigin();
}

void igwCloudMapRepresentation::SetPlaneOpacity(double opacity)
{
    this->ImplicitPlaneWidget->GetPlaneProperty()->SetOpacity(opacity);
}

void igwCloudMapRepresentation::PlaneWidgetOn()
{
    this->ImplicitPlaneWidget->On();
}

void igwCloudMapRepresentation::PlaneWidgetOff()
{
    this->ImplicitPlaneWidget->Off();
}

void igwCloudMapRepresentation::SetLookupTable(vtkScalarsToColors *val)
{
    this->Superclass::SetLookupTable(val);

    this->Mapper->SetLookupTable(val);
}

void igwCloudMapRepresentation::SetPointColorArrayName(const char *arrayName)
{
    this->Superclass::SetPointColorArrayName(arrayName);

    this->Mapper->SetScalarModeToUsePointFieldData();
    this->Mapper->SelectColorArray(arrayName);

}

void igwCloudMapRepresentation::SetInputArrayToProcess(int idx, int port, int connection, int fieldAssociation, const char *name)
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

void igwCloudMapRepresentation::SetDataType(DataType type)
{
    this->Type = type;

}

//void igwCloudMapRepresentation::UpdateDataSet(void *newData)
//{

//    if(newData == nullptr)
//    {
//        // 数据为空时，返回
//        return ;
//    }
//    vtkDataSet* data = static_cast<vtkDataSet*>(newData);
//    this->SetInputData(data);
//    this->DataSet = data;
//    this->Modified();

//    this->SetInputArrayToProcess(0, 0, 0,vtkDataObject::FIELD_ASSOCIATION_POINTS,
//                                 GetPointColorArrayName());

//}



int igwCloudMapRepresentation::RequestData(vtkInformation *request, vtkInformationVector **inputVector, vtkInformationVector *outputVector)
{
    this->Cutter->SetInputConnection(this->GetInternalOutputPort());
    this->DataSetSurfaceFilter->SetInputConnection(this->GetInternalOutputPort());
    if(Type == THREE_D)
        this->Mapper->SetInputConnection(this->Cutter->GetOutputPort());
    else
        this->Mapper->SetInputConnection(this->DataSetSurfaceFilter->GetOutputPort());
    this->ImplicitPlaneWidget->SetInputConnection(this->GetInternalOutputPort());
    double bound[6];
    this->GetInputDataObject(0,0);

    vtkInformation* inInfo = inputVector[0]->GetInformationObject(0);
//    vtkDataObject* data = vtkDataObject::SafeDownCast(inInfo->Get(vtkDataObject::DATA_OBJECT()));

    this->DataSet->GetBounds(bound);
    this->ImplicitPlaneWidget->PlaceWidget(bound);

    return this->Superclass::RequestData(request, inputVector, outputVector);
}

void igwCloudMapRepresentation::PrepareForRendering(igwRenderView *view)
{

    this->Superclass::PrepareForRendering(view);
}

bool igwCloudMapRepresentation::AddToView(vtkView *view)
{
    igwRenderView* rv = igwRenderView::SafeDownCast(view);
    if (!rv)
    {
        vtkErrorMacro("Can only add to a subclass of igwRenderView.");
        return false;
    }
    rv->GetRenderer()->AddActor(this->Actor);
    this->Superclass::AddToView(view);
    //获取交互器，同时为平面组件设置交互器
    this->ImplicitPlaneWidget->SetInteractor(rv->GetInteractor());
    this->ImplicitPlaneWidget->On();
    //为ImplicitPlaneWidget增加交互回调，保证平面移动时云图移动
    this->ImplicitPlaneWidget->AddObserver(vtkCommand::EndInteractionEvent, this->CallBack);
    this->ImplicitPlaneWidget->AddObserver(vtkCommand::PositionProp3DEvent, this->CallBack);


    return true;
}

bool igwCloudMapRepresentation::RemoveFromView(vtkView *view)
{
    igwRenderView* rv = igwRenderView::SafeDownCast(view);
     if (rv)
     {
       rv->GetRenderer()->RemoveActor(this->Actor);
       return this->Superclass::RemoveFromView(view);
     }

     return false;
}

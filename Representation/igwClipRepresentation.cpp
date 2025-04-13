#include "igwClipRepresentation.h"
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
#include "vtkClipDataSet.h"
//#include "igwRenderRepObserver.h"

#include <ColorMap/igwColorMapManager.h>

#include <vtkInformationVector.h>
class igwClipRepresentation::igwCMCallback : public vtkCommand
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

    planeWidget->SetNormal(0,1,0);
    planeWidget->GetPlane(this->plane);
//    planeWidget->Off();


  }

  igwCMCallback() = default;

  vtkPlane* plane{nullptr};
};



vtkStandardNewMacro(igwClipRepresentation);

igwClipRepresentation::igwClipRepresentation()
{
    this->DataSetSurfaceFilter = vtkSmartPointer<vtkDataSetSurfaceFilter>::New();
    this->Plane = vtkPlane::New();
    this->Cutter = vtkCutter::New();
    this->Cutter->SetCutFunction(this->Plane);
    this->ClipDataSet = vtkSmartPointer<vtkClipDataSet>::New();
    this->ClipDataSet->SetClipFunction(this->Plane);
    this->CallBack = igwCMCallback::New();
    this->CallBack->plane = this->Plane;

    this->ImplicitPlaneWidget = vtkImplicitPlaneWidget::New();

    this->ImplicitPlaneWidget->SetPlaceFactor(1);
    this->ImplicitPlaneWidget->SetNormalToXAxis(1);
    this->ImplicitPlaneWidget->GetPlaneProperty()->SetOpacity(0.3);

    this->ImplicitPlaneWidget->SetOriginTranslation(false);

    this->ImplicitPlaneWidget->ScaleEnabledOff();
    this->ImplicitPlaneWidget->OutlineTranslationOff();
    this->ImplicitPlaneWidget->GetOutlineProperty()->SetOpacity(0.0);
    this->ImplicitPlaneWidget->SetDiagonalRatio(0);

    this->Plane->SetNormal(0,1,0);

    this->Mapper = vtkPolyDataMapper::New();

    this->Actor->SetMapper(Mapper);

//    this->SetPlaneVisibility(false);
//    this->ImplicitPlaneWidget->GetPlaneProperty()->SetOpacity(0);
//     默认三维数据
//    this->Type = THREE_D;

    // 初始化Observer

}

igwClipRepresentation::~igwClipRepresentation()
{
    this->Plane->Delete();
    this->CallBack->Delete();

    this->Cutter->Delete();
    this->Mapper->Delete();

}
void igwClipRepresentation::PrintSelf(std::ostream &os, vtkIndent indent)
{

}

void igwClipRepresentation::SetDataSet(vtkDataSet *dataSet)
{
    this->Superclass::SetDataSet(dataSet);

}

void igwClipRepresentation::SetNormalToXAxis()
{
    this->ImplicitPlaneWidget->SetNormalToXAxis(1);
    this->ImplicitPlaneWidget->PlaceWidget();
}

void igwClipRepresentation::SetNormalToYAxis()
{
    this->ImplicitPlaneWidget->NormalToYAxisOn();
    this->ImplicitPlaneWidget->PlaceWidget();
}

void igwClipRepresentation::SetNormalToZAxis()
{
    this->ImplicitPlaneWidget->NormalToZAxisOn();
    this->ImplicitPlaneWidget->PlaceWidget();
}

void igwClipRepresentation::SetPlaneNormal(double normal[])
{
    this->ImplicitPlaneWidget->SetNormal(normal);
}

void igwClipRepresentation::SetPlaneNormal(double x, double y, double z)
{
    this->ImplicitPlaneWidget->SetNormal(x, y, z);
}

double *igwClipRepresentation::GetPlaneNormal()
{
    return this->ImplicitPlaneWidget->GetNormal();
}


void igwClipRepresentation::SetPlaneOrigin(double origin[])
{
    this->ImplicitPlaneWidget->SetOrigin(origin);
}

void igwClipRepresentation::SetPlaneOrigin(double x, double y, double z)
{
    this->ImplicitPlaneWidget->SetOrigin(x, y, z);
}

double *igwClipRepresentation::GetPlaneOrigin()
{
    return this->ImplicitPlaneWidget->GetOrigin();
}

void igwClipRepresentation::SetPlaneOpacity(double opacity)
{
    this->ImplicitPlaneWidget->GetPlaneProperty()->SetOpacity(opacity);
}

void igwClipRepresentation::PlaneWidgetOn()
{
    this->ImplicitPlaneWidget->On();
}

void igwClipRepresentation::PlaneWidgetOff()
{
    this->ImplicitPlaneWidget->Off();
}

void igwClipRepresentation::SetLookupTable(vtkScalarsToColors *val)
{
    this->Superclass::SetLookupTable(val);

    this->Mapper->SetLookupTable(val);
}

void igwClipRepresentation::SetPointColorArrayName(const char *arrayName)
{
    this->Superclass::SetPointColorArrayName(arrayName);

    this->Mapper->SetScalarModeToUsePointFieldData();
    this->Mapper->SelectColorArray(arrayName);

}

void igwClipRepresentation::SetInputArrayToProcess(int idx, int port, int connection, int fieldAssociation, const char *name)
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



//void igwClipRepresentation::UpdateDataSet(void *newData)
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



int igwClipRepresentation::RequestData(vtkInformation *request, vtkInformationVector **inputVector, vtkInformationVector *outputVector)
{
//    this->Cutter->SetInputConnection(this->GetInternalOutputPort());
    this->ClipDataSet->SetInputConnection(this->GetInternalOutputPort());
    this->DataSetSurfaceFilter->SetInputConnection(this->ClipDataSet->GetOutputPort());
//    if(Type == THREE_D)
//        this->Mapper->SetInputConnection(this->GetOutputPort());
//    else
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

void igwClipRepresentation::PrepareForRendering(igwRenderView *view)
{

    this->Superclass::PrepareForRendering(view);
}

bool igwClipRepresentation::AddToView(vtkView *view)
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

bool igwClipRepresentation::RemoveFromView(vtkView *view)
{
    igwRenderView* rv = igwRenderView::SafeDownCast(view);
     if (rv)
     {
       rv->GetRenderer()->RemoveActor(this->Actor);
       return this->Superclass::RemoveFromView(view);
     }

     return false;
}



#include "igwRenderedRepresentation.h"

#include "vtkIdTypeArray.h"
#include "vtkInformation.h"
#include "vtkObjectFactory.h"
#include "vtkProp.h"
#include "vtkRenderer.h"
#include "vtkRenderView.h"
#include "vtkSelection.h"
#include "vtkSelectionNode.h"
#include "vtkSmartPointer.h"
#include "igwRenderView.h"
#include "vtkProperty.h"
#include "vtkMapper.h"
#include "vtkApplyColors.h"
#include "vtkPointData.h"
#include "vtkDataArray.h"
#include "vtkDoubleArray.h"
#include "vtkDataSet.h"
#include "vtkScalarBarActor.h"
#include "ColorMap/igwColorMapManager.h"
#include "vtkCellData.h"
#include "igwCommand.h"

#include "igwRenderRepObserver.h"

#include <vector>
#include <vtkCompositeDataSet.h>
#include <vtkTextProperty.h>



vtkStandardNewMacro(igwRenderedRepresentation);

class igwRenderedRepresentation::Internals
{
public:
  // Convenience vectors for storing props to add/remove until the next render,
  // where they are added/removed by PrepareForRendering().
  std::vector<vtkSmartPointer<vtkProp> > PropsToAdd;
  std::vector<vtkSmartPointer<vtkProp> > PropsToRemove;
};


igwRenderedRepresentation::igwRenderedRepresentation()
{

    this->Implementation = new Internals();
    this->LabelRenderMode = vtkRenderView::FREETYPE;

    this->Actor = vtkActor::New();
    this->Property = vtkProperty::New();

    this->Actor->SetProperty(Property);
    this->PointColorArrayNameInternal = nullptr;

    this->ScalarBarActor = vtkSmartPointer<vtkScalarBarActor>::New();
    this->ScalarBarActor->SetLookupTable(igwColorMapManager::GetInstance()->GetColorFunction());
    this->ScalarBarActor->SetWidth( 0.15 );
    this->ScalarBarActor->SetHeight(0.4);
    vtkTextProperty*lableProperty =  this->ScalarBarActor->GetLabelTextProperty();
    lableProperty->SetColor(0,0,0);

    vtkTextProperty* titleProperty = this->ScalarBarActor->GetTitleTextProperty();

    titleProperty->SetBold(true);
    titleProperty->SetColor(0,0,0);

    // 事件处理
    this->Observer = vtkSmartPointer<igwRenderRepObserver>::New();
    this->Observer->setRepresentation(this);
}

igwRenderedRepresentation::~igwRenderedRepresentation()
{
    delete this->Implementation;
    this->Property->Delete();
    this->Actor->Delete();
    this->PointColorArrayNameInternal = nullptr;

}

void igwRenderedRepresentation::SetAmbientColor(double r, double g, double b)
{
    this->Property->SetAmbientColor(r, g, b);
}

void igwRenderedRepresentation::SetColor(double r, double g, double b)
{
    this->Property->SetColor(r, g, b);
}

void igwRenderedRepresentation::SetDiffuseColor(double r, double g, double b)
{
    this->Property->SetDiffuseColor(r, g, b);
}

void igwRenderedRepresentation::SetEdgeColor(double r, double g, double b)
{
    this->Property->SetEdgeColor(r, g, b);
}

void igwRenderedRepresentation::SetInterpolation(int val)
{
    this->Property->SetInterpolation(val);
}

void igwRenderedRepresentation::SetLineWidth(double val)
{
    this->SetLineWidth(val);
}

void igwRenderedRepresentation::SetOpacity(double val)
{
    this->Property->SetOpacity(val);
}

void igwRenderedRepresentation::SetPointSize(double val)
{
    this->Property->SetPointSize(val);
}

void igwRenderedRepresentation::SetSpecularColor(double r, double g, double b)
{
    this->Property->SetSpecularColor(r, g, b);
}

void igwRenderedRepresentation::SetSpecularPower(double val)
{
    this->Property->SetSpecularPower(val);
}

void igwRenderedRepresentation::SetOrientation(double x, double y, double z)
{
    this->Actor->SetOrientation(x, y, z);
}

void igwRenderedRepresentation::SetOrigin(double x, double y, double z)
{
    this->Actor->SetOrigin(x, y, z);

}

void igwRenderedRepresentation::SetPickable(int val)
{
    this->Actor->SetPickable(val);
}

void igwRenderedRepresentation::SetPosition(double x, double y, double z)
{
    this->Actor->SetPosition(x, y, z);
}

void igwRenderedRepresentation::SetScale(double x, double y, double z)
{
    this->SetScale(x, y, z);
}

void igwRenderedRepresentation::SetVisibility(bool visibility)
{
   this->Actor->SetVisibility(visibility);
}

void igwRenderedRepresentation::UpdateDataSet(void *newData)
{
    if(newData == nullptr)
    {
        // 数据为空时，返回
        return ;
    }
    vtkDataSet* data = static_cast<vtkDataSet*>(newData);
    this->SetInputData(data);
    this->DataSet = data;
    this->Modified();

    this->SetInputArrayToProcess(0, 0, 0,vtkDataObject::FIELD_ASSOCIATION_POINTS,
                                 GetPointColorArrayName());
}

void igwRenderedRepresentation::SetLookupTable(vtkScalarsToColors *val)
{

}

void igwRenderedRepresentation::SetPointColorArrayName(const char *arrayName)
{
    this->SetPointColorArrayNameInternal(arrayName);
}

void igwRenderedRepresentation::SetInputArrayToProcess(int idx, int port, int connection, int fieldAssociation, const char *name)
{
    this->Superclass::SetInputArrayToProcess(idx, port, connection, fieldAssociation, name);
    switch (fieldAssociation) {
    case vtkDataObject::FIELD_ASSOCIATION_POINTS:
        this->SetPointColorArrayName(name);
        break;
//    case vtkDataObject::FIELD_ASSOCIATION_CELLS:
//        this->SetCellColorArrayNameInternal(name);
    default:
        break;
    }
    this->SetPointColorArrayName(name);

    igwColorMapManager::GetInstance()->SetRange(this->GetArrayRange(fieldAssociation, name));
    igwColorMapManager::GetInstance()->ApplyPreset();
    this->ScalarBarActor->SetTitle(name);
    this->ScalarBarActor->UnconstrainedFontSizeOn();


}

void igwRenderedRepresentation::SetInputData(vtkDataObject * dataObject)
{
    this->Superclass::SetInputData(dataObject);

    if(dataObject == nullptr) return;

    int dataType = dataObject->GetDataObjectType();
    vtkDataSet* dataSet = nullptr;

    if(dataType == VTK_MULTIBLOCK_DATA_SET)
    {
        vtkCompositeDataSet* compositeData = vtkCompositeDataSet::SafeDownCast(dataObject);

        auto iter = compositeData->NewIterator();
        if( compositeData!=nullptr)
        {

            iter->SetDataSet(compositeData);
            iter->SkipEmptyNodesOn();
//            iter->VisitOnlyLeavesOn();
//            iter->SetTraverseSubTree(false);
            for (iter->InitTraversal(); !iter->IsDoneWithTraversal();
                   iter->GoToNextItem())
              {
                dataSet = vtkDataSet::SafeDownCast(iter->GetCurrentDataObject());
//                dso->ShallowCopy(iter->GetCurrentDataObject());
//                datas.push_back(dso);

              }
        }
    }
    else /*if(dataType == VTK_DATA_SET)*/
    {
        dataSet = vtkDataSet::SafeDownCast(dataObject);
    }
    if(dataSet == nullptr) return;
    this->SetDataSet(dataSet);
    vtkPointData* pointData = dataSet->GetPointData();

    this->SetInputArrayToProcess(0,0,0, vtkDataObject::FIELD_ASSOCIATION_POINTS, pointData->GetArrayName(0));

}

void igwRenderedRepresentation::SetInputData(int port, vtkDataObject *dataObject)
{
    this->Superclass::SetInputData(port, dataObject);
}

void igwRenderedRepresentation::AddPropOnNextRender(vtkProp* p)
{
  this->Implementation->PropsToAdd.push_back(p);
}

void igwRenderedRepresentation::RemovePropOnNextRender(vtkProp* p)
{
  this->Implementation->PropsToRemove.push_back(p);
}

void igwRenderedRepresentation::PrepareForRendering(igwRenderView* view)
{
  // Add props scheduled to be added on next render.
  for (size_t i = 0; i < this->Implementation->PropsToAdd.size(); ++i)
  {
    view->GetRenderer()->AddViewProp(this->Implementation->PropsToAdd[i]);
  }
  this->Implementation->PropsToAdd.clear();

  // Remove props scheduled to be removed on next render.
  for (size_t i = 0; i < this->Implementation->PropsToRemove.size(); ++i)
  {
    view->GetRenderer()->RemoveViewProp(this->Implementation->PropsToRemove[i]);
  }
  this->Implementation->PropsToRemove.clear();
}

bool igwRenderedRepresentation::AddToView(vtkView *view)
{
    igwRenderView* rv = igwRenderView::SafeDownCast(view);
    if (!rv)
    {
        vtkErrorMacro("Can only add to a subclass of igwRenderView.");
        return false;
    }


    rv->GetRenderer()->AddActor2D(ScalarBarActor);

     // 添加ETKF数据更新回调
    vtkRenderWindowInteractor* interactor = rv->GetInteractor();
    interactor->AddObserver(iGreatWorks::ETKFDataUpdateEvent, this->Observer);
    return true;
}

//vtkUnicodeString igwRenderedRepresentation::GetHoverText(vtkView* view, vtkProp* prop, vtkIdType cell)
//{
//  vtkSmartPointer<vtkSelection> cellSelect = vtkSmartPointer<vtkSelection>::New();
//  vtkSmartPointer<vtkSelectionNode> cellNode = vtkSmartPointer<vtkSelectionNode>::New();
//  cellNode->GetProperties()->Set(vtkSelectionNode::PROP(), prop);
//  cellNode->SetFieldType(vtkSelectionNode::CELL);
//  cellNode->SetContentType(vtkSelectionNode::INDICES);
//  vtkSmartPointer<vtkIdTypeArray> idArr = vtkSmartPointer<vtkIdTypeArray>::New();
//  idArr->InsertNextValue(cell);
//  cellNode->SetSelectionList(idArr);
//  cellSelect->AddNode(cellNode);
//  vtkSelection* converted = this->ConvertSelection(view, cellSelect);
//  vtkUnicodeString text = this->GetHoverTextInternal(converted);
//  if (converted != cellSelect)
//  {
//    converted->Delete();
//  }
//  return text;
//}

void igwRenderedRepresentation::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
    os << indent << "LabelRenderMode: " << this->LabelRenderMode << endl;
}

void igwRenderedRepresentation::SetDataSet(vtkDataSet * dataSet)
{

    this->DataSet = dataSet;
}

vtkDataSet *igwRenderedRepresentation::GetDataSet()
{
    return this->DataSet;
}

double* igwRenderedRepresentation::GetArrayRange(int fieldAssociation, const char *arrayName)
{


    vtkDataSetAttributes* data;
    switch (fieldAssociation) {
    case vtkDataObject::FIELD_ASSOCIATION_POINTS:

        data = this->DataSet->GetPointData();

        break;
    case vtkDataObject::FIELD_ASSOCIATION_CELLS:
        data = this->DataSet->GetCellData();
        break;
    default:
        break;
    }
    if(data == nullptr) return nullptr;
    vtkDataArray* arrays = data->GetArray(arrayName);
    if(arrays == nullptr) return nullptr;
    int numOfCompoment = arrays->GetNumberOfComponents();

    return numOfCompoment == 1 ? arrays->GetRange() : arrays->GetRange(-1);
}

double *igwRenderedRepresentation::GetArrayRange(const char *arrayName)
{
    vtkDataSetAttributes* data = this->DataSet->GetPointData();
    vtkDataArray* arrays = data->GetArray(arrayName);
    int numOfCompoment = arrays->GetNumberOfComponents();

    return numOfCompoment == 1 ? arrays->GetRange() : arrays->GetRange(-1);
}

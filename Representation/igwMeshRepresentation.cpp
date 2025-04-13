#include "igwMeshRepresentation.h"
#include "vtkObjectFactory.h"
#include "vtkMapper.h"
#include "vtkOutlineFilter.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "igwRenderView.h"
#include "vtkRenderer.h"
#include "vtkProperty.h"
#include "vtkPlaneSource.h"
#include "igwCommand.h"
#include "vtkCommand.h"
#include "vtkCellData.h"
#include "vtkLookupTable.h"
class igwMeshRepresentation::igwMeshDataUpadetObeserver : public vtkCommand
{
public:
  vtkTypeMacro(igwMeshDataUpadetObeserver, vtkCommand)
  static igwMeshDataUpadetObeserver* New()
  {
    return new igwMeshDataUpadetObeserver;
  }
  igwMeshDataUpadetObeserver(){

  }

  void setMeshRepresentation(igwMeshRepresentation * rep){
      m_igeMeshRep = rep;
  }

  void Execute(vtkObject* caller, unsigned long eventId,
               void* callData) override
  {

    m_igeMeshRep->UpdateData(callData);
    vtkRenderWindowInteractor* iren = static_cast<vtkRenderWindowInteractor*>(caller);
    iren->Render();
  }
   ~igwMeshDataUpadetObeserver(){
      m_igeMeshRep = 0;
  }

private:

  igwMeshRepresentation* m_igeMeshRep;

};

vtkStandardNewMacro(igwMeshRepresentation)
igwMeshRepresentation::igwMeshRepresentation()
{
    this->MeshDataUpdateObeserver = vtkSmartPointer<igwMeshDataUpadetObeserver>::New();
    this->MeshDataUpdateObeserver->setMeshRepresentation(this);


    this->PlaneSource = vtkSmartPointer<vtkPlaneSource>::New();

    this->Mapper = vtkPolyDataMapper::New();
    this->Actor->SetMapper(this->Mapper);
    //设置网格边框
    this->Property->SetRepresentationToSurface();
    this->Property->SetEdgeVisibility(1);

    this->Mapper->SetInputConnection(this->PlaneSource->GetOutputPort());

    //设置网格数量,默认为5*5
    this->Row = 5;
    this->Col = 5;
    this->PlaneSource->SetXResolution(Row);
    this->PlaneSource->SetYResolution(Col);

    this->PlaneSource->Update();
    this->DataSet = this->PlaneSource->GetOutput();

    this->InitCellData("press");
//    this->DataSet->Print(std::cout);
    // 为了保证左上角是网格原点 cellid = 0
    this->Actor->RotateX(180);
//    this->Actor->RotateY(180);

}

igwMeshRepresentation::~igwMeshRepresentation()
{
    this->Mapper->Delete();

}

void igwMeshRepresentation::SetLookupTable(vtkScalarsToColors *val)
{
    this->Mapper->SetLookupTable(val);
}

void igwMeshRepresentation::SetXResolution(int xr)
{
    this->PlaneSource->SetXResolution(xr);
    this->SetCol(xr);
    // 删除array
    this->PlaneSource->Update();
    int index;
    this->DataSet->GetCellData()->GetArray(this->GetPointColorArrayName(), index);
    this->DataSet->GetCellData()->RemoveArray(index);
    // 重新构建arry
    this->InitCellData("press");

}

void igwMeshRepresentation::SetYResolution(int yr)
{
    this->PlaneSource->SetYResolution(yr);

    this->SetRow(yr);
    // 删除array
    this->PlaneSource->Update();
    int index;
    this->DataSet->GetCellData()->GetArray(this->GetPointColorArrayName(), index);
    this->DataSet->GetCellData()->RemoveArray(index);
    // 重新构建arry
    this->InitCellData("press");
}

vtkDataArray *igwMeshRepresentation::GetCellArray()
{
    return this->DataSet->GetCellData()->GetArray(this->GetPointColorArrayName());
}

void igwMeshRepresentation::SetInputArrayToProcess(int idx, int port, int connection, int fieldAssociation, const char *name)
{
    this->Superclass::SetInputArrayToProcess(idx, port, connection, fieldAssociation, name);

    if (idx == 1)
    {
        return ;
    }

//    this->Mapper->GetLookupTable()->SetRange(this->GetArrayRange(fieldAssociation ,name));
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


int igwMeshRepresentation::RequestData(vtkInformation *request, vtkInformationVector **inputVector, vtkInformationVector *outputVector)
{

    return this->Superclass::RequestData(request, inputVector, outputVector);
}

bool igwMeshRepresentation::AddToView(vtkView *view)
{
    igwRenderView* rv = igwRenderView::SafeDownCast(view);
      if (!rv)
      {
        vtkErrorMacro("Can only add to a subclass of igwRenderView.");
        return false;
      }
      this->Superclass::AddToView(view);
      rv->GetRenderer()->AddActor(this->Actor);

      vtkRenderWindowInteractor* interactor = rv->GetInteractor();
      interactor->AddObserver(iGreatWorks::MeshDataUpdateEvent, this->MeshDataUpdateObeserver);
      return true;
}

bool igwMeshRepresentation::RemoveFromView(vtkView *view)
{
    igwRenderView* rv = igwRenderView::SafeDownCast(view);
     if (rv)
     {
       rv->GetRenderer()->RemoveActor(this->Actor);
       return this->Superclass::RemoveFromView(view);
     }
//     vtkRenderWindowInteractor* interactor = rv->GetInteractor();
//     interactor->RemoveObserver(this->MeshDataUpdateObeserver);
     return false;
}

void igwMeshRepresentation::UpdateData(void *newdata)
{
    double* data = static_cast<double*>(newdata);// 数据转换为double指针
    for(int i = 0; i < DataSet->GetNumberOfCells(); i++){
        DataSet->GetCellData()->GetArray(GetPointColorArrayName())->SetTuple1(i, data[i]);
    }

    DataSet->GetCellData()->GetArray(GetPointColorArrayName())->Modified();

    DataSet->Modified();

    Mapper->SetScalarRange( DataSet->GetCellData()->GetArray(GetPointColorArrayName())->GetRange());

    Mapper->Update();

    this->SetInputArrayToProcess(0, 0, 0,vtkDataObject::FIELD_ASSOCIATION_CELLS,
                                  DataSet->GetCellData()->GetArray(GetPointColorArrayName())->GetName());

}

void igwMeshRepresentation::InitCellData(const char *arrayname)
{
    vtkNew<vtkDoubleArray> array;
    array->SetName(arrayname);
    array->SetNumberOfTuples(this->DataSet->GetNumberOfCells());
    for(int i = 0; i < this->DataSet->GetNumberOfCells(); ++i)
    {
        array->SetTuple1(i, 0);
    }
    this->DataSet->GetCellData()->AddArray(array);

}

void igwMeshRepresentation::PrintSelf(std::ostream &os, vtkIndent indent)
{

}

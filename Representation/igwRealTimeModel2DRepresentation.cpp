#include "igwRealTimeModel2DRepresentation.h"
#include "vtkPolyDataMapper.h"
#include "vtkObjectFactory.h"
#include "vtkRenderer.h"
#include "vtkGlyph3D.h"
#include "vtkArrowSource.h"
#include "vtkTransform.h"
#include "vtkTransformPolyDataFilter.h"
#include "vtkMaskPoints.h"
#include "vtkDoubleArray.h"
#include "vtkPointData.h"
#include "vtkSmartPointer.h"

#include "igwRenderView.h"
#include "igwCommand.h"

vtkStandardNewMacro(igwRealTimeModel2DRepresentation)
/**
 * @brief The igwRealTimeModel2DRepresentation::igwRealTimeModel2DObserver class:
 * 更新igwRealTimeModel2DRepresentation数据
 */
class igwRealTimeModel2DRepresentation::igwRealTimeModel2DObserver : public vtkCommand
{
public:
  vtkTypeMacro(igwRealTimeModel2DObserver, vtkCommand)
  static igwRealTimeModel2DObserver* New()
  {
    return new igwRealTimeModel2DObserver;
  }
  igwRealTimeModel2DObserver(){

  }

  void SetRealTimeModel2DRep(igwRealTimeModel2DRepresentation * rep){
      m_igwRealTimeModel2DRep = rep;
  }

  void Execute(vtkObject* caller, unsigned long eventId,
               void* callData) override
  {

    m_igwRealTimeModel2DRep->CallBack(callData);
    vtkRenderWindowInteractor* iren = static_cast<vtkRenderWindowInteractor*>(caller);
    iren->Render();
  }
   ~igwRealTimeModel2DObserver(){
      m_igwRealTimeModel2DRep = 0;
  }

private:

  igwRealTimeModel2DRepresentation* m_igwRealTimeModel2DRep;

};
igwRealTimeModel2DRepresentation::igwRealTimeModel2DRepresentation()
{
    this->RealTimeModel2DObserver = vtkSmartPointer<igwRealTimeModel2DObserver>::New();
    this->RealTimeModel2DObserver->SetRealTimeModel2DRep(this);
    InitGlyph3D();
    this->Mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    this->Mapper->SetInputConnection(this->Glyph3D->GetOutputPort());

    this->Actor->SetMapper(Mapper);

    this->ModelMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    this->ModelActor = vtkSmartPointer<vtkActor>::New();
    this->ModelActor->SetMapper(this->ModelMapper);
}

igwRealTimeModel2DRepresentation::~igwRealTimeModel2DRepresentation()
{

}

void igwRealTimeModel2DRepresentation::SetLookupTable(vtkScalarsToColors *val)
{
    this->Superclass::SetLookupTable(val);

    this->Mapper->SetLookupTable(val);

    this->ModelMapper->SetLookupTable(val);
}

void igwRealTimeModel2DRepresentation::SetInputArrayToProcess(int idx, int port, int connection, int fieldAssociation, const char *name)
{
    this->Superclass::SetInputArrayToProcess(idx, port, connection, fieldAssociation, name);

    if (idx == 1)
    {
        return ;
    }

    this->Mapper->SetInputArrayToProcess(idx, port, connection, fieldAssociation, name);
    this->ModelMapper->SetUseLookupTableScalarRange(1);
    if(name && name[0])
    {
        this->Mapper->SetScalarVisibility(1);
        this->Mapper->SelectColorArray(name);
        this->Mapper->SetUseLookupTableScalarRange(1);

        this->ModelMapper->SetScalarVisibility(1);
        this->ModelMapper->SelectColorArray(name);
        this->ModelMapper->SetUseLookupTableScalarRange(1);

    }
    else
    {
        this->Mapper->SetScalarVisibility(0);
        this->Mapper->SelectColorArray(static_cast<const char*>(NULL));

        this->ModelMapper->SetScalarVisibility(0);
        this->ModelMapper->SelectColorArray(static_cast<const char*>(NULL));
    }

    switch (fieldAssociation)
    {
      case vtkDataObject::FIELD_ASSOCIATION_CELLS:
        this->Mapper->SetScalarMode(VTK_SCALAR_MODE_USE_CELL_FIELD_DATA);

        this->ModelMapper->SetScalarMode(VTK_SCALAR_MODE_USE_CELL_FIELD_DATA);
        break;

      case vtkDataObject::FIELD_ASSOCIATION_POINTS:
      default:
        this->Mapper->SetScalarMode(VTK_SCALAR_MODE_USE_POINT_FIELD_DATA);

        this->ModelMapper->SetScalarMode(VTK_SCALAR_MODE_USE_POINT_FIELD_DATA);
        break;
    }

}

void igwRealTimeModel2DRepresentation::CallBack(void *newData)
{
    double* data = static_cast<double*>(newData);
    this->UpdateData(data);

}

void igwRealTimeModel2DRepresentation::SetPointColorArrayName(const char *arrayName)
{
    this->Superclass::SetPointColorArrayName(arrayName);

    this->Mapper->SetScalarModeToUsePointFieldData();
    this->Mapper->SelectColorArray(arrayName);

    this->ModelMapper->SetScalarModeToUsePointFieldData();
    this->ModelMapper->SelectColorArray(arrayName);
}

void igwRealTimeModel2DRepresentation::PrepareForRendering(igwRenderView *view)
{
    this->Superclass::PrepareForRendering(view);
}

bool igwRealTimeModel2DRepresentation::RemoveFromView(vtkView *view)
{
    igwRenderView* rv = igwRenderView::SafeDownCast(view);
     if (rv)
     {
       rv->GetRenderer()->RemoveActor(this->Actor);
       return this->Superclass::RemoveFromView(view);
     }

     return false;
}

void igwRealTimeModel2DRepresentation::InitGlyph3D()
{
    this->Glyph3D = vtkSmartPointer<vtkGlyph3D>::New();

    this->MaskPoints = vtkSmartPointer<vtkMaskPoints>::New();

    this->MaskPoints->SetOnRatio(1);


    this->Arrow = vtkSmartPointer<vtkArrowSource>::New();
    this->Arrow->SetTipResolution(1);
    this->Arrow->SetShaftResolution(1);
    this->Transform = vtkSmartPointer<vtkTransform>::New();
//    transform->Translate(0.5, 0, 0);
    this->TransformPolyDataFilter = vtkSmartPointer<vtkTransformPolyDataFilter>::New();
    this->TransformPolyDataFilter->SetInputConnection(Arrow->GetOutputPort());
    this->TransformPolyDataFilter->SetTransform(Transform);

    this->Glyph3D->SetInputConnection(MaskPoints->GetOutputPort());

    this->Glyph3D->SetSourceConnection(TransformPolyDataFilter->GetOutputPort());
    this->Glyph3D->SetVectorModeToUseVector();
    this->Glyph3D->SetScaleModeToScaleByScalar();
    this->Glyph3D->SetScaleFactor(0.01);
//    this->Glyph3D->Update();

}

void igwRealTimeModel2DRepresentation::ComputerNormal()
{
    double XY_Normal[3] = {0, 0, 1};
    vtkNew<vtkDoubleArray> point_normal;
    point_normal->SetNumberOfComponents(3);


    point_normal->SetNumberOfComponents(3);
    point_normal->SetName("NormalToGlyph");
    vtkPolyData* poly_data = vtkPolyData::SafeDownCast(DataSet);
    vtkPoints* points = poly_data->GetPoints();
    vtkIdType points_number = points->GetNumberOfPoints();
    for(vtkIdType i = 0; i < DataSet->GetNumberOfPoints(); i++){
        double vec_1[3], vec_2[3];
        double point_1[3], point_2[3], point_3[3];
        if (i == 0){

            points->GetPoint(i, point_1);
            points->GetPoint(i + 1, point_2);
            points->GetPoint(points_number - 1, point_3);

        }
        else {
            points->GetPoint(i, point_1);
            points->GetPoint((i + 1) % points_number, point_2);
            points->GetPoint(i - 1, point_3);

        }
        vtkMath::Subtract(point_2, point_1, vec_1);
        vtkMath::Subtract(point_1, point_3, vec_2);

        double normal_1[3], normal_2[3];
        vtkMath::Cross(XY_Normal, vec_1, normal_1);
        vtkMath::Cross(XY_Normal, vec_2, normal_2);

        double normal[3];
        vtkMath::Add(normal_1, normal_2, normal);
        vtkMath::Normalize(normal);
        point_normal->InsertNextTuple3(normal[0], normal[1], normal[2]);
    }

    DataSet->GetPointData()->SetVectors(point_normal);
}

void igwRealTimeModel2DRepresentation::UpdateData(double *newData)
{
    for(int i = 0; i < DataSet->GetNumberOfPoints(); i++){
        DataSet->GetPointData()->GetScalars()->SetTuple1(i, newData[i]);
    }
    DataSet->GetPointData()->GetScalars()->Modified();

    DataSet->Modified();

    Mapper->SetScalarRange(DataSet->GetPointData()->GetScalars()->GetRange());

    Mapper->Update();

    ModelMapper->SetScalarRange(DataSet->GetPointData()->GetScalars()->GetRange());
    ModelMapper->Update();
    this->SetInputArrayToProcess(0, 0, 0,vtkDataObject::FIELD_ASSOCIATION_POINTS,
                                 DataSet->GetPointData()->GetScalars()->GetName());
}

bool igwRealTimeModel2DRepresentation::AddToView(vtkView *view)
{

    igwRenderView* rv = igwRenderView::SafeDownCast(view);
    if (!rv)
    {
        vtkErrorMacro("Can only add to a subclass of igwRenderView.");
        return false;
    }
    rv->GetRenderer()->AddActor(this->Actor);
    rv->GetRenderer()->AddActor(this->ModelActor);
//    this->Superclass::AddToView(view);
    vtkRenderWindowInteractor* interactor = rv->GetInteractor();
    interactor->AddObserver(iGreatWorks::RealTimeModelUpdateEvent, this->RealTimeModel2DObserver);

    return true;

}

int igwRealTimeModel2DRepresentation::RequestData(vtkInformation *request, vtkInformationVector **inputVector, vtkInformationVector *outputVector)
{

    this->ModelMapper->SetInputConnection(this->GetInternalOutputPort());
    ComputerNormal();
    MaskPoints->SetInputConnection(this->GetInternalOutputPort());
    InitGlyph3D();
    return this->Superclass::RequestData(request, inputVector, outputVector);
}

void igwRealTimeModel2DRepresentation::PrintSelf(std::ostream &os, vtkIndent indent)
{

}

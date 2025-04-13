#include "igwRealTimeModel2D.h"
#include "vtkCommand.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderWindow.h"
#include "vtkRenderer.h"
#include "vtkDoubleArray.h"
#include "vtkPolyData.h"
#include "vtkPointData.h"
#include "vtkPoints.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkSmartPointer.h"
#include "vtkMaskPoints.h"
#include "vtkTransform.h"
#include "vtkTransformPolyDataFilter.h"
#include "vtkArrowSource.h"
#include "vtkGlyph3D.h"
#include "vtkNew.h"

#include "ColorMap/igwColorMapManager.h"

class igwRealTimeModel2D::igwRealTimeModel2DObserver : public vtkCommand
{
public:
  vtkTypeMacro(igwRealTimeModel2DObserver, vtkCommand)
  static igwRealTimeModel2DObserver* New()
  {
    return new igwRealTimeModel2DObserver;
  }
  igwRealTimeModel2DObserver(){

  }

  void SetRealTimeModel2D(igwRealTimeModel2D * modelCloud){
      m_igwRealTimeModel2D = modelCloud;
  }

  void Execute(vtkObject* caller, unsigned long eventId,
               void* callData) override
  {
      m_igwRealTimeModel2D->CallBack(callData);

  }
   ~igwRealTimeModel2DObserver(){
      m_igwRealTimeModel2D = 0;
  }

private:

  igwRealTimeModel2D* m_igwRealTimeModel2D;

};
igwRealTimeModel2D::igwRealTimeModel2D(vtkRenderer *render, vtkRenderWindowInteractor *iren, vtkPolyData *model) {

    m_Render = render;
    m_Iren = iren;
    m_Model = model;

    //计算法
    ComputerNormal();

    InitGlyph();
    m_igwRealTimeModel2DObserver = igwRealTimeModel2DObserver::New();
    m_igwRealTimeModel2DObserver->SetRealTimeModel2D(this);
//    m_Iren->AddObserver(vtkCommand::UserEvent + iGreatWorks::RealTimeModelUpdateEvent, m_igwRealTimeModel2DObserver);

}

void igwRealTimeModel2D::ComputerNormal()
{
    double XY_Normal[3] = {0, 0, 1};
    vtkNew<vtkDoubleArray> point_normal;
    point_normal->SetNumberOfComponents(3);


    point_normal->SetNumberOfComponents(3);
    point_normal->SetName("NormalToGlyph");
    vtkPoints* points = m_Model->GetPoints();
    vtkIdType points_number = points->GetNumberOfPoints();
    for(vtkIdType i = 0; i < m_Model->GetNumberOfPoints(); i++){
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

    m_Model->GetPointData()->SetVectors(point_normal);
}

void igwRealTimeModel2D::CallBack(void* new_data)
{
    double* data = static_cast<double*>(new_data);
    UpdateData(data);
    m_Iren->Render();
}

void igwRealTimeModel2D::UpdateData(double* new_data)
{
    for(int i = 0; i < m_Model->GetNumberOfPoints(); i++){
        m_Model->GetPointData()->GetScalars()->SetTuple1(i, new_data[i]);
    }
    m_Model->GetPointData()->GetScalars()->Modified();
    std::cout << "Point Data: " << m_Model->GetPointData()->GetScalars()->GetTuple1(0) << std::endl;

    m_Model->Modified();
    m_ModelMapper->SetScalarRange(m_Model->GetPointData()->GetScalars()->GetRange());
    m_GlyphMapper->SetScalarRange(m_Model->GetPointData()->GetScalars()->GetRange());
    m_ModelMapper->Update();
    m_GlyphMapper->Update();
    igwColorMapManager::GetInstance()->SetRange(m_Model->GetScalarRange());
    igwColorMapManager::GetInstance()->ApplyPreset("Cool to Warm");

}

void igwRealTimeModel2D::InitGlyph()
{
     m_GlyphGenerate = vtkSmartPointer<vtkGlyph3D>::New();

     vtkNew<vtkMaskPoints> pMask;
     pMask->SetInputData(m_Model);
     pMask->SetOnRatio(1);


     vtkNew<vtkArrowSource> arrow;
     arrow->SetTipResolution(1);
     arrow->SetShaftResolution(1);
     vtkNew<vtkTransform> transform;
 //    transform->Translate(0.5, 0, 0);
     vtkNew<vtkTransformPolyDataFilter> transformF;
     transformF->SetInputConnection(arrow->GetOutputPort());
     transformF->SetTransform(transform);


     m_GlyphGenerate->SetInputConnection(pMask->GetOutputPort());

     m_GlyphGenerate->SetSourceConnection(transformF->GetOutputPort());
     m_GlyphGenerate->SetVectorModeToUseVector();
     m_GlyphGenerate->SetScaleModeToScaleByScalar();
     m_GlyphGenerate->SetScaleFactor(0.01);
     m_GlyphGenerate->Update();

     m_ModelMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
     m_ModelActor = vtkSmartPointer<vtkActor>::New();
     m_GlyphMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
     m_GlyphActor = vtkSmartPointer<vtkActor>::New();


     m_GlyphMapper->SetInputConnection(m_GlyphGenerate->GetOutputPort());
     m_GlyphActor->SetMapper(m_GlyphMapper);
     m_GlyphMapper->SetScalarRange(m_Model->GetPointData()->GetScalars()->GetRange());


     m_ModelMapper->SetInputData(m_Model);

     m_ModelActor->SetMapper(m_ModelMapper);

     m_ModelMapper->SetScalarRange(m_Model->GetPointData()->GetScalars()->GetRange());

     //设置范围
     igwColorMapManager::GetInstance()->SetRange(m_Model->GetScalarRange());
     igwColorMapManager::GetInstance()->ApplyPreset("Cool to Warm");
     m_ModelMapper->SetLookupTable(igwColorMapManager::GetInstance()->GetColorFunction());
     m_GlyphMapper->SetLookupTable(igwColorMapManager::GetInstance()->GetColorFunction());


     m_Render->AddActor(m_ModelActor);
     m_Render->AddActor(m_GlyphActor);


}



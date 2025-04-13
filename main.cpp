#include "mainwindow.h"
#include "vtkVolumeTexture.h"
#include <QApplication>
#include <iostream>
#include <vtkNew.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkUnstructuredGrid.h>
#include <vtkUnstructuredGridReader.h>
#include <vtkGPUVolumeRayCastMapper.h>
#include <vtkMapper.h>
#include <vtkPolyDataMapper.h>
#include <vtkContourFilter.h>
//#include <vtkmGradient.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include "Representation/igwIsoSurfaceRepresentation.h"
#include "vtkRenderView.h"
#include "vtkRenderedSurfaceRepresentation.h"

#include <vtkInteractorStyleTrackballCamera.h>
#include "vtkFlyingEdges3D.h"
#include "vtkObjectBase.h"
#include "vtkLineSource.h"
// 测试流面
int TestStreamSurface(int argc, char* argv[]);

int TestOpenXR(const char* IP);

int TestVolumeRender(const char* filename);
void NacaCellesToVTK(const char* fluentCasName, const char* txtFileName);
void M6SmalToVTK(const char* fluentname, const char* txtFilename);
void TestGaussianData(const char* plyFileName);

void testAnimationActors();
#include "Core/igwApplicationCore.h"
int main(int argc, char *argv[])
{
    vtkObject::GlobalWarningDisplayOff();
    QApplication a(argc, argv);
    igwApplicationCore appcore(argc, argv);
    MainWindow w;

//    NacaCellesToVTK("0.76Ma_0angel_nacelles_2024.vtu","nacelle_wall_Cp_ETKF.txt");

    w.show();
    return a.exec();
//    testAnimationActors();
//    TestStreamSurface(argc, argv);
//    return 0;
}

// SPDX-FileCopyrightText: Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
// SPDX-License-Identifier: BSD-3-Clause
#include "vtkActor.h"
#include "vtkArrayCalculator.h"
#include "vtkDataSetMapper.h"
#include "vtkMath.h"
#include "vtkNew.h"
#include "vtkPointSource.h"
#include "vtkPoints.h"
#include "vtkPolyData.h"
#include "vtkProperty.h"
#include "vtkRTAnalyticSource.h"
#include "vtkRegressionTestImage.h"
#include "vtkRegularPolygonSource.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkStreamSurface.h"
#include "vtkWarpScalar.h"


#include <vtkSTLReader.h>
#include "vtkActor.h"
#include "vtkOpenXRManager.h"
#include "vtkOpenXRCamera.h"
#include "vtkOpenXRManagerRemoteConnection.h"
#include "vtkOpenXRRemotingRenderWindow.h"
#include "vtkOpenXRRenderWindowInteractor.h"
#include "vtkOpenXRRenderer.h"
#include "vtkPolyDataMapper.h"
#include "vtkSphereSource.h"
#include "vtkTestUtilities.h"
#include "vtkSmartPointer.h"
#include "vtkStructuredGrid.h"
#include "vtkStructuredGridReader.h"
#include "vtkNew.h"
#include "vtksys/SystemTools.hxx"
#include "Representation/vtkStreamLinesMapper.h"
#include "vtkPolyDataReader.h"
#include "ColorMap/igwColorMapManager.h"
int TestOpenXR(const char* IP)
{
    const char* playerIP = IP;

    vtkOpenXRRenderer* renderer = vtkOpenXRRenderer::New();

    vtkOpenXRRemotingRenderWindow* renderWindow = vtkOpenXRRemotingRenderWindow::New();
    vtkOpenXRRenderWindowInteractor* iren = vtkOpenXRRenderWindowInteractor::New();
    vtkNew<vtkOpenXRCamera> cam;
    renderWindow->AddRenderer(renderer);
    iren->SetRenderWindow(renderWindow);
    renderer->SetActiveCamera(cam);
    renderWindow->SetRemotingIPAddress(playerIP);

    vtkNew<vtkSTLReader> model_read;
    model_read->SetFileName("M6Wing3.stl");
    vtkNew<vtkPolyDataMapper> model_mapper;
    model_mapper->SetInputConnection(model_read->GetOutputPort());
    vtkNew<vtkActor> model_Actor;
    model_Actor->SetMapper(model_mapper);
    renderer->AddActor(model_Actor);

//    vtkNew<vtkStructuredGridReader> torRead;
//    torRead->SetFileName("tor_bin.vtk");
//    torRead->Update();
//    vtkDataSet* data = torRead->GetOutput();

//    vtkNew<vtkPolyDataReader> nacaRead;
//    nacaRead->SetFileName("2D_Data/NACA0012.vtk");

//    vtkNew<vtkStreamLinesMapper> streamLinesMapper;
//    streamLinesMapper->SetInputConnection(nacaRead->GetOutputPort());
//    streamLinesMapper->SetNumberOfParticles(100);
//    streamLinesMapper->SetMaxTimeToLive(600);
//    streamLinesMapper->SetAlpha(0.01);
//    streamLinesMapper->SetLookupTable(igwColorMapManager::GetInstance()->GetColorFunction());

//    vtkNew<vtkActor> streamLinesActor;
//    streamLinesActor->SetMapper(streamLinesMapper);
//    renderer->AddActor(streamLinesActor);
//    renderer->ResetCamera();

    iren->Start();

    return EXIT_SUCCESS;
}

#include "vtkVolume.h"
#include "vtkUnstructuredGridVolumeMapper.h"
#include "vtkUnstructuredGridVolumeRayCastMapper.h"
#include "vtkGPUVolumeRayCastMapper.h"
#include "vtkProjectedTetrahedraMapper.h"
#include "vtkMergeVectorComponents.h"
#include "vtkDataSet.h"
#include "vtkPointData.h"
#include "vtkUnstructuredGridWriter.h"
#include "vtkDataSetTriangleFilter.h"
#include "vtkVolumeProperty.h"
#include "vtkOpenGLProjectedTetrahedraMapper.h"
#include "vtkArrayCalculator.h"
#include "vtkStructuredPoints.h"
#include "vtkPointData.h"
#include "vtkLODProp3D.h"
#include "vtkMaskPoints.h"
#include "vtkOpenGLRenderer.h"
#include "vtkResampleWithDataSet.h"
#include "vtkResampleToImage.h"
#include "vtkStructuredPoints.h"
int TestVolumeRender(const char* filename)
{

    vtkNew<vtkStructuredGridReader> torRead;
    torRead->SetFileName(filename);
    torRead->Update();

    vtkDataSet* data = torRead->GetOutput();
    data->Print(std::cout);
    data->GetPointData()->SetActiveScalars("x");
    vtkNew<vtkArrayCalculator> caculator;
    caculator->SetInputData(data);
    caculator->SetAttributeTypeToPointData();
    caculator->AddVectorArrayName("Velocity");
    caculator->SetResultArrayName("Magnitude");
    caculator->SetFunction("mag(Velocity)");
    caculator->Update();
    vtkDataSet* out = vtkDataSet::SafeDownCast(caculator->GetOutput());
    out->GetPointData()->SetActiveScalars("Magnitude");
    out->GetPointData()->Print(std::cout);
    vtkNew<vtkStructuredPoints> result;
    result->SetDimensions(64, 64, 64);
    result->SetOrigin(0.0, 0.0, 0.0);

//    result->GetExtent()
    double a =(double)(20.0 / 64.0);
    result->SetSpacing(a, a, a);
    vtkNew<vtkResampleToImage> Resample;
    Resample->SetInputDataObject(out);

    Resample->SetSamplingDimensions(128, 128, 128);
    Resample->Update();
    Resample->GetOutput()->Print(std::cout);

//    vtkStructuredPoints* r = static_cast<vtkStructuredPoints*>(Resample->GetOutput());
//    r->Print(std::cout);

    vtkNew<vtkDataSetTriangleFilter> DataSetTriangleFilter;
    DataSetTriangleFilter->SetInputData(out);

    vtkNew<vtkGPUVolumeRayCastMapper> volumeMapper;
    volumeMapper->SetInputConnection(Resample->GetOutputPort());

//    volumeMapper->SetImageSampleDistance(4.0f);
    volumeMapper->SelectScalarArray("Magnitude");
    volumeMapper->SetScalarModeToUsePointFieldData();
//    volumeMapper->SetInputArrayToProcess(0,0,0,vtkDataObject::FIELD_ASSOCIATION_POINTS, "velocity");

    vtkNew<vtkOpenGLProjectedTetrahedraMapper> highMapper;
    highMapper->SetInputConnection(DataSetTriangleFilter->GetOutputPort());
//    highMapper->SetAutoAdjustSampleDistances(true);

    igwColorMapManager::GetInstance()->SetRange(0.57, 6.25);
    igwColorMapManager::GetInstance()->ApplyPreset("Rainbow Desaturated");
//    volumeMapper->SetScalarModeToUsePointFieldData();
    vtkNew<vtkVolumeProperty> volumeProperty;
    vtkNew<vtkPiecewiseFunction> pwf;
    pwf->AddPoint(0.57, 0);
    pwf->AddPoint(6.25, 1);
    volumeProperty->SetScalarOpacity(pwf);
    volumeProperty->SetColor(igwColorMapManager::GetInstance()->GetColorFunction());

    vtkNew<vtkLODProp3D> prop;

    //prop->AddLOD(hireMapper, volumeProperty, 0);
    //prop->AddLOD(volumeMapper, volumeProperty, 0);
    prop->AddLOD(volumeMapper, volumeProperty, 0);
    prop->AddLOD(highMapper, volumeProperty, 1);
//    prop->EnableLOD(1);
//    highMapper->SetNumberOfThreads(16);
//    prop->SetProperty(volumeProperty);
    //volume->GetProperty()->SetScalarOpacity(igwColorMapManager::GetInstance()->GetPiecewiseFunction());
    vtkNew<vtkRenderer> renderer;

    renderer->AddActor(prop);
    renderer->ResetCamera();
    renderer->SetBackground(1., 1., 1.);

    vtkNew<vtkRenderWindow> renWin;
    renWin->AddRenderer(renderer);


    renWin->SetSize(600, 600);

    vtkNew<vtkRenderWindowInteractor> iren;
    iren->SetRenderWindow(renWin);
    iren->Render();

    iren->Start();

    return 0;
}
#include "vtkParticleTracer.h"
#include "vtkInformation.h"
#include "vtkStreamingDemandDrivenPipeline.h"
int TestStreamSurface(int argc, char* argv[])
{
  vtkNew<vtkStructuredGridReader> torRead;
  torRead->SetFileName("tdelta-low.vtk");
  torRead->Update();
  torRead->GetOutput()->Print(std::cout);
  vtkDataSet* data = torRead->GetOutput();
  data->GetPointData()->SetActiveVectors("velocity");
//  data->GetPointData()->SetActiveScalars("x");
  vtkNew<vtkRTAnalyticSource> wavelet;
  wavelet->SetWholeExtent(-10, 10, -10, 10, -10, 10);

  vtkNew<vtkArrayCalculator> calc;
  calc->AddCoordinateScalarVariable("coordsX", 0);
  calc->AddCoordinateScalarVariable("coordsY", 1);
  calc->AddCoordinateScalarVariable("coordsZ", 2);
  calc->SetFunction("coordsX*iHat + coordsY*jHat + 0.5*(coordsZ^2+coordsX+coordsY)*kHat");
  calc->SetInputConnection(wavelet->GetOutputPort());
  calc->Update();

  vtkNew<vtkRegularPolygonSource> circle;
  circle->SetNumberOfSides(6);
  circle->SetRadius(100);
  circle->SetCenter(0, 0, 1);
  circle->SetNormal(0, 0, 1);
  circle->Update();
  circle->GetOutput()->GetPoints()->InsertNextPoint(circle->GetOutput()->GetPoint(0));
  vtkNew<vtkLineSource> line;
  line->SetPoint1(-100,-200,0);
  line->SetPoint2(-100,200,0);
  line->SetResolution(50);
  vtkNew<vtkStreamTracer> stream;
  stream->SetMaximumPropagation(10000);
  stream->SetMaximumNumberOfSteps(100000);
  stream->SetInputData(0, data);
  stream->SetInputConnection(1, line->GetOutputPort());
  stream->SetInitialIntegrationStep(0.1);
  stream->SetIntegrationStepUnit(1);
  stream->SetIntegratorTypeToRungeKutta4();


//  stream->SetUseIterativeSeeding(true);
  stream->Update();
  stream->GetOutput()->Print(std::cout);

  // 设置输入

  vtkNew<vtkDataSetMapper> streamMapper;
  streamMapper->SetInputConnection(stream->GetOutputPort());
  streamMapper->SetInputArrayToProcess(0,0,0,vtkDataObject::FIELD_ASSOCIATION_POINTS, "velocity");

  streamMapper->SelectColorArray("velocity");
  streamMapper->SetUseLookupTableScalarRange(1);
  streamMapper->SetScalarModeToUsePointFieldData();
  vtkNew<vtkDataSetMapper> waveletMapper;
  waveletMapper->SetInputConnection(torRead->GetOutputPort());
  waveletMapper->SetInputArrayToProcess(0,0,0,vtkDataObject::FIELD_ASSOCIATION_POINTS, "velocity");
  waveletMapper->SetScalarVisibility(1);
  waveletMapper->SelectColorArray("velocity");
  waveletMapper->SetUseLookupTableScalarRange(1);
  waveletMapper->SetScalarModeToUsePointFieldData();
  vtkNew<vtkActor> streamActor;
  streamActor->SetMapper(streamMapper);
  streamActor->GetProperty()->SetColor(0.1, 0.1, 0.1);
//  streamActor->GetProperty()->SetRepresentationToWireframe();
  streamActor->GetProperty()->SetOpacity(0.5);

  vtkNew<vtkActor> waveletActor;
  waveletActor->SetMapper(waveletMapper);
  waveletActor->GetProperty()->SetColor(0.4, 0.4, 0.4);
  waveletActor->GetProperty()->SetOpacity(0.1);
  waveletActor->GetProperty()->SetRepresentationToSurface();

  vtkNew<vtkRenderer> renderer;
  renderer->AddActor(waveletActor);
  renderer->AddActor(streamActor);
  renderer->ResetCamera();
  renderer->SetBackground(1., 1., 1.);

  vtkNew<vtkRenderWindow> renWin;
  renWin->AddRenderer(renderer);
//  renWin->SetMultiSamples(0);
  renWin->SetSize(300, 300);

  vtkNew<vtkRenderWindowInteractor> iren;
  iren->SetRenderWindow(renWin);

  iren->Start();

  return 0;
}

#include "IO/igwStreamReader.h"
#include "IO/igwStreamIO.h"
#include "vtkTable.h"
#include "vtkXMLUnstructuredGridReader.h"
#include "vtkXMLUnstructuredGridWriter.h"
void NacaCellesToVTK(const char* fluentCasName, const char* txtFileName)
{
    vtkSmartPointer<vtkTable> table = DelimitedTextReader(txtFileName);
    // 读取cas文件
//    vtkSmartPointer<vtkUnstructuredGrid> gridData = ReadCASFile(fluentCasName);

    vtkNew<vtkXMLUnstructuredGridReader> reader;
    reader->SetFileName(fluentCasName);
    reader->Update();

    vtkSmartPointer<vtkDataSet> gridData = reader->GetOutput();
    gridData->Print(std::cout);
    ConnetDataWithGrid(table, gridData);

    vtkNew<vtkXMLUnstructuredGridWriter> writer;
    writer->SetInputData(gridData);
    writer->SetFileName("nace_20250331.vtu");
    writer->Update();
    std::cout << "OK" << std::endl;
}

//#include "vtkXMLUnstructuredGridReader.h"
//#include "vtkUnstructuredGridWriter.h"
//void M6SmalToVTK(const char* fluentname, const char* txtFilename)
//{
//    vtkNew<vtkXMLUnstructuredDataReader> reader;
//    reader->SetFileName(fluentname);
//    reader->Update();

//    vtkSmartPointer<vtkDataSet> gridData = reader->GetOutput();
//    gridData->Print(std::cout);
//    ConnetDataWithGrid(table, gridData);

//    vtkNew<vtkXMLUnstructuredGridWriter> writer;
//    writer->SetInputData(gridData);
//    writer->SetFileName("M6_SMALL.vtu");
//    writer->Update();

//}

#include "Externsions/Core/vtkGaussianSurfaceMapper.h"
#include "vtkOpenGLRenderWindow.h"
#include "vtkRenderWindow.h"
void TestGaussianData(const char* plyFileName)
{

    // 设置输入
    using namespace GS;
    vtkNew<vtkGaussianSurfaceMapper> mapper;
    vtkNew<vtkActor> actor;
    actor->SetMapper(mapper);
    vtkNew<vtkRenderer> renderer;
    renderer->AddActor(actor);
    renderer->ResetCamera();
    renderer->SetBackground(1., 1., 1.);

    vtkNew<vtkRenderWindow> renWin;
    renWin->AddRenderer(renderer);
  //  renWin->SetMultiSamples(0);
    renWin->SetSize(800, 800);

    vtkNew<vtkRenderWindowInteractor> iren;
    iren->SetRenderWindow(renWin);

    iren->Start();

    return ;
}

#include <vtkAnimationCue.h>
#include <vtkAnimationScene.h>
#include <vtkCommand.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>

namespace {
class CueAnimator
{
public:
  CueAnimator()
  {
    this->SphereSource = nullptr;
    this->Mapper = nullptr;
    this->Actor = nullptr;
  }

  ~CueAnimator()
  {
    this->Cleanup();
  }

  void StartCue(vtkAnimationCue::AnimationCueInfo* vtkNotUsed(info),
                vtkRenderer* ren)
  {
    vtkNew<vtkNamedColors> colors;

    cout << "*** IN StartCue " << endl;
    this->SphereSource = vtkSphereSource::New();
    this->SphereSource->SetRadius(0.5);

    this->Mapper = vtkPolyDataMapper::New();
    this->Mapper->SetInputConnection(this->SphereSource->GetOutputPort());

    this->Actor = vtkActor::New();
    this->Actor->SetMapper(this->Mapper);
    this->Actor->GetProperty()->SetSpecular(0.6);
    this->Actor->GetProperty()->SetSpecularPower(30);
    this->Actor->GetProperty()->SetColor(
        colors->GetColor3d("Peacock").GetData());

    ren->AddActor(this->Actor);
    ren->ResetCamera();
    ren->Render();
  }

  void Tick(vtkAnimationCue::AnimationCueInfo const* info, vtkRenderer* ren)
  {
    double newradius = 0.1 +
        (static_cast<double>(info->AnimationTime - info->StartTime) /
         static_cast<double>(info->EndTime - info->StartTime)) *
            1;
    this->SphereSource->SetRadius(newradius);
    this->SphereSource->Update();
    ren->Render();
  }

  void EndCue(vtkAnimationCue::AnimationCueInfo* vtkNotUsed(info),
              vtkRenderer* ren)
  {
    // (void)ren;
    // don't remove the actor for the regression image.
    //      ren->RemoveActor(this->Actor);
    this->Cleanup();
  }

protected:
  vtkSphereSource* SphereSource;
  vtkPolyDataMapper* Mapper;
  vtkActor* Actor;

  void Cleanup()
  {
    if (this->SphereSource != nullptr)
    {
      this->SphereSource->Delete();
      this->SphereSource = nullptr;
    }

    if (this->Mapper != nullptr)
    {
      this->Mapper->Delete();
      this->Mapper = nullptr;
    }
    if (this->Actor != nullptr)
    {
      this->Actor->Delete();
      this->Actor = nullptr;
    }
  }
};

class vtkAnimationCueObserver : public vtkCommand
{
public:
  static vtkAnimationCueObserver* New()
  {
    return new vtkAnimationCueObserver;
  }

  virtual void Execute(vtkObject* vtkNotUsed(caller), unsigned long event,
                       void* calldata)
  {
    if (this->Animator != nullptr && this->Renderer != nullptr)
    {
      vtkAnimationCue::AnimationCueInfo* info =
          static_cast<vtkAnimationCue::AnimationCueInfo*>(calldata);
      switch (event)
      {
      case vtkCommand::StartAnimationCueEvent:
        this->Animator->StartCue(info, this->Renderer);
        break;
      case vtkCommand::EndAnimationCueEvent:
        this->Animator->EndCue(info, this->Renderer);
        break;
      case vtkCommand::AnimationCueTickEvent:
        this->Animator->Tick(info, this->Renderer);
        break;
      }
    }
    if (this->RenWin != nullptr)
    {
      this->RenWin->Render();
    }
  }

  vtkRenderer* Renderer;
  vtkRenderWindow* RenWin;
  CueAnimator* Animator;

protected:
  vtkAnimationCueObserver()
  {
    this->Renderer = nullptr;
    this->Animator = nullptr;
    this->RenWin = nullptr;
  }
};
} // namespace

void testAnimationActors()
{
  vtkNew<vtkNamedColors> colors;

  // Create the graphics structure. The renderer renders into the
  // render window.
  vtkNew<vtkRenderWindowInteractor> iren;
  vtkNew<vtkRenderer> ren1;
  vtkNew<vtkRenderWindow> renWin;
  renWin->SetMultiSamples(0);
  renWin->SetWindowName("AnimationScene");

  iren->SetRenderWindow(renWin);
  renWin->AddRenderer(ren1);
  ren1->SetBackground(colors->GetColor3d("MistyRose").GetData());
  renWin->Render();

  // Create an Animation Scene
  vtkNew<vtkAnimationScene> scene;

  scene->SetModeToRealTime();
  // scene->SetModeToSequence();

  scene->SetLoop(0);
  scene->SetFrameRate(5);
  scene->SetStartTime(3);
  scene->SetEndTime(20);

  // Create an Animation Cue.
  vtkNew<vtkAnimationCue> cue1;
  cue1->SetStartTime(5);
  cue1->SetEndTime(23);
  scene->AddCue(cue1);

  // Create cue animator;
  CueAnimator animator;

  // Create Cue observer.
  vtkNew<vtkAnimationCueObserver> observer;
  observer->Renderer = ren1;
  observer->Animator = &animator;
  observer->RenWin = renWin;

  cue1->AddObserver(vtkCommand::StartAnimationCueEvent, observer);
  cue1->AddObserver(vtkCommand::EndAnimationCueEvent, observer);
  cue1->AddObserver(vtkCommand::AnimationCueTickEvent, observer);


  scene->Play();
  scene->Stop();
  iren->Start();


  return ;
}

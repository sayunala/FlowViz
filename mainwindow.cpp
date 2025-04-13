
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMainWindow>
#include <QSurfaceFormat>
#include <QVTKOpenGLNativeWidget.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkNamedColors.h>
#include <vtkProperty.h>
#include <vtkSmartPointer.h>
#include <vtkUnstructuredGrid.h>
#include <vtkUnstructuredGridReader.h>
#include <vtkGPUVolumeRayCastMapper.h>
#include <vtkMapper.h>
#include <vtkView.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkLookupTable.h>
#include <iostream>
#include <vtkRenderView.h>
#include "vtkUnstructuredGridReader.h"
#include "vtkStructuredGridReader.h"
#include "vtkUnstructuredGrid.h"
#include "vtkStructuredGrid.h"
#include "vtkSTLReader.h"
#include "vtkGeometryFilter.h"
#include "vtkPointData.h"
#include "vtkAppendFilter.h"
#include "vtkEventQtSlotConnect.h"
#include "vtkDataObject.h"
#include "vtkOBJReader.h"
#include "vtkOpenGLState.h"
//-------------------Representation------------------------
#include "Representation/igwRenderView.h"
#include "Representation/igwIsoSurfaceRepresentation.h"
#include "Representation/igwCloudMapRepresentation.h"
#include "Representation/igwRenderViewbase.h"
#include "Representation/igwIsoSurfaceRepresentation.h"
#include "Representation/igwVortexRepresentation.h"
#include "Representation/igwFlowingStreamLinesRepresentation.h"
#include "Representation/igwStreamLinesRepresentation.h"
#include "Representation/igwStreamSurfaceRepresentation.h"
#include "Representation/igwVolumeRepresentation.h"
#include "Representation/igwMeshRepresentation.h"

#include "Representation/igwOutLineRepresentation.h"
#include "Representation/igwRenderedSurfaceRepresentation.h"
#include "Representation/vtkStreamLinesMapper.h"
#include "Representation/igwRealTimeModel2D.h"
#include "Representation/igwTextureRepresentation.h"
#include "Representation/igwClipRepresentation.h"
#include "Representation/igwRealTimeModel2DRepresentation.h"

//-------------------Representation Widget------------------------
#include "ColorMap/igwColorMapEditorWidget.h"
#include "ColorMap/igwColorMapManager.h"

#include "RepresentationWidget/RepresentationDialog.h"
#include "RepresentationWidget/igwCloudMapRepresentationDialog.h"
#include "RepresentationWidget/RepresentationDialog.h"
#include "RepresentationWidget/igwStreamLinesRepresentationWidget.h"
#include "RepresentationWidget/igwFlowingStreamRepWidget.h"
#include "RepresentationWidget/igwIsoSurfaceRepresentationWidget.h"
#include "RepresentationWidget/igwCloudMapRepresentationWidget.h"
#include "RepresentationWidget/igwTextureRepresentationWidget.h".h"
#include "RepresentationWidget/igwMeshRepresentationWidget.h"

//-------------------Other------------------------
#include "IO/igwStreamReader.h"
#include "igwCommand.h"
#include "vtkAutoInit.h"
#include "vtkCamera.h"
#include "vtkXMLUnstructuredGridReader.h"
#include "Components/igwActiveObjects.h"
#include "Widgets/igwCameraToolBar.h"
#include "Components/igwVCRToolBar.h"
#include "Widgets/igwAnimationTimeToolBar.h"
#include "Components/igwSpreadSheet.h"
#include "Widgets/igwFileReaction.h"
#include "Externsions/Core/vtkGaussianSurfaceMapper.h"

//#include "Externsions/XrInterface/igwXRInterfaceDockWidget.h"
#include "Core/igwApplicationCore.h"
#include <QMessageBox>
#include <QTimer>
VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkInteractionStyle)
VTK_MODULE_INIT(vtkRenderingVolumeOpenGL2)
VTK_MODULE_INIT(vtkRenderingFreeType)
VTK_MODULE_INIT(vtkRenderingContextOpenGL2)

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("FlowViz");
    InitAction();
    InitColorMapWidget();
    QSurfaceFormat::setDefaultFormat(QVTKOpenGLNativeWidget::defaultFormat());
    vtkNew<vtkNamedColors> colors;

    renderer = vtkSmartPointer<vtkRenderer>::New();

//    renderer->SetBackground(colors->GetColor3d("SteelBlue").GetData());

    renderer->SetBackground(colors->GetColor3d("White").GetData());
    renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();


    renderWindow->AddRenderer(renderer);
    renderWindow->SetWindowName("RenderWindowNoUIFile");


    // init ToolBar
    QToolBar* Toolbar = new igwCameraToolBar(this);
    this->addToolBar(Toolbar);
    this->addToolBarBreak();
    QToolBar* AnimationToolBar = new igwVCRToolBar(this);
    this->insertToolBar(Toolbar, AnimationToolBar);
    QToolBar* AnimationTimeToolBar = new igwAnimationTimeToolBar(this);
    this->insertToolBar(AnimationToolBar, AnimationTimeToolBar);

    //End init ToolBar

    view->SetRenderWindow(renderWindow);
    view->SetRenderer(renderer);
    ui->openGLWidget->setRenderWindow(renderWindow);

    //-------------------龙卷风数据------------------------


    //-------------------naca数据------------------------
//    vtkSmartPointer<vtkDataSet>  data = ConstructDataset("2D_Data/result_alldata.etkf", "2D_Data/fluent_naca0012.etkfg");
//    vtkSmartPointer<vtkDataSet> naca_wing = ConstrucNACA0012DataSet("2D_Data/NACA0012_Wing_Data.csv");


    // 设置当前的视图、数据源
//    igwActiveObjects::GetInstance().SetActiveView(view);
//    igwActiveObjects::GetInstance().SetActiveData(data);

//    vtkDataArray* array = data->GetPointData()->GetArray("velocity");
//    array->Print(std::cout);

    // 设置输入数据

//    realTimeModel2DRep->SetInputData(naca_wing);


//    igwColorMapManager::GetInstance()->SetRange(array->GetRange(-1));
    igwColorMapManager::GetInstance()->ApplyPreset("Cool to Warm");
    igwColorMapManager::GetInstance()->GetColorFunction()->SetVectorModeToMagnitude();

    // 设置颜色映射表
//    realTimeModel2DRep->SetLookupTable(igwColorMapManager::GetInstance()->GetColorFunction());
    meshRep->SetLookupTable(igwColorMapManager::GetInstance()->GetColorFunction());

//    realTimeModel2DRep->SetDataSet(naca_wing);



//    realTimeModel2DRep->SetInputArrayToProcess(0, 0, 0, vtkDataObject::FIELD_ASSOCIATION_POINTS, "cp");
    meshRep->SetInputArrayToProcess(0, 0, 0, vtkDataObject::FIELD_ASSOCIATION_CELLS, "press");
//    view->AddRepresentation(rep2);
//    realTimeModel2DRep->Update();
//    view->AddRepresentation(realTimeModel2DRep);



    view->GetRenderer()->GetActiveCamera()->Zoom(3);
    view->GetRenderer()->GetActiveCamera()->SetFocalPoint(0.1, 0, 0);

    view->Render();

    ui->groupBox->hide();
    ui->InformationDock->hide();
    ui->menu->removeAction(ui->actionmesh);
    ui->menu->removeAction(ui->actionGaussianSplatting);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitColorMapWidget()
{
    ColorMapEditorWidget = new igwColorMapEditorWidget;
    QObject::connect(this->ColorMapEditorWidget, SIGNAL(ChangedFinished()), this, SLOT(ReRender()));
    ui->ColorMapDockWidget->setWidget(ColorMapEditorWidget);


//    ui->ColorMapDockWidget->hide();
}

void MainWindow::InitAction()
{
    QObject::connect(ui->actioncloud, &QAction::triggered, this, &MainWindow::showCloudDialog);
    QObject::connect(ui->actionstreamlines, &QAction::triggered, this, &MainWindow::showStreamDialog);
    QObject::connect(ui->actionflowingstream, &QAction::triggered, this, &MainWindow::showFlowingStreamDialog);
    QObject::connect(ui->actionisosurface, &QAction::triggered, this, &MainWindow::showIsoSurfaceDialog);
    QObject::connect(ui->actionTexture, &QAction::triggered, this, &MainWindow::showTextureDialog);
    QObject::connect(ui->actionmesh, &QAction::triggered, this, &MainWindow::showMesh);
    QObject::connect(ui->actionVolume, &QAction::triggered, this, &MainWindow::showVolumeDialog);
    QObject::connect(ui->actionSpreadSheet, &QAction::triggered, this, &MainWindow::ShowSpreadSheet);
    QObject::connect(ui->actionVotex, &QAction::triggered, this, &MainWindow::showVortexDialog);
    QObject::connect(ui->actionclip, &QAction::triggered, this, &MainWindow::showClip);
    QObject::connect(ui->toolButton, SIGNAL(validColorChosen(const QColor&)), this, SLOT(ColorChosen(QColor)));

    ui->spreadSheetDockWidget->hide();


    igwFileReaction* fileAction = new igwFileReaction(ui->actionOpenFile);
    QObject::connect(fileAction, &igwFileReaction::loadedData, ui->DataTree, &igwDataTreeWidget::onLoadData);


}

void MainWindow::StartClock()
{
    timer = new QTimer(this);
    timer->setInterval(1);

    QObject::connect(timer, &QTimer::timeout, this, &MainWindow::UpdateMeshData);
    timer->start();
}

void MainWindow::UpdateMeshData()
{
    double pre[25] = {
        1,2,3,4,5,
        6,7,8,9,10,
        11,12,13,14,15,
        16,17,18,19,20,
        21,22,23,24,25
    };
    for(int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            pre[i*5+j] += rand();
        }
    }
    view->InvokeEvent(iGreatWorks::MeshDataUpdateEvent, pre);
}
void MainWindow::ReRender(){
//    this->renderer->ResetCamera();

    this->renderWindow->Render();

}

void MainWindow::showCloudDialog()
{
    RepresentationDialog* dialog = new RepresentationDialog(this);

    igwCloudMapRepresentationWidget* widget = new igwCloudMapRepresentationWidget(dialog);

    // 创建新的云图
    vtkNew<igwCloudMapRepresentation> cloudRep;
    cloudRep->SetLookupTable(igwColorMapManager::GetInstance()->GetColorFunction());
    cloudRep->SetObjectName("Cloud Representation");
    if (!ui->DataTree->onAddRepresentation(cloudRep))
    {
      QMessageBox msgBox;
      msgBox.setIcon(QMessageBox::Information);
      msgBox.setText(QString::fromLocal8Bit("警告"));
      msgBox.setInformativeText(QString::fromLocal8Bit("没有选中数据"));
      msgBox.setWindowTitle(QString::fromLocal8Bit("警告"));
      msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
      msgBox.exec();
      return ;
    }
    cloudRep->SetDataType(THREE_D);
    cloudRep->SetInputArrayToProcess(0, 0, 0, vtkDataObject::FIELD_ASSOCIATION_POINTS, "velocity");
    cloudRep->Update();

    widget->SetigwCloudMapRepresentation(cloudRep);
    dialog->AddWidget(widget, "Setting");
    QObject::connect(dialog, SIGNAL(SettingApplied()), widget, SLOT(ApplySetting()));
    QObject::connect(widget, SIGNAL(Applied()), this, SLOT(ReRender()));
    dialog->show();
    this->ReRender();
}

void MainWindow::showStreamDialog()
{
    RepresentationDialog* dialog = new RepresentationDialog(this);

    igwStreamLinesRepresentationWidget* widget = new igwStreamLinesRepresentationWidget(dialog);

    vtkNew<igwStreamLinesRepresentation> streamRep;
    streamRep->SetLookupTable(igwColorMapManager::GetInstance()->GetColorFunction());
    streamRep->SetObjectName("Stream Lines");
    if (!ui->DataTree->onAddRepresentation(streamRep))
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText(QString::fromLocal8Bit("警告"));
        msgBox.setInformativeText(QString::fromLocal8Bit("没有选中数据"));
        msgBox.setWindowTitle(QString::fromLocal8Bit("警告"));
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.exec();
        return ;
    }

//    streamRep->SetInputArrayToProcess(0, 0, 0, vtkDataObject::FIELD_ASSOCIATION_POINTS, "velocity");
    streamRep->Update();

    // 连接dialog ok 按钮 与 widget 设置更新
    QObject::connect(dialog, SIGNAL(SettingApplied()), widget, SLOT(ApplySetting()));
    QObject::connect(widget, SIGNAL(Applied()), this, SLOT(ReRender()));

    widget->SetRepresentation(streamRep);
    dialog->AddWidget(widget, "Setting");

    dialog->show();

}

void MainWindow::showFlowingStreamDialog()
{

    RepresentationDialog* dialog = new RepresentationDialog(this);

    igwFlowingStreamRepWidget* widget = new igwFlowingStreamRepWidget(dialog);

    //新建一个flowingstream
    vtkNew<igwFlowingStreamLinesRepresentation> flowRep;
    flowRep->SetLookupTable(igwColorMapManager::GetInstance()->GetColorFunction());
    flowRep->SetObjectName("Flowing Stream");
    if (!ui->DataTree->onAddRepresentation(flowRep))
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText(QString::fromLocal8Bit("警告"));
        msgBox.setInformativeText(QString::fromLocal8Bit("没有选中数据"));
        msgBox.setWindowTitle(QString::fromLocal8Bit("警告"));
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.exec();
        return ;
    }

//    flowRep->SetInputArrayToProcess(0, 0, 0, vtkDataObject::FIELD_ASSOCIATION_POINTS, "velocity");


    QObject::connect(dialog, SIGNAL(SettingApplied()), widget, SLOT(ApplySetting()));

    QObject::connect(widget, SIGNAL(Applied()), this, SLOT(ReRender()));

    widget->SetRepresentation(flowRep);

    dialog->AddWidget(widget, "Setting");
    dialog->show();
}

void MainWindow::showIsoSurfaceDialog()
{
    RepresentationDialog* dialog = new RepresentationDialog(this);

    igwIsoSurfaceRepresentationWidget* widget = new igwIsoSurfaceRepresentationWidget(dialog);

      // 创建新的等值面Representation
    vtkNew<igwIsoSurfaceRepresentation> isoRep;
    isoRep->SetLookupTable(igwColorMapManager::GetInstance()->GetColorFunction());
    isoRep->SetObjectName("IsoSurface");
    if (!ui->DataTree->onAddRepresentation(isoRep))
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText(QString::fromLocal8Bit("警告"));
        msgBox.setInformativeText(QString::fromLocal8Bit("没有选中数据"));
        msgBox.setWindowTitle(QString::fromLocal8Bit("警告"));
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.exec();
        return ;
    }

//    isoRep->SetInputArrayToProcess(0, 0, 0, vtkDataObject::FIELD_ASSOCIATION_POINTS, "velocity");
    isoRep->Update();

//    isoSurfaceRepresentation->SetInputConnection(torRead->GetOutputPort());
    //isoSurfaceRepresentation->Update();
    //view->AddRepresentation(isoSurfaceRepresentation);

    QObject::connect(dialog, SIGNAL(SettingApplied()), widget, SLOT(ApplySetting()));
    QObject::connect(widget, SIGNAL(Applied()), this, SLOT(ReRender()));

    widget->SetRepresentation(isoRep);
    dialog->AddWidget(widget, "Setting");

    dialog->show();

}

void MainWindow::showTextureDialog()
{
    RepresentationDialog* dialog = new RepresentationDialog(this);

    igwTextureRepresentationWidget* widget = new igwTextureRepresentationWidget(dialog);

    // 创建新的纹理Representation
    vtkNew<igwTextureRepresentation> Rep;
    Rep->SetLookupTable(igwColorMapManager::GetInstance()->GetColorFunction());
    Rep->SetObjectName("Texture");
    if (!ui->DataTree->onAddRepresentation(Rep))
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText(QString::fromLocal8Bit("警告"));
        msgBox.setInformativeText(QString::fromLocal8Bit("没有选中数据"));
        msgBox.setWindowTitle(QString::fromLocal8Bit("警告"));
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.exec();
        return ;
    }

//    Rep->SetInputArrayToProcess(0, 0, 0, vtkDataObject::FIELD_ASSOCIATION_POINTS, "velocity");
    Rep->Update();

    widget->SetRepresentation(Rep);
    dialog->AddWidget(widget, "Setting");
    QObject::connect(dialog, SIGNAL(SettingApplied()), widget, SLOT(ApplySetting()));
    QObject::connect(widget, SIGNAL(Applied()), this, SLOT(ReRender()));
    dialog->show();
    this->ReRender();

}

void MainWindow::showMesh()
{

    RepresentationDialog* dialog = new RepresentationDialog(this);

    igwMeshRepresentationWidget* widget = new igwMeshRepresentationWidget(dialog);


    view->AddRepresentation(meshRep);

    widget->SetRepresentation(meshRep);
    dialog->AddWidget(widget, "Setting");
    QObject::connect(dialog, SIGNAL(SettingApplied()), widget, SLOT(ApplySetting()));
    QObject::connect(widget, SIGNAL(Applied()), this, SLOT(ReRender()));

    EventsQSlotConnect->Connect(view->GetRenderWindow()->GetInteractor(),
                        iGreatWorks::MeshDataUpdateEvent,
                        widget,
                        SLOT(UpdateMeshTableWidget(vtkObject*, unsigned long, void*, void*)));
    dialog->show();
    this->ReRender();

}

void MainWindow::showVolumeDialog()
{
//    RepresentationDialog* dialog = new RepresentationDialog(this);

//    igwTextureRepresentationWidget* widget = new igwTextureRepresentationWidget(dialog);

    // 创建新的纹理Representation
    vtkNew<igwVolumeRepresentation> Rep;
    Rep->SetLookupTable(igwColorMapManager::GetInstance()->GetColorFunction());
    Rep->SetObjectName("Volume");
    if (!ui->DataTree->onAddRepresentation(Rep))
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText(QString::fromLocal8Bit("警告"));
        msgBox.setInformativeText(QString::fromLocal8Bit("没有选中数据"));
        msgBox.setWindowTitle(QString::fromLocal8Bit("警告"));
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.exec();
        return ;
    }

//    Rep->SetInputArrayToProcess(0, 0, 0, vtkDataObject::FIELD_ASSOCIATION_POINTS, "velocity");
    Rep->Update();

//    widget->SetRepresentation(Rep);
//    dialog->AddWidget(widget, "Setting");
//    QObject::connect(dialog, SIGNAL(SettingApplied()), widget, SLOT(ApplySetting()));
//    QObject::connect(widget, SIGNAL(Applied()), this, SLOT(ReRender()));
//    dialog->show();
    this->ReRender();
}

void MainWindow::showVortexDialog()
{
    vtkNew<igwVortexRepresentation> Rep;
    Rep->SetLookupTable(igwColorMapManager::GetInstance()->GetColorFunction());
    Rep->SetObjectName("Vortex");
    if (!ui->DataTree->onAddRepresentation(Rep))
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText(QString::fromLocal8Bit("警告"));
        msgBox.setInformativeText(QString::fromLocal8Bit("没有选中数据"));
        msgBox.setWindowTitle(QString::fromLocal8Bit("警告"));
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.exec();
        return ;
    }

//    Rep->SetInputArrayToProcess(0, 0, 0, vtkDataObject::FIELD_ASSOCIATION_POINTS, "velocity");
    Rep->Update();

//    widget->SetRepresentation(Rep);
//    dialog->AddWidget(widget, "Setting");
//    QObject::connect(dialog, SIGNAL(SettingApplied()), widget, SLOT(ApplySetting()));
//    QObject::connect(widget, SIGNAL(Applied()), this, SLOT(ReRender()));
//    dialog->show();
    this->ReRender();
}

void MainWindow::ShowSpreadSheet()
{
    igwSpreadSheet *sheet = new igwSpreadSheet(this);


    ui->spreadSheetDockWidget->setWidget(sheet);
    ui->spreadSheetDockWidget->show();

}

void MainWindow::showClip()
{
    vtkNew<igwClipRepresentation> cloudRep;
    cloudRep->SetLookupTable(igwColorMapManager::GetInstance()->GetColorFunction());
    cloudRep->SetObjectName("clip Representation");
    if (!ui->DataTree->onAddRepresentation(cloudRep))
    {
      QMessageBox msgBox;
      msgBox.setIcon(QMessageBox::Information);
      msgBox.setText(QString::fromLocal8Bit("警告"));
      msgBox.setInformativeText(QString::fromLocal8Bit("没有选中数据"));
      msgBox.setWindowTitle(QString::fromLocal8Bit("警告"));
      msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
      msgBox.exec();
      return ;
    }

    cloudRep->SetInputArrayToProcess(0, 0, 0, vtkDataObject::FIELD_ASSOCIATION_POINTS, "velocity");
    cloudRep->Update();
    this->ReRender();
}


void MainWindow::on_RealTime2D_clicked()
{
    double pre[222] = {
          0.08920933, -0.07162736, -0.19423686 ,-0.28529796 ,-0.35396457, -0.39996326,
         -0.43600488, -0.47661805, -0.5283892  ,-0.5992097  ,-0.71844035, -0.8730517 ,
         -1.0900259 , -1.3888068 , -1.8590574  ,-2.3295422  ,-2.7432199 , -3.0711665 ,
         -3.2119565 , -3.168397  , -3.0460806  ,-2.9127908  ,-2.7453423 , -2.3867168 ,
         -1.7880151 , -1.080547  , -0.5320641  ,-0.3390721  ,-0.2963361 , -0.16839069,
         -0.02747768,  0.04814422,  0.02723449 ,-0.0569005  ,-0.20029831, -0.44178465,
         -0.6202183 , -0.6881325 , -0.72430885 ,-0.66581213 ,-0.5698936 , -0.49100822,
         -0.44435525, -0.42792147, -0.40790695 ,-0.39245793 ,-0.3839183 , -0.3816026 ,
         -0.38591725, -0.39283842, -0.40527308 ,-0.41888633 ,-0.43536374, -0.45099363,
         -0.46646836, -0.4813031 , -0.49644065 ,-0.50898427 ,-0.52065265, -0.53075564,
         -0.5401121 , -0.5490029 , -0.55591846 ,-0.56177664 ,-0.568467  , -0.573964  ,
         -0.57899535, -0.58443654, -0.5887859  ,-0.59375894 ,-0.5976553 , -0.6035049 ,
         -0.6087439 , -0.61341923, -0.6205789  ,-0.6255201  ,-0.6316661 , -0.6385765 ,
         -0.64529437, -0.65204394, -0.6598811  ,-0.6677844  ,-0.67535484, -0.6840496 ,
         -0.6924813 , -0.70170516, -0.7105384  ,-0.7204756  ,-0.7302009 , -0.7404888 ,
         -0.7513894 , -0.7612187 , -0.77407885 ,-0.7853977  ,-0.79638743, -0.810503  ,
         -0.8223948 , -0.8361468 , -0.84919554 ,-0.8631303  ,-0.87774366, -0.8912227 ,
         -0.90423155, -0.9167915 , -0.9277914  ,-0.9361105  ,-0.94192314, -0.93920755,
         -0.94391537, -0.9242208 , -0.94984144 ,-0.9739618  ,-0.90792423, -0.8080685 ,
         -0.75407606, -0.7016703 , -0.6680073  ,-0.63767666 ,-0.6166434 , -0.5954131 ,
         -0.5774217 , -0.5616655 , -0.5487098  ,-0.5372959  ,-0.52323455, -0.5188399 ,
         -0.50859994, -0.4949008 , -0.49448806 ,-0.4846759  ,-0.47626194, -0.47078794,
         -0.46750164, -0.4593591 , -0.45737803 ,-0.4489635  ,-0.4453661 , -0.44401777,
         -0.4377907 , -0.43606675, -0.42988852 ,-0.4280507  ,-0.42771235, -0.42160934,
         -0.42031714, -0.4176349 , -0.41408357 ,-0.4141925  ,-0.40980405, -0.40943557,
         -0.40588015, -0.4045854 , -0.40406197 ,-0.39901406 ,-0.3987987 , -0.39975882,
         -0.3956452 , -0.39595658, -0.39309803 ,-0.39129236 ,-0.39086568, -0.38828003,
         -0.388175  , -0.38433695, -0.38469416 ,-0.3814128  ,-0.38083485, -0.37798318,
         -0.376477  , -0.37211362, -0.3682257  ,-0.36758953 ,-0.3650545 , -0.3592757 ,
         -0.355142  , -0.353025  , -0.34572595 ,-0.34325022 ,-0.3363436 , -0.32787174,
         -0.321663  , -0.31545562, -0.30555105 ,-0.29681998 ,-0.2858466 , -0.27230248,
         -0.2598176 , -0.24689873, -0.23300816 ,-0.21370292 ,-0.19186977, -0.17274114,
         -0.1521058 , -0.12290084, -0.0942177  ,-0.06360035 ,-0.02794327,  0.00898577,
          0.05203542,  0.10648435,  0.16063154 , 0.21504168 , 0.28119582,  0.36309713,
          0.45846057,  0.55857885,  0.6504261  , 0.783512   , 1.0041054 ,  1.1467781 ,
          1.1778861 ,  1.1839861 ,  1.1803082  , 1.1622196  , 1.1321429 ,  1.0748675 ,
          0.99752045,  0.8944379 ,  0.7567822  , 0.5910521  , 0.41252637,  0.24461377
    };

    view->InvokeEvent(iGreatWorks::RealTimeModelUpdateEvent, pre);
}


void MainWindow::on_MeshDataUpdate_clicked()
{
//    double pre[25] = {
//        1,2,3,4,5,
//        6,7,8,9,10,
//        11,12,13,14,15,
//        16,17,18,19,20,
//        21,22,23,24,25
//    };
//    for(int i = 0; i < 5; ++i)
//    {
//        for (int j = 0; j < 5; ++j)
//        {
//            pre[i*5+j] += rand();
//        }
//    }
//    view->InvokeEvent(iGreatWorks::MeshDataUpdateEvent, pre);
    this->StartClock();
}

void MainWindow::on_PosX_clicked()
{
    view->ResetActiveCameraToDirection(1, 0, 0, 0, 0, 1);
}

void MainWindow::on_NegX_clicked()
{
    view->ResetActiveCameraToDirection(-1, 0, 0, 0, 0, 1);
}

void MainWindow::on_PosY_clicked()
{
    view->ResetActiveCameraToDirection(0, 1, 0, 0, 0, 1);
}

void MainWindow::on_NegY_clicked()
{
    view->ResetActiveCameraToDirection(0, -1, 0, 0, 0, 1);
}

void MainWindow::on_PosZ_clicked()
{
    view->ResetActiveCameraToDirection(0, 0, 1, 0, 1, 0);
}

void MainWindow::on_NegZ_clicked()
{
    view->ResetActiveCameraToDirection(0, 0, -1, 0, 1, 0);
}

void MainWindow::ColorChosen(const QColor & color)
{
    int r,g,b;
    double c[3] = {color.redF(), color.greenF(), color.blueF()};
    view->SetBackGroundColor(c);

}


void MainWindow::on_pushButton_clicked()
{
    vtkSmartPointer<vtkDataSet>  data = ConstructDataset("2D_Data/result_alldata1.txt", "2D_Data/fluent_naca0012.cas");
    igwActiveObjects::GetInstance().SetActiveData(data);
    view->InvokeEvent(iGreatWorks::ETKFDataUpdateEvent, data);
}


void MainWindow::on_actionColorMap_triggered()
{
    ui->ColorMapDockWidget->show();
}


void MainWindow::on_actionGaussianSplatting_triggered()
{
    using namespace GS;
    vtkNew<vtkGaussianSurfaceMapper> mapper;
    vtkNew<vtkOBJReader>  reader;
    reader->SetFileName("2D_Data/sugarfine_3Dgs7000_densityestim02_sdfnorm02_level03_decim200000_normalconsistency01_gaussperface6.obj");
    mapper->SetInputConnection(reader->GetOutputPort());
    vtkNew<vtkActor> actor;
    actor->SetMapper(mapper);
    this->renderer->AddActor(actor);
    this->renderWindow->Render();
}




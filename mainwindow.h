#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vtkStructuredGridReader.h>
#include <vtkUnstructuredGridReader.h>
#include "vtkSmartPointer.h"
#include "Representation/igwStreamLinesRepresentation.h"
#include <QTimer>
class vtkGenericOpenGLRenderWindow;
class vtkRenderer;
class igwColorMapEditorWidget;
class igwCloudMapRepresentation;
class igwFlowingStreamLinesRepresentation;
class igwIsoSurfaceRepresentation;
class igwRealTimeModel2DRepresentation;
class igwStreamSurfaceRepresentation;
class igwVolumeRepresentation;
class igwTextureRepresentation;
class igwMeshRepresentation;
class vtkEventQtSlotConnect;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected slots:
    /**
     * @brief ReRender: 刷线QVTKWidget的槽函数
     */
    void ReRender();

    void showCloudDialog();

    void showStreamDialog();

    void showFlowingStreamDialog();

    void showIsoSurfaceDialog();

    void showTextureDialog();

    void showMesh();

    void showVolumeDialog();

    void showVortexDialog();

    void ShowSpreadSheet();

    void showClip();

private slots:
    void on_RealTime2D_clicked();

    void on_MeshDataUpdate_clicked();

    //-------------------重置相机------------------------
    void on_PosX_clicked();

    void on_NegX_clicked();

    void on_PosY_clicked();

    void on_NegY_clicked();

    void on_PosZ_clicked();

    void on_NegZ_clicked();

    void ColorChosen(const QColor&);

    void UpdateMeshData();
    void on_pushButton_clicked();

    void on_actionColorMap_triggered();



    void on_actionGaussianSplatting_triggered();

private:
    void InitColorMapWidget();
    void InitAction();

    void StartClock();

    Ui::MainWindow *ui;
    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow;


    vtkNew<igwMeshRepresentation> meshRep;

    vtkNew<igwRealTimeModel2DRepresentation> realTimeModel2DRep;

    vtkNew<igwRenderView> view;
    vtkNew<vtkUnstructuredGridReader> read;
    vtkNew<vtkStructuredGridReader> torRead;
    igwColorMapEditorWidget* ColorMapEditorWidget;

    vtkNew<vtkEventQtSlotConnect> EventsQSlotConnect;

    QTimer* timer;
};
#endif // MAINWINDOW_H

QT       += core gui
QT += opengl
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += console
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
QMAKE_CXXFLAGS+= -openmp
QMAKE_LFLAGS +=  -openmp
SOURCES += \
    ColorMap/igwColorMapCore.cpp \
    ColorMap/igwColorMapEditorWidget.cpp \
    ColorMap/igwColorMapManager.cpp \
    ColorMap/igwCoreUtilities.cxx \
    ColorMap/igwPresetDialog.cpp \
    ColorMap/igwPresetGroupsManager.cxx \
    ColorMap/igwPresetToPixmap.cpp \
    ColorMap/igwTimer.cxx \
    ColorMap/igwTransferFunctionPresets.cpp \
    ColorMap/igwTransferFunctionWidget.cxx \
    ColorMap/vtkPVColorTransferControlPointsItem.cxx \
    Components/igwActiveObjects.cpp \
    Components/igwAnimationManager.cpp \
    Components/igwAnimationScene.cpp \
    Components/igwAnimationTimeWidget.cpp \
    Components/igwDataTreeModel.cpp \
    Components/igwDataTreeWidget.cpp \
    Components/igwInformationWidget.cpp \
    Components/igwMultiViewWidget.cpp \
    Components/igwSpreadSheet.cpp \
    Components/igwSpreadSheetModel.cpp \
    Components/igwTimeKeeper.cpp \
    Components/igwTimeStepsAnimation.cpp \
    Components/igwTreeItem.cpp \
    Components/igwVCRControl.cpp \
    Components/igwVCRToolBar.cpp \
    Components/igwView.cpp \
    Components/igwViewFrame.cpp \
    Components/igwVtkView.cpp \
    Components/igwVtkWidget.cpp \
    Components/vtkAnimationPlayer.cpp \
    Components/vtkTimestepsAnimationPlayer.cpp \
    Core/igwViewManager.cpp \
    Externsions/Core/vtkGaussianSplattionPlyReader.cpp \
    Externsions/Core/vtkGaussianSurfaceMapper.cpp \
    Externsions/Core/vtkGaussinSplattingMapper.cpp \
    Externsions/Sources/vtkDataObjectMeshCache.cxx \
    Externsions/Sources/vtkGridSource.cxx \
    Externsions/Sources/vtkHyperTreeGridFeatureEdges.cxx \
    Externsions/Sources/vtkLidarGridActor.cxx \
    Externsions/Sources/vtkPVGeometryFilter.cxx \
    Externsions/Sources/vtkPVTrivialProducer.cxx \
    Externsions/XrInterface/igwXRInterfaceHelper.cpp \
    IO/igwCSVWriter.cpp \
    IO/igwIOCore.cpp \
    IO/igwReadCGNSFile.cpp \
    IO/igwReadFile.cpp \
    IO/igwReadFileFactory.cpp \
    IO/igwReadOpenFOAMFile.cpp \
    IO/igwReadSeriesFiles.cpp \
    IO/igwReadVtkFile.cpp \
    IO/igwReadeXMLMultiBlockFile.cpp \
    IO/igwStreamIO.cpp \
    IO/igwStreamReader.cpp \
    Representation/igwClipRepresentation.cpp \
    Representation/igwCloudMapRepresentation.cpp \
    Representation/igwMeshRepresentation.cpp \
    Representation/igwRealTimeModel2D.cpp \
    Representation/igwRealTimeModel2DRepresentation.cpp \
    Representation/igwRenderRepObserver.cpp \
    Representation/igwStreamSurfaceRepresentation.cpp \
    Representation/igwTextureRepresentation.cpp \
    Representation/igwVolumeRepresentation.cpp \
    RepresentationWidget/RepresentationDialog.cpp \
    RepresentationWidget/igwCloudMapRepresentationDialog.cpp \
    Representation/igwFlowingStreamLinesRepresentation.cpp \
    Representation/igwIsoSurfaceRepresentation.cpp \
    Representation/igwOutLineRepresentation.cpp \
    Representation/igwRenderView.cpp \
    Representation/igwRenderedRepresentation.cpp \
    Representation/igwRenderedSurfaceRepresentation.cpp \
    Representation/igwStreamLinesRepresentation.cpp \
    Representation/igwVortexRepresentation.cpp \
    Representation/igwRenderViewBase.cpp \
    Representation/vtkStreamLinesMapper.cpp \
    RepresentationWidget/igwCloudMapRepresentationWidget.cpp \
    RepresentationWidget/igwFlowingStreamRepWidget.cpp \
    RepresentationWidget/igwIsoSurfaceRepresentationWidget.cpp \
    RepresentationWidget/igwLineParametersWidget.cpp \
    RepresentationWidget/igwMeshRepresentationWidget.cpp \
    RepresentationWidget/igwMeshTableModel.cpp \
    RepresentationWidget/igwPlaneParametersWidget.cpp \
    RepresentationWidget/igwRepresentationWidget.cpp \
    RepresentationWidget/igwStreamLinesRepresentationWidget.cpp \
    RepresentationWidget/igwTextureRepresentationWidget.cpp \
    Widgets/igwAnimationTimeToolBar.cpp \
    Widgets/igwCameraReaction.cpp \
    Widgets/igwCameraToolBar.cpp \
    Widgets/igwColorChooserButton.cxx \
    Widgets/igwFileDialog.cpp \
    Widgets/igwFileReaction.cpp \
    Widgets/igwHierarchicalGridLayout.cpp \
    Widgets/igwHierarchicalGridWidget.cpp \
    Widgets/igwItemReaction.cpp \
    Widgets/igwReaction.cpp \
    Widgets/igwRenderViewSelectionReaction.cpp \
    Widgets/igwSaveScreenShotReaction.cpp \
    Widgets/igwSaveSpreadSheetReaction.cpp \
    Widgets/igwSelectionReaction.cpp \
    Core/igwApplicationCore.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ColorMap/igwColorMapCore.h \
    ColorMap/igwColorMapEditorWidget.h \
    ColorMap/igwColorMapManager.h \
    ColorMap/igwCoreUtilities.h \
    ColorMap/igwPresetDialog.h \
    ColorMap/igwPresetGroupsManager.h \
    ColorMap/igwPresetToPixmap.h \
    ColorMap/igwTimer.h \
    ColorMap/igwTransferFunctionPresets.h \
    ColorMap/igwTransferFunctionPresetsBuiltin.h \
    ColorMap/igwTransferFunctionWidget.h \
    ColorMap/vtkPVColorTransferControlPointsItem.h \
    Components/igwActiveObjects.h \
    Components/igwAnimationManager.h \
    Components/igwAnimationScene.h \
    Components/igwAnimationTimeWidget.h \
    Components/igwDataTreeModel.h \
    Components/igwDataTreeWidget.h \
    Components/igwInformationWidget.h \
    Components/igwMultiViewWidget.h \
    Components/igwSpreadSheet.h \
    Components/igwSpreadSheetModel.h \
    Components/igwTimeKeeper.h \
    Components/igwTimeStepsAnimation.h \
    Components/igwTreeItem.h \
    Components/igwVCRControl.h \
    Components/igwVCRToolBar.h \
    Components/igwView.h \
    Components/igwViewFrame.h \
    Components/igwVtkView.h \
    Components/igwVtkWidget.h \
    Components/vtkAnimationPlayer.h \
    Components/vtkTimestepsAnimationPlayer.h \
    Core/igwViewManager.h \
    Externsions/Core/vtkGaussianSplattionPlyReader.h \
    Externsions/Core/vtkGaussianSurfaceMapper.h \
    Externsions/Core/vtkGaussinSplattingMapper.h \
    Externsions/Sources/vtkDataObjectMeshCache.h \
    Externsions/Sources/vtkGridSource.h \
    Externsions/Sources/vtkHyperTreeGridFeatureEdges.h \
    Externsions/Sources/vtkLidarGridActor.h \
    Externsions/Sources/vtkPVGeometryFilter.h \
    Externsions/Sources/vtkPVTrivialProducer.h \
    Externsions/XrInterface/igwXRInterfaceHelper.h \
    Externsions/XrInterface/igwXRInterfacePanel.h \
    IO/igwCSVWriter.h \
    IO/igwIOCore.h \
    IO/igwReadCGNSFile.h \
    IO/igwReadFile.h \
    IO/igwReadFileFactory.h \
    IO/igwReadOpenFOAMFile.h \
    IO/igwReadSeriesFiles.h \
    IO/igwReadVtkFile.h \
    IO/igwReadeXMLMultiBlockFile.h \
    IO/igwStreamIO.h \
    IO/igwStreamReader.h \
    Representation/igwClipRepresentation.h \
    Representation/igwCloudMapRepresentation.h \
    Representation/igwMeshRepresentation.h \
    Representation/igwRealTimeModel2D.h \
    Representation/igwRealTimeModel2DRepresentation.h \
    Representation/igwRenderRepObserver.h \
    Representation/igwStreamSurfaceRepresentation.h \
    Representation/igwTextureRepresentation.h \
    Representation/igwVolumeRepresentation.h \
    RepresentationWidget/RepresentationDialog.h \
    RepresentationWidget/igwCloudMapRepresentationDialog.h \
    Representation/igwFlowingStreamLinesRepresentation.h \
    Representation/igwIsoSurfaceRepresentation.h \
    Representation/igwOutLineRepresentation.h \
    Representation/igwRenderView.h \
    Representation/igwRenderedRepresentation.h \
    Representation/igwRenderedSurfaceRepresentation.h \
    Representation/igwStreamLinesRepresentation.h \
    Representation/igwVortexRepresentation.h \
    Representation/igwRenderViewBase.h \
    Representation/shader.h \
    Representation/vtkStreamLinesMapper.h \
    Representation/vtkTextureObjectVS.h \
    RepresentationWidget/igwCloudMapRepresentationWidget.h \
    RepresentationWidget/igwFlowingStreamRepWidget.h \
    RepresentationWidget/igwIsoSurfaceRepresentationWidget.h \
    RepresentationWidget/igwLineParametersWidget.h \
    RepresentationWidget/igwMeshRepresentationWidget.h \
    RepresentationWidget/igwMeshTableModel.h \
    RepresentationWidget/igwPlaneParametersWidget.h \
    RepresentationWidget/igwRepresentationWidget.h \
    RepresentationWidget/igwStreamLinesRepresentationWidget.h \
    RepresentationWidget/igwTextureRepresentationWidget.h \
    Widgets/igwAnimationTimeToolBar.h \
    Widgets/igwCameraReaction.h \
    Widgets/igwCameraToolBar.h \
    Widgets/igwColorChooserButton.h \
    Widgets/igwFileDialog.h \
    Widgets/igwFileReaction.h \
    Widgets/igwHierarchicalGridLayout.h \
    Widgets/igwHierarchicalGridWidget.h \
    Widgets/igwItemReaction.h \
    Widgets/igwReaction.h \
    Widgets/igwRenderViewSelectionReaction.h \
    Widgets/igwSaveScreenShotReaction.h \
    Widgets/igwSaveSpreadSheetReaction.h \
    Widgets/igwSelectionReaction.h \
    Core/igwApplicationCore.h \
    igwCommand.h \
    mainwindow.h \

FORMS += \
    ColorMap/igwColorMapEditorWidget.ui \
    ColorMap/igwPresetDialog.ui \
    ColorMap/igwSavePresetOptions.ui \
    Components/igwAnimationTimeWidget.ui \
    Components/igwDataTreeWidget.ui \
    Components/igwInformationWidget.ui \
    Components/igwMultiViewWidget.ui \
    Components/igwSpreadSheet.ui \
    Components/igwVCRToolBar.ui \
    Components/igwViewFrame.ui \
    Components/igwVtkWidget.ui \
    RepresentationWidget/RepresentationDialog.ui \
    RepresentationWidget/igwCloudMapRepresentationDialog.ui \
    RepresentationWidget/igwCloudMapRepresentationWidget.ui \
    RepresentationWidget/igwFlowingStreamRepWidget.ui \
    RepresentationWidget/igwIsoSurfaceRepresentationWidget.ui \
    RepresentationWidget/igwLineParametersWidget.ui \
    RepresentationWidget/igwMeshRepresentationWidget.ui \
    RepresentationWidget/igwPlaneParametersWidget.ui \
    RepresentationWidget/igwStreamLinesRepresentationWidget.ui \
    RepresentationWidget/igwTextureRepresentationWidget.ui \
    Widgets/igwCameraToolBar.ui \
    mainwindow.ui

# Default rules for deployment.

    THIRD_PATH = $$PWD\ThirdParty
    EIGEN_PATH = $$THIRD_PATH\eigen-3.4.0
    OPENXR_PATH = $$THIRD_PATH\OpenXR-SDK-Debug
    INCLUDEPATH += $$OPENXR_PATH\include\openxr
    INCLUDEPATH += $$PWD\ThirdParty\eigen-3.4.0\eigen-3.4.0

    LIBS += opengl32.lib

# VTK_LI
#
    VTK_PATH = $$PWD\VTK

    VTK_VERSION = vtk-9.3
    VTK_LIB_PATH = $$VTK_PATH\lib
    VTK_INCLUDE_PATH = $$VTK_PATH\include\vtk-9.3

    INCLUDEPATH += $$VTK_INCLUDE_PATH
    LIBS += $$VTK_LIB_PATH\*.lib



DISTFILES += \
    ColorMap/ColorManager/ColorMaps.json \
    ColorMap/ColorManager/pqPresetGroups.json

SUBDIRS += \
    ColorMap/ColorMap.pro

RESOURCES += \
    res.qrc




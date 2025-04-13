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
    Externsions/XrInterface/igwXRInterfaceDockWidget.cpp \
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
    Externsions/XrInterface/igwXRInterfaceDockWidget.h \
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
    Externsions/XrInterface/igwXRInterfaceDockWidget.ui \
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

    INCLUDEPATH += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\include\vtk-9.3
    INCLUDEPATH += F:\VR_Code\OpenXR-SDK-Debug\include\openxr
    INCLUDEPATH += F:\CppLib\eigen-3.4.0\eigen-3.4.0

#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkcgns-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkChartsCore-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkCommonColor-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkCommonComputationalGeometry-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkCommonCore-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkCommonDataModel-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkCommonExecutionModel-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkCommonMath-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkCommonMisc-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkCommonSystem-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkCommonTransforms-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkDICOMParser-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkDomainsChemistry-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkDomainsChemistryOpenGL2-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkdoubleconversion-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkexodusII-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkexpat-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkFiltersAMR-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkFiltersCellGrid-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkFiltersCore-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkFiltersExtraction-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkFiltersFlowPaths-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkFiltersGeneral-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkFiltersGeneric-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkFiltersGeometry-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkFiltersGeometryPreview-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkFiltersHybrid-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkFiltersHyperTree-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkFiltersImaging-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkFiltersModeling-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkFiltersParallel-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkFiltersParallelImaging-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkFiltersPoints-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkFiltersProgrammable-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkFiltersReduction-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkFiltersSelection-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkFiltersSMP-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkFiltersSources-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkFiltersStatistics-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkFiltersTensor-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkFiltersTexture-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkFiltersTopology-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkFiltersVerdict-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkfmt-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkfreetype-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkGeovisCore-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkgl2ps-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkglew-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkGUISupportQt-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkGUISupportQtQuick-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkGUISupportQtSQL-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkhdf5-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkhdf5_hl-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkImagingColor-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkImagingCore-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkImagingFourier-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkImagingGeneral-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkImagingHybrid-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkImagingMath-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkImagingMorphological-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkImagingSources-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkImagingStatistics-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkImagingStencil-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkInfovisCore-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkInfovisLayout-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkInteractionImage-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkInteractionStyle-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkInteractionWidgets-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkIOAMR-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkIOAsynchronous-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkIOCellGrid-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkIOCesium3DTiles-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkIOCGNSReader-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkIOChemistry-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkIOCityGML-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkIOCONVERGECFD-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkIOCore-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkIOEnSight-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkIOExodus-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkIOExport-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkIOExportGL2PS-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkIOExportPDF-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkIOFLUENTCFF-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkIOGeometry-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkIOHDF-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkIOImage-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkIOImport-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkIOInfovis-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkIOIOSS-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkIOLegacy-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkIOLSDyna-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkIOMINC-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkIOMotionFX-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkIOMovie-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkIONetCDF-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkIOOggTheora-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkIOParallel-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkIOParallelXML-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkIOPLY-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkIOSegY-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkIOSQL-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkioss-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkIOTecplotTable-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkIOVeraOut-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkIOVideo-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkIOXML-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkIOXMLParser-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkjpeg-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkjsoncpp-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkkissfft-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtklibharu-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtklibproj-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtklibxml2-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkloguru-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtklz4-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtklzma-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkmetaio-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtknetcdf-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkogg-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkParallelCore-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkParallelDIY-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkpng-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkpugixml-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkRenderingAnnotation-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkRenderingCellGrid-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkRenderingContext2D-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkRenderingContextOpenGL2-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkRenderingCore-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkRenderingFreeType-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkRenderingGL2PSOpenGL2-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkRenderingHyperTreeGrid-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkRenderingImage-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkRenderingLabel-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkRenderingLICOpenGL2-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkRenderingLOD-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkRenderingOpenGL2-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkRenderingOpenXR-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkRenderingOpenXRRemoting-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkRenderingQt-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkRenderingSceneGraph-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkRenderingUI-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkRenderingVolume-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkRenderingVolumeOpenGL2-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkRenderingVR-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkRenderingVtkJS-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtksqlite-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtksys-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkTestingRendering-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtktheora-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtktiff-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkverdict-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkViewsContext2D-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkViewsCore-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkViewsInfovis-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkViewsQt-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkWrappingTools-9.3d.lib
#    LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Debug\lib\vtkzlib-9.3d.lib

# Have Accelator Debug
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkAcceleratorsVTKmCore-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkAcceleratorsVTKmDataModel-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkAcceleratorsVTKmFilters-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkcgns-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkChartsCore-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkCommonColor-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkCommonComputationalGeometry-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkCommonCore-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkCommonDataModel-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkCommonExecutionModel-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkCommonMath-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkCommonMisc-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkCommonSystem-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkCommonTransforms-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkDICOMParser-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkDomainsChemistry-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkDomainsChemistryOpenGL2-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkdoubleconversion-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkexodusII-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkexpat-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkFiltersAMR-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkFiltersCellGrid-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkFiltersCore-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkFiltersExtraction-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkFiltersFlowPaths-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkFiltersGeneral-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkFiltersGeneric-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkFiltersGeometry-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkFiltersGeometryPreview-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkFiltersHybrid-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkFiltersHyperTree-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkFiltersImaging-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkFiltersModeling-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkFiltersParallel-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkFiltersParallelFlowPaths-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkFiltersParallelImaging-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkFiltersPoints-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkFiltersProgrammable-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkFiltersReduction-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkFiltersSelection-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkFiltersSMP-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkFiltersSources-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkFiltersStatistics-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkFiltersTensor-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkFiltersTexture-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkFiltersTopology-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkFiltersVerdict-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkfmt-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkfreetype-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkGeovisCore-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkgl2ps-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkglew-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkGUISupportQt-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkGUISupportQtQuick-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkGUISupportQtSQL-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkhdf5-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkhdf5_hl-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkImagingColor-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkImagingCore-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkImagingFourier-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkImagingGeneral-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkImagingHybrid-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkImagingMath-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkImagingMorphological-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkImagingSources-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkImagingStatistics-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkImagingStencil-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkInfovisCore-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkInfovisLayout-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkInteractionImage-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkInteractionStyle-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkInteractionWidgets-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkIOAMR-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkIOAsynchronous-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkIOCellGrid-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkIOCesium3DTiles-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkIOCGNSReader-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkIOChemistry-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkIOCityGML-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkIOCONVERGECFD-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkIOCore-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkIOEnSight-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkIOExodus-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkIOExport-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkIOExportGL2PS-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkIOExportPDF-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkIOFLUENTCFF-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkIOGeometry-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkIOHDF-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkIOImage-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkIOImport-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkIOInfovis-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkIOIOSS-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkIOLegacy-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkIOLSDyna-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkIOMINC-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkIOMotionFX-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkIOMovie-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkIONetCDF-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkIOOggTheora-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkIOParallel-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkIOParallelXML-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkIOPLY-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkIOSegY-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkIOSQL-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkioss-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkIOTecplotTable-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkIOVeraOut-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkIOVideo-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkIOXML-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkIOXMLParser-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkjpeg-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkjsoncpp-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkkissfft-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtklibharu-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtklibproj-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtklibxml2-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkloguru-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtklz4-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtklzma-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkmdiympi_nompi.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkmetaio-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkm_cont-9.3.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkm_cont_testing-9.3.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkm_filter_clean_grid-9.3.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkm_filter_connected_components-9.3.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkm_filter_contour-9.3.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkm_filter_core-9.3.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkm_filter_density_estimate-9.3.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkm_filter_entity_extraction-9.3.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkm_filter_field_conversion-9.3.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkm_filter_field_transform-9.3.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkm_filter_flow-9.3.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkm_filter_geometry_refinement-9.3.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkm_filter_image_processing-9.3.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkm_filter_mesh_info-9.3.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkm_filter_multi_block-9.3.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkm_filter_resampling-9.3.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkm_filter_scalar_topology-9.3.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkm_filter_vector_analysis-9.3.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkm_filter_zfp-9.3.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkm_io-9.3.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkm_source-9.3.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkm_worklet-9.3.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtknetcdf-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkogg-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkParallelCore-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkParallelDIY-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkParallelMPI-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkpng-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkpugixml-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkRenderingAnnotation-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkRenderingCellGrid-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkRenderingContext2D-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkRenderingContextOpenGL2-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkRenderingCore-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkRenderingFreeType-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkRenderingGL2PSOpenGL2-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkRenderingHyperTreeGrid-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkRenderingImage-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkRenderingLabel-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkRenderingLICOpenGL2-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkRenderingLOD-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkRenderingOpenGL2-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkRenderingOpenXR-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkRenderingOpenXRRemoting-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkRenderingQt-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkRenderingSceneGraph-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkRenderingUI-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkRenderingVolume-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkRenderingVolumeOpenGL2-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkRenderingVR-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkRenderingVtkJS-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtksqlite-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtksys-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkTestingRendering-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtktheora-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtktiff-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkverdict-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkViewsContext2D-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkViewsCore-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkViewsInfovis-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkViewsQt-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkWrappingTools-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkzlib-9.3d.lib
LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelate-Debug\lib\vtkRenderingParallel-9.3d.lib
    LIBS += opengl32.lib

#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkAcceleratorsVTKmCore-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkAcceleratorsVTKmDataModel-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkAcceleratorsVTKmFilters-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkcgns-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkChartsCore-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkCommonColor-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkCommonComputationalGeometry-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkCommonCore-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkCommonDataModel-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkCommonExecutionModel-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkCommonMath-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkCommonMisc-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkCommonSystem-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkCommonTransforms-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkDICOMParser-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkDomainsChemistry-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkDomainsChemistryOpenGL2-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkdoubleconversion-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkexodusII-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkexpat-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkFiltersAMR-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkFiltersCellGrid-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkFiltersCore-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkFiltersExtraction-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkFiltersFlowPaths-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkFiltersGeneral-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkFiltersGeneric-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkFiltersGeometry-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkFiltersGeometryPreview-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkFiltersHybrid-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkFiltersHyperTree-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkFiltersImaging-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkFiltersModeling-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkFiltersParallel-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkFiltersParallelFlowPaths-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkFiltersParallelImaging-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkFiltersPoints-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkFiltersProgrammable-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkFiltersReduction-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkFiltersSelection-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkFiltersSMP-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkFiltersSources-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkFiltersStatistics-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkFiltersTensor-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkFiltersTexture-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkFiltersTopology-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkFiltersVerdict-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkfmt-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkfreetype-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkGeovisCore-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkgl2ps-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkglew-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkGUISupportQt-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkGUISupportQtQuick-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkGUISupportQtSQL-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkhdf5-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkhdf5_hl-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkImagingColor-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkImagingCore-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkImagingFourier-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkImagingGeneral-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkImagingHybrid-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkImagingMath-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkImagingMorphological-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkImagingSources-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkImagingStatistics-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkImagingStencil-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkInfovisCore-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkInfovisLayout-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkInteractionImage-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkInteractionStyle-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkInteractionWidgets-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkIOAMR-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkIOAsynchronous-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkIOCellGrid-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkIOCesium3DTiles-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkIOCGNSReader-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkIOChemistry-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkIOCityGML-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkIOCONVERGECFD-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkIOCore-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkIOEnSight-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkIOExodus-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkIOExport-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkIOExportGL2PS-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkIOExportPDF-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkIOFLUENTCFF-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkIOGeometry-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkIOHDF-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkIOImage-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkIOImport-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkIOInfovis-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkIOIOSS-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkIOLegacy-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkIOLSDyna-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkIOMINC-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkIOMotionFX-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkIOMovie-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkIONetCDF-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkIOOggTheora-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkIOParallel-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkIOParallelXML-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkIOPLY-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkIOSegY-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkIOSQL-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkioss-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkIOTecplotTable-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkIOVeraOut-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkIOVideo-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkIOXML-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkIOXMLParser-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkjpeg-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkjsoncpp-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkkissfft-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtklibharu-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtklibproj-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtklibxml2-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkloguru-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtklz4-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtklzma-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkmdiympi_nompi.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkmetaio-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkm_cont-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkm_cont_testing-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkm_filter_clean_grid-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkm_filter_connected_components-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkm_filter_contour-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkm_filter_core-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkm_filter_density_estimate-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkm_filter_entity_extraction-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkm_filter_field_conversion-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkm_filter_field_transform-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkm_filter_flow-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkm_filter_geometry_refinement-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkm_filter_image_processing-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkm_filter_mesh_info-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkm_filter_multi_block-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkm_filter_resampling-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkm_filter_scalar_topology-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkm_filter_vector_analysis-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkm_filter_zfp-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkm_io-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkm_source-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkm_worklet-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtknetcdf-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkogg-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkParallelCore-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkParallelDIY-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkParallelMPI-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkpng-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkpugixml-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkRenderingAnnotation-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkRenderingCellGrid-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkRenderingContext2D-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkRenderingContextOpenGL2-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkRenderingCore-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkRenderingFreeType-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkRenderingGL2PSOpenGL2-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkRenderingHyperTreeGrid-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkRenderingImage-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkRenderingLabel-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkRenderingLICOpenGL2-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkRenderingLOD-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkRenderingOpenGL2-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkRenderingOpenXR-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkRenderingOpenXRRemoting-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkRenderingParallel-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkRenderingQt-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkRenderingSceneGraph-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkRenderingUI-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkRenderingVolume-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkRenderingVolumeOpenGL2-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkRenderingVR-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkRenderingVtkJS-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtksqlite-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtksys-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkTestingRendering-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtktheora-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtktiff-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkverdict-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkViewsContext2D-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkViewsCore-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkViewsInfovis-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkViewsQt-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkWrappingTools-9.3.lib
#LIBS += D:\BaiduNetdiskDownload\VTK-9.3.0-Accelators-Release\lib\vtkzlib-9.3.lib


# ParaView Lib

#PARAVIEW_DIR = "D:\BaiduNetdiskDownload\ParaViewInstall\install"

## 添加头文件路径
#INCLUDEPATH += D:\BaiduNetdiskDownload\ParaViewInstall\install\include\paraview-5.7\vtkqttesting
#INCLUDEPATH += D:\BaiduNetdiskDownload\ParaViewInstall\install\include\paraview-5.7


## 添加库文件路径
#LIBS += -L"$$PARAVIEW_DIR/lib"

## 链接 ParaView 所需的库文件

#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\pqApplicationComponents-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\pqComponents-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\pqCore-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\pqWidgets-pv5.7d.lib

#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkAcceleratorsVTKm-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkAcceleratorsVTKmCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkAnalyzeNIfTIIOCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkArrowGlyphFilterCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkBagPlotViewsAndFiltersBagPlotCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkCDIReaderCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkcgns-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkChartsCore-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkChartsCoreCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkClientServer-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkClientServerCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkCommonColor-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkCommonColorCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkCommonComputationalGeometry-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkCommonComputationalGeometryCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkCommonCore-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkCommonCoreCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkCommonDataModel-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkCommonDataModelCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkCommonExecutionModel-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkCommonExecutionModelCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkCommonMath-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkCommonMathCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkCommonMisc-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkCommonMiscCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkCommonSystem-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkCommonSystemCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkCommonTransforms-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkCommonTransformsCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkDICOMParser-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkDigitalRocksFiltersCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkDomainsChemistry-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkDomainsChemistryCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkdoubleconversion-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkEmbossingRepresentationsCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkexodusII-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkexpat-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkExplicitStructuredGridCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkEyeDomeLightingViewCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkFiltersAMR-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkFiltersAMRCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkFiltersCore-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkFiltersCoreCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkFiltersExtraction-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkFiltersExtractionCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkFiltersFlowPaths-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkFiltersFlowPathsCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkFiltersGeneral-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkFiltersGeneralCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkFiltersGeneric-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkFiltersGenericCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkFiltersGeometry-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkFiltersGeometryCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkFiltersHybrid-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkFiltersHybridCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkFiltersHyperTree-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkFiltersHyperTreeCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkFiltersModeling-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkFiltersModelingCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkFiltersParallel-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkFiltersParallelCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkFiltersParallelStatistics-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkFiltersParallelStatisticsCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkFiltersPoints-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkFiltersPointsCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkFiltersProgrammable-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkFiltersProgrammableCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkFiltersSources-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkFiltersSourcesCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkFiltersStatistics-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkFiltersStatisticsCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkFiltersTexture-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkFiltersTextureCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkFiltersVerdict-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkFiltersVerdictCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkfreetype-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkGeodesicMeasurementFiltersCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkgl2ps-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkglew-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkGMVReaderCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkGUISupportQt-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkh5part-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkhdf5-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkhdf5_hl-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkImagingColor-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkImagingColorCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkImagingCore-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkImagingCoreCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkImagingFourier-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkImagingFourierCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkImagingGeneral-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkImagingGeneralCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkImagingHybrid-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkImagingHybridCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkImagingMath-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkImagingMathCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkImagingSources-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkImagingSourcesCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkInfovisCore-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkInfovisCoreCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkInteractionStyle-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkInteractionStyleCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkInteractionWidgets-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkInteractionWidgetsCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIOAMR-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIOAMRCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIOAsynchronous-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIOAsynchronousCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIOCore-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIOCoreCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIOEnSight-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIOEnSightCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIOExodus-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIOExodusCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIOExport-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIOExportCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIOExportGL2PS-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIOExportGL2PSCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIOGeometry-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIOGeometryCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIOH5part-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIOH5partCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIOImage-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIOImageCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIOImport-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIOImportCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIOInfovis-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIOInfovisCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIOLegacy-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIOLegacyCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIOLSDyna-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIOLSDynaCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIOMovie-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIOMovieCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIONetCDF-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIONetCDFCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIOParallel-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIOParallelCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIOParallelExodus-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIOParallelExodusCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIOParallelLSDyna-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIOParallelLSDynaCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIOParallelXML-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIOParallelXMLCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIOPLY-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIOPLYCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIOSegY-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIOSegYCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIOTecplotTable-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIOTecplotTableCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIOTRUCHAS-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIOTRUCHASCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIOVeraOut-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIOVeraOutCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIOVPIC-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIOVPICCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIOXdmf2-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIOXdmf2CSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIOXML-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIOXMLCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIOXMLParser-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkIOXMLParserCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkjpeg-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkjsoncpp-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkLagrangianParticleTrackerCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtklibharu-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtklibprotoc-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtklibxml2-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkloguru-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtklz4-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtklzma-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkmetaio-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkMomentFiltersCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkMooseXfemClipCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkm_cont-pv5.7.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkm_worklet-pv5.7.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtknetcdf-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkNonOrthogonalSourcesCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkPanoramicProjectionViewsCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkParallelCore-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkParallelCoreCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkpng-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkprotobuf-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkpugixml-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkPVAnimation-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkPVAnimationCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkPVCatalyst-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkPVClientServerCoreCore-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkPVClientServerCoreCoreCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkPVClientServerCoreDefault-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkPVClientServerCoreDefaultCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkPVClientServerCoreRendering-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkPVClientServerCoreRenderingCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkPVCore-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkPVCoreCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkPVServerImplementationCore-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkPVServerImplementationCoreCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkPVServerImplementationRendering-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkPVServerImplementationRenderingCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkPVServerManagerApplication-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkPVServerManagerCore-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkPVServerManagerCoreCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkPVServerManagerDefault-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkPVServerManagerDefaultCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkPVServerManagerRendering-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkPVServerManagerRenderingCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkPVVTKExtensionsCGNSReader-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkPVVTKExtensionsCGNSReaderCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkPVVTKExtensionsCore-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkPVVTKExtensionsCoreCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkPVVTKExtensionsDefault-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkPVVTKExtensionsDefaultCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkPVVTKExtensionsPoints-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkPVVTKExtensionsPointsCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkPVVTKExtensionsRendering-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkPVVTKExtensionsRenderingCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkPVVTKExtensionsSIL-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkPVVTKExtensionsSILCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkqttesting-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkRenderingAnnotation-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkRenderingAnnotationCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkRenderingContext2D-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkRenderingContext2DCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkRenderingContextOpenGL2-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkRenderingContextOpenGL2CSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkRenderingCore-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkRenderingCoreCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkRenderingFreeType-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkRenderingFreeTypeCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkRenderingGL2PSOpenGL2-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkRenderingGL2PSOpenGL2CSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkRenderingLabel-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkRenderingLabelCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkRenderingLICOpenGL2-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkRenderingLICOpenGL2CSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkRenderingOpenGL2-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkRenderingOpenGL2CSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkRenderingParallel-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkRenderingParallelCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkRenderingVolume-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkRenderingVolumeAMR-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkRenderingVolumeAMRCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkRenderingVolumeCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkRenderingVolumeOpenGL2-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkRenderingVolumeOpenGL2CSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkSLACFiltersCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkStreamingParticlesCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkStreamLinesCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkSurfaceLICRepresentationsCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtksys-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkTestingRendering-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkTestingRenderingCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkThickenLayeredCellsFiltersCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtktiff-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkverdict-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkViewsContext2D-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkViewsContext2DCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkViewsCore-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkViewsCoreCSd.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkvpic-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkWrappingTools-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkxdmf2-pv5.7d.lib
#LIBS += D:\BaiduNetdiskDownload\ParaViewInstall\install\lib\vtkzlib-pv5.7d.lib


DISTFILES += \
    ColorMap/ColorManager/ColorMaps.json \
    ColorMap/ColorManager/pqPresetGroups.json

SUBDIRS += \
    ColorMap/ColorMap.pro

RESOURCES += \
    res.qrc




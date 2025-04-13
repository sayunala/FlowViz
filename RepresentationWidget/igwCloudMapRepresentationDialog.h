#ifndef IGWCLOUDMAPREPRESENTATIONDIALOG_H
#define IGWCLOUDMAPREPRESENTATIONDIALOG_H

#include <QDialog>
#include "igwStreamLinesRepresentationWidget.h"
#include "vtkSmartPointer.h"
class igwCloudMapRepresentation;
class igwPlaneParametersWidget;
class igwColorMapEditorWidget;
class vtkEventQtSlotConnect;

namespace Ui {
class igwCloudMapRepresentationDialog;
}

class igwCloudMapRepresentationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit igwCloudMapRepresentationDialog(QWidget *parent = nullptr);
    ~igwCloudMapRepresentationDialog();
    void SetigwCloudMapRepresentation(igwCloudMapRepresentation* rep);

protected slots:
    /**
      * @brief SetNormalTo*Axis:
      * @brief SetNormalTo*Axis:设置平面法线方向与坐标轴对齐的槽函数
      */
     void SetNormalToXAxis();
     void SetNormalToYAxis();
     void SetNormalToZAxis();

     /**
      * @brief SetPlaneEnable:
      * @brief SetPlaneEnable: 设置交互平面是否可见的槽函数，监听igwPlaneParametersWidget的
      * @param type
      */
     void SetPlaneEnable(int type);

     /**
      * @brief SetPlaneNormal:
      * @brief SetPlaneNormal: 设置交互平面的法线，监听igwPlaneParametersWidget的
      * @param type
      */
     void SetPlaneNormal(double x, double y, double z);
     /**
      * @brief SetPlaneOrigin:
      * @brief SetPlaneOrigin: 设置交互平面位置，监听igwPlaneParametersWidget的
      * @param type
      */
     void SetPlaneOrigin(double x, double y, double z);

     /**
      * @brief PlaneWidgetEndInterActorSlot:
      * @brief PlaneWidgetEndInterActorSlot:监听vtkImplicitPlaneWidget交互结束事件，同时发送更新参数信号
      */
     void PlaneWidgetEndInterActorSlot();
Q_SIGNALS:
     /**
      * @brief UpdatePlaneParametersWidget:
      * @brief UpdatePlaneParametersWidget: 更新igwPlaneParametersWidget的Origin和Normal
      */
     void UpdatePlaneParametersWidget(double, double, double, double, double, double);

     /**
      * @brief PlaneUpdated: 通知主窗口需要刷新VTK界面了。
      */
     void Applied();

private:

    void ConnectSignalAndSlot();

    Ui::igwCloudMapRepresentationDialog *ui;
    igwCloudMapRepresentation* m_igwCloudMapRepresentation;
    igwPlaneParametersWidget* m_igwPlaneParametersWidget;
    igwColorMapEditorWidget* m_igwColorMapEditorWidget;
    igwStreamLinesRepresentationWidget* streamWidget;
    vtkEventQtSlotConnect* m_Connect;
};

#endif // IGWCLOUDMAPREPRESENTATIONDIALOG_H

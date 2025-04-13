#ifndef IGWSTREAMLINESREPRESENTATIONWIDGET_H
#define IGWSTREAMLINESREPRESENTATIONWIDGET_H

#include <QWidget>
#include "vtkSmartPointer.h"
class igwPlaneParametersWidget;
class igwColorMapEditorWidget;
class igwStreamLinesRepresentation;
class igwLineParametersWidget;
class vtkEventQtSlotConnect;

namespace Ui {
class igwStreamLinesRepresentationWidget;
}

class igwStreamLinesRepresentationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit igwStreamLinesRepresentationWidget(QWidget *parent = nullptr);
    ~igwStreamLinesRepresentationWidget();

    void SetRepresentation(igwStreamLinesRepresentation* rep);

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

     void LineWidgetChangedSlot();

     void ApplySetting();
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



private slots:
    void on_DataArrayComboBox_currentIndexChanged(const QString &);

    void on_comboBox_currentIndexChanged(int index);

    //----------------基本设置槽函数---------------------------
    void on_StreamTypeComboBox_currentIndexChanged(int index);

    void on_DirectionComboBox_currentIndexChanged(int index);

    void on_WidthSpinBox_valueChanged(int arg1);

    void on_LengthSpinBox_valueChanged(int arg1);

    //-------------------平面种子点选取------------------------
    void on_PlaneXAxisSpinBox_valueChanged(int arg1);

    void on_PlaneYAxisSpinBox_valueChanged(int arg1);

    //-------------------线种子点选取------------------------
    void on_NumOfLineSeedsSpinBox_valueChanged(int arg1);

private:
     /**
     * @brief ConnetPlaneSignalAndSlot: Connet the Plane Signal and the Slot.
     */
    void ConnetPlaneSignalAndSlot();

    /**
     * @brief ConnetLineSignalAndSlot
     */
    void ConnetLineSignalAndSlot();

    /**
     * @brief InitDataArrayComboBox: 初始化物理量选择下拉框
     */
    void InitDataArrayComboBox();

    /**
     * @brief Init:初始化部分UI
     */
    void Init();

    Ui::igwStreamLinesRepresentationWidget *ui;
    igwStreamLinesRepresentation* m_igwStreamLinesRepresentation;
    igwColorMapEditorWidget* m_igwColorMapEditorWidget;
    vtkSmartPointer<vtkEventQtSlotConnect> m_Connect;
};

#endif // IGWSTREAMLINESREPRESENTATIONWIDGET_H

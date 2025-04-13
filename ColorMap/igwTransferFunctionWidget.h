
/**********************************************
* @projectName   IGreatWorks
* @file          igwTransferFunctionWidget.h
* @brief         修改自ParaView用于颜色编辑的小组件。
* @author        ZYB
* @date          2023-09-23
* @version       1.0
**********************************************/

#ifndef igwTransferFunctionWidget_h
#define igwTransferFunctionWidget_h


#include "vtkType.h"
#include <QWidget>

class vtkPiecewiseFunction;
class vtkScalarsToColors;
class vtkTable;


class  igwTransferFunctionWidget : public QWidget
{
  Q_OBJECT
  typedef QWidget Superclass;

public:
  igwTransferFunctionWidget(QWidget* parent = nullptr);
  ~igwTransferFunctionWidget() override;

  /**
   *使用给定的 color-transfer-function 和 piecewise-function（二者均可为空）初始化 igwTransferFunctionWidget。
   *可编辑标志用于控制是否允许用户编辑/更改特定的转移函数。是否允许用户编辑/更改特定的转移函数。
   */
  void initialize(
    vtkScalarsToColors* stc, bool stc_editable, vtkPiecewiseFunction* pwf, bool pwf_editable);

  /**
   * 返回当前点索引。-1表示没有选择。
   */
  vtkIdType currentPoint() const;

  /**
   * 返回编辑器 widget 中控制点的数量。
   */
  vtkIdType numberOfControlPoints() const;

  ///@{
  /**
   * 将图表切换为使用对数缩放 X 轴。
   */
  void SetLogScaleXAxis(bool logScale);
  bool GetLogScaleXAxis() const;
  ///@}

  ///@{
  /**
   * Provides access to vtkScalarsToColors and vtkPiecewiseFunction passed to
   * `initialize`.
   */
  /**
   * @brief scalarsToColors,piecewiseFunction 提供可用的vtkScalarsToColors 和 vtkPiecewiseFunction
   * 供`initialize`使用
   * @return
   */
  vtkScalarsToColors* scalarsToColors() const;
  vtkPiecewiseFunction* piecewiseFunction() const;
  ///@}

  ///@{
  /**
   * 设置/获取控制点的自由绘图。
   */
  void SetControlPointsFreehandDrawing(bool use);
  bool GetControlPointsFreehandDrawing() const;
  ///@}

public Q_SLOTS: // NOLINT(readability-redundant-access-specifiers)

  /** Set the current point. Set to -1 clear the current point.
   * 设置当前点。设置为 -1，清除当前点。
   */
  void setCurrentPoint(vtkIdType index);

  /**
   * Set the X-position for the current point (without changing the Y position,
   * if applicable. We ensure that the point doesn't move past neighbouring
   * points. Note this will not change the end points i.e. start and end points.
   */
  /**
   * @brief setCurrentPointPosition设置当前点的 X 位置（不改变 Y 位置（如适用））。
   * 我们会确保该点不会移过邻近点。注意这不会改变终点，即起点和终点。
   * @param xpos
   */
  void setCurrentPointPosition(double xpos);

  /**
   * re-renders the transfer function view. This doesn't render immediately,
   * schedules a render.
   */
  /**
   * @brief 重新渲染转移函数视图
   */
  void render();

  /**
   * Set the histogram table to display as a plot bar.
   * If set to nullptr, a simple color texture is used, the default.
   */
  void setHistogramTable(vtkTable* table);

Q_SIGNALS:
  /**
   * signal fired when the \c current selected control point changes.
   */
  /**
   * @brief 当前所选控制点改变之后处罚该信号
   * @param index
   */
  void currentPointChanged(vtkIdType index);

  /**
   * signal fired to indicate that the control points changed i.e. either they
   * were moved, orone was added/deleted, or edited to change color, etc.
   */
  /**
   * @brief 该信号触发表明，控制点已经改变，包括移动，增加，删除或者被change color编辑
   */
  void controlPointsModified();

  /**
   * signal fired when the chart range is modified.
   */
  /**
   * @brief 当图表范围修改时触发该信号
   */
  void chartRangeModified();

  /**
   * signal fired when the range handles changed the range.
   */
  void rangeHandlesRangeChanged(double rangeMin, double rangeMax);

  /**
   * signal fired when the range handles are double clicked.
   */
  void rangeHandlesDoubleClicked();

protected Q_SLOTS:
  /**
   * slot called when the internal vtkControlPointsItem fires
   * vtkControlPointsItem::CurrentPointChangedEvent
   */
  void onCurrentChangedEvent();

  /**
   * slot called when the internal vtkRangeHandlesItem fires a
   * vtkRangeHandlesItem::RangeHandlesRangeChanged
   */
  void onRangeHandlesRangeChanged();

  /**
   * Show usage info in the application status bar
   */
  void showUsageStatus();

  /**
   * Show color dialog to edit color for a specific control point.
   */
  void editColorAtCurrentControlPoint();

protected: // NOLINT(readability-redundant-access-specifiers)
  /**
   * callback called when vtkControlPointsItem fires
   * vtkControlPointsItem::CurrentPointEditEvent.
   */
  void onCurrentPointEditEvent();

private:
  Q_DISABLE_COPY(igwTransferFunctionWidget)

  class pqInternals;
  pqInternals* Internals;
};

#endif

/**********************************************
* @projectName   IGreatWorks
* @file          vtkPVColorTransferControlPointsItem.h
* @brief         重载 VTK 基类以自定义 鼠标/键盘交互。在igwTransferFunctionWidget中使用
* @author        ZYB
* @date          2023-09-23
* @version       1.0
**********************************************/

#ifndef vtkPVColorTransferControlPointsItem_h
#define vtkPVColorTransferControlPointsItem_h


#include "vtkColorTransferControlPointsItem.h"

/**
 * vtkPVColorTransferControlPointsItem 重载 VTK 基类以自定义 鼠标/键盘交互。
 */
class  vtkPVColorTransferControlPointsItem
  : public vtkColorTransferControlPointsItem
{
  vtkTypeMacro(vtkPVColorTransferControlPointsItem, vtkColorTransferControlPointsItem)

  static vtkPVColorTransferControlPointsItem* New();

  // 忽略左键双击，改为按 Enter 键事件。
  bool MouseDoubleClickEvent(const vtkContextMouseEvent& mouse) override;
  // 使用 Enter/Return 键启动点编辑事件
  bool KeyPressEvent(const vtkContextKeyEvent& key) override;

protected:
  vtkPVColorTransferControlPointsItem();
  ~vtkPVColorTransferControlPointsItem() override;

private:
  vtkPVColorTransferControlPointsItem(const vtkPVColorTransferControlPointsItem&) = delete;
  void operator=(const vtkPVColorTransferControlPointsItem&) = delete;
};

#endif

#ifndef IGWCOMMAND_H
#define IGWCOMMAND_H

/**********************************************
* @projectName   iGreatWorks
* @file          igwCommand.h
* @brief         事件回调函数，用于处理用户自定义事件
* @author        ZYB
* @date          2023-04-10
* @version       1.0
**********************************************/

#include <vtkCommand.h>

#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkDoubleArray.h>
#include <vtkPolyData.h>
/***
*   Event:
*   RealTimeModeUpdateEvent:
*   MeshDataUpdateEvent:
*   ETKFDataFileUpdateEvent: ETKF输出txt 文件路径更新事件
*   ETKFDataUpdateEvent:  ETKF数据
***/
namespace iGreatWorks {

// 仿照vtk进行事件定义，目的是增强事件的可扩展性使用iGreatWorks::ChangeDataEvent

#define igwAllEventsMacro() \
    _igw_add_event(RealTimeModelUpdateEvent)\
    _igw_add_event(MeshDataUpdateEvent)\
    _igw_add_event(ETKFDataFileUpdateEvent)\
    _igw_add_event(ETKFDataUpdateEvent)\

#define igwEventDeclarationMacro(_enum_name)\
  enum _enum_name{\
    NoEvent = 1001,\
    igwAllEventsMacro() \
    OtherEvent\
  };

#define _igw_add_event(Enum)  Enum,
  igwEventDeclarationMacro(EventIds)
#undef _igw_add_event
}

#endif // IGWCOMMAND_H

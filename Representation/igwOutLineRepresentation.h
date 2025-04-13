#ifndef IGWOUTLINEREPRESENTATION_H
#define IGWOUTLINEREPRESENTATION_H

#include "igwRenderedRepresentation.h"
#include "vtkOutlineFilter.h"
class vtkMapper;
class vtkOutlineFilter;
class vtkPolyDataMapper;
class igwOutLineRepresentation : public igwRenderedRepresentation
{
public:
    static  igwOutLineRepresentation* New();
    vtkTypeMacro(igwOutLineRepresentation, igwRenderedRepresentation)
    void PrintSelf(std::ostream &os, vtkIndent indent) override;

    igwOutLineRepresentation();
    virtual ~igwOutLineRepresentation();

protected:
    /**
      * @brief RequestData: Sets the input pipeline connection to this representation.
      * @brief RequestData: 重载VTK算法的函数，主要处理算法的逻辑在此处拥有构建整个等值面计算管道(pipeline)
      * @param request
      * @param inputVector
      * @param outputVector
      * @return
      */
     int RequestData(
       vtkInformation* request,
       vtkInformationVector** inputVector,
       vtkInformationVector* outputVector) override;

    /**
    * @brief AddToView: Adds the representation to the view.  This is called from vtkView::AddRepresentation().
    * @brief AddToView: 增加表征(representation)到视图(view)中. 在vtkView的AddRepresentation()被调用
    * @param view: 视图
    * @return 如果添加成功返回true，反之返回false。
    */
    bool AddToView(vtkView* view) override;

    /**
    * @brief RemoveFromView: Removes the representation to the view. This is called from
    *        vtkView::RemoveRepresentation().
    * @brief RemoveFromView: 移除视图(view)中的表征(representation).
    * 在vtkView中的RemoveRepresentation()中被调用
    * @param view: 视图
    * @return 如果移除成功返回true，反之返回false。
    */
    bool RemoveFromView(vtkView* view) override;

    vtkPolyDataMapper* Mapper;
    vtkOutlineFilter* OutlineFilter;

private:
    igwOutLineRepresentation(const igwOutLineRepresentation&) = delete;
    void operator =(const igwOutLineRepresentation&) = delete;
};

#endif // IGWOUTLINEREPRESENTATION_H

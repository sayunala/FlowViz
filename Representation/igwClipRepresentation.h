/**********************************************
* @projectName   iGreatWorks
* @file          igwClipRepresentation.h
* @brief         云图 Representation
* @author        ZYB
* @date          2024/04/08
* @version       1.0
**********************************************/

#ifndef igwClipRepresentation_H
#define igwClipRepresentation_H

#include "igwRenderedRepresentation.h"
#include "vtkSmartPointer.h"
class vtkActor;
class vtkMapper;
class vtkPolyDataMapper;
class vtkPlane;
class vtkCutter;
class vtkImplicitPlaneRepresentation;
class vtkImplicitPlaneWidget2;
class vtkImplicitPlaneWidget;
class vtkDataSetSurfaceFilter;
class vtkClipDataSet;

class igwClipRepresentation : public igwRenderedRepresentation
{
public:
    vtkTypeMacro(igwClipRepresentation, igwRenderedRepresentation);
    static igwClipRepresentation* New();
    void PrintSelf(std::ostream &os, vtkIndent indent) override;

    void SetDataSet(vtkDataSet* dataSet) override;
    vtkPlane* GetPlane(){
        return this->Plane;
    }
    /**
     * @brief SetNormalTo?Axis: Force the plane widget to be aligned with one of the x-y-z axes.
     * @brief SetNormalTo?Axis: 强制窗口组件与x-y-z轴之一的对齐
     */
    void SetNormalToXAxis();
    void SetNormalToYAxis();
    void SetNormalToZAxis();

    /**
     * @brief SetPlaneNormal
     * @param normal
     */
    void SetPlaneNormal(double normal[3]);
    void SetPlaneNormal(double x, double y, double z);
    double* GetPlaneNormal();
    /**
     * @brief SetPlaneOrigin: Set the Plane Origin.
     * @brief SetPlaneOrigin: 平面上一点与平面法线确定一个平面。设置该平面上一点
     */
    void SetPlaneOrigin(double origin[3]);
    void SetPlaneOrigin(double x, double y, double z);
    double* GetPlaneOrigin();

    /**
     * @brief SetPlaneOpacity
     * @param opacity
     */
    void SetPlaneOpacity(double opacity);

    /**
     * @brief PlaneWidgetOn/Off: On or Off the Plane Widget
     */
    void PlaneWidgetOn();
    void PlaneWidgetOff();
    /**
     * @brief SetLookupTable: Set the Color Map of the Mapper.
     * @brief SetLookupTable: 设置Mapper的颜色映射
     * @param val
     */
    void SetLookupTable(vtkScalarsToColors* val);

    void SetPointColorArrayName(const char* arrayName) override;

    /**
     * @brief SetInputArrayToProcess: Set the input data arrays that this algorithm will process.
     *        The main thing to do here is to set the array of colours to be displayed.
     * @brief SetInputArrayToProcess: 设置输入这个算法需要处理的数据数组。在这个类中主要时为了设置需要进行颜色映射的数组。
     * @param idx: Please set this parameter to 0
     * @param port: Please set this parameter to 0
     * @param connection: Please set this parameter to 0
     * @param fieldAssociation: vtkDataObject::FIELD_ASSOCIATION_POINTS
     * @param name: The Array Name.
     */
    void SetInputArrayToProcess(
      int idx, int port, int connection, int fieldAssociation, const char* name) override;
    void SetInputArrayToProcess(
      int idx, int port, int connection, int fieldAssociation, int fieldAttributeType) override
    {
      this->Superclass::SetInputArrayToProcess(
        idx, port, connection, fieldAssociation, fieldAttributeType);
    }
    void SetInputArrayToProcess(int idx, vtkInformation* info) override
    {
      this->Superclass::SetInputArrayToProcess(idx, info);
    }
    void SetInputArrayToProcess(int idx, int port, int connection, const char* fieldAssociation,
      const char* attributeTypeorName) override
    {
      this->Superclass::SetInputArrayToProcess(
        idx, port, connection, fieldAssociation, attributeTypeorName);
    }

    /**
     * @brief GetImplicitPlaneWidget: Get the ImplicitWidget
     * @return
     */
    vtkImplicitPlaneWidget* GetImplicitPlaneWidget()
    {
        return this->ImplicitPlaneWidget;
    }

    /**
     * @brief vtkGetMacro
     */
    vtkGetMacro(PlaneVisibility, bool);
    vtkSetMacro(PlaneVisibility, bool);


    /**
     * @brief UpdateDataSet:重载父类，用于更新数据
     * @param newData
     */
//    void UpdateDataSet(void *newData) override;
protected:
    igwClipRepresentation();
    ~igwClipRepresentation();

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
    * @brief PrepareForRendering: Performs per-render operations.
    * @brief PrepareForRendering: 预渲染，将下一次Render的Prop加入到vtkRenderer中
    * @param view: 视图指针。目的是通过 view 获取vtkRenderer指针
    */
    void PrepareForRendering(igwRenderView* view) override;

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

    vtkSmartPointer<vtkDataSetSurfaceFilter> DataSetSurfaceFilter;

    vtkPlane* Plane;
    vtkCutter* Cutter;
    vtkPolyDataMapper* Mapper;
    vtkImplicitPlaneWidget* ImplicitPlaneWidget;
    vtkSmartPointer<vtkClipDataSet> ClipDataSet;
    class igwCMCallback;
    igwCMCallback* CallBack;

    bool Animation;

    bool PlaneVisibility;

    char* ColorArrayName;


private:
    igwClipRepresentation(const igwClipRepresentation&) = delete;
    void operator =(const igwClipRepresentation&) = delete;
};

#endif // igwClipRepresentation_H

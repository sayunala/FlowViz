#ifndef IGWREALTIMEMODEL2DREPRESENTATION_H
#define IGWREALTIMEMODEL2DREPRESENTATION_H

#include "igwRenderedRepresentation.h"
class vtkGlyph3D;
class vtkMapper;
class vtkPolyDataMapper;
class vtkMaskPoints;
class vtkTransform;
class vtkArrowSource;
class vtkTransformPolyDataFilter;

class igwRealTimeModel2DRepresentation : public igwRenderedRepresentation
{
public:
    vtkTypeMacro(igwRealTimeModel2DRepresentation, igwRenderedRepresentation)
    static igwRealTimeModel2DRepresentation* New();

    void PrintSelf(std::ostream &os, vtkIndent indent) override;

    igwRealTimeModel2DRepresentation();
    ~igwRealTimeModel2DRepresentation();

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
     * @brief CallBack: 更新数据回调，调用Update。
     * @param data:更新的数据
     */
    void CallBack(void* data);
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

    vtkSmartPointer<vtkGlyph3D> Glyph3D;
    vtkSmartPointer<vtkMaskPoints> MaskPoints;
    vtkSmartPointer<vtkArrowSource> Arrow;
    vtkSmartPointer<vtkTransform> Transform;
    vtkSmartPointer<vtkTransformPolyDataFilter> TransformPolyDataFilter;
    vtkSmartPointer<vtkPolyDataMapper> Mapper;

    vtkSmartPointer<vtkPolyDataMapper> ModelMapper;
    vtkSmartPointer<vtkActor> ModelActor;
    class igwRealTimeModel2DObserver;
    vtkSmartPointer<igwRealTimeModel2DObserver> RealTimeModel2DObserver;

private:

    /**
     * @brief InitGlyph3D:连接Glyph3D的数据流管道
     */
    void InitGlyph3D();

    void ComputerNormal();

    void UpdateData(double* newData);
    igwRealTimeModel2DRepresentation(const igwRealTimeModel2DRepresentation&) = delete;
    void operator =(const igwRealTimeModel2DRepresentation&) = delete;
};

#endif // IGWREALTIMEMODEL2DREPRESENTATION_H

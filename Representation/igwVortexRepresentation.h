#ifndef IGWVORTEXREPRESENTATION_H
#define IGWVORTEXREPRESENTATION_H

#include "igwRenderedRepresentation.h".h"

class vtkGradientFilter;
class vtkActor;
class vtkPolyDataMapper;
class vtkContourFilter;
class vtkVortexCore;
class igwVortexRepresentation : public igwRenderedRepresentation
{
public:
    static igwVortexRepresentation* New();
    vtkTypeMacro(igwVortexRepresentation, igwRenderedRepresentation);
    void PrintSelf(std::ostream &os, vtkIndent indent) override;


    void SetPointVelocityArrayName(const char* arrayName);
    const char* GetPointVelocityArrayName()
    {return this->GetVelocityArrayName();}

    void SetPointQCriterionArrayName(const char* arrayName);
    const char* GetPointQCriterionArrayName()
    {return this->GetQCriterionArrayName();}

    /**
     * @brief Set or Get the Velocity array Name, default is "velocity".
     *        the Velocity array is used to compute the QCriterion
     * @brief 设置或者获取速度数组名，默认为"veloity".
     *        速度数组是用于计算Q准则(QCriterion)
     */
    vtkGetStringMacro(VelocityArrayName)
    vtkSetStringMacro(VelocityArrayName)

    /**
     * @brief Set the QCriterion array name, default is "QCriterion".
     *        The Vortex is the IsoSurface of the QCriterion.
     * @brief 设置或获取Q准则数组名，默认为"QCriterion"
     *        通过提取QCriterion等值面来生成涡(Vortex).
     */
    vtkSetStringMacro(QCriterionArrayName)
    vtkGetStringMacro(QCriterionArrayName)

    /**
     * @brief Set or Get the QCriterionValue. default is 0.0. then update the ContourFilter
     * @brief 设置或者获取提取等值面的Q准则的值，默认是0.0。同时更新ContouFilter。
     * @param value: double类型，设置的变量
     */
    virtual void SetQCriterionValue(double value);
    virtual double GetQCriterionValue()
    { return this->GetQCriterion();}

    /**
     * @brief SetLookupTable: Set the Color Map of the Mapper.
     * @brief SetLookupTable: 设置Mapper的颜色映射
     * @param val
     */
    void SetLookupTable(vtkScalarsToColors* val);

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
     * @brief SetPointColorArrayName
     * @param arrayName
     */
    void SetPointColorArrayName(const char *arrayName) override;

protected:
    igwVortexRepresentation();
    ~igwVortexRepresentation();

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
      * vtkView::RemoveRepresentation().
      * @brief RemoveFromView: 移除视图(view)中的表征(representation).
      * 在vtkView中的RemoveRepresentation()中被调用
      * @param view: 视图
      * @return 如果移除成功返回true，反之返回false。
      */
     bool RemoveFromView(vtkView* view) override;


     /**
      * @brief ConvertSelection: vtkView所需要重载的函数，因为与QVTKInteractor不兼容但是又要重载因此。在此处永远返回true
      * @param view
      * @param selection
      * @return 永远返回nullptr
      */
    vtkSelection* ConvertSelection(vtkView* view, vtkSelection* selection) override;

    vtkGradientFilter* GradientFilter;// 计算Q准则、或者Vorticity
    vtkContourFilter* ContourFilter;
    vtkPolyDataMapper* Mapper;
    vtkVortexCore* VortexCore;
    /**
     * @brief Set or Get the value of QCriterion, default is 0.0
     * @brief 设置或者获取提取Q准则等值面的值。默认值是0.0
     */
    vtkGetMacro(QCriterion, double);
    vtkSetMacro(QCriterion, double);

private:



    char* QCriterionArrayName;

    char* VelocityArrayName;

    double QCriterion;

    igwVortexRepresentation(const igwVortexRepresentation&) = delete;
    void operator =(const igwVortexRepresentation&) = delete;
};

#endif // IGWVORTEXREPRESENTATION_H

#ifndef igwVolumeRepresentation_H
#define igwVolumeRepresentation_H


#include "igwRenderedRepresentation.h"

class vtkProp;
class vtkMapper;
class vtkActor;
class vtkAlgorithmOutput;
class vtkApplyColors;
class vtkDataObject;
class vtkPolyDataMapper;
class igwRenderView;
class vtkScalarsToColors;
class vtkPiecewiseFunction;
class vtkSelection;
class vtkTransformFilter;
class vtkView;
class vtkGPUVolumeRayCastMapper;
class vtkLODProp3D;
class vtkResampleToImage;
class vtkVolumeProperty;
class vtkArrayCalculator;
class igwVolumeRepresentation : public igwRenderedRepresentation
{
public:
    static igwVolumeRepresentation* New();
    vtkTypeMacro(igwVolumeRepresentation, igwRenderedRepresentation);
    void PrintSelf(ostream& os, vtkIndent indent) override;

    void SetPointColorArrayName(const char* arrayName) override;

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

    void SetDataSet(vtkDataSet *) override;


    //***************************************************************************
    // Forwarded to vtkResampleToImage
    void SetSamplingDimensions(int dims[3])
    {
      this->SetSamplingDimensions(dims[0], dims[1], dims[2]);
    }
    void SetSamplingDimensions(int xdim, int ydim, int zdim);

    // Forwarded to Actor.
     void SetOrientation(double, double, double);
     void SetOrigin(double, double, double);
     void SetPickable(int val);
     void SetPosition(double, double, double);
     void SetScale(double, double, double);

     //***************************************************************************
     // Forwarded to vtkVolumeProperty and vtkProperty (when applicable).
     void SetInterpolationType(int val);

     void SetScalarOpacity(vtkPiecewiseFunction* pwf);
     void SetScalarOpacityUnitDistance(double val);

protected:
    igwVolumeRepresentation();
    ~igwVolumeRepresentation() override;

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


    /**
      * @brief ConvertSelection: vtkView所需要重载的函数，因为与QVTKInteractor不兼容但是又要重载因此。在此处永远返回true
      * @param view
      * @param selection
      * @return 永远返回true
      */
    vtkSelection* ConvertSelection(vtkView* view, vtkSelection* selection) override;



    vtkTransformFilter* TransformFilter;
    vtkPolyDataMapper* Mapper;

    vtkSmartPointer<vtkGPUVolumeRayCastMapper> VolumeMapper;
    vtkSmartPointer<vtkLODProp3D> LODProp3D;
    vtkSmartPointer<vtkResampleToImage> ResampleToImage;
    vtkSmartPointer<vtkVolumeProperty> VolumeProperty;
    vtkSmartPointer<vtkArrayCalculator> ArrayCalculator;

    /**
     * @brief Set or Get color array name
     * @brief 设置或者获得进行颜色映射的数组名
     */
    vtkSetStringMacro(ColorArrayName)
    vtkGetStringMacro(ColorArrayName)
    char* ColorArrayName;

    vtkApplyColors* ApplyColors;//颜色映射

    double Origin[3];
    double Spacing[3];
    int WholeExtent[6];

private:
    igwVolumeRepresentation(const igwVolumeRepresentation&) = delete;
    void operator =(const igwVolumeRepresentation&) = delete;
};

#endif // igwVolumeRepresentation_H

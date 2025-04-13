#ifndef igwTextureRepresentation_H
#define igwTextureRepresentation_H
#include "igwRenderedRepresentation.h"
class vtkGeometryFilter;
class vtkCompositeSurfaceLICMapper;
class vtkSurfaceLICInterface;
class igwTextureRepresentation : public igwRenderedRepresentation
{
public:
    static igwTextureRepresentation* New();
    vtkTypeMacro(igwTextureRepresentation, igwRenderedRepresentation);
    void PrintSelf(ostream& os, vtkIndent indent) override;

    vtkSurfaceLICInterface* GetLICInterface();

    //***************************************************************************
    // Forwarded to vtkCompositeSurfaceLICMapper
    void SetEnable(bool val);

    void SetNumberOfSteps(int val);
    void SetStepSize(double val);
    void SetNormalizeVectors(int val);

    void SetEnhancedLIC(int val);

    void SetEnhanceContrast(int val);
    void SetLowLICContrastEnhancementFactor(double val);
    void SetHighLICContrastEnhancementFactor(double val);
    void SetLowColorContrastEnhancementFactor(double val);
    void SetHighColorContrastEnhancementFactor(double val);
    void SetAntiAlias(int val);

    void SetColorMode(int val);
    void SetMapModeBias(double val);
    void SetLICIntensity(double val);

    void SetMaskOnSurface(int val);
    void SetMaskThreshold(double val);
    void SetMaskColor(double* val);
    void SetMaskColor(double r, double g, double b)
    {
      double rgb[3] = { r, g, b };
      this->SetMaskColor(rgb);
    }
    void SetMaskIntensity(double val);

    void SetGenerateNoiseTexture(int val);
    void SetNoiseType(int val);
    void SetNoiseTextureSize(int val);
    void SetNoiseGrainSize(int val);
    void SetMinNoiseValue(double val);
    void SetMaxNoiseValue(double val);
    void SetNumberOfNoiseLevels(int val);
    void SetImpulseNoiseProbability(double val);
    void SetImpulseNoiseBackgroundValue(double val);
    void SetNoiseGeneratorSeed(int val);

    void SetCompositeStrategy(int val);

    void WriteTimerLog(const char* fileName);

    void SelectInputVectors(int, int, int, int attributeMode, const char* name);

    void SetLookupTable(vtkScalarsToColors *) override;

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


protected:

    igwTextureRepresentation();
    virtual ~igwTextureRepresentation();
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
    vtkSmartPointer<vtkGeometryFilter> GeometryFilter;
    vtkSmartPointer<vtkCompositeSurfaceLICMapper> SurfaceLICMapper;

private:
    void operator =(const igwTextureRepresentation&) = delete;
    igwTextureRepresentation(const igwTextureRepresentation &) = delete;
};

#endif // igwTextureRepresentation_H

#ifndef IGWFLOWINGSTREAMLINESREPRESENTATION_H
#define IGWFLOWINGSTREAMLINESREPRESENTATION_H

#include "igwRenderedRepresentation.h"

class vtkProperty;
class vtkActor;
class vtkMapper;
class vtkStreamLinesMapper;
class vtkScalarsToColors;
class igwFlowingStreamLinesRepresentation : public igwRenderedRepresentation
{
public:
    static igwFlowingStreamLinesRepresentation* New();
    vtkTypeMacro(igwFlowingStreamLinesRepresentation, igwRenderedRepresentation);
    void PrintSelf(ostream& os, vtkIndent indent);

    igwFlowingStreamLinesRepresentation();
    ~igwFlowingStreamLinesRepresentation();

    // Call the corresponding function in vtkStreamLinesMapper;
    vtkGetMacro(Alpha, double)
    vtkGetMacro(StepLength, double)
    vtkGetMacro(NumberOfAnimationSteps, double)
    vtkGetMacro(NumberOfParticles, int)
    vtkGetMacro(MaxTimeToLive, int)

    virtual void SetAnimate(bool val);
    virtual void SetAlpha(double val);
    virtual void SetStepLength(double val);
    virtual void SetNumberOfParticles(int val);
    virtual void SetMaxTimeToLive(int val);
    virtual void SetNumberOfAnimationSteps(int val);

    void SetInputerVectors(int, int, int, int attributeMode, const char* name);

    void SetInterpolateScalarsBeforeMapping(int val);

    void SetLookupTable(vtkScalarsToColors* val);

    void SetPointColorArrayName(const char* arrayName) override;

    /**
     * @brief SetMapScalars
     * @param val
     */
    void SetMapScalars(int val);

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

     /**
      * @brief InitParameters: Initialise the following parameters.
      * @brief InitParameters: 初始化下面的参数。
      */
     void InitParameters();
     bool Animate;
     double Alpha;
     double StepLength;
     int NumberOfParticles;
     int MaxTimeToLive;
     int NumberOfAnimationSteps;

     vtkStreamLinesMapper* Mapper;
     class igwFlowingStreamLinesObserver;
     vtkSmartPointer<igwFlowingStreamLinesObserver> FlowingStreamLinesObserver;

private:
    igwFlowingStreamLinesRepresentation(const igwFlowingStreamLinesRepresentation&) = delete;
    void operator =(const igwFlowingStreamLinesRepresentation&) = delete;
};

#endif // IGWFLOWINGSTREAMLINESREPRESENTATION_H

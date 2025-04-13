

#ifndef igwRenderedRepresentation_h
#define igwRenderedRepresentation_h

//#include "vtkViewsInfovisModule.h" // For export macro
#include "vtkDataRepresentation.h"
#include "vtkSmartPointer.h" // for SP ivars
#include <string>

class vtkApplyColors;
class vtkProp;
class igwRenderView;
class vtkRenderWindow;
class vtkTextProperty;
class vtkTexture;
class vtkView;
class vtkActor;
class vtkProperty;
class vtkMapper;
class vtkScalarsToColors;
class vtkDataSet;
class vtkScalarBarActor;
class vtkAxesActor;
class vtkOrientationMarkerWidget;

class igwRenderRepObserver;

class  igwRenderedRepresentation : public vtkDataRepresentation
{
public:
    static igwRenderedRepresentation* New();
    vtkTypeMacro(igwRenderedRepresentation, vtkDataRepresentation);
    void PrintSelf(ostream& os, vtkIndent indent) override;

    /**
     * @brief Set/GetDataSet: Set or Get the DataSet Pointer that this Representation dependes on.
     */
    virtual void SetDataSet(vtkDataSet*);
    virtual vtkDataSet* GetDataSet();

    /**
     * @brief GetArrayRange: 获取给定数组名的新的
     * @param arrayName
     */
    virtual double* GetArrayRange(int fieldAssociation, const char* arrayName);
    virtual double* GetArrayRange(const char *arrayName);
//  vtkSetMacro(LabelRenderMode, int);
//  vtkGetMacro(LabelRenderMode, int);

    virtual void SetAmbientColor(double r, double g, double b);
    virtual void SetColor(double r, double g, double b);
    virtual void SetDiffuseColor(double r, double g, double b);
    virtual void SetEdgeColor(double r, double g, double b);
    virtual void SetInterpolation(int val);
    virtual void SetLineWidth(double val);
    virtual void SetOpacity(double val);
    virtual void SetPointSize(double val);
    virtual void SetSpecularColor(double r, double g, double b);
    virtual void SetSpecularPower(double val);


    virtual void SetOrientation(double, double, double);
    virtual void SetOrigin(double, double, double);
    virtual void SetPickable(int val);
    virtual void SetPosition(double, double, double);
    virtual void SetScale(double, double, double);
    virtual void SetVisibility(bool visibility);

    virtual void UpdateDataSet(void* newData);

    /**
     * @brief SetLookupTable
     * @param val
     */
    virtual void SetLookupTable(vtkScalarsToColors* val);


    /**
     * @brief SetPointColorArrayName:
     * @param arrayName
     */
    virtual void SetPointColorArrayName(const char* arrayName);
    virtual const char* GetPointColorArrayName()
    {
        return this->GetPointColorArrayNameInternal();
    }

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
    virtual void SetInputArrayToProcess(
      int idx, int port, int connection, int fieldAssociation, const char* name) override;
    virtual void SetInputArrayToProcess(
      int idx, int port, int connection, int fieldAssociation, int fieldAttributeType) override
    {
      this->Superclass::SetInputArrayToProcess(
        idx, port, connection, fieldAssociation, fieldAttributeType);
    }
    virtual void SetInputArrayToProcess(int idx, vtkInformation* info) override
    {
      this->Superclass::SetInputArrayToProcess(idx, info);
    }
    virtual void SetInputArrayToProcess(int idx, int port, int connection, const char* fieldAssociation,
      const char* attributeTypeorName) override
    {
      this->Superclass::SetInputArrayToProcess(
        idx, port, connection, fieldAssociation, attributeTypeorName);
    }

    ///@{
    /**
     * Assign a data object as input. Note that this method does not
     * establish a pipeline connection. Use SetInputConnection() to
     * setup a pipeline connection.
     */
    virtual void SetInputData(vtkDataObject*);
    virtual void SetInputData(int, vtkDataObject*);
protected:
    igwRenderedRepresentation();
    virtual ~igwRenderedRepresentation() override;

    //@{
    /**
    * @brief AddPropOnNextRender: Subclasses may call these methods to add or remove props from the representation.
    *        Use these if the number of props/actors changes as the result of input connection
    *        changes.
    * @brief AddPropOnNextRender: 子类可能调用这些方法来从表征(representation)中添加或者删除道具。
    *        如果输入连接变化导致道具数量发生变化，请使用这些道具(props)/行为体(actors)。
    * @param p: The props to be added or removed.
    * @param p: 待增加或者移除的道具(props).
    */
    void AddPropOnNextRender(vtkProp* p);
    void RemovePropOnNextRender(vtkProp* p);
    //@}


    /**
    * @brief PrepareForRendering: The view will call this method before every render.
    *        Representations may add their own pre-render logic here.
    * @brief PrepareForRendering: 再每一次渲染之前视图(view)都会调用这个方法。
    *        表征(Representations)可以在这里添加自己的预渲染逻辑。
    * @param view: The view that owns the representation.
    * @param view: 拥有该表征(Representation)的视图(view)。
    */
    virtual void PrepareForRendering(igwRenderView* view);

    /**
    * @brief AddToView: Adds the representation to the view.  This is called from vtkView::AddRepresentation().
    * @brief AddToView: 增加表征(representation)到视图(view)中. 在vtkView的AddRepresentation()被调用
    * @param view: 视图
    * @return 如果添加成功返回true，反之返回false。
    */
    bool AddToView(vtkView* view) override;

    friend class igwRenderView;

    int LabelRenderMode;

    vtkActor* Actor;
    vtkProperty* Property;
    vtkDataSet* DataSet;


    /**
     * @brief Set or Get the array name to color the data, default is nullptr;
     * @brief 设置或获取用于颜色映射的数组名，默认是空指针。
     */
    vtkGetStringMacro(CellColorArrayNameInternal)
    vtkSetStringMacro(CellColorArrayNameInternal)
    char* CellColorArrayNameInternal;

    /**
     * @brief Set or Get the array name to color the data, default is nullptr;
     * @brief 设置或获取用于颜色映射的数组名，默认是空指针。
     */
    vtkSetStringMacro(PointColorArrayNameInternal);
    vtkGetStringMacro(PointColorArrayNameInternal);
    char* PointColorArrayNameInternal;

    vtkSmartPointer<vtkScalarBarActor> ScalarBarActor;

    vtkSmartPointer<igwRenderRepObserver> Observer;


private:
  igwRenderedRepresentation(const igwRenderedRepresentation&) = delete;
  void operator=(const igwRenderedRepresentation&) = delete;

  class Internals;
  Internals* Implementation;
};

#endif


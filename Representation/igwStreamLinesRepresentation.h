#ifndef IGWSTREAMLINESREPRESENTATION_H
#define IGWSTREAMLINESREPRESENTATION_H

#include "igwRenderedRepresentation.h"

class vtkActor;
class vtkMapper;
class vtkPolyDataMapper;
class vtkLineWidget;
class vtkStreamTracer;
class vtkDataSet;
class vtkAlgorithmOutput;
class vtkRibbonFilter;
class vtkPlaneWidget;
class vtkPlane;
class vtkStreamSurface;
class vtkTubeFilter;

// 种子生成方式
enum SeedWidget{
    USE_PLANE_WIDGET,
    USE_LINE_WIDGET
};

enum StreamLinesType{
    STREAM_LINE = 0,    //流线
    STREAM_TUBE,        //流管
    STREAM_RIBBON,      //流带
    STREAM_SURFACE      //流面
};

class igwStreamLinesRepresentation : public igwRenderedRepresentation
{
public:
    static igwStreamLinesRepresentation* New();
    vtkTypeMacro(igwStreamLinesRepresentation, igwRenderedRepresentation)
    void PrintSelf(std::ostream &os, vtkIndent indent) override;


    /**
     * @brief SetSourceConnection: Setting up the Integration Data Source or out port. The data source can be points, line, etc.
     * @brief SetSourceConnection: 设置积分起点的数据源。数据源可以是一堆点，后者一条线上的点。
     */
    void SetSourceConnection(vtkAlgorithmOutput* );
    void SetSourceData(vtkDataSet* source);

    /**
     * @brief SetResolutionToUpdate: Set the number of the seed point.
     * @brief SetResolutionToUpdate: 设置种子点个数
     * @param resolution
     */
    void SetResolutionToUpdate(int resolution);


    /**
     * @brief LineWidgetOn/Off: Set the LineWidget On/Off.
     * @brief LineWidgetOn/Off: 显示或关闭线组件。
     */
    void LineWidgetOn();
    void LineWidgetOff();
    vtkLineWidget* GetLineWidget();
    vtkGetMacro(LineVisibility, double)
    vtkSetMacro(LineVisibility, double)

    /**
     * @brief PlaneWidgetOn/Off: Set the PlaneWidget On/Off.
     * @brief PlaneWidgetOn/Off: 显示或关闭平面组件。
     */
    void PlaneWidgetOn();
    void PlaneWidgetOff();
    vtkPlaneWidget* GetPlaneWidget();
    vtkGetMacro(PlaneVisibility, double)
    vtkSetMacro(PlaneVisibility, double)
    vtkPlane* GetPlane();

    /**
     * @brief Set the Normal.
     */
    void SetPlaneNormalToXAxis();
    void SetPlaneNormalToYAxis();
    void SetPlaneNormalToZAxis();
    void SetPlaneNormal(double x, double y, double z);
    void SetPlaneNormal(double normal[3]);
    double* GetPlaneNormal();

    void SetPlaneOrigin(double x, double y, double z);
    void SetPlaneOrigin(double origin[3]);
    double* GetPlaneOrigin();


    /**
     * @brief SetSeedType: Set the type of widget that generates seed points. USE_LINE_WIDGET is vtkLineWidget
     *        USE_PLANE_WIDGET is vtkPlaneWidget. defalue is USE_PLANE_WIDGET.
     * @param type
     */
    void SetSeedType(SeedWidget type);
    int GetSeedType();

    /**
     * @brief UpdateSeed
     */
    void UpdateSeed();

    /**
     * @brief SetPointColorArrayName
     * @param arrayName
     */
    void SetPointColorArrayName(const char* arrayName) override;

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

    //-------------------设置相关参数------------------------

    /**
     * @brief ChaneStreamLineType: Set the type of the stream lines.
     * @brief ChaneStreamLineType: 设置流线类型，默认为
     * @param type
     */
    int GetStreamLineType();

    void SetStreamLineType(StreamLinesType type);


    /**
     * @brief SetStreamLinesDirection
     * @param d
     */
    vtkGetMacro(Direction, int);
    void SetStreamLineDirection(int d);

    /**
     * @brief SetStreamLinesWidth
     * @param w
     */
    vtkGetMacro(StreamLineWidth, double);
    void SetWidth(double w);

    vtkGetMacro(MaxPropagation, double);
    void SetLength(int l);

    vtkGetMacro(Resolution, int);
    void SetLineSeedResolution(int r);

    vtkGetMacro(NumberOfXResolution, int);
    void SetPlaneSeedXResolution(int x);

    vtkGetMacro(NumberOfYResolution, int);
    void SetPlaneSeedYResolution(int y);

    void GenerateEntropySeeds();
protected:

    igwStreamLinesRepresentation();
    ~igwStreamLinesRepresentation();

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

    //StreamTracer 需要的参数
    vtkStreamTracer* StreamTracer;

    vtkSetMacro(MaxPropagation, double);
    double MaxPropagation;

    vtkSetMacro(MaxStep, double);
    vtkGetMacro(MaxStep, double);
    double MaxStep;

    vtkSetMacro(MinStep, double);
    vtkGetMacro(MinStep, double);
    double MinStep;

    vtkSetMacro(InitStep, double);
    vtkGetMacro(InitStep, double);
    double InitStep;

    SeedWidget SeedWidgetType;

    //vtkStreamSurface* StreamSurface;
    vtkPolyDataMapper* Mapper;

    // 线种子点选取
    vtkPolyData* Seeds;
    vtkLineWidget* LineWidget;
    bool LineVisibility;

    class LWCallback;
    vtkSmartPointer<LWCallback> GenerateStreamLines;

    // 平面种子点选取
    vtkPlaneWidget* PlaneWidget;
    class PWCallback;
    vtkSmartPointer<PWCallback> PlaneWidgetCallback;

    bool PlaneVisibility;

    class EnableActorCallback;
    vtkSmartPointer<EnableActorCallback> BeginInteraction;


    // 流带、流管、流面
    vtkSmartPointer<vtkRibbonFilter> RibbonFilter;

    vtkSmartPointer<vtkTubeFilter> TubeFilter;

    vtkSmartPointer<vtkStreamSurface> StreamSurface;

    // 流线、流带、流管、流面四选一，默认为流线
    StreamLinesType Type;

    /**
     * @brief Set the Width of the Tube or Ribbon
     */
    vtkSetMacro(StreamLineWidth, double);
    double StreamLineWidth;     // 流带和流管的宽度

    /**
     * @brief Set the Number of the seeds
     */
    vtkSetMacro(Resolution, int);
    int Resolution;             //使用LineWidget时的种子点数量

    vtkSetMacro(NumberOfXResolution, int);
    int NumberOfXResolution;              // 使用PlaneWidget生成流线种子时的X

    vtkSetMacro(NumberOfYResolution, int);
    int NumberOfYResolution;              // 使用PlaneWidget成成流线种子时的Y

    int Direction;

    bool isLinePlaced = false;
    bool isPlanePlaced = false;


private:

    void InitCallback();

    /**
     * @brief ConstructLineWidget: Construct the LineWiget to Generate seeds.
     * @brief ConstructLineWidget: 构造场景中用于生成种子点的线组件
     */
    void ConstructLineWidget();

    /**
     * @brief ConstructPlaneWidget: Construct the PlaneWiget to Generate seeds.
     * @brief ConstructPlaneWidget: 构造场景中用于生成种子点的平面组件
     */
    void ConstructPlaneWidget();


    /**
     * @brief InitParameters: Init the Parameters of vtkStreamTracer;
     * @brief InitParameters: 初始化流线生成相关的参数。包括积分
     */
    void InitParameters();

    /**
     * @brief InitStreamTracer: Init vtkStreamTracer.
     * @brief InitStreamTracer: 初始化vtkStreamTracer。设置积分类型，积分步长等。
     */
    void InitStreamTracer();

    /**
     * @brief InitStreamTube: Init InitStreamTube.
     * @brief InitStreamTube: 初始化InitStreamTube。
     */
    void InitStreamTube();

    /**
     * @brief InitStreamRibbon: Init InitStreamRibbon.
     * @brief InitStreamRibbon: 初始化InitStreamRibbon
     */
    void InitStreamRibbon();

    /**
     * @brief InitStreamSurface: Init InitStreamSurface.
     * @brief InitStreamSurface: 初始化InitStreamSurface。
     */
    void InitStreamSurface();

    igwStreamLinesRepresentation(const igwStreamLinesRepresentation &) = delete;
    void operator =(const igwStreamLinesRepresentation&) = delete;
};

#endif // IGWSTREAMLINESREPRESENTATION_H

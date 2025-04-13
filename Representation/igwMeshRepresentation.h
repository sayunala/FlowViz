#ifndef igwMeshRepresentation_H
#define igwMeshRepresentation_H

#include "igwRenderedRepresentation.h"
#include "vtkSmartPointer.h"
class vtkMapper;
class vtkPlaneSource;
class vtkPolyDataMapper;
class igwMeshRepresentation : public igwRenderedRepresentation
{
public:
    static  igwMeshRepresentation* New();
    vtkTypeMacro(igwMeshRepresentation, igwRenderedRepresentation)
    void PrintSelf(std::ostream &os, vtkIndent indent) override;

    igwMeshRepresentation();
    virtual ~igwMeshRepresentation();

    /**
     * @brief SetLookupTable: Set the Color Map of the Mapper.
     * @brief SetLookupTable: 设置Mapper的颜色映射
     * @param val
     */
    void SetLookupTable(vtkScalarsToColors* val) override;

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
     * @brief SetXResolution:设置行数和列数,xr为行数，yr为列数
     * @param xr/yr
     */
    void SetXResolution(int xr);
    void SetYResolution(int yr);

    /**
     * @brief vtkSet/Get...:获取行数和列数
     */
    vtkSetMacro(Row, int);
    vtkGetMacro(Row, int);
    vtkSetMacro(Col, int);
    vtkGetMacro(Col, int);

    /**
     * @brief GetCellArray: 获取映射蒙皮的属性数组
     * @return vtkDataArray*: 返回数组指针，可以获取数组数据
     */
    vtkDataArray* GetCellArray();
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


    /**
     * @brief UpdateData: Update the Mesh Cell Data
     * @param newdata
     * @return
     */
    void UpdateData(void* newdata);

    void InitCellData(const char* arrayname);

    vtkPolyDataMapper* Mapper;
    vtkSmartPointer<vtkPlaneSource> PlaneSource;
    vtkSmartPointer<vtkImageData> MeshGrid;

    class igwMeshDataUpadetObeserver;
    vtkSmartPointer<igwMeshDataUpadetObeserver> MeshDataUpdateObeserver;

    // 蒙皮行数列数
    int Row;
    int Col;


private:
    igwMeshRepresentation(const igwMeshRepresentation&) = delete;
    void operator =(const igwMeshRepresentation&) = delete;
};

#endif // igwMeshRepresentation_H

#ifndef IGWIOCORE_H
#define IGWIOCORE_H

#include "vtkSmartPointer.h"
#include "vtkUnstructuredGrid.h"
#include "vtkObject.h"

#include <map>
class vtkTable;
class vtkDataObject;

class vtkAlgorithm;
class igwReadFile;
class igwIOCore : public vtkObject
{
public:

    enum class FileType
    {
        CGNS,
        OPENFOAM,
        ETKF,
        FLUENT,
        CFF_FLUENT,
        LEGENCY_VTK,
        VTK_SERIES,
        IGW_SERIES
    };


    static igwIOCore* New();
    vtkTypeMacro(igwIOCore, vtkObject)
    void PrintSelf(ostream&os, vtkIndent indent) override;


    static igwIOCore* GetInstance();

    /**
     * @brief ReadETKFDataFile:读取ETKF算法txt数据文件
     * @param fileName:文件路径
     * @return
     */
    vtkSmartPointer<vtkTable> ReadETKFDataFile(const char* fileName);

    /**
     * @brief ReadETKFGridFile: 读取ETKF算法网格文件
     * @param fileName
     * @return
     */
    vtkSmartPointer<vtkDataObject> ReadETKFGridFile(const char* fileName);

    /**
     * @brief GetETKFData
     * @param gridFile: 网格文件
     * @param dataFile: 数据文件
     * @return
     */
    vtkSmartPointer<vtkDataObject> GetETKFData(const char* gridFile, const char* dataFile);

    /**
     * @brief ReadSTLData
     * @param stlFile
     * @return
     */
    vtkSmartPointer<vtkDataObject> ReadSTLData(const char* stlFile);

    /**
     * @brief ReadPLTData
     * @param pltFile
     * @return
     */
    vtkSmartPointer<vtkDataObject> ReadPLTData(const char* pltFile);

    /**
     * @brief ReadVTKData
     * @param vtkFile
     * @return
     */
    vtkDataObject* ReadVTKData(const char* vtkFile);


    /**
     * @brief ReadCSVFile
     * @param fileName
     * @return
     */
    vtkSmartPointer<vtkDataObject> ReadCSVFile(const char* fileName);


    vtkDataObject* ReadCGNSFile(const char* fileName);

    vtkDataObject *ReadOpenFOAMFile(const char* fileName);
    vtkSmartPointer<vtkDataObject> ReadCGNSSeriesFile(const char* fileName);

    static vtkDataObject* ReadFile(const char* fileName, FileType type);
    static vtkDataObject* ReadFile(const char* fileName, const char suffix);

    static const char* GetOpenFileName();


protected:
    igwIOCore();
    ~igwIOCore();

    // 尝试一下
    static std::map<FileType, igwReadFile*> ReaderFileMap;             // key: ReaderType, Value ReaderAlgorithm

    static std::map<FileType, const char*> FileTypeMapClass;     // key: ReaderType, Value ReaderClassName



};

#endif // IGWIOCORE_H

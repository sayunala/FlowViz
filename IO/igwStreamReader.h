#ifndef IGWSTREAMREADER_H
#define IGWSTREAMREADER_H
#include "igwStreamIO.h"
#include "vtkSmartPointer.h"
class vtkAlgorithm;
class vtkDataSet;
class vtkTable;
class vtkUnstructuredGrid;
/**
 * @brief ConnectDataAndAttributes: 把table 与 gridData给映射上,使用分块进行加速
 * @param table: 属性表
 * @param gird: 流场拓扑数据集
 */
void ConnectDataAndAttributes(vtkTable* table, vtkSmartPointer<vtkDataSet> gridData);

/**
 * @brief ConstructDataset:根据.txt文件名和.cas 文件名构造vtkDataSet数据
 * @param txtFileName: txt数据集路径
 * @param casFileName: Fluent .cas文件路径
 * @return
 */
vtkSmartPointer<vtkDataSet> ConstructDataset(const char* txtFileName ,const char *casFileName);

/**
 * @brief ConnetDataWithGrid:把table 与 gridData给映射上
 * @param table: 属性表
 * @param gird: 流场拓扑数据集
 */
void ConnetDataWithGrid(vtkTable* table, vtkSmartPointer<vtkDataSet> gridData);

/**
 * @brief ConstrucNACA0012DataSet: 构造NACA0012表面数据集，用于实时重构可视化显示。
 * @param fileName
 */

vtkSmartPointer<vtkDataSet> ConstrucNACA0012DataSet(const char* fileName);
#endif // IGWSTREAMREADER_H

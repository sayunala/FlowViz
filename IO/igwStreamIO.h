/**********************************************
* @projectName   iGreatWorks
* @file          igwStreamIO.h
* @brief         流场数据输入输出函数
* @author        ZYB
* @date          2023-09-24
* @version       1.0
**********************************************/

#ifndef IGWSTREAMIO_H
#define IGWSTREAMIO_H

#include"vtkUnstructuredGrid.h"
class vtkTable;

/**
 * @brief 读取TXT流场数据,使用vtkDelimitedTextReader，速度很慢
 * @param 流场文件名
 * @return vtkTable
 */
vtkSmartPointer<vtkTable> ReadStreamData(const char* filename, const char* arg);
/**
 * @brief DelimitedTextReader 使用OpenMp加速后的读取文件
 * @param filename：流场文件名
 * @return 构造好的数据表格
 */
vtkSmartPointer<vtkTable> DelimitedTextReader(const char* filename);

/**
 * @brief 读取.cas网格文件
 * @param 网格文件路径
 * @return vtkUnstructedGrid
 */
vtkSmartPointer<vtkUnstructuredGrid> ReadCASFile(const char* filename);



#endif

#include "igwStreamReader.h"

#include "vtkAlgorithm.h"
#include "vtkAppendFilter.h"
#include "vtkTable.h"
#include "vtkDataArray.h"
#include "vtkDoubleArray.h"
#include "vtkPointLocator.h"
#include "vtkNew.h"
#include "vtkSmartPointer.h"
#include "vtkDataSet.h"
#include "vtkPolyData.h"
#include "vtkPointData.h"
#include "vtkAppendFilter.h"
#include "vtkLineSource.h"
#include "vtkUnstructuredGrid.h"

vtkSmartPointer<vtkDataSet> ConstructDataset(const char *txtFileName, const char *casFileName)
{
    // 读取txt文件
    vtkSmartPointer<vtkTable> table = DelimitedTextReader(txtFileName);
    // 读取cas文件
    vtkSmartPointer<vtkDataSet> gridData = ReadCASFile(casFileName);

    ConnectDataAndAttributes(table, gridData);


    return gridData;

}
void ConnectDataAndAttributes(vtkTable *table, vtkSmartPointer<vtkDataSet> gridData)
{
    std::vector<vtkSmartPointer<vtkDoubleArray>> arrays;//arrays
    int n = table->GetNumberOfColumns() - 4;
    arrays.resize(n);

    for(int i = 0; i < arrays.size(); i++){
        arrays[i] = vtkSmartPointer<vtkDoubleArray>::New();
        arrays[i]->SetName(table->GetColumnName(i + 4));
        arrays[i]->SetNumberOfTuples(table->GetNumberOfRows());
    }

     vtkNew<vtkDoubleArray> velocity;
     velocity->SetNumberOfComponents(3); // 3d velocity (ie x,y,z)
     velocity->SetName("velocity");
     velocity->SetNumberOfTuples(table->GetNumberOfRows());
    //设置属性个数

    // 数据设置

    vtkNew<vtkPointLocator> gridLocator;
    gridLocator->SetDataSet(gridData);
    gridLocator->Update();

    vtkIdType blockSize = 10;
    double tolerance = 1e-7;

    int UNMATCH_COUNT = 0;



    for (vtkIdType i = 0; i < table->GetNumberOfRows(); i += blockSize)
    {
        //提取block_size的点数
        vtkNew<vtkPointLocator> pointlocator;
        vtkNew<vtkPolyData> pointset;
        vtkNew<vtkPoints> gridPoints;
        gridPoints->SetNumberOfPoints(blockSize);

        for(vtkIdType j = 0; j < blockSize; j++){
            gridPoints->SetPoint(j, gridData->GetPoint(i + j));
        }

        pointset->SetPoints(gridPoints);
        pointlocator->SetDataSet(pointset);
        pointlocator->Update();
//        #pragma omp parallel for num_threads(16)
        for(vtkIdType j = 0; j < blockSize; j++){
            //在网格中查找点
            double coord[3] = {table->GetValue(i + j, 1).ToDouble(), table->GetValue(i + j, 2).ToDouble(), table->GetValue(i + j, 3).ToDouble() };
            vtkIdType closetId = pointlocator->FindClosestPoint(coord);

            double grid_point[3];
            pointset->GetPoint(closetId, grid_point);
            double distance = std::sqrt(std::pow( grid_point[0] - coord[0], 2) + std::pow( grid_point[1] - coord[1], 2) + std::pow( grid_point[2] - coord[2], 2));

            if(distance < tolerance){

                for(int k = 0; k < arrays.size(); k++){
                    arrays[k]->SetTuple1(i + closetId, table->GetValue(i + j, k + 4).ToDouble());
                }

//#pragma omp critical
                double v[3];
                v[0] = table->GetValue(i + j, 5).ToDouble();
                v[1] = table->GetValue(i + j, 6).ToDouble();
                v[2] = table->GetValue(i + j, 7).ToDouble();
                velocity->SetTuple3(i + closetId, v[0], v[1], v[2]);
            }
            else {
                //不匹配
                UNMATCH_COUNT++;
                closetId = gridLocator->FindClosestPoint(coord);
//
//#pragma omp critical

                for(int k = 0; k < arrays.size(); k++){
                    arrays[k]->SetTuple1(closetId, table->GetValue(i + j, k + 4).ToDouble());
                }
                double v[3];
                v[0] = table->GetValue(i + j, 5).ToDouble();
                v[1] = table->GetValue(i + j, 6).ToDouble();
                v[2] = table->GetValue(i + j, 7).ToDouble();
                velocity->SetTuple3(closetId, v[0], v[1], v[2]);
            }

        }
    }


    for(int i = 0; i < arrays.size(); i++){

        if(i == 0)
            gridData->GetPointData()->SetScalars(arrays[i]);
        else
            gridData->GetPointData()->AddArray(arrays[i]);

    }
    gridData->GetPointData()->SetVectors(velocity);

}

vtkSmartPointer<vtkDataSet> ConstrucNACA0012DataSet(const char *fileName)
{
#define C 0.1524
    vtkSmartPointer<vtkTable> table = ReadStreamData(fileName, ",");

    vtkSmartPointer<vtkLineSource> line = vtkSmartPointer<vtkLineSource>::New();
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();

    vtkNew<vtkDoubleArray> press;
    press->SetNumberOfComponents(1);
    press->SetName(table->GetColumnName(3));
    line->SetPoints(points);

    vtkIdType points_number = table->GetNumberOfRows();
    for(vtkIdType i = 0; i < points_number; i++){
        points->InsertNextPoint(table->GetValue(i, 0).ToDouble() * C, table->GetValue(i, 1).ToDouble() * C, table->GetValue(i, 2).ToDouble() * C);
        press->InsertNextTuple1(table->GetValue(i, 3).ToDouble());
    }

    line->Update();
    vtkIdType id[2] = {table->GetNumberOfRows() - 1, 0};
    line->GetOutput()->GetLines()->InsertNextCell(2, id);
    line->Update();
    line->GetOutput()->GetPointData()->SetScalars(press);
    vtkDataSet* data = line->GetOutput();
    return data;
}

void ConnetDataWithGrid(vtkTable *table, vtkSmartPointer<vtkDataSet> gridData)
{

    std::vector<vtkSmartPointer<vtkDoubleArray>> arrays;//arrays
    // 去除前四列
    int n = table->GetNumberOfColumns() - 4;
    arrays.resize(n);

    for(int i = 0; i < arrays.size(); i++){
        arrays[i] = vtkSmartPointer<vtkDoubleArray>::New();
        arrays[i]->SetName(table->GetColumnName(i + 4));
        arrays[i]->SetNumberOfTuples(table->GetNumberOfRows());
    }
    vtkNew<vtkDoubleArray> velocity;
    velocity->SetNumberOfComponents(3); // 3d normals (ie x,y,z)
    velocity->SetName("velocity");
    velocity->SetNumberOfTuples(table->GetNumberOfRows());

    //设定定位器
    vtkNew<vtkPointLocator> pointlocator;
    pointlocator->SetDataSet(gridData);
    for (vtkIdType i = 0; i < table->GetNumberOfRows(); i++)
    {
      //在网格中查找点
      double coord[3] = {table->GetValue(i, 1).ToDouble(), table->GetValue(i, 2).ToDouble(), table->GetValue(i, 3).ToDouble()};
      vtkIdType closetId = pointlocator->FindClosestPoint(coord);

      //属性设置
      for(int j = 0; j < arrays.size(); j++){
          // 2024/6/22修改前四列为
          arrays[j]->SetTuple1(closetId, table->GetValue(i, j + 4).ToDouble());
      }
      double v[3];
      v[0] = table->GetValue(i, 5).ToDouble();
      v[1] = table->GetValue(i, 6).ToDouble();
      v[2] = table->GetValue(i, 7).ToDouble();
      velocity->SetTuple3(closetId, v[0], v[1], v[2]);
    }
    for(int i = 0; i < arrays.size(); i++){
        if(i == 0)
            gridData->GetPointData()->SetScalars(arrays[i]);
        else
            gridData->GetPointData()->AddArray(arrays[i]);
    }
    gridData->GetPointData()->SetVectors(velocity);
}

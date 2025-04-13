#include"igwStreamIO.h"
#include"vtkMultiBlockDataSet.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <omp.h>
#include <regex>
#include<chrono>
#include "vtkVariantArray.h"
#include "vtkSmartPointer.h"
#include "vtkDelimitedTextReader.h"
#include "vtkTable.h"
#include "vtkFLUENTReader.h"
#include "vtkNew.h"
vtkSmartPointer<vtkTable> ReadStreamData(const char *filename, const char* arg)
{
    vtkNew<vtkDelimitedTextReader> reader;
    reader->SetFileName(filename);
    reader->DetectNumericColumnsOn();
    // 分割符
    reader->SetFieldDelimiterCharacters(arg);
//    reader->SetMergeConsecutiveDelimiters(true);
    reader->SetHaveHeaders(true);
    reader->Update();

    vtkSmartPointer<vtkTable> table = reader->GetOutput();// 生成第一个Table
    table->Print(std::cout);
    if(table->GetColumnName(table->GetNumberOfColumns() - 1) == "")
        std::cout << "null" <<std::endl;
    return table;
}

vtkSmartPointer<vtkTable> DelimitedTextReader(const char* filename){

    //std::string filename = "all_data_oneram6.txt";
       std::ifstream file(filename);

       if (!file.is_open()) {
           std::cout << "Failed to open file: " << filename << std::endl;
           return nullptr;
       }


       std::string firstLine;
       std::getline(file, firstLine);  // 读取第一行
       std::regex rege("\\s+");
       std::string result = std::regex_replace(firstLine, rege, " ");

       std::istringstream str(firstLine);
       std::string token;
       std::vector<std::string> stringData;
       while (str >> token)
       {
           stringData.push_back(token);
       }
       // 输出第一行字符串
       std::cout << "First line: " << result << std::endl;
       for (int i = 0; i < stringData.size(); ++i) {
           std::cout << "Header: " << stringData[i] << std::endl;
       }
       //std::vector<double> data;
       std::vector<std::string> lineData;
       double value;
       std::string line;

       //Get all line
       while (std::getline(file, line)) {
             lineData.push_back(std::move(line));
       }
       file.close();

       int row = lineData.size();
       int col = stringData.size();

       vtkSmartPointer<vtkTable> table = vtkSmartPointer<vtkTable>::New();
       for(int i = 0; i < col; i++)
       {
           vtkSmartPointer<vtkVariantArray> col =
               vtkSmartPointer<vtkVariantArray>::New();
           col->SetNumberOfValues(row);
           col->SetName(stringData[i].c_str());
           table->AddColumn(col);
       }
       double startTime = omp_get_wtime();
       //omp_set_nested(1);
   #pragma omp parallel for
       for (int i = 0; i < row; ++i) {
           std::istringstream iss(lineData[i]);
           for (int j = 0; j < col; ++j) {
               double value;
               iss >> value;
               table->SetValue(i, j, vtkVariant(value));
               //std::cout << "j Thread ID: " << omp_get_thread_num() << std::endl;
           }
           //std::cout << "i Thread ID: " << omp_get_thread_num() << std::endl;

       }
       double endTime = omp_get_wtime();
       table->Print(std::cout);
       std::cout << "计算耗时: " << endTime - startTime << std::endl;

       return table;
}

vtkSmartPointer<vtkUnstructuredGrid> ReadCASFile(const char *filename)
{

    vtkNew<vtkFLUENTReader> fluentreader;
    fluentreader->SetFileName(filename);
    fluentreader->Update();

    vtkSmartPointer<vtkUnstructuredGrid> grid_data = vtkUnstructuredGrid::SafeDownCast(fluentreader->GetOutput()->GetBlock(0));

    return grid_data;
}




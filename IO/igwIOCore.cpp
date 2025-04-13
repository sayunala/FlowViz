#include "igwIOCore.h"

#include "vtkObjectFactory.h"
#include "vtkTable.h"

#include "vtkFLUENTReader.h"
#include "vtkPolyDataReader.h"
#include "vtkDelimitedTextReader.h"
#include "vtkUnstructuredGridReader.h"
#include "vtkDataSetReader.h"
#include "vtkTecplotReader.h"
#include "vtkSTLReader.h"

#include "vtkMultiBlockDataSet.h"
#include "vtkXMLMultiBlockDataReader.h"
#include "vtkXMLDataReader.h"
#include "vtkDataSet.h"
#include "vtkCGNSReader.h"
#include "vtkCGNSFileSeriesReader.h"
#include "vtkObjectBase.h"
#include <QFileDialog>


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <omp.h>
#include <regex>
#include<chrono>
#include <vtkVariantArray.h>

#include "igwReadFile.h"
#include "igwReadOpenFOAMFile.h"
#include "igwReadCGNSFile.h"
#include "igwReadeXMLMultiBlockFile.h"
#include "igwReadSeriesFiles.h"
#include "igwReadVtkFile.h"
vtkStandardNewMacro(igwIOCore)

std::map<igwIOCore::FileType, const char*> igwIOCore::FileTypeMapClass = {
            {igwIOCore::FileType::CGNS, "igwReadCGNSFile"},
            {igwIOCore::FileType::OPENFOAM, "igwReadOpenFOAMFile"},
            {igwIOCore::FileType::VTK_SERIES, "igwReadSeriesVtkFile"},
            {igwIOCore::FileType::LEGENCY_VTK, "igwReadVtkFile"}


        };

std::map<igwIOCore::FileType, igwReadFile*> igwIOCore::ReaderFileMap;
igwIOCore::igwIOCore()
{
    ReaderFileMap = {
        {igwIOCore::FileType::OPENFOAM, igwReadOpenFOAMFile::New()},
        {igwIOCore::FileType::CGNS, igwReadCGNSFile::New()},
        {igwIOCore::FileType::VTK_SERIES, igwReadeXMLMultiBlockFile::New()},
        {igwIOCore::FileType::IGW_SERIES, igwReadSeriesFiles::New()},
        {igwIOCore::FileType::LEGENCY_VTK, igwReadVtkFile::New()}
    };
}

igwIOCore::~igwIOCore()
{
//    for(std::pair<igwIOCore::FileType, igwReadFile*> item: ReaderFileMap)
//    {
//        item.second->Delete();
//    }
}
void igwIOCore::PrintSelf(std::ostream &os, vtkIndent indent)
{

}
igwIOCore *igwIOCore::GetInstance()
{
    vtkSmartPointer<igwIOCore> Instance;
    if (Instance.GetPointer() == nullptr)
    {
        igwIOCore* temp = igwIOCore::New();
        Instance = temp;
        temp->FastDelete();
    }

    return Instance;
}

vtkSmartPointer<vtkTable> igwIOCore::ReadETKFDataFile(const char *fileName)
{
    //std::string filename = "all_data_oneram6.txt";
       std::ifstream file(fileName);

       if (!file.is_open()) {
           std::cout << "Failed to open file: " << fileName << std::endl;
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

vtkSmartPointer<vtkDataObject> igwIOCore::ReadETKFGridFile(const char *fileName)
{

    vtkNew<vtkFLUENTReader> fluentreader;
    fluentreader->SetFileName(fileName);
    fluentreader->Update();

//    vtkSmartPointer<vtkUnstructuredGrid> grid_data = vtkUnstructuredGrid::SafeDownCast(fluentreader->GetOutput()->GetBlock(0));
    return nullptr;
}

vtkSmartPointer<vtkDataObject> igwIOCore::GetETKFData(const char *gridFile, const char *dataFile)
{
    vtkDataObject* gridData = ReadETKFGridFile(gridFile);
    vtkDataObject* txtData = ReadETKFDataFile(dataFile);

    return gridData;

}

vtkSmartPointer<vtkDataObject> igwIOCore::ReadSTLData(const char *stlFile)
{
    vtkNew<vtkSTLReader> reader;
    reader->SetFileName(stlFile);
    reader->Update();
    return reader->GetOutput();
}

vtkSmartPointer<vtkDataObject> igwIOCore::ReadPLTData(const char *pltFile)
{
    if(pltFile == nullptr)
    {
        return nullptr;
    }

    vtkNew<vtkTecplotReader> reader;

    reader->SetFileName(pltFile);
    reader->Update();
    return reader->GetOutput();
}

vtkDataObject* igwIOCore::ReadVTKData(const char *vtkFile)
{
    if(vtkFile == nullptr)
    {
        return nullptr;
    }
    vtkDataSetReader* reader = vtkDataSetReader::New();
    reader->SetFileName(vtkFile);
    reader->Update();
//    reader->GetOutput()->Print(std::cout);
//    vtkDataObject* data = vtkDataObject::New();

    vtkDataObject* data = vtkDataObject::New();

    vtkSmartPointer<vtkDataObject> o;

    data = reader->GetOutput();
    if(data == nullptr)
    {
        return nullptr;
    }
    data->SetObjectName(vtkFile);



    return data;

}

vtkDataObject* igwIOCore::ReadCGNSFile(const char *fileName)
{
    if(fileName == nullptr)
    {
        return nullptr;
    }
    vtkCGNSReader* reader = vtkCGNSReader::New();
    reader->LoadMeshOn();


    reader->SetFileName(fileName);
    reader->SetDataLocation(vtkCGNSReader::CELL_DATA);

    reader->Update();
    int basearr = reader->GetNumberOfBaseArrays();
    int facearr = reader->GetNumberOfFaceArrays();
    int familyarrays = reader->GetNumberOfFamilyArrays();
    int cellarr = reader->GetNumberOfCellArrays();
    int pointarr = reader->GetNumberOfPointArrays();
    std::cout << basearr << std::endl;
    std::cout << facearr << std::endl;
    std::cout << familyarrays<< std::endl;
    std::cout << cellarr << std::endl;
    std::cout << pointarr << std::endl;
    for(int i = 0; i < reader->GetNumberOfPointArrays();++i)
    {
        const char* array = reader->GetPointArrayName(i);
        reader->SetPointArrayStatus(array, 1);
    }
    reader->Update();
    vtkDataObject* block0 = reader->GetOutput();

    vtkDataObject* data = vtkDataObject::New();
    data = reader->GetOutput();
    vtkSmartPointer<vtkDataObject> o;

//    o = reader->GetOutput();
    if(data == nullptr)
    {
        return nullptr;
    }
    data->SetObjectName(fileName);
    data->Print(std::cout);
    return data;
}

vtkDataObject *igwIOCore::ReadOpenFOAMFile(const char *fileName)
{
    return nullptr;
}

vtkSmartPointer<vtkDataObject> igwIOCore::ReadCGNSSeriesFile(const char *fileName)
{
    if(fileName == nullptr)
    {
        return nullptr;
    }
    vtkNew<vtkCGNSFileSeriesReader>reader;
    vtkNew<vtkCGNSReader> CGNSRead;
    CGNSRead->SetLoadBndPatch(true);
    CGNSRead->SetLoadMesh(true);

    reader->SetReader(CGNSRead);
    int a = reader->CanReadFile(fileName);
    std::cout << a << std::endl;
    reader->AddFileName(fileName);
    reader->Update();
    int basearr = CGNSRead->GetNumberOfBaseArrays();
    int facearr = CGNSRead->GetNumberOfFaceArrays();
    int pointarr = CGNSRead->GetNumberOfFamilyArrays();
//    vtkDataObject* data = vtkDataObject::New();

    vtkSmartPointer<vtkDataObject> o;

    o = reader->GetOutput();
    o->Print(std::cout);
    if(o == nullptr)
    {
        return nullptr;
    }
    o->SetObjectName(fileName);

    return o;
}

vtkDataObject *igwIOCore::ReadFile(const char *fileName, igwIOCore::FileType type)
{

    if(fileName == nullptr)
    {

        return nullptr;
    }
    if(ReaderFileMap.count(type) == 0)
    {

        return nullptr;
    }
//    const char* className = FileTypeMapClass[type];
    igwReadFile* object = ReaderFileMap[type];

    igwReadFile* ReadFile = object->NewInstance();
//    igwReadFile* ReadFile = igwReadOpenFOAMFile::New();
    vtkDataObject* data = ReadFile->ReadFile(fileName);

    return data;


}

vtkDataObject *igwIOCore::ReadFile(const char *fileName, const char suffix)
{
    if(fileName == nullptr)
    {
        return nullptr;
    }

}

const char *igwIOCore::GetOpenFileName()
{
    QString filename = QFileDialog::getOpenFileName();

    if(filename.isEmpty())
    {
        return nullptr;
    }

    return filename.toUtf8().data();

}

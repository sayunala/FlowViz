#include "igwReadCGNSFile.h"

#include "vtkCGNSFileSeriesReader.h"
#include "vtkCGNSReader.h"
#include "vtkMultiBlockDataSet.h"

vtkStandardNewMacro(igwReadCGNSFile)
igwReadCGNSFile::igwReadCGNSFile()
    :igwReadFile()
{
    this->Reader = vtkSmartPointer<vtkCGNSReader>::New();

    this->SeriesReader = vtkSmartPointer<vtkCGNSFileSeriesReader>::New();
    this->SeriesReader->SetReader(vtkCGNSReader::SafeDownCast(Reader));
}

igwReadCGNSFile::~igwReadCGNSFile()
{


}

void igwReadCGNSFile::PrintSelf(std::ostream &ostream, vtkIndent indent)
{

}

vtkDataObject * igwReadCGNSFile::ReadFile(const char *filename)
{
    if(filename == nullptr)
    {
//        vtkDebugMacro(<<"ReadCGNSFile: FileName is Empty.\n"<<);
        return nullptr;
    }
    vtkCGNSReader* reader = vtkCGNSReader::SafeDownCast(this->Reader);
    reader->SetFileName(filename);
//    reader->SetFileName(filename);
    reader->Update();
//    SeriesReader->AddFileName(filename);
//    SeriesReader->Update();
    int numberOfPointArrays = reader->GetNumberOfPointArrays();
    int numberOfCellArrays = reader->GetNumberOfCellArrays();
    for(int i = 0; i < numberOfPointArrays;++i)
    {
        reader->SetPointArrayStatus(reader->GetPointArrayName(i), true);
    }
    for(int i = 0; i < numberOfCellArrays; ++i)
    {
        reader->SetCellArrayStatus(reader->GetCellArrayName(i), true);
    }

    reader->Update();
//    SeriesReader->Update();
    reader->GetOutput()->Print(std::cout);

//    SeriesReader->GetOutput()->Print(std::cout);
    return reader->GetOutput();


}

void igwReadCGNSFile::SetTimeValue(double time)
{
    vtkCGNSFileSeriesReader* cgnsReader = vtkCGNSFileSeriesReader::SafeDownCast(this->Reader);
    if(cgnsReader == nullptr)
    {
        return;
    }

    cgnsReader->UpdateTimeStep(time);
    cgnsReader->Update();
}

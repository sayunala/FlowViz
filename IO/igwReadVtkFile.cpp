#include "igwReadVtkFile.h"

#include "vtkDataSetReader.h"
#include "vtkDataSet.h"

vtkStandardNewMacro(igwReadVtkFile)
igwReadVtkFile::igwReadVtkFile()
    :igwReadFile()
{
    this->Reader = vtkSmartPointer<vtkDataSetReader>::New();
}

igwReadVtkFile::~igwReadVtkFile()
{

}

void igwReadVtkFile::PrintSelf(std::ostream &ostream, vtkIndent indent)
{

}

vtkDataObject *igwReadVtkFile::ReadFile(const char *filename)
{
    if(filename == nullptr)
    {
        return nullptr;
    }
    vtkDataSetReader* reader = vtkDataSetReader::SafeDownCast(this->Reader);
    reader->SetFileName(filename);
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
    data->SetObjectName(filename);



    return data;

}

void igwReadVtkFile::SetTimeValue(double time)
{

}

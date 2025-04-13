#include "igwReadFileFactory.h"

#include "vtkVersion.h"
vtkStandardNewMacro(igwReadFileFactory)
igwReadFileFactory::igwReadFileFactory()
{

}
igwReadFileFactory::~igwReadFileFactory()
{

}
const char* igwReadFileFactory::GetVTKSourceVersion()
{
    return VTK_SOURCE_VERSION;
}

vtkObject *igwReadFileFactory::CreateObject(const char *vtkclassname)
{
    return nullptr;
}

const char* igwReadFileFactory::GetDescription()
{
    return "A factory for creating Sub-Class of igwReadFile";
}



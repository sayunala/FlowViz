#ifndef IGWREADEXMLMULTIBLOCKFILE_H
#define IGWREADEXMLMULTIBLOCKFILE_H

#include "igwReadFile.h"
class vtkDataObject;
class igwReadeXMLMultiBlockFile : public igwReadFile
{
public:
    vtkTypeMacro(igwReadeXMLMultiBlockFile, igwReadFile)
    void PrintSelf(std::ostream &ostream, vtkIndent indent) override;

    static igwReadeXMLMultiBlockFile* New();
    virtual vtkDataObject* ReadFile(const char* filename);
    virtual void SetTimeValue(double time);



    igwReadeXMLMultiBlockFile();
    ~igwReadeXMLMultiBlockFile();

//private:
//    igwReadeXMLMultiBlockFile(const igwReadeXMLMultiBlockFile&) = delete;
//    void operator =(const igwReadeXMLMultiBlockFile&) = delete;
};

#endif // IGWREADEXMLMULTIBLOCKFILE_H

#ifndef IGWREADOPENFOAMFILE_H
#define IGWREADOPENFOAMFILE_H

#include "igwReadFile.h"

class vtkDataObject;
class igwReadOpenFOAMFile : public igwReadFile
{
public:
    vtkTypeMacro(igwReadOpenFOAMFile, igwReadFile)

    igwReadOpenFOAMFile();
    ~igwReadOpenFOAMFile();

    static igwReadOpenFOAMFile* New();
    void PrintSelf(ostream&fstream, vtkIndent indent);
    virtual vtkDataObject *ReadFile(const char *filename) override;
    virtual void SetTimeValue(double time);
};

#endif // IGWREADOPENFOAMFILE_H

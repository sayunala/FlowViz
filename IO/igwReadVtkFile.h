#ifndef IGWREADVTKFILE_H
#define IGWREADVTKFILE_H

#include "igwReadFile.h"
class igwReadVtkFile : public igwReadFile
{
public:
    vtkTypeMacro(igwReadVtkFile, igwReadFile)
    igwReadVtkFile();
    virtual ~igwReadVtkFile();
    static igwReadVtkFile* New();
    void PrintSelf(ostream& ostream, vtkIndent indent) override;

    vtkDataObject *ReadFile(const char *filename) override;

    virtual void SetTimeValue(double time) override ;

    virtual vtkAlgorithm* GetReader(){ return Reader;}
    virtual vtkDoubleArray* GetTimeArray() {return TimeValues;}

private:
    igwReadVtkFile(const igwReadVtkFile&) = delete;
    void operator =(const igwReadVtkFile &) = delete;
};

#endif // IGWREADVTKFILE_H

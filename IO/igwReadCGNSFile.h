#ifndef IGWREADCGNSFILE_H
#define IGWREADCGNSFILE_H
#include "igwReadFile.h"

#include "vtkCGNSFileSeriesReader.h"
class igwReadCGNSFile   : public igwReadFile
{
public:
    vtkTypeMacro(igwReadCGNSFile, igwReadFile)
    igwReadCGNSFile();
    virtual ~igwReadCGNSFile();
    void PrintSelf(std::ostream &ostream, vtkIndent indent) override;
    static igwReadCGNSFile* New();
    virtual vtkDataObject *ReadFile(const char *filename) override;
    virtual void SetTimeValue(double time) override;
protected:
    vtkSmartPointer<vtkCGNSFileSeriesReader> SeriesReader;

private:
    igwReadCGNSFile(const igwReadCGNSFile&) = delete;
    void operator =(const igwReadCGNSFile&) = delete;
};

#endif // IGWREADCGNSFILE_H

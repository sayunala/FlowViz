#ifndef IGWREADFILE_H
#define IGWREADFILE_H


#include "vtkDataObject.h"
#include "vtkObject.h"
#include "vtkObjectFactory.h"
#include "vtkObjectFactoryCollection.h"
#include "vtkSmartPointer.h"
#include "vtkAlgorithm.h"
#include "vtkAlgorithmOutput.h"
class vtkDoubleArray;
class igwReadFile : public vtkObject
{
public:
    vtkTypeMacro(igwReadFile, vtkObject)

    igwReadFile(){};
    virtual ~igwReadFile(){};

    void PrintSelf(ostream& ostream, vtkIndent indent) override;
    virtual vtkDataObject* ReadFile(const char* filename) = 0;

    virtual void SetTimeValue(double time) = 0 ;

    virtual vtkAlgorithm* GetReader(){ return Reader;}
    virtual vtkDoubleArray* GetTimeArray() {return TimeValues;}
    virtual vtkAlgorithmOutput* GetOutPort(){return this->Reader->GetOutputPort();}

protected:
    vtkSmartPointer<vtkAlgorithm> Reader;
    vtkDoubleArray* TimeValues;
private:
    igwReadFile(const igwReadFile&) = delete;
    void operator =(const igwReadFile&) = delete;
};

#endif // IGWREADFILE_H

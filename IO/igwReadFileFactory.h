#ifndef IGWREADFILEFACTORY_H
#define IGWREADFILEFACTORY_H

#include  "vtkObjectFactory.h"
#include  "vtkObject.h"
#include "vtkObjectBase.h"
class igwReadFileFactory : public vtkObjectFactory
{
public:
    igwReadFileFactory();
    ~igwReadFileFactory();
    static igwReadFileFactory* New();
    virtual const char *GetVTKSourceVersion();


    const char* igwReadFileFactory::GetDescription();



protected:
    virtual vtkObject *CreateObject(const char *vtkclassname) override;

};

#endif // IGWREADFILEFACTORY_H

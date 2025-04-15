#ifndef IGWXRINTERFACEHELPER_H
#define IGWXRINTERFACEHELPER_H

#include "vtkNew.h"
#include "vtkObject.h"
#include "vtkVRCamera.h"
#include "vtkOpenGLRenderer.h"
class igwXRInterfaceHelper : public  vtkObject
{
public:
    static igwXRInterfaceHelper* New();
    vtkTypeMacro(igwXRInterfaceHelper, vtkObject);
    void PrintSelf(ostream& os, vtkIndent indent) override;

    void ShowXRView();
    void SendToXR();

    void RenderXRView();

    void DoOneEvent();
    void UpdateProps();
protected:
    igwXRInterfaceHelper();
     ~igwXRInterfaceHelper() override;
private:
    igwXRInterfaceHelper(const igwXRInterfaceHelper&) = delete;
    void operator=(const igwXRInterfaceHelper&) = delete;

    vtkSmartPointer<vtkOpenGLRenderer> Renderer;
    vtkNew<vtkPropCollection> AddedProps;

    std::string RemotingAddress = "192.168.148.206";

    struct igwInternals;
    std::unique_ptr<igwInternals> Internals;
};

#endif // IGWXRINTERFACEHELPER_H

#include "igwXRInterfaceHelper.h"

// Qt Headers
#include <QCoreApplication>

#include "vtkQWidgetWidget.h"

#include "vtkOpenGLRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkObjectFactory.h"

#include "vtkVRRenderWindowInteractor.h"
#include "vtkVRRenderer.h"

#include "vtkOpenXRRemotingRenderWindow.h"
#include "vtkOpenXRRenderWindowInteractor.h"
#include "vtkOpenXRRenderer.h"
#include "vtkWin32OpenGLDXRenderWindow.h"
#include "vtkRendererCollection.h"

#include "vtkOpenGLFramebufferObject.h"
#include "vtkShaderProgram.h"
#include "vtkOpenGLState.h"
#include "vtkTextureObject.h"
#include "vtkOpenGLShaderCache.h"
#include "vtkGenericOpenGLRenderWindow.h"
#include "vtkLight.h"
#include "vtkLightCollection.h"
#include "vtkCullerCollection.h"
#include "QVTKOpenGLWindow.h"
#include "vtkImplicitPlaneRepresentation.h"
#include "vtkQWidgetRepresentation.h"
#include "vtkVRInteractorStyle.h"

#include "Components/igwActiveObjects.h"


struct igwXRInterfaceHelper::igwInternals
{
    vtkNew<vtkQWidgetWidget> QWidgetWidget;
    igwRenderView* View = nullptr;
    vtkSmartPointer<vtkOpenGLRenderWindow> RenderWindow;
    vtkSmartPointer<vtkRenderWindowInteractor> Interactor;

    vtkTimeStamp PropUpdateTime;                                // 时间戳
    bool Done = false;
    QVTKOpenGLWindow* ObserverWidget = nullptr;
    vtkNew<vtkOpenGLCamera> ObserverCamera;
};

vtkStandardNewMacro(igwXRInterfaceHelper);
igwXRInterfaceHelper::igwXRInterfaceHelper()
    :Internals(new igwXRInterfaceHelper::igwInternals())
{

}
igwXRInterfaceHelper::~igwXRInterfaceHelper(){};

void igwXRInterfaceHelper::SendToXR()
{
    this->Internals->View = igwActiveObjects::GetInstance().GetActiveView();
    if(this->Internals->View == nullptr)
    {
        std::cout << "no valid view" << std::endl;
        return;
    }
    if(this->Internals->Interactor != nullptr)
    {
        this->UpdateProps();
        return;
    }

    vtkOpenGLRenderer* igwvRenderer =
       vtkOpenGLRenderer::SafeDownCast(this->Internals->View->GetRenderer());
    vtkOpenGLRenderWindow* igwvRenderWindow =
       vtkOpenGLRenderWindow::SafeDownCast(igwvRenderer->GetVTKWindow());

    vtkSmartPointer<vtkVRRenderWindow> renWin = nullptr;
    vtkSmartPointer<vtkVRRenderer> ren = nullptr;
    vtkSmartPointer<vtkVRRenderWindowInteractor> vriren = nullptr;

    // Open XR Remoting
    renWin = vtkSmartPointer<vtkOpenXRRemotingRenderWindow>::New();
    auto* renWinRemote = dynamic_cast<vtkOpenXRRemotingRenderWindow*>(renWin.Get());
    if (renWinRemote)
    {
      // TODO :
      renWinRemote->SetRemotingIPAddress(this->RemotingAddress.c_str());
    }
    vtkNew<vtkWin32OpenGLDXRenderWindow> dxw;
    dxw->SetSharedRenderWindow(igwvRenderWindow);
    renWin->SetHelperWindow(dxw);

    ren = vtkSmartPointer<vtkOpenXRRenderer>::New();
    vtkNew<vtkOpenXRRenderWindowInteractor> oxriren;
    vriren = oxriren;

    // 填充 Internals

    this->Internals->RenderWindow = renWin;
    this->Renderer = ren;
    this->Internals->Interactor = vriren;

    // 非空判断
    if (!this->Internals->Interactor || !this->Internals->RenderWindow || !this->Renderer)
    {
      vtkErrorMacro("Attempted to SendToXR without any backend available");
      this->Internals->RenderWindow = nullptr;
      this->Internals->Interactor = nullptr;
      this->Renderer = nullptr;
      return;
    }

//    vtkVRInteractorStyle::SafeDownCast(this->Internals->Interactor->GetInteractorStyle())
//       ->MapInputToAction(vtkCommand::Select3DEvent, VTKIS_PICK);

    if (this->Internals->ObserverWidget)
    {
      this->Internals->ObserverWidget->destroy();
      delete this->Internals->ObserverWidget;
      this->Internals->ObserverWidget = nullptr;
    }

    renWin->SetBaseStationVisibility(false);
    renWin->SetNumberOfLayers(2);
    this->Internals->RenderWindow->AddRenderer(this->Renderer);
    this->Internals->RenderWindow->SetInteractor(this->Internals->Interactor);

    // 有待商榷
    renWin->InitializeViewFromCamera(igwvRenderer->GetActiveCamera());
    this->Renderer->SetUseImageBasedLighting(igwvRenderer->GetUseImageBasedLighting());
    this->Renderer->SetEnvironmentTexture(igwvRenderer->GetEnvironmentTexture());
    this->Renderer->SetBackground(igwvRenderer->GetBackground());


//    this->Internals->Interactor->AddObserver(
//       vtkCommand::Select3DEvent, this, &vtkPVXRInterfaceHelper::InteractorEventCallback, 2.0);
//     this->Internals->Interactor->AddObserver(
//       vtkCommand::Move3DEvent, this, &vtkPVXRInterfaceHelper::InteractorEventCallback, 2.0);
//     this->Internals->Interactor->AddObserver(
//       vtkCommand::NextPose3DEvent, this, &vtkPVXRInterfaceHelper::InteractorEventCallback, 3.0);

    igwvRenderer->GetLights()->RemoveAllItems();
    {
      vtkNew<vtkLight> light;
      light->SetPosition(0.0, 1.0, 0.0);
      light->SetIntensity(1.0);
      light->SetLightTypeToSceneLight();
      this->Renderer->AddLight(light);
      igwvRenderer->AddLight(light);
    }
    {
      vtkNew<vtkLight> light;
      light->SetPosition(0.8, -0.2, 0.0);
      light->SetIntensity(0.8);
      light->SetLightTypeToSceneLight();
      this->Renderer->AddLight(light);
      igwvRenderer->AddLight(light);
    }
    {
      vtkNew<vtkLight> light;
      light->SetPosition(-0.3, -0.2, 0.7);
      light->SetIntensity(0.6);
      light->SetLightTypeToSceneLight();
      this->Renderer->AddLight(light);
      igwvRenderer->AddLight(light);
    }
    {
      vtkNew<vtkLight> light;
      light->SetPosition(-0.3, -0.2, -0.7);
      light->SetIntensity(0.4);
      light->SetLightTypeToSceneLight();
      this->Renderer->AddLight(light);
      igwvRenderer->AddLight(light);
    }

    this->Renderer->RemoveCuller(this->Renderer->GetCullers()->GetLastItem());
    this->Renderer->SetBackground(igwvRenderer->GetBackground());
    this->Internals->RenderWindow->SetMultiSamples(0);



    this->Internals->RenderWindow->SetDesiredUpdateRate(200.0);
    this->Internals->Interactor->SetDesiredUpdateRate(200.0);
    this->Internals->Interactor->SetStillUpdateRate(200.0);

    this->Internals->RenderWindow->Initialize();

    vtkVRRenderWindow* vrRenWin = vtkVRRenderWindow::SafeDownCast(this->Internals->RenderWindow);

    if(vrRenWin && vrRenWin->GetVRInitialized())
    {
        this->UpdateProps();
        this->Internals->RenderWindow->Render();
        this->Renderer->ResetCamera();
        this->Renderer->ResetCameraClippingRange();

        // 渲染循环
        this->Internals->Done = false;
        while(!this->Internals->Done)
        {
            // Do One Event
            this->DoOneEvent();
            this->RenderXRView();
            QCoreApplication::processEvents();


        }
    }

    //TODO: 渲染循环结束时释放掉资源
}


class vtkEndRenderObserver : public vtkCommand
{
public:
  static vtkEndRenderObserver* New() { return new vtkEndRenderObserver; }

  void Execute(vtkObject* vtkNotUsed(caller), unsigned long vtkNotUsed(event),
    void* vtkNotUsed(calldata)) override
  {
    if (!this->ObserverWindow)
    {
      return;
    }

    if (!this->ObserverDraw)
    {
      // use a simple vertex shader
      // remove clang option once we move to cpp11 on clang
      std::string vshader = R"***(
        //VTK::System::Dec
        in vec4 ndCoordIn;
      in vec2 texCoordIn;
      out vec2 texCoords;
      uniform vec4 aspect;
      void main()
      {
        gl_Position = ndCoordIn * aspect * vec4(1.5, 1.5, 1.0, 1.0);
        texCoords = texCoordIn;
      }
      )***";

      // just add the standard VTK header to the fragment shader
      std::string fshader = "//VTK::System::Dec\n\n";

      fshader += R"***(
        in vec2 texCoords;
      out vec4 fragColor;
      uniform sampler2D screenTex;
      void main() { fragColor = vec4(texture(screenTex, texCoords.xy).rgb, 1.0); }
        )***";
      this->ObserverDraw =
        new vtkOpenGLQuadHelper(this->ObserverWindow, vshader.c_str(), fshader.c_str(), "");
    }
    else
    {
      this->ObserverWindow->GetShaderCache()->ReadyShaderProgram(this->ObserverDraw->Program);
    }

    auto& prog = this->ObserverDraw->Program;

    vtkOpenGLState* ostate = this->ObserverWindow->GetState();

    // push and bind
    ostate->PushFramebufferBindings();
    this->ObserverWindow->GetRenderFramebuffer()->Bind();
    this->ObserverWindow->GetRenderFramebuffer()->ActivateDrawBuffer(0);

    this->ObserverWindow->GetState()->vtkglDepthMask(GL_FALSE);
    this->ObserverWindow->GetState()->vtkglDisable(GL_DEPTH_TEST);

    int* size = this->ObserverWindow->GetSize();
    this->ObserverWindow->GetState()->vtkglViewport(0, 0, size[0], size[1]);
    this->ObserverWindow->GetState()->vtkglScissor(0, 0, size[0], size[1]);

    float faspect[4];
    faspect[0] = static_cast<float>(ResolveSize[0] * size[1]) / (ResolveSize[1] * size[0]);
    faspect[1] = 1.0;
    faspect[2] = 1.0;
    faspect[3] = 1.0;
    prog->SetUniform4f("aspect", faspect);
    // pass to ObserverTexture
    if (this->ObserverTexture->GetHandle() != this->RenderTextureHandle)
    {
      this->ObserverTexture->AssignToExistingTexture(this->RenderTextureHandle, GL_TEXTURE_2D);
    }

    this->ObserverTexture->Activate();
    prog->SetUniformi("screenTex", this->ObserverTexture->GetTextureUnit());

    // draw the full screen quad using the special shader
    this->ObserverDraw->Render();

    this->ObserverTexture->Deactivate();
    ostate->PopFramebufferBindings();
  }

  vtkOpenGLRenderWindow* ObserverWindow = nullptr;
  unsigned int RenderTextureHandle = 0;
  int ResolveSize[2];
  vtkSmartPointer<vtkTextureObject> ObserverTexture;
  vtkOpenGLQuadHelper* ObserverDraw = nullptr;

  void Initialize(vtkOpenGLRenderWindow* rw, unsigned int handle, int* resolveSize)
  {
    this->ObserverWindow = rw;
    this->RenderTextureHandle = handle;
    this->ResolveSize[0] = resolveSize[0];
    this->ResolveSize[1] = resolveSize[1];
    if (!this->ObserverTexture)
    {
      this->ObserverTexture = vtkSmartPointer<vtkTextureObject>::New();
      this->ObserverTexture->SetMagnificationFilter(vtkTextureObject::Linear);
      this->ObserverTexture->SetMinificationFilter(vtkTextureObject::Linear);
    }
    this->ObserverTexture->SetContext(rw);
  }

protected:
  vtkEndRenderObserver()
  {
    this->ObserverWindow = nullptr;
    this->ObserverTexture = nullptr;
    this->ObserverDraw = nullptr;
  }
  ~vtkEndRenderObserver() override
  {
    if (this->ObserverDraw != nullptr)
    {
      delete this->ObserverDraw;
      this->ObserverDraw = nullptr;
    }
    if (this->ObserverTexture != nullptr)
    {
      this->ObserverTexture = nullptr;
    }
  }
};

void igwXRInterfaceHelper::ShowXRView()
{
    vtkVRRenderWindow* vrrw = vtkVRRenderWindow::SafeDownCast(this->Internals->RenderWindow);
    if (!vrrw)
    {
      return;
    }

    if (!this->Internals->ObserverWidget)
    {
      vrrw->MakeCurrent();
      QOpenGLContext* ctx = QOpenGLContext::currentContext();

      this->Internals->ObserverWidget = new QVTKOpenGLWindow(ctx);
      this->Internals->ObserverWidget->setFormat(QVTKOpenGLWindow::defaultFormat());

      vtkNew<vtkGenericOpenGLRenderWindow> observerWindow;
      observerWindow->GetState()->SetVBOCache(this->Internals->RenderWindow->GetVBOCache());
      this->Internals->ObserverWidget->setRenderWindow(observerWindow);
      this->Internals->ObserverWidget->resize(QSize(800, 600));
      this->Internals->ObserverWidget->show();

      vtkNew<vtkEndRenderObserver> endObserver;
      endObserver->Initialize(observerWindow,
        this->Internals->RenderWindow->GetDisplayFramebuffer()
          ->GetColorAttachmentAsTextureObject(0)
          ->GetHandle(),
        this->Internals->RenderWindow->GetSize());
      observerWindow->AddObserver(vtkCommand::RenderEvent, endObserver);
      observerWindow->SetMultiSamples(8);
    }
    else
    {
      this->Internals->ObserverWidget->show();
    }
}


void igwXRInterfaceHelper::RenderXRView()
{
    if (this->Internals->ObserverWidget)
    {
        vtkRenderer* ren = this->Internals->RenderWindow->GetRenderers()->GetFirstRenderer();


        vtkSmartPointer<vtkWin32OpenGLDXRenderWindow> hw = nullptr;

        hw = vtkWin32OpenGLDXRenderWindow::SafeDownCast(
        vtkOpenXRRemotingRenderWindow::SafeDownCast(this->Internals->RenderWindow)
            ->GetHelperWindow());
        if (hw)
        {
            hw->Lock();
        }



        vtkVRRenderWindow* vrrw = vtkVRRenderWindow::SafeDownCast(this->Internals->RenderWindow);

        // bind framebuffer with texture
        this->Internals->RenderWindow->GetState()->PushFramebufferBindings();
        this->Internals->RenderWindow->GetRenderFramebuffer()->Bind();
        this->Internals->RenderWindow->GetRenderFramebuffer()->ActivateDrawBuffer(0);

        // save old camera
        auto* ocam = ren->GetActiveCamera();

        // update observer camera based on oldCam
        // watch for sudden jumps
        double pos[3];
        double dop[3];
        double vup[3];
        double fp[3];
        ocam->GetPosition(pos);
        ocam->GetFocalPoint(fp);
        ocam->GetDirectionOfProjection(dop);
        ocam->GetViewUp(vup);
        double distance = ocam->GetDistance();

        auto* opos = this->Internals->ObserverCamera->GetPosition();
        auto* odop = this->Internals->ObserverCamera->GetDirectionOfProjection();
        auto* ovup = this->Internals->ObserverCamera->GetViewUp();

        // adjust ratio based on current delta
        double ratio = 0.0;
        double angle = vtkMath::DegreesFromRadians(acos(vtkMath::Dot(vup, ovup)));
        if (angle > 3.0)
        {
          ratio = (angle - 3.0) / 27.0;
        }
        ratio = ratio > 1.0 ? 1.0 : ratio;
        double ratio2 = 1.0 - ratio;
        ocam->SetViewUp(ratio * vup[0] + ratio2 * ovup[0], ratio * vup[1] + ratio2 * ovup[1],
          ratio * vup[2] + ratio2 * ovup[2]);

        // adjust ratio based on movement
        double moveDist = sqrt(vtkMath::Distance2BetweenPoints(pos, opos));
        double scale = vrrw->GetPhysicalScale();
        moveDist /= scale;
        ratio = 0.0;
        if (moveDist > 0.05) // in meters
        {
          ratio = (moveDist - 0.05) / 0.5;
        }
        ratio = ratio > 1.0 ? 1.0 : ratio;
        ratio2 = 1.0 - ratio;
        ocam->SetPosition(ratio * pos[0] + ratio2 * opos[0], ratio * pos[1] + ratio2 * opos[1],
          ratio * pos[2] + ratio2 * opos[2]);

        ratio = 0.0;
        angle = vtkMath::DegreesFromRadians(acos(vtkMath::Dot(dop, odop)));
        if (angle > 3.0)
        {
          ratio = (angle - 3.0) / 27.0;
        }
        ratio = ratio > 1.0 ? 1.0 : ratio;
        ratio2 = 1.0 - ratio;
        double npos[3];
        ocam->GetPosition(npos);
        double ndop[3] = { ratio * dop[0] + ratio2 * odop[0], ratio * dop[1] + ratio2 * odop[1],
          ratio * dop[2] + ratio2 * odop[2] };
        vtkMath::Normalize(ndop);
        ocam->SetFocalPoint(
          npos[0] + distance * ndop[0], npos[1] + distance * ndop[1], npos[2] + distance * ndop[2]);

        // store new values
        this->Internals->ObserverCamera->SetPosition(ocam->GetPosition());
        this->Internals->ObserverCamera->SetFocalPoint(ocam->GetFocalPoint());
        this->Internals->ObserverCamera->SetViewUp(ocam->GetViewUp());

        // render
        this->Internals->RenderWindow->GetRenderers()->Render();
        vrrw->RenderModels();

        // restore
        ocam->SetPosition(pos);
        ocam->SetFocalPoint(fp);
        ocam->SetViewUp(vup);

        // resolve the framebuffer
        this->Internals->RenderWindow->GetDisplayFramebuffer()->Bind(GL_DRAW_FRAMEBUFFER);

        int* size = this->Internals->RenderWindow->GetDisplayFramebuffer()->GetLastSize();
        glBlitFramebuffer(
          0, 0, size[0], size[1], 0, 0, size[0], size[1], GL_COLOR_BUFFER_BIT, GL_LINEAR);

        // unbind framebuffer
        this->Internals->RenderWindow->GetState()->PopFramebufferBindings();

        // do a FSQ render
        this->Internals->ObserverWidget->renderWindow()->Render();
        this->Internals->RenderWindow->MakeCurrent();



        hw->Unlock();


    }
}

void igwXRInterfaceHelper::DoOneEvent()
{
    if (auto* vr_rw = vtkVRRenderWindow::SafeDownCast(this->Internals->RenderWindow))
    {
        std::cout << "Do one Event" << std::endl;
        vtkVRRenderWindowInteractor::SafeDownCast(this->Internals->Interactor)
          ->DoOneEvent(vr_rw, this->Renderer);
    }
    else
    {
      double dist = this->Renderer->GetActiveCamera()->GetDistance();
      this->Renderer->ResetCameraClippingRange();
      double farz = this->Renderer->GetActiveCamera()->GetClippingRange()[1];
      this->Renderer->GetActiveCamera()->SetClippingRange(dist * 0.1, farz + 3 * dist);

    }
}

void igwXRInterfaceHelper::UpdateProps()
{
    if (this->Internals->View == nullptr)
    {
       return;
    }

     vtkRenderer* igwvRenderer = this->Internals->View->GetRenderer();

     if (this->Renderer == nullptr)
     {
       return;
     }

     this->Internals->RenderWindow->MakeCurrent();
     if (igwvRenderer->GetViewProps()->GetMTime() > this->Internals->PropUpdateTime ||
       this->AddedProps->GetNumberOfItems() == 0)
     {
       // remove prior props
       vtkCollectionSimpleIterator pit;
       vtkProp* prop;

       // if in VR remove props from VR renderer
       if (this->Renderer != igwvRenderer)
       {
         for (this->AddedProps->InitTraversal(pit); (prop = this->AddedProps->GetNextProp(pit));)
         {
           this->Renderer->RemoveViewProp(prop);
         }
       }

       vtkPropCollection* pcol = igwvRenderer->GetViewProps();
       this->AddedProps->RemoveAllItems();
       for (pcol->InitTraversal(pit); (prop = pcol->GetNextProp(pit));)
       {
         // look for plane widgets and QWidgetRepresentations and do not add
         // them as we will be creating copies for VR so that we can interact
         // with them.
         auto* impPlane = vtkImplicitPlaneRepresentation::SafeDownCast(prop);
         auto* qwidgetrep = vtkQWidgetRepresentation::SafeDownCast(prop);
         if (impPlane || qwidgetrep)
         {
           continue;
         }

         this->AddedProps->AddItem(prop);
         // if in VR add props to VR renderer
         if (this->Renderer != igwvRenderer)
         {
           this->Renderer->AddViewProp(prop);
           std::cout << "add View Prop" << std::endl;
         }
       }
       this->Internals->PropUpdateTime.Modified();
     }

     this->DoOneEvent();
}

void igwXRInterfaceHelper::PrintSelf(std::ostream &os, vtkIndent indent)
{

}

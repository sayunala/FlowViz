#ifndef IGWRENDERVIEW_H
#define IGWRENDERVIEW_H

#include "igwrenderviewbase.h"
class vtkScalarBarActor;
class vtkAxesActor;
class vtkOrientationMarkerWidget;
class vtkInteractorStyleRubberBandZoom;
class vtkInteractorStyleRubberBand2D;
class vtkInteractorStyleRubberBand3D;
class vtkInteractorStyle3D;
class vtkInteractorStyleTrackballCamera;
class vtkLidarGridActor;
class igwRenderView : public igwRenderViewBase
{
public:
    static igwRenderView* New();
    vtkTypeMacro(igwRenderView, igwRenderViewBase);
    void PrintSelf(std::ostream &os, vtkIndent indent) override;

    enum class InteractionModes{
        INTERACTION_MODE_UNINTIALIZED = -1,
        INTERACTION_MODE_3D = 0,
        INTERACTION_MODE_2D,
        INTERACTION_MODE_SELECTION,
        INTERACTION_MODE_ZOOM
    };

    /**
     * @brief SetInteractor: Set the render window interacotr for the render view.
     * @brief SetInteractor: 为视图(view)中的渲染窗口(render window)设置交互器(vtkRenderWindowInteractor*)
     *        为了与QVTKOpenGLNativeWidget兼容，请使用QVTKInteractor指针
     * @param interactor: the render window interactor.
     * @param interactor: 渲染窗口交互器
     */
    void SetInteractor(vtkRenderWindowInteractor* interactor) override;

    /**
     * @brief SetInteractorStyle: Set the interactor style associated with the render view.
     * @brief SetInteractorStyle: 为视图(render view)设置交互风格(Interactor Style)
     * @param style: Interactor Style
     * @param style: 交互器风格
     */
    virtual void SetInteractorStyle(vtkInteractorObserver* style) ;

    void SetInteractorMode(InteractionModes mode);

    /**
     * @brief GetInteractorStyle: Get the interactor style associated with the render view.
     * @brief GetInteractorStyle: 获取视图(render view)的交互风格
     */
    virtual vtkInteractorObserver* GetInteractorStyle() ;

    /**
     * @brief SetRenderWindow: Set the render window for this view.
     * @brief SetRenderWindow: 为渲染视图(render view)设置渲染窗口(render window).
     *        为了与QVTKOpenGLNativeWidget兼容，请使用vtkGenericOpenGLRenderWindow指针
     * @param win: vtkGenericOpenGLRenderWindow pointer.
     * @param win: vtkGenericOpenGLRenderWindow 指针。
     */
    void SetRenderWindow(vtkGenericOpenGLRenderWindow* win) override;

    /**
     * @brief Render: Updates the representations, then calls Render() on the render window
     * asociated with the view
     * @brief Render: 更新所有表征(representation),然后调用view拥有的渲染窗口(render window)
     */
    void Render() override;

    /**
     * @brief ApplyViewTheme:Applies a view theme to thie view
     * @brief ApplyViewTheme:应用主题到视图(view)中
     * @param theme：主题
     */
    void ApplyViewTheme(vtkViewTheme* theme) override;

    /**
     * @brief InvokeEvent
     * @param event
     * @param callData
     */
    void InvokeEvent(unsigned int Event, void *callData);

    /**
     * @brief ResetActiveCameraToDirection: 设置相机方向
     * @param look_x
     * @param look_y
     * @param look_z
     * @param up_x
     * @param up_y
     * @param up_z
     */
    void ResetActiveCameraToDirection(const double& look_x, const double& look_y,
      const double& look_z, const double& up_x, const double& up_y, const double& up_z);

    void ResetViewDirectionToPositiveX();
    void ResetViewDirectionToPositiveY();
    void ResetViewDirectionToPositiveZ();
    void ResetViewDirectionToNegativeX();
    void ResetViewDirectionToNegativeY();
    void ResetViewDirectionToNegativeZ();

    /**
     * @brief ZoomIn:相机靠近物体
     */
    void ZoomIn();
    /**
     * @brief ZoomOut:相机远离物体
     */
    void ZoomOut();

    /**
     * @brief AdjustRoll: 旋转摄像头
     * @param angle:旋转角度
     */
    void AdjustRoll(double angle);

    void ShowAxes(bool value);

    void SetBackGroundColor(double color[3]);

protected:
    igwRenderView();
    ~igwRenderView() override;

    /**
     * @brief PrepareForRendering: called by thew view when the renderrer is about render.
     * @brief PrepareForRendering: 当renderer 需要重新渲染/刷新时被view 调用
     */
    void PrepareForRendering() override;

    /**
     * @brief ProcessEvents Called to process events
     *        Captures StartEvent events from the renderer and calls Update().
     *        This may be overridden by subclasses to process additional events.
     * @brief 被调用用来处理事件，捕获来自renderer的StartEvent 之后调用 Update()函数
     * @param caller
     * @param eventId
     * @param calLData
     */
    void ProcessEvents(vtkObject* caller, unsigned long eventId, void* calLData) override;


    //左下角坐标轴
    vtkSmartPointer<vtkAxesActor> AxesActor;
    vtkSmartPointer<vtkOrientationMarkerWidget> AxesWidget;

    InteractionModes InteractionMode;
    vtkInteractorStyleRubberBandZoom* RubberBandZoom;
    vtkInteractorStyleRubberBand2D* RubberBand2D;
    vtkInteractorStyleRubberBand3D* RubberBand3D;
    vtkInteractorStyleTrackballCamera* TrackballCamera;
    vtkInteractorStyle3D* InteractorStyle3D;
    vtkSmartPointer<vtkLidarGridActor> LidarGridActor;


};

#endif // IGWRENDERVIEW_H

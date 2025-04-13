#ifndef IGWRENDERVIEWBASE_H
#define IGWRENDERVIEWBASE_H

#include "vtkView.h"
#include "vtkSmartPointer.h"

class vtkInteractorObserver;
class vtkRenderer;
class vtkRenderWindow;
class vtkRenderWindowInteractor;
class vtkGenericOpenGLRenderWindow;
class igwRenderViewBase : public vtkView
{
public:

    static igwRenderViewBase* New();
    vtkTypeMacro(igwRenderViewBase, vtkView);
    void PrintSelf(ostream&os, vtkIndent indent) override;

    virtual vtkRenderer* GetRenderer();

    virtual void SetRenderer(vtkRenderer* ren);

    /**
     * @brief GetRenderWindow: Get a handle(pointer) to the render window.
     * @brief GetRenderWindow: 获取渲染窗口句柄(获取vtkRenderWindow指针)，为了
     *        兼容Qt组件使用 vtkGenericOpenGLRenderWindow 对象(派生自vtkRenderWindow，多态).
     * @return vtkRenderWindow*: 渲染窗口指针，可用于操控渲染窗口
     */
    virtual vtkRenderWindow* GetRenderWindow();

    /**
     * @brief SetRenderWindow: Set the render window for thie view. Note that this requires special
     *        handling in order to do correctly.
     * @brief SetRenderWindow: 为本视图(view)设置渲染窗口(render window)。需要注意的需要按照一定顺序处理。
     *        为了与QVTKOpenGLStereoWidget兼容，请使用vtkGenericOpenGLRenderWindow指针
     * @param win: vtkGenericOpenGLRenderWindow指针对象。
     */
    virtual void SetRenderWindow(vtkGenericOpenGLRenderWindow *win);

    /**
     * @brief GetInteractor: Get the render window interactor. Note that this return the pointer of QVTKInteractor Object.
     * @brief GetInteractor: 获取渲染窗口交互器指针(vtkRenderWindowInteractor*)，为了兼容QVTKOpenGLNativeWidget返回的是
     *        QVTKInteractor 对象指针(多态)。
     * @return vtkRenderWindowInteractor*: vtkRenderWindowInteracor指针。
     */
    virtual vtkRenderWindowInteractor* GetInteractor();

    /**
     * @brief SetInteractor: Set the render window interactor. Note that this requires the pointer of QVTKInteractor Object.
     * @brief SetInteractor: 设置渲染窗口交互器指针(vtkRenderWindowInteracotr*)。为了兼容QVTKOpenGLNativeWidget需要设置
     *        QVTKInteractor 对象指针
     */
    virtual void SetInteractor(vtkRenderWindowInteractor*);



    /**
     * @brief Render: Updates the representations, then calls Render() on the render window
     *        associated with this view.
     * @brief Render: 更新所有表征(representations)，之后调用和本视图相联系的渲染窗口(render window)
     *        的渲染函数(Render())
     */
    virtual void Render();

    /**
     * @brief ResetCamera: Updates the representations, then calls ResetCamera() on the renderer
     *        associated with this view.
     * @brief ResetCamera: 更新表征(representations)，之后调用与本视图(view)的渲染器(renderer)的ResetCamera函数重置相机位置。
     */
    virtual void ResetCamera();

    /**
     * @brief ResetCameraClippingRange: Updates the representations, then calls
     *        ResetCameraClippingRange() on the renderer associated with this view.
     * @brief ResetCameraClippingRange: 更新所有表征(representations)然后调用和本视图(view)
     *        相关联渲染器(renderer)的ResetCameraClippingRange()函数
     */
    virtual void ResetCameraClippingRange();

  protected:
    igwRenderViewBase();
    igwRenderViewBase(vtkGenericOpenGLRenderWindow* win);

    ~igwRenderViewBase() override;

    /**
     * @brief PrepareForRendering: Called by the view when the renderer is about to render.
     * @brief PrepareForRendering: 当视图(view)将要渲染时调用该函数，在本函数中调用表征(representation)的
     *        PrepareForRendering函数
     */
    virtual void PrepareForRendering();

    vtkSmartPointer<vtkRenderer> Renderer;
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> RenderWindow;

  private:
    igwRenderViewBase(const igwRenderViewBase&) = delete;
    void operator=(const igwRenderViewBase&) = delete;
};

#endif // IGWRENDERVIEWBASE_H

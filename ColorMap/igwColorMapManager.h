
#ifndef IGWCOLORMAPMANAGER_H
#define IGWCOLORMAPMANAGER_H
/**********************************************
* @projectName   iGreatWorks
* @file          igwColorMapManager.h
* @brief         主要管理程序中应用到了颜色映射,使用单例模式，主要用于获取vtkColorTransferFunction, vtkPiecewiseFunction...
* @author        ZYB
* @date          2023-07-16
* @version       1.0
**********************************************/

#include "vtkDiscretizableColorTransferFunction.h"
#include "vtkPiecewiseFunction.h"
#include "vtk_jsoncpp_fwd.h"


class igwColorMapManager: public vtkObject
{
public:
    static igwColorMapManager* New();
    vtkTypeMacro(igwColorMapManager, vtkObject);
    void PrintSelf(ostream& os, vtkIndent indent) override;


    /**
     * Get singleton instance.
     */
    static igwColorMapManager* GetInstance();

    /**
     * @brief 获取vtkColorTransferFunction对象指针，用于颜色修改与设置
     */
    vtkDiscretizableColorTransferFunction* GetColorFunction();


    /**
     * @brief 获取vtkPiecewiseFunction对象指针，用于透明度修改与设置
     */
    vtkPiecewiseFunction* GetPiecewiseFunction();


    /**
     * @brief 应用预设接口
     * @param presetName根据预设的名字选择预设，value则是应用json格式的颜色
     * @return
     */
    bool ApplyPreset(const char* presetName);
    bool ApplyPreset(const Json::Value& value);
    bool ApplyPreset();
    /**
     * @brief 设置颜色映射的范围
     * @param range
     */
    void SetRange(double* range);
    void SetRange(double rangeMin, double rangeMax);

    Json::Value GetStateAsPreset();

protected:
  igwColorMapManager();
  ~igwColorMapManager() override;

private:
  igwColorMapManager(const igwColorMapManager&) = delete;
  void operator=(const igwColorMapManager&) = delete;
private:

    class igwInternals;
    igwInternals* Internals;
    vtkSetStringMacro(PresetName)
    vtkGetStringMacro(PresetName)
    char* PresetName;
    static vtkSmartPointer<igwColorMapManager> Instance;

};

#endif // IGWCOLORMAPMANAGER_H

#ifndef IGWREALTIMEMODEL2D_H
#define IGWREALTIMEMODEL2D_H

#include "vtkSmartPointer.h"
class vtkGlyph3D;
class vtkPolyData;
class vtkRenderWindowInteractor;
class vtkRenderer;
class vtkPolyDataMapper;
class vtkActor;

class igwRealTimeModel2D
{
public:
    igwRealTimeModel2D(vtkRenderer* render, vtkRenderWindowInteractor* iren, vtkPolyData* model);
    ~igwRealTimeModel2D(){
        m_Render = 0;
        m_Iren = 0;
        m_Model = 0;

    }

    /**
     * @brief 计算法线，用于指明力的方向为法线方向
     */
    void ComputerNormal();

    /**
     * @brief 更新数据的回调
     */
    void CallBack(void* new_data);

    /**
     * @brief UpdateData 更新数据
     */
    void UpdateData(double* new_data);


private:
    vtkRenderer* m_Render;
    vtkRenderWindowInteractor* m_Iren;
    vtkSmartPointer<vtkGlyph3D> m_GlyphGenerate;
    vtkSmartPointer<vtkPolyData> m_Model;

    vtkSmartPointer<vtkPolyDataMapper> m_ModelMapper;
    vtkSmartPointer<vtkActor> m_ModelActor;
    vtkSmartPointer<vtkPolyDataMapper> m_GlyphMapper;
    vtkSmartPointer<vtkActor> m_GlyphActor;

    class igwRealTimeModel2DObserver;
    igwRealTimeModel2DObserver * m_igwRealTimeModel2DObserver;
    friend class igwRealTimeModel2DObserver;

private:
    //private function
    void InitGlyph();

};

#endif // IGWREALTIMEMODEL2D_H

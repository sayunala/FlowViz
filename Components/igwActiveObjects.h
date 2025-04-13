#ifndef IGWACTIVEOBJECTS_H
#define IGWACTIVEOBJECTS_H

/**********************************************
* @projectName   iGreatWorks
* @file          igwActiveObjects.h
* @brief         使用单例模式管理当前激活(选中)的Object，包括View、模型树中选中的Model、
*                场景中的Represnetation等，目前只有选中的View，其余功能需要进一步完善。
* @author        ZYB
* @date          2024/06/14
* @version       1.0
**********************************************/

#include "vtkSmartPointer.h"

#include "Representation/igwRenderView.h"
#include "Representation/igwRenderedRepresentation.h"
#include <QObject>

class vtkDataSet;
class igwRenderedRepresentation;
class igwActiveObjects : public QObject
{
    Q_OBJECT
    typedef QObject SupperClass;
public :
    static igwActiveObjects& GetInstance();

    igwRenderView* GetActiveView();

    vtkDataObject* GetActiveData();

    igwRenderedRepresentation* GetAvtiveRepresentation();


public Q_SLOTS:

    void SetActiveView(igwRenderView* view);

    void SetActiveData(vtkDataObject* data);

    void SetAvtiveRepresentation(igwRenderedRepresentation* rep);

Q_SIGNALS:
    void viewChanged(igwRenderView* view);

    void dataChanged(vtkDataObject* data);

    void representationChanged(igwRenderedRepresentation* rep);
protected:

    igwActiveObjects();
    ~igwActiveObjects() override;

    void triggerSignals();
private:
    vtkSmartPointer<igwRenderView> ActiveView;
    vtkSmartPointer<vtkDataObject> ActiveData;
    vtkSmartPointer<igwRenderedRepresentation> ActiveRep;

    void *CacheView;
    void *CacheData;
    void *CacheRep;
};
#endif

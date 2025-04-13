#include "igwActiveObjects.h"
#include "vtkQtTableView.h"
#include "vtkDataObject.h"
igwActiveObjects::igwActiveObjects():
    CacheView(nullptr)
{

}

void igwActiveObjects::triggerSignals()
{
    if(this->signalsBlocked())
    {
        // 当信号被锁定时不更新cache变量
        return;
    }
    //确保ActiveView已经更改，并发送viewChanged信号
    if(this->ActiveView.Get()!= this->CacheView)
    {
        this->CacheView = this->ActiveView;
        Q_EMIT this->viewChanged(this->ActiveView);
    }

    // 确保ActiveData 已经更改，并发送dataChanged信号
    if(this->ActiveData.Get() != this->CacheData)
    {
        this->CacheView = this->ActiveData;
        Q_EMIT this->dataChanged(this->ActiveData);
    }

    if(this->ActiveRep.Get() != this->CacheRep)
    {
        std::cout << "Rep changed" << std::endl;
        this->CacheRep = this->ActiveRep;
        Q_EMIT this->representationChanged(this->ActiveRep);
    }

}

igwActiveObjects::~igwActiveObjects() = default;


igwActiveObjects &igwActiveObjects::GetInstance()
{
    static igwActiveObjects Instance;
    return Instance;
}

igwRenderView *igwActiveObjects::GetActiveView()
{
    return this->ActiveView;
}

vtkDataObject *igwActiveObjects::GetActiveData()
{
    return this->ActiveData;
}

igwRenderedRepresentation *igwActiveObjects::GetAvtiveRepresentation()
{
    return this->ActiveRep;
}

void igwActiveObjects::SetActiveView(igwRenderView *view)
{
    bool prev = this->blockSignals(true);
    if(view == nullptr)
        return ;

    this->ActiveView = view;

    this->blockSignals(prev);
    this->triggerSignals();
}

void igwActiveObjects::SetActiveData(vtkDataObject *data)
{
    bool prev = this->blockSignals(true);
    if(data == nullptr)
    {
        return;
    }
    data->Print(std::cout);
    this->ActiveData = data;
    this->blockSignals(prev);
    this->triggerSignals();
}

void igwActiveObjects::SetAvtiveRepresentation(igwRenderedRepresentation *rep)
{
    bool prev = this->blockSignals(true);
    if(rep == nullptr)
    {
        return;
    }
    this->ActiveRep = rep;
    this->blockSignals(prev);
    this->triggerSignals();
}


#include "igwVCRControl.h"

#include <QApplication>

#include "vtkAnimationScene.h"
#include "vtkEventQtSlotConnect.h"
#include "Core/igwApplicationCore.h"
#include "igwAnimationScene.h"
igwVCRControl::igwVCRControl(QObject *parent) : QObject(parent)
{
    Connect = vtkEventQtSlotConnect::New();
}

igwVCRControl::~igwVCRControl()
{
    Connect->Delete();
}

void igwVCRControl::setAnimationScene(vtkAnimationScene *scene)
{
    if(this->Scene == scene)
    {
        return;
    }
    this->Scene = scene;
    if(this->Scene)
    {
        Connect->Connect(this->Scene, vtkCommand::StartEvent, this, SLOT(onBeginPlay(vtkObject*,ulong,void*,void*)));
        Connect->Connect(this->Scene, vtkCommand::AnimationCueTickEvent, this, SLOT(onTick()));
        Connect->Connect(this->Scene, vtkCommand::EndEvent, this, SLOT(onEndPlay(vtkObject*,ulong,void*,void*)));
    }
    Q_EMIT this->enabled(this->Scene != nullptr);
}

void igwVCRControl::setIgwAnimationScene(igwAnimationScene *scene)
{
    if(this->igwSence == scene)
    {
        return;
    }
    this->igwSence = scene;
    if(this->igwSence)
    {
        Connect->Connect(this->igwSence, vtkCommand::StartEvent, this, SLOT(onBeginPlay(vtkObject*,ulong,void*,void*)));
        Connect->Connect(this->igwSence, vtkCommand::AnimationCueTickEvent, this, SLOT(onTick()));
        Connect->Connect(this->igwSence, vtkCommand::EndEvent, this, SLOT(onEndPlay(vtkObject*,ulong,void*,void*)));

    }
    Q_EMIT this->enabled(this->igwSence != nullptr);
}

void igwVCRControl::onTimeRangesChanged()
{
    if(this->Scene)
    {
        double begin = this->Scene->GetStartTime();
        double end = this->Scene->GetEndTime();
        QPair<double, double> range(begin, end);
        Q_EMIT this->timeRanges(range.first, range.second);
    }
}

void igwVCRControl::onFirstFrame()
{
    if(this->igwSence)
    {
        this->igwSence->GoToFirst();
    }

}

void igwVCRControl::onPreviousFrame()
{
    if(this->igwSence)
    {
        this->igwSence->GoToPrevious();
    }
}

void igwVCRControl::onNextFrame()
{
    if(this->igwSence)
    {
        this->igwSence->GoToNext();
    }
}

void igwVCRControl::onLastFrame()
{
    if(this->igwSence)
    {
        this->igwSence->GoToLast();
    }
}

void igwVCRControl::onPlay()
{
//    this->Scene->Play();
    this->Scene->Print(std::cout);
    // 测试
    this->igwSence->Play();
    igwApplicationCore::GetInstance()->render();

}

void igwVCRControl::onReverse()
{
    if(this->igwSence)
    {
        this->igwSence->Reverse();
    }
}

void igwVCRControl::onPause()
{
//    this->Scene->Stop();

    if(this->igwSence)
    {
        this->igwSence->Stop();
    }
}

void igwVCRControl::onLoop(bool checked)
{
    this->Scene->SetLoop(checked);
    if(this->igwSence)
    {
        this->igwSence->SetLoop(checked);
    }

}

void igwVCRControl::onTick()
{

    QApplication::processEvents();
    Q_EMIT this->timestepChanged();
}

void igwVCRControl::onLoopPropertyChanged()
{

}

void igwVCRControl::onBeginPlay(vtkObject *caller, unsigned long, void *, void *reversed)
{
    bool* reversedPtr = reinterpret_cast<bool*>(reversed);
    Q_EMIT this->playing(true, reversedPtr != nullptr ? *reversedPtr : false);
}

void igwVCRControl::onEndPlay(vtkObject *caller, unsigned long, void *, void *reversed)
{
    bool* reversedPtr = reinterpret_cast<bool*>(reversed);
    Q_EMIT this->playing(false, reversedPtr != nullptr ? *reversedPtr : false);
}

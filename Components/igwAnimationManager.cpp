#include "igwAnimationManager.h"

#include "vtkAnimationScene.h"
#include "vtkAnimationCue.h"
#include "vtkEventQtSlotConnect.h"
#include "vtkAnimationPlayer.h"
#include "vtkTimestepsAnimationPlayer.h"
#include "igwAnimationScene.h"
igwAnimationManager::igwAnimationManager(QObject *parent) : QObject(parent)
{
    this->Connect = vtkEventQtSlotConnect::New();
    initScene();
    this->Player = vtkTimestepsAnimationPlayer::New();
    this->IgwScene = igwAnimationScene::New();
//    this->Player->SetAnimationScene(this->Scene);

    QObject::connect(this,
      QOverload<vtkObject*, unsigned long, void*, void*>::of(&igwAnimationManager::beginPlay), this,
      QOverload<vtkObject*, unsigned long, void*, void*>::of(&igwAnimationManager::onBeginPlay));
    QObject::connect(this,
      QOverload<vtkObject*, unsigned long, void*, void*>::of(&igwAnimationManager::endPlay), this,
      QOverload<vtkObject*, unsigned long, void*, void*>::of(&igwAnimationManager::onEndPlay));
    Connect->Connect(this->Scene, vtkCommand::StartEvent, this, SLOT(onBeginPlay(vtkObject* , unsigned long, void*, void* )));
    Connect->Connect(this->Scene, vtkCommand::EndEvent, this, SLOT(onEndPlay(vtkObject*, unsigned long, void*, void*)));

}

igwAnimationManager::~igwAnimationManager()
{
    this->Connect->Delete();
    this->Connect = nullptr;
    this->Scene->Delete();
    this->Scene = nullptr;
}

vtkAnimationScene *igwAnimationManager::getScene() const
{
    return this->Scene;
}

vtkAnimationPlayer *igwAnimationManager::getPlayer() const
{
    return this->Player;
}

igwAnimationScene *igwAnimationManager::getIgwScene() const
{
    return this->IgwScene;
}

void igwAnimationManager::onTick(int progress)
{
    Q_EMIT this->saveProgress(qPrintable(QString::fromLocal8Bit("保存动画..")), progress);
}

void igwAnimationManager::onBeginPlay(vtkObject *caller, unsigned long, void *, void *reversed)
{
    this->AnimationPlaying = true;
    std::cout << "Begin Play " << std::endl;
}

void igwAnimationManager::onEndPlay(vtkObject *caller, unsigned long, void *, void *reversed)
{
    this->AnimationPlaying = false;
     std::cout << "End Play " << std::endl;
}

void igwAnimationManager::initScene()
{
    this->Scene = vtkAnimationScene::New();
    this->Scene->SetFrameRate(30);
//    this->Scene->SetStartTime(1);

    this->Scene->SetLoop(false);

}



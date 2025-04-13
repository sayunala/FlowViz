#include "igwApplicationCore.h"

#include "igwViewManager.h"
#include "Components/igwView.h"
#include "Components/igwAnimationManager.h"
#include "Components/igwTimeKeeper.h"
#include "Components/igwAnimationScene.h"
igwApplicationCore* igwApplicationCore::instance = nullptr;
igwApplicationCore::igwApplicationCore(int& argc, char** argv,QObject* parent)
    :QObject(parent)
{
    igwApplicationCore::instance = this;
    TimeKeeper = igwTimeKeeper::New();

    ViewManager = new igwViewManager(this);
    AnimationManager = new igwAnimationManager(this);

    igwAnimationScene* scene = AnimationManager->getIgwScene();
    scene->SetTimeKeeper(TimeKeeper);
}

igwApplicationCore::~igwApplicationCore()
{
    delete ViewManager;
    ViewManager = nullptr;
    delete AnimationManager;
    AnimationManager = nullptr;
    TimeKeeper->Delete();
}

igwApplicationCore *igwApplicationCore::GetInstance()
{

    return igwApplicationCore::instance;
}

void igwApplicationCore::render()
{
    QList<igwView*> Views = this->ViewManager->getViews();
    Q_FOREACH(igwView* view , Views)
    {
        view->render();
    }
}

void igwApplicationCore::prepareQuit()
{

}

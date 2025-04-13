#include "igwViewManager.h"

igwViewManager::igwViewManager(QObject* parent)
    :QObject(parent)
{

}

igwViewManager::~igwViewManager()
{

}

QList<igwView *> igwViewManager::getViews()
{
    return ViewLists;
}

void igwViewManager::removeView(igwView *view)
{
    if(view == nullptr)
        return;
    for(igwView* v : this->ViewLists)
    {
        if(v == view)
        {
            ViewLists.removeOne(view);

        }
    }
}

void igwViewManager::addView(igwView* view)
{
    if(view == nullptr)
        return;

    this->ViewLists.push_back(view);
}



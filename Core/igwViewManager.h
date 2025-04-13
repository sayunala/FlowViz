#ifndef IGWVIEWMANAGER_H
#define IGWVIEWMANAGER_H

#include <QObject>
#include "Components/igwView.h"
class igwViewManager  : public  QObject
{
    Q_OBJECT
public:
    igwViewManager(QObject* parent = nullptr);
    ~igwViewManager() override;

    QList<igwView*> getViews();
    void addView(igwView* view);
    void removeView(igwView* view);
protected:

    QList<igwView*> ViewLists;

};

#endif // IGWVIEWMANAGER_H

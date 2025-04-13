#ifndef IGWAPPLICATIONCORE_H
#define IGWAPPLICATIONCORE_H

#include <QObject>

class QSetting;
class igwViewManager;
class igwAnimationManager;
class igwTimeKeeper;
class igwApplicationCore  : public  QObject
{
    Q_OBJECT
public:
    igwApplicationCore(int& argc, char** argv,QObject* parent = nullptr);
    ~igwApplicationCore() override;
    static igwApplicationCore *GetInstance();

    igwAnimationManager* GetAnimationManager() const{return AnimationManager;}
    igwViewManager* GetViewManager() const {return ViewManager;}
    igwTimeKeeper* GetTimeKeeper() const {return TimeKeeper;}
public Q_SLOTS:
    void render();
    void prepareQuit();
protected:
    QSetting* Setting;

    igwViewManager* ViewManager;
    igwAnimationManager* AnimationManager;

    igwTimeKeeper* TimeKeeper;
    static igwApplicationCore* instance;

};

#endif // IGWAPPLICATIONCORE_H

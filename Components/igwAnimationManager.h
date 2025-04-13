#ifndef IGWANIMATIONMANAGER_H
#define IGWANIMATIONMANAGER_H

#include <QObject>
#include <QSize>
class vtkAnimationScene;
class vtkAnimationCue;
class vtkEventQtSlotConnect;
class vtkObject;
class QSize;
class vtkAnimationPlayer;
class igwAnimationScene;
class igwAnimationManager : public QObject
{
    Q_OBJECT
public:
    explicit igwAnimationManager(QObject *parent = nullptr);
    ~igwAnimationManager();

    vtkAnimationScene *getScene() const;

    vtkAnimationPlayer *getPlayer() const;

    // 测试函数将要替换getScene
    igwAnimationScene *getIgwScene() const;
//    vtkAnimationCue *getCue(
//        vtkAnimationScene* scene, int index) const;

    void writeAnimation(const QString& filename, int magnification, double frameRate);

    bool animationPlaying() const;
signals:
    void beginPlay(vtkObject* caller, unsigned long, void*, void* reversed);

    void endPlay(vtkObject* caller, unsigned long, void*, void* reversed);

    void saveProgress(const QString&, int);

protected Q_SLOTS:

    void onTick(int);

    void onBeginPlay(vtkObject* caller, unsigned long, void*, void* reversed);
    void onEndPlay(vtkObject* caller, unsigned long, void*, void* reversed);


protected:

    QSize OldMaxSize;
    QSize OldSize;

    double AspectRatio;
    bool AnimationPlaying;
    int OldNumberOfFrames;
    vtkAnimationScene* Scene;
    igwAnimationScene* IgwScene;
    vtkEventQtSlotConnect* Connect;

    vtkAnimationPlayer * Player;
private:
    Q_DISABLE_COPY(igwAnimationManager);

    void initScene();
    void initPlayer();

};

#endif // IGWANIMATIONMANAGER_H

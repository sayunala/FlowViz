#ifndef IGWVCRCONTROL_H
#define IGWVCRCONTROL_H

#include <QObject>
#include "vtkObject.h"

class vtkAnimationScene;
class vtkEventQtSlotConnect;
class igwAnimationScene;
class igwVCRControl : public QObject
{
    Q_OBJECT
public:
    explicit igwVCRControl(QObject *parent = nullptr);
    ~igwVCRControl() override;

Q_SIGNALS:
  /**
   * Emitted for each tick.
   */
  void timestepChanged();

  /**
   * Emitted as `playing(true, reversed)` when playback begins
   * and `playing(false, reversed)` when playback ends.
   * The value of `reversed` argument is true if playback was
   * requested in backward direction
   */
  void playing(bool, bool);

  /**
   * Fired when the enable state of the VCR control changes and
   * each time setAnimationScene() is called.
   * If called when a valid scene, enabled(true) is fired,
   * else enabled(false).
   */
  void enabled(bool);

  /**
   * Emitted to update the check state of the loop.
   */
  void loop(bool);

  /**
   * Emitted when the time ranges is updated.
   */
  void timeRanges(double, double);
public Q_SLOTS:

    virtual void setAnimationScene(vtkAnimationScene*);
    virtual void setIgwAnimationScene(igwAnimationScene* scene);

    virtual void onTimeRangesChanged();

    virtual void onFirstFrame();
    virtual void onPreviousFrame();
    virtual void onNextFrame();
    virtual void onLastFrame();
    virtual void onPlay();
    virtual void onReverse();
    virtual void onPause();
    virtual void onLoop(bool checked);

protected Q_SLOTS:
    void onTick();
    void onLoopPropertyChanged();
    void onBeginPlay(vtkObject* caller, unsigned long, void*, void* reversed);
    void onEndPlay(vtkObject* caller, unsigned long, void*, void* reversed);
private:

    vtkAnimationScene* Scene;
    // 测试用会替换掉Scene;
    igwAnimationScene* igwSence;
    vtkEventQtSlotConnect* Connect;
};

#endif // IGWVCRCONTROL_H

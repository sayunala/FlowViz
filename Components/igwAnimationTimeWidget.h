#ifndef IGWANIMATIONTIMEWIDGET_H
#define IGWANIMATIONTIMEWIDGET_H

#include <QWidget>
#include <QVariant>
#include <vtkObject.h>
namespace Ui {
class igwAnimationTimeWidget;
}

class igwAnimationScene;
class vtkEventQtSlotConnect ;
class WidgetState
{
  // Timesteps comes from TimeKeeper
  std::vector<double> TimeSteps;
  // Computed from AnimationSceneProperty, this is not the same as TimeSteps but as same usage here.
  // We store it appart to be safe with PropertyLinks.
  std::vector<double> SequenceTimeSteps;
  double Time = 0.0;
  bool PlayModeSnapToTimeSteps = true;

public:
  bool DisableModifications = false;

  double StartTime = 0;
  double EndTime = 1;

  bool playModeSnapToTimeSteps() const { return this->PlayModeSnapToTimeSteps; }
  double time() const { return this->Time; }

  /**
   * TimeSteps is up to date with TimeKeeper, while SequenceTimeSteps is computed from
   * AnimationScene properties. They differ in origin but are similar in use in this class. This
   * method allows to use the relevant one, hiding the switch logic.
   */
  const std::vector<double>& timeSteps() const
  {
    return playModeSnapToTimeSteps() ? this->TimeSteps : this->SequenceTimeSteps;
  }
  const QList<QVariant>& timeStepsAsVariantList() const
  {
    this->TimeStepsVariants.clear();
    std::transform(this->TimeSteps.begin(), this->TimeSteps.end(),
      std::back_inserter(this->TimeStepsVariants), [](const double& val) { return QVariant(val); });
    return this->TimeStepsVariants;
  }

  /**
   * Checks if the index in input has an associated timestep.
   * If so, the timestep is passed to the input timestep parameter and the function returns true.
   */
  bool checkTimeStepFromIndex(int index, double& timestep)
  {
    if (!this->DisableModifications && index >= 0 &&
      index < static_cast<int>(this->timeSteps().size()))
    {
      timestep = this->timeSteps()[index];
      return this->canTimeBeSet(timestep);
    }
    return false;
  }

  // sets the current time
  void setTime(double time) { this->Time = time; }

  // checks if the time value in input can be set to the current time
  bool canTimeBeSet(double time) { return (!this->DisableModifications && time != this->Time); }

  bool setPlayModeSnapToTimeSteps(bool val)
  {
    if (!this->DisableModifications && this->PlayModeSnapToTimeSteps != val)
    {
      this->PlayModeSnapToTimeSteps = val;
      return true;
    }
    return false;
  }

  void updateSequenceTimeSteps() { this->updateSequenceTimeSteps(this->numberOfFrames()); }

  void updateSequenceTimeSteps(int nbOfFrames)
  {
    this->SequenceTimeSteps.resize(nbOfFrames);
    if (nbOfFrames > 1)
    {
      double step = (this->EndTime - this->StartTime) / (nbOfFrames - 1);
      for (int idx = 0; idx < nbOfFrames; idx++)
      {
        this->SequenceTimeSteps[idx] = this->StartTime + idx * step;
      }
    }
    else if (nbOfFrames == 1)
    {
      this->SequenceTimeSteps[0] = this->StartTime;
    }
  }

  int numberOfFrames() { return static_cast<int>(this->SequenceTimeSteps.size()); }

  bool setTimeSteps(const QList<QVariant>& list)
  {
    if (this->DisableModifications)
    {
      return false;
    }

    std::vector<double> times(list.size());
    std::transform(
      list.begin(), list.end(), times.begin(), [](const QVariant& var) { return var.toDouble(); });
    if (this->TimeSteps != times)
    {
      this->TimeSteps = std::move(times);
      return true;
    }
    return false;
  }

private:
  mutable QList<QVariant> TimeStepsVariants;
};

class igwAnimationTimeWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(double startTime READ startTime WRITE setStartTime)
    Q_PROPERTY(double endTime READ endTime WRITE setEndTime)
//    Q_PROPERTY(QString timeLabel READ timeLabel WRITE setTimeLabel)
    Q_PROPERTY(QList<QVariant> timestepValues READ timestepValues WRITE setTimestepValues)
public:
    explicit igwAnimationTimeWidget(QWidget *parent = nullptr);
    ~igwAnimationTimeWidget();


    void setAnimationScene(igwAnimationScene* scene);
    void setTimestepValues(const QList<QVariant>& list);
    const QList<QVariant>& timestepValues() const;
    ///@}

    ///@{
    /**
     * Get/Set the animation start time.
     */
    void setStartTime(double start);
    double startTime() const;
    ///@}

    ///@{
    /**
     * Get/Set the animation end time.
     */
    void setEndTime(double end);
    double endTime() const;

    void setCurrentTime(double t);

protected Q_SLOTS:

    void updateCurrentTime(double t);
    void updateCurrentTime(vtkObject* caller, unsigned long, void*, void* reversed);
    void updateUI();

    void updateStartEndTime(vtkObject* caller, unsigned long, void*, void* reversed);
    void updateTimeValues(vtkObject* caller, unsigned long, void*, void* reversed);
private:
    Ui::igwAnimationTimeWidget *ui;

    igwAnimationScene* AnimationScene;
    WidgetState State;
    vtkEventQtSlotConnect* Connect;

};

#endif // IGWANIMATIONTIMEWIDGET_H

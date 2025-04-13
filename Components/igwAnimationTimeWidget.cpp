#include "igwAnimationTimeWidget.h"
#include "ui_igwAnimationTimeWidget.h"

#include <QLineEdit>
#include <QScopedValueRollback>
#include <QSignalBlocker>

#include "vtkEventQtSlotConnect.h"
#include "igwAnimationScene.h"

#include "igwTimeKeeper.h"
#include "ColorMap/igwTimer.h"
igwAnimationTimeWidget::igwAnimationTimeWidget(QWidget *parent ) :
    QWidget(parent),
    ui(new Ui::igwAnimationTimeWidget)
{

    ui->setupUi(this);

    // init ui
    ui->timeValueComboBox->setValidator(new QDoubleValidator(this));
    ui->timeValueComboBox->setLineEdit(new QLineEdit(this));
    auto metrics = this->ui->timeValueComboBox->fontMetrics();
    auto minW = metrics.horizontalAdvance("210.123456789");
    ui->timeValueComboBox->setMinimumWidth(minW);
    metrics = this->ui->timestepValue->fontMetrics();
    minW = metrics.horizontalAdvance("12345 (?) ");
    ui->timestepValue->setMinimumWidth(minW);

    this->setEnabled(false);
    (void)QObject::connect(ui->timeValueComboBox->lineEdit(), &QLineEdit::editingFinished, [this]()
    {
       const double time = ui->timeValueComboBox->currentData().toDouble();
       if(this->State.canTimeBeSet(time))
       {
           this->setCurrentTime(time);
       }
    });
    QObject::connect(ui->timeValueComboBox, &QComboBox::currentTextChanged, [this]() {
      // user has selected a timestep using the combo-box.
      const double time = ui->timeValueComboBox->currentData().toDouble();
      if (this->State.canTimeBeSet(time))
      {
        this->setCurrentTime(time);
      }
    });

    auto timer = new igwTimer(this);
    timer->setInterval(100);
    timer->setSingleShot(true);
    QObject::connect(timer, &QTimer::timeout, [this]() {
      // user has changed the time-step in the spinbox.
      const int timeIndex = this->ui->timestepValue->value();
      double time;
      if (this->State.checkTimeStepFromIndex(timeIndex, time))
      {
        this->setCurrentTime(time);
      }
    });


    this->Connect = vtkEventQtSlotConnect::New();
    this->AnimationScene = nullptr;
}

igwAnimationTimeWidget::~igwAnimationTimeWidget()
{
    delete ui;
    this->Connect->Delete();
}

void igwAnimationTimeWidget::setAnimationScene(igwAnimationScene *scene)
{

    if(this->AnimationScene == scene)
    {
        return;
    }
    if(this->AnimationScene != nullptr)
    {
        igwTimeKeeper* timeKeeper = this->AnimationScene->GetTimeKeeper();
        this->Connect->Disconnect(timeKeeper, igwTimeKeeper::TimeValuesChangedEvent, this, SLOT(updateTimeValues(vtkObject*  , unsigned long, void*, void* )));
    }
    this->Connect->Disconnect(this->AnimationScene, igwAnimationScene::UpdateStartEndTimesEvent, this, SLOT(updateStartEndTime(vtkObject* , unsigned long, void*, void* )));
    this->AnimationScene = scene;
    this->setEnabled(scene != nullptr);
    if(scene == nullptr)
    {
        return;
    }
    igwTimeKeeper* timeKeeper = this->AnimationScene->GetTimeKeeper();

    // TODO: 连接
    Connect->Connect(this->AnimationScene, vtkCommand::AnimationCueTickEvent, this, SLOT(updateCurrentTime(vtkObject*,ulong,void*,void*)));
    Connect->Connect(this->AnimationScene, igwAnimationScene::UpdateStartEndTimesEvent, this, SLOT(updateStartEndTime(vtkObject* , unsigned long, void*, void*)));
//    this->Connect->Connect(timeKeeper, igwTimeKeeper::TimeValuesChangedEvent, this, SLOT(updateTimeValues(vtkObject* caller, unsigned long, void*, void* reversed)));
    Connect->Connect(timeKeeper, igwTimeKeeper::TimeValuesChangedEvent, this, SLOT(updateTimeValues(vtkObject*, unsigned long, void*, void*)));
}

void igwAnimationTimeWidget::setTimestepValues(const QList<QVariant> &list)
{
    if(this->State.setTimeSteps(list))
    {
        this->updateUI();
    }
}

const QList<QVariant> &igwAnimationTimeWidget::timestepValues() const
{
    return this->State.timeStepsAsVariantList();
}

void igwAnimationTimeWidget::setStartTime(double start)
{
    this->State.StartTime = start;
    this->State.updateSequenceTimeSteps();
    this->updateUI();
}

double igwAnimationTimeWidget::startTime() const
{
    return this->State.StartTime;
}

void igwAnimationTimeWidget::setEndTime(double end)
{
    this->State.EndTime = end;
    this->State.updateSequenceTimeSteps();
    this->update();
}

double igwAnimationTimeWidget::endTime() const
{
    return this->State.EndTime;
}

void igwAnimationTimeWidget::setCurrentTime(double t)
{
    if(this->AnimationScene != nullptr)
    {

        this->AnimationScene->SetSceneTime(t);
    }
    this->AnimationScene->Modified();
}

void igwAnimationTimeWidget::updateCurrentTime(double t)
{
    this->State.setTime(t);
    this->updateUI();
}

void igwAnimationTimeWidget::updateCurrentTime(vtkObject *caller, unsigned long, void *, void *calldata)
{
    vtkAnimationCue::AnimationCueInfo* info =
        reinterpret_cast<vtkAnimationCue::AnimationCueInfo*>(calldata);
    this->updateCurrentTime(info->ClockTime);
}

void igwAnimationTimeWidget::updateUI()
{
    QSignalBlocker blocker(this);
    QScopedValueRollback<bool> rollback(this->State.DisableModifications, true);

    auto& state = this->State;
    ui->timestepCountLabel->setVisible(state.playModeSnapToTimeSteps());

    // update combo-box.
    ui->timeValueComboBox->clear();
    int currentIndex = -1;
    for (const auto& val : state.timeSteps())
    {
      if (val == state.time())
      {
        currentIndex = ui->timeValueComboBox->count();
      }
      else if (currentIndex == -1 && state.time() < val)
      {
        // `state.time()` is not part of the current timesteps, insert it.
        currentIndex = ui->timeValueComboBox->count();
        ui->timeValueComboBox->addItem(QString::number(val),state.time());
      }

      ui->timeValueComboBox->addItem(QString::number(val), val);
    }

    if (currentIndex == -1)
    {
      // `state.time()` is not part of the current timesteps, append it.
      currentIndex = ui->timeValueComboBox->count();
      ui->timeValueComboBox->addItem(
        QString("%1 (?)").arg(QString::number(state.time()), state.time()));
    }
    ui->timeValueComboBox->setCurrentIndex(currentIndex);

    // update spin-box.
    if (!state.timeSteps().empty())
    {
      const int count = static_cast<int>(state.timeSteps().size());
      ui->timestepValue->setMaximum(count - 1);
      int idx = 0;
      for (auto ts : state.timeSteps())
      {
        if (ts >= state.time())
        {
          break;
        }
        idx++;
      }
      ui->timestepValue->setValue(idx);
      ui->timestepValue->setSuffix(state.timeSteps()[idx] == state.time() ? "" : " (?)");
      ui->timestepCountLabel->setText(tr("max is %1").arg(count - 1));
    }
    else
    {
      ui->timestepValue->setMaximum(0);
      ui->timestepValue->setValue(0);
      ui->timestepValue->setPrefix(QString());
      ui->timestepCountLabel->setText(QString());
    }

}

void igwAnimationTimeWidget::updateStartEndTime(vtkObject* caller, unsigned long, void*, void* reversed)
{
    if(this->AnimationScene != nullptr)
    {
        this->setStartTime(this->AnimationScene->GetStartTime());
        this->setEndTime(this->AnimationScene->GetEndTime());
    }
    this->updateUI();
}

void igwAnimationTimeWidget::updateTimeValues(vtkObject* caller, unsigned long, void*, void* reversed)
{
    if(this->AnimationScene != nullptr)
    {
        igwTimeKeeper* timeKeeper= this->AnimationScene->GetTimeKeeper();
        std::vector<double> timeSteps = timeKeeper->GetTimeValues();
        QList<QVariant> list;
        for(double time : timeSteps)
        {
            list.append(time);
        }
        this->setTimestepValues(list);
    }
    this->updateUI();
}

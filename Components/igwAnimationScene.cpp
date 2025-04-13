// SPDX-FileCopyrightText: Copyright (c) Kitware Inc.
// SPDX-License-Identifier: BSD-3-Clause

#include "igwAnimationScene.h"

#include "vtkTimestepsAnimationPlayer.h"
#include "vtkEventForwarderCommand.h"
#include "vtkNew.h"
#include "vtkObjectFactory.h"
//#include "vtkPVCameraAnimationCue.h"
//#include "vtkPVLogger.h"
//#include "vtkSMProperty.h"
//#include "vtkSMPropertyHelper.h"
//#include "vtkSMTransferFunctionManager.h"
//#include "vtkSMViewProxy.h"
#include "vtkSmartPointer.h"
#include "vtkVector.h"
#include "vtkView.h"

#include "igwTimeKeeper.h"

#include <algorithm>
#include <cassert>
#include <vector>

bool igwAnimationScene::GlobalUseGeometryCache;
//----------------------------------------------------------------------------
void igwAnimationScene::SetGlobalUseGeometryCache(bool val)
{
  igwAnimationScene::GlobalUseGeometryCache = val;
}

//----------------------------------------------------------------------------
bool igwAnimationScene::GetGlobalUseGeometryCache()
{
  return igwAnimationScene::GlobalUseGeometryCache;
}

//----------------------------------------------------------------------------
class igwAnimationScene::vtkInternals
{
//  vtkNew<vtkSMTransferFunctionManager> TransferFunctionManager;

public:
  typedef std::vector<vtkSmartPointer<vtkAnimationCue>> VectorOfAnimationCues;
  VectorOfAnimationCues AnimationCues;

  typedef std::vector<vtkSmartPointer<vtkView>> VectorOfViews;
  VectorOfViews ViewModules;

  void UpdateAllViews()
  {
    if (this->ViewModules.empty())
    {
      return;
    }

//    vtkVLogScopeF(PARAVIEW_LOG_APPLICATION_VERBOSITY(), "update-all-views for animation");

//    vtkSMSessionProxyManager* pxm = nullptr;
//    for (VectorOfViews::iterator iter = this->ViewModules.begin(); iter != this->ViewModules.end();
//         ++iter)
//    {
//      // save the proxy manager for later.
//      if (pxm)
//      {
//        assert(iter->GetPointer()->GetSessionProxyManager() == pxm);
//      }
//      else
//      {
//        pxm = iter->GetPointer()->GetSessionProxyManager();
//      }
//      iter->GetPointer()->Update();
//    }

//    vtkVLogStartScope(PARAVIEW_LOG_APPLICATION_VERBOSITY(), "reset transfer functions");
//    this->TransferFunctionManager->ResetAllTransferFunctionRangesUsingCurrentData(
//      pxm, true /*animating*/);
//    vtkLogEndScope("reset transfer functions");
  }

  void StillRenderAllViews()
  {
//    vtkVLogScopeF(PARAVIEW_LOG_APPLICATION_VERBOSITY(), "still-render-all-views for animation");
//    for (VectorOfViews::iterator iter = this->ViewModules.begin(); iter != this->ViewModules.end();
//         ++iter)
//    {
//      iter->GetPointer()->StillRender();
//    }
  }

  void PassCacheTime(double cachetime)
  {
//    VectorOfViews::iterator iter = this->ViewModules.begin();
//    for (; iter != this->ViewModules.end(); ++iter)
//    {
//      vtkSMPropertyHelper((*iter), "CacheKey").Set(cachetime);
//      iter->GetPointer()->UpdateProperty("CacheKey");
//    }
  }

  void PassUseCache(bool usecache)
  {
//    VectorOfViews::iterator iter = this->ViewModules.begin();
//    for (; iter != this->ViewModules.end(); ++iter)
//    {
//      vtkSMPropertyHelper((*iter), "UseCache").Set(usecache);
//      iter->GetPointer()->UpdateProperty("UseCache");
//    }
  }
};

namespace
{
// Helper class used by for_each() to call Tick on all cues if they are not
// one of the "exception" classes.
class vtkTickOnGenericCue
{
  double StartTime;
  double EndTime;
  double CurrentTime;
  double DeltaTime;
  double ClockTime;
  vtkAnimationCue::PlayDirection Direction;

protected:
  virtual bool IsAcceptable(vtkAnimationCue* cue) const
  {
//    return (cue &&
//#if VTK_MODULE_ENABLE_VTK_PythonInterpreter
//      (vtkPythonAnimationCue::SafeDownCast(cue) == nullptr) &&
//#endif
//      (vtkPVCameraAnimationCue::SafeDownCast(cue) == nullptr));
      return (cue);
  }

public:
  vtkTickOnGenericCue(double starttime, double endtime, double currenttime, double deltatime,
    double clocktime, vtkAnimationCue::PlayDirection direction)
    : StartTime(starttime)
    , EndTime(endtime)
    , CurrentTime(currenttime)
    , DeltaTime(deltatime)
    , ClockTime(clocktime)
    , Direction(direction)
  {
  }
  virtual ~vtkTickOnGenericCue() = default;
  virtual void operator()(vtkAnimationCue* cue) const
  {
    if (!this->IsAcceptable(cue))
    {
      return;
    }

    const auto& dir = cue->GetDirection();
    cue->SetDirection(this->Direction);
    switch (cue->GetTimeMode())
    {
      case vtkAnimationCue::TIMEMODE_RELATIVE:
        cue->Tick(this->CurrentTime - this->StartTime, this->DeltaTime, this->ClockTime);
        break;
      case vtkAnimationCue::TIMEMODE_NORMALIZED:
        cue->Tick((this->CurrentTime - this->StartTime) / (this->EndTime - this->StartTime),
          this->DeltaTime / (this->EndTime - this->StartTime), this->ClockTime);
        break;
      default:
        vtkGenericWarningMacro("Invalid cue time mode");
    }
    cue->SetDirection(dir);
  }
};
}

vtkStandardNewMacro(igwAnimationScene);
//----------------------------------------------------------------------------
igwAnimationScene::igwAnimationScene()
{
  this->SceneTime = 0;
  this->PlaybackTimeWindow[0] = 1.0;
  this->PlaybackTimeWindow[1] = -1.0;
  this->ForceDisableCaching = false;
  this->InTick = false;
  this->LockEndTime = false;
  this->LockStartTime = false;
  this->OverrideStillRender = false;
  this->TimeKeeper = nullptr;
  this->TimeRangeObserverID = 0;
  this->TimestepValuesObserverID = 0;
  this->AnimationPlayer = vtkTimestepsAnimationPlayer::New();
  // vtkAnimationPlayer::SetAnimationScene() is not reference counted.
  this->AnimationPlayer->SetAnimationScene(this);
  this->Internals = new vtkInternals();

  this->Forwarder = vtkEventForwarderCommand::New();
  this->Forwarder->SetTarget(this);
  this->AnimationPlayer->AddObserver(vtkCommand::StartEvent, this->Forwarder);
  this->AnimationPlayer->AddObserver(vtkCommand::EndEvent, this->Forwarder);
}

//----------------------------------------------------------------------------
igwAnimationScene::~igwAnimationScene()
{
  this->SetTimeKeeper(nullptr);

  this->AnimationPlayer->RemoveObserver(this->Forwarder);
  this->AnimationPlayer->Delete();
  this->AnimationPlayer = nullptr;

  this->Forwarder->SetTarget(nullptr);
  this->Forwarder->Delete();

  delete this->Internals;
  this->Internals = nullptr;
}

//----------------------------------------------------------------------------
void igwAnimationScene::AddCue(vtkAnimationCue* cue)
{
  vtkInternals::VectorOfAnimationCues& cues = this->Internals->AnimationCues;
  if (std::find(cues.begin(), cues.end(), cue) != cues.end())
  {
    vtkErrorMacro("Animation cue already present in the scene");
    return;
  }
  cues.push_back(cue);
  this->Modified();
}

//----------------------------------------------------------------------------
void igwAnimationScene::RemoveCue(vtkAnimationCue* cue)
{
  vtkInternals::VectorOfAnimationCues& cues = this->Internals->AnimationCues;
  vtkInternals::VectorOfAnimationCues::iterator iter = std::find(cues.begin(), cues.end(), cue);
  if (iter != cues.end())
  {
    cues.erase(iter);
    this->Modified();
  }
}

//----------------------------------------------------------------------------
void igwAnimationScene::RemoveAllCues()
{
  if (!this->Internals->AnimationCues.empty())
  {
    this->Internals->AnimationCues.clear();
    this->Modified();
  }
}

//----------------------------------------------------------------------------
int igwAnimationScene::GetNumberOfCues()
{
  return static_cast<int>(this->Internals->AnimationCues.size());
}

//----------------------------------------------------------------------------
void igwAnimationScene::SetTimeKeeper(igwTimeKeeper* tkp)
{
  if (this->TimeKeeper == tkp)
  {
    return;
  }

  if (this->TimeKeeper && this->TimeRangeObserverID)
  {
    this->TimeKeeper->RemoveObserver(this->TimeRangeObserverID);
  }
  if (this->TimeKeeper && this->TimestepValuesObserverID)
  {
    this->TimeKeeper->RemoveObserver(this->TimestepValuesObserverID);
  }
  this->TimeRangeObserverID = 0;
  this->TimestepValuesObserverID = 0;
//  vtkSetObjectBodyMacro(TimeKeeper, vtkSMProxy, tkp);
  this->TimeKeeper = tkp;
  if (this->TimeKeeper)
  {
    this->TimeRangeObserverID = this->TimeKeeper
                                  ->AddObserver(igwTimeKeeper::TimeRangeChangedEvent, this,
                                    &igwAnimationScene::TimeKeeperTimeRangeChanged);
    this->TimestepValuesObserverID = this->TimeKeeper
                                       ->AddObserver(igwTimeKeeper::TimeValuesChangedEvent, this,
                                         &igwAnimationScene::TimeKeeperTimestepsChanged);
    this->TimeKeeperTimestepsChanged();
    this->TimeKeeperTimeRangeChanged();
  }
}

//----------------------------------------------------------------------------
void igwAnimationScene::TimeKeeperTimestepsChanged()
{
  this->AnimationPlayer->RemoveAllTimeSteps();

//  vtkSMPropertyHelper helper(this->TimeKeeper, "TimestepValues");
  std::vector<double> timeSteps = this->TimeKeeper->GetTimeValues();
  for (unsigned int cc = 0; cc < timeSteps.size(); cc++)
  {
    this->AnimationPlayer->AddTimeStep(timeSteps[cc]);
  }
//  this->SetEndTime(timeSteps.size());
}

//----------------------------------------------------------------------------
void igwAnimationScene::TimeKeeperTimeRangeChanged()
{
  // If time keeper has a non-trivial time range and the times are not locked,
  // then we change the times to match the time range.
//  vtkVector2d range;
//  vtkSMPropertyHelper(this->TimeKeeper, "TimeRange").Get(range.GetData(), 2);
  double *range = this->TimeKeeper->GetTimeRange();
  if (range[0] <= range[1])
  {
    this->InvokeEvent(igwAnimationScene::UpdateStartEndTimesEvent, &range);
  }
  this->SetStartTime(range[0]);
  this->SetEndTime(range[1]);
}

//----------------------------------------------------------------------------
void igwAnimationScene::AddView(vtkView* view)
{
  vtkInternals::VectorOfViews::iterator iter = this->Internals->ViewModules.begin();
  for (; iter != this->Internals->ViewModules.end(); ++iter)
  {
    if (iter->GetPointer() == view)
    {
      // already added.
      return;
    }
  }
  this->Internals->ViewModules.push_back(view);
}

//----------------------------------------------------------------------------
void igwAnimationScene::RemoveView(vtkView* view)
{
  vtkInternals::VectorOfViews::iterator iter = this->Internals->ViewModules.begin();
  for (; iter != this->Internals->ViewModules.end(); ++iter)
  {
    if (iter->GetPointer() == view)
    {
      this->Internals->ViewModules.erase(iter);
      break;
    }
  }
}

//----------------------------------------------------------------------------
void igwAnimationScene::RemoveAllViews()
{
  this->Internals->ViewModules.clear();
}

//----------------------------------------------------------------------------
unsigned int igwAnimationScene::GetNumberOfViews()
{
  return static_cast<unsigned int>(this->Internals->ViewModules.size());
}

//----------------------------------------------------------------------------
vtkView* igwAnimationScene::GetView(unsigned int cc)
{
  if (cc < this->GetNumberOfViews())
  {
    return this->Internals->ViewModules[cc];
  }

  return nullptr;
}

//----------------------------------------------------------------------------
void igwAnimationScene::StartCueInternal()
{
  this->Superclass::StartCueInternal();

  // Initialize all the animation cues.
  vtkInternals::VectorOfAnimationCues& cues = this->Internals->AnimationCues;
  for (vtkInternals::VectorOfAnimationCues::iterator iter = cues.begin(); iter != cues.end();
       ++iter)
  {
    iter->GetPointer()->Initialize();
  }
}

//----------------------------------------------------------------------------
void igwAnimationScene::EndCueInternal()
{
  // finalize all the animation cues.
  vtkInternals::VectorOfAnimationCues& cues = this->Internals->AnimationCues;
  for (vtkInternals::VectorOfAnimationCues::iterator iter = cues.begin(); iter != cues.end();
       ++iter)
  {
    iter->GetPointer()->Finalize();
  }

  this->Superclass::EndCueInternal();
}

//----------------------------------------------------------------------------
void igwAnimationScene::TickInternal(double currenttime, double deltatime, double clocktime)
{
  assert(!this->InTick);

  // We see that here we don't check if the cache is full at all. Views have
  // logic in them to periodically check and synchronize the "fullness" of cache
  // among all participating processes. So we don't have to manage that here at
  // all.
  bool caching_enabled =
    (!this->ForceDisableCaching) && igwAnimationScene::GlobalUseGeometryCache;
  if (caching_enabled)
  {
    this->Internals->PassUseCache(true);
    this->Internals->PassCacheTime(currenttime);
  }

  // this ensures that if this->SetSceneTime() is called, we don't call Tick()
  // again.
  this->InTick = true;

  this->SceneTime = currenttime;

  vtkInternals::VectorOfAnimationCues& cues = this->Internals->AnimationCues;
  // Now the animation update loop is as follows:
  //    - Update all cues not explicitly listed here
  //    - Update all Python cues
  // UpdateAllViews()
  //    - Update all Camera cues
  // Superclass::TickInternal
  // RenderAllViews()

  std::for_each(cues.begin(), cues.end(),
    vtkTickOnGenericCue(
      this->StartTime, this->EndTime, currenttime, deltatime, clocktime, this->Direction));

//  std::for_each(cues.begin(), cues.end(),
//    vtkTickOnPythonCue(
//      this->StartTime, this->EndTime, currenttime, deltatime, clocktime, this->Direction));

  this->Internals->UpdateAllViews();

//  std::for_each(cues.begin(), cues.end(),
//    vtkTickOnCameraCue(this->StartTime, this->EndTime, currenttime, deltatime, clocktime,
//      this->Direction, this->TimeKeeper));

  this->Superclass::TickInternal(currenttime, deltatime, clocktime);

  if (!this->OverrideStillRender)
  {
    this->Internals->StillRenderAllViews();
  }
  this->InTick = false;

  if (caching_enabled)
  {
    this->Internals->PassUseCache(false);
  }
}

//----------------------------------------------------------------------------
void igwAnimationScene::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
  os << indent << "ForceDisableCaching: " << this->ForceDisableCaching << endl;
}

//----------------------------------------------------------------------------
void igwAnimationScene::SetLoop(int val)
{
  this->AnimationPlayer->SetLoop(val != 0);
}

//----------------------------------------------------------------------------
int igwAnimationScene::GetLoop()
{
  return this->AnimationPlayer->GetLoop();
}

//----------------------------------------------------------------------------
void igwAnimationScene::Play()
{
  this->AnimationPlayer->Play();
}

//----------------------------------------------------------------------------
void igwAnimationScene::Reverse()
{
  this->SetDirection(vtkAnimationCue::PlayDirection::BACKWARD);
  this->AnimationPlayer->Play(static_cast<int>(vtkAnimationCue::PlayDirection::BACKWARD));
  this->SetDirection(vtkAnimationCue::PlayDirection::FORWARD);
}

//----------------------------------------------------------------------------
void igwAnimationScene::Stop()
{
  this->AnimationPlayer->Stop();
}

//----------------------------------------------------------------------------
void igwAnimationScene::GoToNext()
{
  static_cast<vtkAnimationPlayer*>(this->AnimationPlayer)->GoToNext();
}

//----------------------------------------------------------------------------
void igwAnimationScene::GoToPrevious()
{
  static_cast<vtkAnimationPlayer*>(this->AnimationPlayer)->GoToPrevious();
}

//----------------------------------------------------------------------------
void igwAnimationScene::GoToFirst()
{
  this->AnimationPlayer->GoToFirst();
}

//----------------------------------------------------------------------------
void igwAnimationScene::GoToLast()
{
  this->AnimationPlayer->GoToLast();
}

//----------------------------------------------------------------------------
void igwAnimationScene::SetPlayMode(int val)
{
//  this->AnimationPlayer->SetPlayMode(val);
}

//----------------------------------------------------------------------------
int igwAnimationScene::GetPlayMode()
{
//  return this->AnimationPlayer->GetPlayMode();
    return 0;
}

//----------------------------------------------------------------------------
void igwAnimationScene::SetNumberOfFrames(int val)
{
//  this->AnimationPlayer->SetNumberOfFrames(val);
}

//----------------------------------------------------------------------------
void igwAnimationScene::SetFramesPerTimestep(int val)
{
  this->AnimationPlayer->SetFramesPerTimestep(val);
}

//----------------------------------------------------------------------------
void igwAnimationScene::SetStride(int val)
{
  this->AnimationPlayer->SetStride(val);
}

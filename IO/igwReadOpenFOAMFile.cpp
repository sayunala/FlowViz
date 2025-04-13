#include "igwReadOpenFOAMFile.h"

#include "vtkOpenFOAMReader.h"
#include "vtkDoubleArray.h"
#include "vtkMultiBlockDataSet.h"
#include "vtkDataSet.h"

#include <vtkAnimationCue.h>
#include "vtkCommand.h"
#include "vtkAnimationScene.h"
#include "Components/igwAnimationScene.h"
#include "Core/igwApplicationCore.h"
#include "Components/igwAnimationManager.h"
#include <Components/igwTimeKeeper.h>
class OpenFOAMAnimator
{
public:
  OpenFOAMAnimator(vtkOpenFOAMReader* reader)
    :Reader(reader)
  {
  }

  OpenFOAMAnimator()
    : Reader(nullptr)
  {
  }

  ~OpenFOAMAnimator() = default;

  void SetReader(vtkOpenFOAMReader* reader)
  {
    this->Reader = reader;
  }

  void AddObserversToCue(vtkAnimationCue* cue)
  {
    cue->AddObserver(vtkCommand::StartAnimationCueEvent, this,
                     &OpenFOAMAnimator::Start);
    cue->AddObserver(vtkCommand::EndAnimationCueEvent, this,
                     &OpenFOAMAnimator::End);
    cue->AddObserver(vtkCommand::AnimationCueTickEvent, this,
                     &OpenFOAMAnimator::Tick);
  }

private:

  void Start()
  {
//    this->Actor->SetPosition(this->StartPosition.GetData());
      i = 1;
  }

  void Tick(vtkObject* vtkNotUsed(caller), unsigned long vtkNotUsed(event),
            void* calldata)
  {


    vtkAnimationCue::AnimationCueInfo* info =
        reinterpret_cast<vtkAnimationCue::AnimationCueInfo*>(calldata);
    std::cout << info->ClockTime << std::endl;
    vtkDoubleArray* timeValues = Reader->GetTimeValues();
    double *range = timeValues->GetRange();
    double time = info->ClockTime < range[0] ? range[0] : info->ClockTime;
    time = time > range[1] ? range[1] : time;
    Reader->UpdateTimeStep(time);
    Reader->Update();
    Reader->Print(std::cout);
    i++;
    igwApplicationCore::GetInstance()->render();
  }

  void End()
  {
//    this->Actor->SetPosition(this->EndPosition.GetData());
      i = 1;
  }
  //@}

  vtkOpenFOAMReader* Reader;
  int i = 1;
};

vtkStandardNewMacro(igwReadOpenFOAMFile)
igwReadOpenFOAMFile::igwReadOpenFOAMFile()
    :igwReadFile()
{

    this->Reader = vtkSmartPointer<vtkOpenFOAMReader>::New();

}

igwReadOpenFOAMFile::~igwReadOpenFOAMFile()
{

}

void igwReadOpenFOAMFile::PrintSelf(std::ostream &fstream, vtkIndent indent)
{

}

vtkDataObject *igwReadOpenFOAMFile::ReadFile(const char *filename)
{
    vtkOpenFOAMReader* openFOAMReader = vtkOpenFOAMReader::SafeDownCast(this->Reader);
    if(openFOAMReader == nullptr)
    {
        return nullptr;
        std::cout << "Reader is Null Ptr" << std::endl;
    }
    openFOAMReader->SetSkipZeroTime(1);
    openFOAMReader->SetCreateCellToPoint(1);
    openFOAMReader->SetFileName(filename);
    openFOAMReader->Update();
    openFOAMReader->SetTimeValue(1);
//    openFOAMReader->CreateCellToPointOn();
    openFOAMReader->Update();

    int numberOfPointArrays = openFOAMReader->GetNumberOfPointArrays();
    int numberOfCellArrays = openFOAMReader->GetNumberOfCellArrays();
    for(int i = 0; i < numberOfPointArrays;++i)
    {
        openFOAMReader->SetPointArrayStatus(openFOAMReader->GetPointArrayName(i), true);
    }
    for(int i = 0; i < numberOfCellArrays; ++i)
    {
        openFOAMReader->SetPointArrayStatus(openFOAMReader->GetCellArrayName(i), true);
    }
    openFOAMReader->Update();
    // 获取时间戳数据
    this->TimeValues = openFOAMReader->GetTimeValues();

    // 动画创建

    igwTimeKeeper* timeKeeper = igwApplicationCore::GetInstance()->GetTimeKeeper();
    timeKeeper->AddTimeStpes(TimeValues);

    igwAnimationManager* animationManager = igwApplicationCore::GetInstance()->GetAnimationManager();
    igwAnimationScene* Scene = animationManager->getIgwScene();

//    Scene->SetFrameRate(30);
//    Scene->SetStartTime(1);
//    Scene->SetEndTime(TimeValues->GetNumberOfTuples());
    vtkNew<vtkAnimationCue> Cue;
    double* timeRange = TimeValues->GetRange();
    Scene->AddCue(Cue);
    Cue->SetStartTime(0);
    Cue->SetEndTime(timeRange[1]);
//    Cue->SetTimeModeToNormalized();
    OpenFOAMAnimator* animator = new OpenFOAMAnimator(openFOAMReader);
    animator->AddObserversToCue(Cue);
    return openFOAMReader->GetOutput();

}

void igwReadOpenFOAMFile::SetTimeValue(double time)
{
    vtkOpenFOAMReader* openFOAMReader = vtkOpenFOAMReader::SafeDownCast(this->Reader);

    if(openFOAMReader == nullptr)
    {
        return ;
    }
    if(time > openFOAMReader->GetTimeValues()->GetNumberOfTuples())
    {
        return;
    }
    openFOAMReader->UpdateTimeStep(time);
//    openFOAMReader->SetTimeValue(time);
    openFOAMReader->Update();

}

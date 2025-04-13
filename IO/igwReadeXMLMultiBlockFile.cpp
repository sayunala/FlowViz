#include "igwReadeXMLMultiBlockFile.h"

#include "vtkXMLGenericDataObjectReader.h"

#include "vtkAnimationCue.h"
#include "vtkAnimationScene.h"
#include "vtkCommand.h"
#include "Core/igwApplicationCore.h"
#include "Components/igwAnimationManager.h"

class XMLAnimatorAnimator
{
public:
  XMLAnimatorAnimator(vtkXMLGenericDataObjectReader* reader)
    :Reader(reader)
  {
  }

  XMLAnimatorAnimator()
    : Reader(nullptr)
  {
  }

  ~XMLAnimatorAnimator() = default;

  void SetReader(vtkXMLGenericDataObjectReader* reader)
  {
    this->Reader = reader;
  }

  void AddObserversToCue(vtkAnimationCue* cue)
  {
    cue->AddObserver(vtkCommand::StartAnimationCueEvent, this,
                     &XMLAnimatorAnimator::Start);
    cue->AddObserver(vtkCommand::EndAnimationCueEvent, this,
                     &XMLAnimatorAnimator::End);
    cue->AddObserver(vtkCommand::AnimationCueTickEvent, this,
                     &XMLAnimatorAnimator::Tick);
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
    int* timeStepRange = Reader->GetTimeStepRange();
    if(i >= timeStepRange[1]) i = 1.0;

    vtkAnimationCue::AnimationCueInfo* info =
        reinterpret_cast<vtkAnimationCue::AnimationCueInfo*>(calldata);
    std::cout << info->ClockTime << std::endl;
//    vtkDoubleArray* timeValues = Reader->GetTimeStepRange();
//    Reader->SetTimeStep(i);
    Reader->Update();
//    Reader->SetFileName("C:/Users/27547/Desktop/0.76_new/0.76_new_0_0.vtm");
//    Reader->Update();
    i++;
    igwApplicationCore::GetInstance()->render();
  }

  void End()
  {
//    this->Actor->SetPosition(this->EndPosition.GetData());
      i = 1;
  }
  //@}

  vtkXMLGenericDataObjectReader* Reader;
  int i = 1;
};

vtkStandardNewMacro(igwReadeXMLMultiBlockFile)

igwReadeXMLMultiBlockFile::igwReadeXMLMultiBlockFile()
    :igwReadFile()
{

    this->Reader = vtkSmartPointer<vtkXMLGenericDataObjectReader>::New();
}
igwReadeXMLMultiBlockFile::~igwReadeXMLMultiBlockFile()
{

}

void igwReadeXMLMultiBlockFile::PrintSelf(std::ostream &ostream, vtkIndent indent)
{

}

vtkDataObject *igwReadeXMLMultiBlockFile::ReadFile(const char *filename)
{
    vtkXMLGenericDataObjectReader* XMLReader = vtkXMLGenericDataObjectReader::SafeDownCast(this->Reader);
    XMLReader->SetFileName(filename);
    XMLReader->Update();
    int* time = XMLReader->GetTimeStepRange();

    igwAnimationManager* animationManager = igwApplicationCore::GetInstance()->GetAnimationManager();
    vtkAnimationScene* Scene = animationManager->getScene();
    Scene->SetFrameRate(30);
    Scene->SetEndTime(10);

    // 创建动画
    vtkNew<vtkAnimationCue> Cue;
    Cue->SetStartTime(1);
    Cue->SetEndTime(10);
    Scene->AddCue(Cue);
//    Cue->SetTimeModeToNormalized();
    XMLAnimatorAnimator* animator = new XMLAnimatorAnimator(XMLReader);
    animator->AddObserversToCue(Cue);
    return XMLReader->GetOutput();

}

void igwReadeXMLMultiBlockFile::SetTimeValue(double time)
{

}

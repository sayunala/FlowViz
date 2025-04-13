#include "igwReadSeriesFiles.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QDir>
#include <QVector>
#include "vtkDataObjectTreeIterator.h"
#include "vtkDoubleArray.h"


#include "vtkAnimationCue.h"
#include "vtkCommand.h"
#include "vtkAnimationScene.h"
#include "vtkDataObjectAlgorithm.h"
#include "vtkCGNSReader.h"
#include "vtkCGNSFileSeriesReader.h"
#include "vtkMultiBlockDataSet.h"
#include "igwIOCore.h"
#include "Core/igwApplicationCore.h"

#include "Components/igwAnimationManager.h"
#include "Components/igwAnimationScene.h"
#include "Components/igwTimeKeeper.h"
class igwSeriesAnimator
{
public:
  igwSeriesAnimator(QVector<vtkDataObject*>& datas)
    :Datas(datas)
  {

  }

  igwSeriesAnimator()
  {
  }
  igwSeriesAnimator(vtkCGNSFileSeriesReader* reader, QList<SeriesFileInFo>& infos)
    :Reader(reader)
    ,Infos(infos)
  {

  }

  ~igwSeriesAnimator() = default;

  void SetDatas(QVector<vtkDataObject*> datas)
  {
    this->Datas = datas;
  }

  void AddObserversToCue(vtkAnimationCue* cue)
  {
    cue->AddObserver(vtkCommand::StartAnimationCueEvent, this,
                     &igwSeriesAnimator::Start);
    cue->AddObserver(vtkCommand::EndAnimationCueEvent, this,
                     &igwSeriesAnimator::End);
    cue->AddObserver(vtkCommand::AnimationCueTickEvent, this,
                     &igwSeriesAnimator::Tick);
  }

private:

  void Start()
  {
//    this->Actor->SetPosition(this->StartPosition.GetData());
      i = 0;
  }

  void Tick(vtkObject* vtkNotUsed(caller), unsigned long vtkNotUsed(event),
            void* calldata)
  {


    vtkAnimationCue::AnimationCueInfo* info =
        reinterpret_cast<vtkAnimationCue::AnimationCueInfo*>(calldata);
    std::cout << info->ClockTime << std::endl;

    this->Reader->UpdateTimeStep(info->ClockTime);
    Reader->UpdateInformation();
    Reader->UpdateDataObject();
    Reader->Update();

    Reader->GetOutput()->Print(std::cout);

    i++;
    igwApplicationCore::GetInstance()->render();
  }

  void End()
  {
//    this->Actor->SetPosition(this->EndPosition.GetData());
      i = 1;
  }
  //@}

  QVector<vtkDataObject*> Datas;
  vtkCGNSFileSeriesReader* Reader;
  QList<SeriesFileInFo> Infos;
//  vtkMultiBlockDataSetAlgorithm*
  int i = 1;
};


vtkStandardNewMacro(igwReadSeriesFiles)
igwReadSeriesFiles::igwReadSeriesFiles()
    :igwReadFile()
{
    this->Reader = vtkSmartPointer<vtkCGNSReader>::New();
    this->SeriesReader = vtkSmartPointer<vtkCGNSFileSeriesReader>::New();
//    this->SeriesReader->SetIgnoreReaderTime(true);

}

igwReadSeriesFiles::~igwReadSeriesFiles()
{

}

void igwReadSeriesFiles::PrintSelf(std::ostream &fstream, vtkIndent indent)
{

}
vtkDataObject *igwReadSeriesFiles::ReadFile(const char *filename)
{
    if(filename == nullptr)
    {
        return nullptr;
    }
    QList<SeriesFileInFo> seriesFiles = this->loadConfigFile(filename);
    vtkCGNSReader* reader = vtkCGNSReader::SafeDownCast(this->Reader);
    SeriesReader->SetReader(reader);

    // 时间戳
    vtkNew<vtkDoubleArray> timeStpes;
    double i = 0.0;
    for(const SeriesFileInFo& info : seriesFiles)
    {
        // 读取文件到QFile中, // 默认是cgns文件

//        vtkDataObject* data = igwIOCore::ReadFile(info.filePath.toStdString().c_str(), igwIOCore::FileType::CGNS);
        timeStpes->InsertNextTuple1(i);
        SeriesReader->AddFileName(info.filePath.toStdString().c_str());
        ++i;
    }
    SeriesReader->Update();

//    this->SeriesReader->Update();


    reader->Update();
    int numberOfPointArrays = reader->GetNumberOfPointArrays();
    int numberOfCellArrays = reader->GetNumberOfCellArrays();
    for(int i = 0; i < numberOfPointArrays;++i)
    {
        reader->SetPointArrayStatus(reader->GetPointArrayName(i), true);
    }


    igwTimeKeeper* timeKeeper = igwApplicationCore::GetInstance()->GetTimeKeeper();
    timeKeeper->AddTimeStpes(timeStpes);

    igwAnimationManager* animationManager = igwApplicationCore::GetInstance()->GetAnimationManager();
    igwAnimationScene* Scene = animationManager->getIgwScene();

//    Scene->SetFrameRate(30);
    Scene->SetFramesPerTimestep(1);
    Scene->SetStartTime(0);
    Scene->SetEndTime(seriesFiles.size() - 1);
    vtkNew<vtkAnimationCue> Cue;

    Scene->AddCue(Cue);
    // 最关键的地方所有Cue必须设置StartTime为0
    Cue->SetStartTime(0);
    Cue->SetEndTime(seriesFiles.size() - 1);

    igwSeriesAnimator* animator = new igwSeriesAnimator(SeriesReader, seriesFiles);
    animator->AddObserversToCue(Cue);
    SeriesReader->Update();

    SeriesReader->GetOutput()->Print(std::cout);

    return SeriesReader->GetOutput();


}

void igwReadSeriesFiles::SetTimeValue(double time)
{

}

QList<SeriesFileInFo> igwReadSeriesFiles::loadConfigFile(const QString &configFile)
{
    QFile file(configFile);
    if (!file.open(QIODevice::ReadOnly)) {
       qWarning() << "Couldn't open the file.";
       return QList<SeriesFileInFo>();
    }
    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject rootObj = doc.object();
    QJsonObject descriptionObj = rootObj["description"].toObject();
    qDebug() << "Description of fileType:" << descriptionObj["fileType"].toString();
    qDebug() << "Description of files:" << descriptionObj["files"].toString();

    QString fileType = rootObj["fileType"].toString();  // 获取文件类型
    QJsonArray filesArray = rootObj["files"].toArray();

    QList<SeriesFileInFo> fileList;
    QFileInfo configFileInfo(configFile);
    QString configDir = configFileInfo.absolutePath();  // 配置文件的绝对路径

      // 如果配置文件在子目录下，可以将其视为根目录
    QDir baseDir(configDir);  // 设置基准目录（配置文件的目录）

    for (const QJsonValue& fileValue : filesArray) {
        QJsonObject fileObj = fileValue.toObject();
        SeriesFileInFo fileInfo;

        QString relativePath = fileObj["filepath"].toString();

        fileInfo.filePath = baseDir.absoluteFilePath(relativePath);
        fileInfo.timeStep = fileObj["timestamp"].toString();
        fileInfo.fileType = fileType;  // 所有文件共享相同的文件类型

        fileList.append(fileInfo);
    }
    return fileList;

}

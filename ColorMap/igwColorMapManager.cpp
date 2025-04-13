#include "igwColorMapManager.h"

#include "igwTransferFunctionPresets.h"

#include <vtkTuple.h>
#include "vtk_jsoncpp.h"
namespace  {
class StrictWeakOrdering
{
public:
  bool operator()(const vtkTuple<double, 4>& x, const vtkTuple<double, 4>& y) const
  {
    return (x.GetData()[0] < y.GetData()[0]);
  }
};

/**
 * @brief igwNormalize：把控制点设置在[0, 1]之内
 * @param cntrlPoints
 * @param log_space
 * @param originalRange
 * @return
 */
bool igwNormalize(std::vector<vtkTuple<double, 4>>& cntrlPoints, bool log_space,
  vtkTuple<double, 2>* originalRange = nullptr)
{
  if (cntrlPoints.empty())
  {
    // nothing to do, but not an error, so return true.
    return true;
  }
  if (cntrlPoints.size() == 1)
  {
    if (originalRange)
    {
      (*originalRange)[0] = cntrlPoints[0][0];
      (*originalRange)[1] = cntrlPoints[0][0];
    }

    // Only 1 control point in the property. We'll add 2 points, however.
    cntrlPoints.resize(2);
    cntrlPoints[1] = cntrlPoints[0];
    cntrlPoints[0][0] = 0.0;
    cntrlPoints[1][0] = 1.0;
    return true;
  }

  // sort the points by x, just in case user didn't add them correctly.
  std::sort(cntrlPoints.begin(), cntrlPoints.end(), StrictWeakOrdering());

  const double old_range[2] = { cntrlPoints.front().GetData()[0], cntrlPoints.back().GetData()[0] };
  if (log_space && (old_range[0] <= 0 || old_range[1] <= 0))
  {
    vtkGenericWarningMacro("Range not valid for log. Assuming control points "
                           "are not specified in log space.");
    log_space = false;
  }
  if (originalRange)
  {
    (*originalRange)[0] = old_range[0];
    (*originalRange)[1] = old_range[1];
  }

  // if in log_space, let's convert all the control point values to
  // log.
  if (log_space)
  {
    for (size_t cc = 0; cc < cntrlPoints.size(); ++cc)
    {
      cntrlPoints[cc][0] = log10(cntrlPoints[cc][0]);
    }
  }

  // now simply normalize the cntrlPoints.
  const double range[2] = { cntrlPoints.front()[0], cntrlPoints.back()[0] };
  if (range[0] == 0.0 && range[1] == 1.0)
  {
    // nothing to do.
    return true;
  }
  const double denominator = (range[1] - range[0]);
  assert(denominator > 0);
  for (size_t cc = 0; cc < cntrlPoints.size(); ++cc)
  {
    cntrlPoints[cc][0] = (cntrlPoints[cc][0] - range[0]) / denominator;
  }
  return true;
}

/**
 * @brief igwRescaleNormalizedControlPoints：把[0, 1]范围内的控制点缩放到[rangeMin, rangeMax]之内
 * @param cntrlPoints
 * @param rangeMin
 * @param rangeMax
 * @param log_space
 * @return
 */
bool igwRescaleNormalizedControlPoints(
  std::vector<vtkTuple<double, 4>>& cntrlPoints, double rangeMin, double rangeMax, bool log_space)
{
  assert(cntrlPoints.size() >= 2);
  assert(cntrlPoints.front()[0] == 0.0 && cntrlPoints.back()[0] == 1.0);
  assert(rangeMin <= rangeMax);

  if (log_space && (rangeMin <= 0.0 || rangeMax <= 0.0))
  {
    // ensure the range is valid for log space.
    double range[2] = { rangeMin, rangeMax };
//    if (vtkSMCoreUtilities::AdjustRangeForLog(range))
//    {
//      // ranges not valid for log-space. Will convert them.
//      vtkGenericWarningMacro("Ranges not valid for log-space. "
//                             "Changed the range to ("
//        << range[0] << ", " << range[1] << ").");
//    }
    rangeMin = range[0];
    rangeMax = range[1];
  }

  double scale = (rangeMax - rangeMin);
  if (log_space)
  {
    rangeMin = log10(rangeMin);
    rangeMax = log10(rangeMax);
    scale = (rangeMax - rangeMin);
  }
  //assert(scale > 0);
  for (size_t cc = 0; cc < cntrlPoints.size(); ++cc)
  {
    double& x = cntrlPoints[cc][0];
    x = x * scale + rangeMin;
    if (log_space)
    {
      x = pow(10.0, x);
    }
  }
  return true;
}
}
vtkSmartPointer<igwColorMapManager> igwColorMapManager::Instance;

class igwColorMapManager::igwInternals
{
public:
  igwInternals()
  {
      STC = vtkSmartPointer<vtkDiscretizableColorTransferFunction>::New();
      auto transferFunctionPresets = igwTransferFunctionPresets::GetInstance();

      const Json::Value& preset = transferFunctionPresets->GetPreset(0);

      const char* key = "RGBPoints";
      auto pointsValue = preset[key];
      for (Json::ArrayIndex cc = 0, max = pointsValue.size() / 4; cc < max; ++cc)
       {

          STC->AddRGBPoint(pointsValue[4 * cc].asDouble(), pointsValue[4 * cc + 1].asDouble(),
                           pointsValue[4 * cc + 2].asDouble(),
                           pointsValue[4 * cc + 3].asDouble());

      }
      STC->SetColorSpaceToDiverging();
      PWF = vtkSmartPointer<vtkPiecewiseFunction>::New();
      PWF->AddPoint(0, 0);
      PWF->AddPoint(1, 1);

  }

  ~igwInternals() = default;

  bool AddColorTransferFunctionPoint();

  bool RemoveAllPointsOfColorTransferFunction(){
      STC->RemoveAllPoints();
      STC->Modified();

  }

  /**
   * @brief ApplyPreset
   * @param presetName
   * @return
   */
  bool ApplyPreset(const Json::Value& preset){
      STC->RemoveAllPoints();
      double *range = this->LastRange;

      const char* key = "RGBPoints";
      auto pointsValue = preset[key];

//      if (pointsValue.isNull() || !pointsValue.isArray() || (pointsValue.size() % 4) != 0 ||
//           pointsValue.empty())
//      {
//           vtkErrorMacro("Preset may not be valid. Please validate the preset:\n"
//             << arg.toStyledString().c_str());
//           return false;
//      }
     // 获取json文件中的控制点
     std::vector<vtkTuple<double, 4>> cntrlPoints;
     cntrlPoints.resize(pointsValue.size() / 4);
     //使用cntrPoints 目的是为了进行缩放
     for (Json::ArrayIndex cc = 0, max = pointsValue.size() / 4; cc < max; ++cc)
     {
       cntrlPoints[cc][0] = pointsValue[4 * cc].asDouble();
       cntrlPoints[cc][1] = pointsValue[4 * cc + 1].asDouble();
       cntrlPoints[cc][2] = pointsValue[4 * cc + 2].asDouble();
       cntrlPoints[cc][3] = pointsValue[4 * cc + 3].asDouble();
     }

     bool presetIsLog = preset.get("UseLogScale", Json::Value(false)).asBool();

     //把控制点的范围缩小为[0,1]
     igwNormalize(cntrlPoints, presetIsLog);
//     preset.removeMember("UseLogScale");

     //[0,1]的控制点缩放到 [rang[0], range[1]]
     igwRescaleNormalizedControlPoints(cntrlPoints, range[0], range[1], false);
//         this->LastRange[0] = range[0];
//         this->LastRange[1] = range[1];

     pointsValue.resize(static_cast<Json::ArrayIndex>(cntrlPoints.size() * 4));
     for (size_t cc = 0; cc < cntrlPoints.size(); cc++)
     {
        pointsValue[static_cast<Json::ArrayIndex>(4 * cc)] = Json::Value(cntrlPoints[cc][0]);
        pointsValue[static_cast<Json::ArrayIndex>(4 * cc) + 1] = Json::Value(cntrlPoints[cc][1]);
        pointsValue[static_cast<Json::ArrayIndex>(4 * cc) + 2] = Json::Value(cntrlPoints[cc][2]);
        pointsValue[static_cast<Json::ArrayIndex>(4 * cc) + 3] = Json::Value(cntrlPoints[cc][3]);

        // 控制点颜色的添加
        STC->AddRGBPoint(pointsValue[static_cast<Json::ArrayIndex>(4 * cc)].asDouble(),
                         pointsValue[static_cast<Json::ArrayIndex>(4 * cc) + 1].asDouble(),
                         pointsValue[static_cast<Json::ArrayIndex>(4 * cc) + 2].asDouble(),
                         pointsValue[static_cast<Json::ArrayIndex>(4 * cc) + 3].asDouble());
        if (preset["ColorSpace"] == "Diverging")
            STC->SetColorSpaceToDiverging();
        else if(preset["ColorSpace"] == "Lab"){
            STC->SetColorSpaceToLab();
        }
        else if(preset["ColorSpace"] == "LabLabCIEDE2000"){
            STC->SetColorSpaceToLabCIEDE2000();
        }
        else if(preset["ColorSpace"] == "RGB"){
            STC->SetColorSpaceToRGB();
        }
        else if(preset["ColorSpace"] == "HSV"){
            STC->SetColorSpaceToHSV();
        }
     }
     STC->Modified();
     this->PWF->RemoveAllPoints();
     this->PWF->AddPoint(range[0], 0);
     this->PWF->AddPoint(range[1], 1);
     this->PWF->Modified();
     double *a = this->PWF->GetRange();
     double b = a[0];
     return true;
  }


  vtkDiscretizableColorTransferFunction* GetColorTransferFunction(){
      return STC;
  }

  vtkPiecewiseFunction* GetPiecewiseFunction(){
      return PWF;
  }

  void SetRange(double rangeMin, double rangeMax){
      LastRange[0] = rangeMin;
      LastRange[1] = rangeMax;
  }
  Json::Value GetStateAsPreset(){
      Json::Value root;
      switch (STC->GetColorSpace()) {
          case VTK_CTF_DIVERGING:
              root["ColorSpace"] = "Diverging";
              break;
          case VTK_CTF_LAB:
              root["ColorSpace"] = "Lab";
          case VTK_CTF_RGB:
              root["ColorSpace"] = "RGB";
          case VTK_CTF_LAB_CIEDE2000:
              root["ColorSpace"] = "LabLabCIEDE2000";
          default:
              break;
      }
      Json::Value RGBPoints(Json::arrayValue);
      for(int i = 0; i < STC->GetSize(); i++){
          double rgbPoint[6];  // 存储RGB点的数组
          STC->GetNodeValue(i, rgbPoint);
          RGBPoints.append(rgbPoint[0]);
          RGBPoints.append(rgbPoint[1]);
          RGBPoints.append(rgbPoint[2]);
          RGBPoints.append(rgbPoint[3]);
      }

      root["RGBPoints"] = RGBPoints;

      return root;


  }

private:
  vtkSmartPointer<vtkDiscretizableColorTransferFunction> STC;

  vtkSmartPointer<vtkPiecewiseFunction> PWF;

  double LastRange[2];



};


igwColorMapManager* igwColorMapManager::New()
{
  auto instance = igwColorMapManager::GetInstance();
  instance->Register(nullptr);
  return instance;
}
igwColorMapManager::igwColorMapManager(): Internals(new igwColorMapManager::igwInternals())
{
    this->Internals->SetRange(0, 1);
    this->PresetName = nullptr;
}

//----------------------------------------------------------------------------
igwColorMapManager::~igwColorMapManager()
{
    delete this->Internals;
    this->Internals = nullptr;
}

igwColorMapManager* igwColorMapManager::GetInstance()
{
  if (igwColorMapManager::Instance.GetPointer() == nullptr)
  {
    auto presets = new igwColorMapManager();
    presets->InitializeObjectBase();
    igwColorMapManager::Instance.TakeReference(presets);
  }

  return Instance;
}

vtkDiscretizableColorTransferFunction *igwColorMapManager::GetColorFunction()
{
    return this->Internals->GetColorTransferFunction();
}

vtkPiecewiseFunction *igwColorMapManager::GetPiecewiseFunction()
{
    return this->Internals->GetPiecewiseFunction();
}

bool igwColorMapManager::ApplyPreset(const char *presetName)
{
    auto transferFunctionPresets = igwTransferFunctionPresets::GetInstance();
    this->SetPresetName(presetName);
    return this->Internals->ApplyPreset(transferFunctionPresets->GetFirstPresetWithName(presetName));
}

bool igwColorMapManager::ApplyPreset(const vtkJson::Value &value)
{
    return this->Internals->ApplyPreset(value);
}

bool igwColorMapManager::ApplyPreset()
{
    auto transferFunctionPresets = igwTransferFunctionPresets::GetInstance();

    return this->Internals->ApplyPreset(transferFunctionPresets->GetFirstPresetWithName(this->PresetName));
}

void igwColorMapManager::SetRange(double *range)
{
    if(range == nullptr) return;
    this->Internals->SetRange(range[0], range[1]);
}

void igwColorMapManager::SetRange(double rangeMin, double rangeMax)
{
    this->Internals->SetRange(rangeMin, rangeMax);
}

vtkJson::Value igwColorMapManager::GetStateAsPreset()
{
    return Internals->GetStateAsPreset();
}


void igwColorMapManager::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}

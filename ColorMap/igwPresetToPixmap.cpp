#include "igwPresetToPixmap.h"
#include "vtkFloatArray.h"
#include "vtkImageData.h"
#include "vtkMath.h"
#include "vtkNew.h"
#include "vtkDiscretizableColorTransferFunction.h"
#include "vtkPiecewiseFunction.h"
#include "igwTransferFunctionPresets.h"
#include "vtk_jsoncpp.h"
#include <vtkUnsignedCharArray.h>
#include <QPainter>
#include <QPixmap>
class igwPresetToPixmap::igwInternals
{


public:
  igwInternals()
  {

  }


};


igwPresetToPixmap::igwPresetToPixmap(QObject* parentObject)
  : Superclass(parentObject)
  , Internals(new igwPresetToPixmap::igwInternals())
{
}

igwPresetToPixmap::~igwPresetToPixmap() = default;

QPixmap igwPresetToPixmap::render(const Json::Value& preset, const QSize& resolution) const
{
  if (resolution.width() <= 0 || resolution.height() <= 0)
  {
    return QPixmap();
  }

  vtkNew<vtkColorTransferFunction> stc;

  const char* key = "RGBPoints";
  auto pointsValue = preset[key];
  for (Json::ArrayIndex cc = 0, max = pointsValue.size() / 4; cc < max; ++cc)
   {

      stc->AddRGBPoint(pointsValue[4 * cc].asDouble(), pointsValue[4 * cc + 1].asDouble(),
                       pointsValue[4 * cc + 2].asDouble(),
                       pointsValue[4 * cc + 3].asDouble());
      if (preset["ColorSpace"] == "Diverging")
          stc->SetColorSpaceToDiverging();
      else if(preset["ColorSpace"] == "Lab"){
          stc->SetColorSpaceToLab();
      }
      else if(preset["ColorSpace"] == "LabLabCIEDE2000"){
          stc->SetColorSpaceToLabCIEDE2000();
      }
      else if(preset["ColorSpace"] == "RGB"){
          stc->SetColorSpaceToRGB();
      }
      else if(preset["ColorSpace"] == "HSV"){
          stc->SetColorSpaceToHSV();
      }
   }
  stc->Modified();

  vtkPiecewiseFunction* pf = nullptr;
  return this->renderColorTransferFunction(stc, pf, resolution);

}

//-----------------------------------------------------------------------------
QPixmap igwPresetToPixmap::renderColorTransferFunction(
  vtkScalarsToColors* stc, vtkPiecewiseFunction* pf, const QSize& resolution) const
{
  int numSamples = std::min(256, std::max(2, resolution.width()));
  vtkNew<vtkFloatArray> data;
  data->SetNumberOfTuples(numSamples);
  const double* range = stc->GetRange();
  int isUsingLog = stc->UsingLogScale();
  double lrange[2];
  if (isUsingLog)
  {
    lrange[0] = log10(range[0]);
    lrange[1] = log10(range[1]);
  }
  for (vtkIdType cc = 0, max = numSamples; cc < max; ++cc)
  {
    double normVal = static_cast<double>(cc) / (max - 1);
    double val;
    if (isUsingLog)
    {
      double lval = lrange[0] + normVal * (lrange[1] - lrange[0]);
      val = pow(10.0, lval);
    }
    else
    {
      val = (range[1] - range[0]) * normVal + range[0];
    }
    data->SetValue(cc, val);
  }
  vtkSmartPointer<vtkUnsignedCharArray> colors;
  colors.TakeReference(vtkUnsignedCharArray::SafeDownCast(
    stc->MapScalars(data.GetPointer(), VTK_COLOR_MODE_MAP_SCALARS, 0)));
  QImage image(numSamples, 1, QImage::Format_RGB888);
  for (int cc = 0; cc < numSamples; ++cc)
  {
    unsigned char* ptr = colors->GetPointer(4 * cc);
    image.setPixel(cc, 0, qRgb(ptr[0], ptr[1], ptr[2]));
  }
  if (pf)
  {
    image = image.scaled(image.width(), resolution.height());
    QPixmap pixmap = QPixmap::fromImage(image);
    QPainterPath path;
    path.moveTo(0, 0);
    for (vtkIdType cc = 0, max = numSamples; cc < max; cc += 10)
    {
      float x = data->GetValue(cc);
      int y = static_cast<int>(resolution.height() * (1.0 - pf->GetValue(x)));
      path.lineTo(cc, y);
    }
    QPainter painter(&pixmap);
    painter.setPen(Qt::black);
    // painter.setRenderHint(QPainter::Antialiasing, true);
    QPen pen = painter.pen();
    pen.setWidth(2);
    painter.strokePath(path, pen);
    return pixmap;
  }
  else
  {
    image = image.scaled(resolution);
    return QPixmap::fromImage(image);
  }
}



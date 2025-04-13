
#include "ui_igwColorMapEditorWidget.h"
#include "ui_igwSavePresetOptions.h"
#include "igwColorMapEditorWidget.h"

#include "QStyledItemDelegate"
#include <QJsonDocument>
#include <QPainter>
#include <QPen>
#include <QStandardItemModel>
#include <vtkFloatArray.h>
#include <vtkPiecewiseFunction.h>
#include <vtkUnsignedCharArray.h>

#include "igwTransferFunctionPresets.h"
#include "igwColorMapManager.h"
#include "igwPresetToPixmap.h"
#include "igwColorMapCore.h"
#include "vtk_jsoncpp.h"

class igwColorMapDelegate : public QStyledItemDelegate
{
public:
  igwColorMapDelegate(QObject* parent = nullptr)
    : QStyledItemDelegate(parent)
  {
  }

  void paint(
    QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override
  {
    painter->save();
    auto opt = option;
    this->initStyleOption(&opt, index);

    // The pixmap takes 3/4 of the height and 1/2 of the width of the item, and the text takes 1/2
    // of the height and 1/2 of the width of the item
    int const pixmapHorizontalMargins = 5;
    auto const pixmapRect =
      QRect(opt.rect.x() + pixmapHorizontalMargins, opt.rect.y() + 0.125 * opt.rect.height(),
        opt.rect.width() / 2 - 2 * pixmapHorizontalMargins, opt.rect.height() * 0.75);
    auto const textRect = QRect(
      opt.rect.x() + opt.rect.width() / 2, opt.rect.y(), opt.rect.width() / 2, opt.rect.height());

    if (opt.state & QStyle::State_Selected)
    {
      // Fill the background of the selected item with a blue color
      painter->fillRect(opt.rect, opt.palette.color(QPalette::Highlight));

      QPen pen = painter->pen();

      pen.setColor(opt.palette.color(QPalette::HighlightedText));
      painter->setPen(pen);
    }
    else
    {
      painter->fillRect(opt.rect, painter->brush());
    }

    // First element is used as a placeholder, so drawing is different
    if (index.row() != 0)
    {
      painter->drawText(QRectF(textRect), Qt::AlignVCenter, index.data().toString());
      auto transferFunctionPresets = igwTransferFunctionPresets::GetInstance();

      QPixmap pixmap = m_PresetToPixmap.render(transferFunctionPresets->GetPreset(index.data(Qt::UserRole).toInt()), opt.rect.size());

      painter->drawPixmap(pixmapRect, pixmap);
    }
    else
    {
      painter->drawText(opt.rect, Qt::AlignVCenter, index.data().toString());

    }

    painter->restore();
  }

  QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex&) const override
  {
    return QSize{ option.rect.width(), option.fontMetrics.height() * 2 };
  }

private:
  igwPresetToPixmap m_PresetToPixmap;

  QPixmap renderColorTransferFunction(
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

};

igwColorMapEditorWidget::igwColorMapEditorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::igwColorMapEditorWidget)
{
    ui->setupUi(this);

    QObject::connect(ui->ColorEditor, SIGNAL(controlPointsModified()), this, SIGNAL(ChangedFinished()));
//    QFile file(":/Color/src/ColorMap/ColorManager/pqPresetGroups.json");
//    file.open(QIODevice::ReadOnly | QIODevice::Text);
//    QJsonParseError error;
//    QJsonDocument document = QJsonDocument::fromJson(file.readAll(), &error);
    m_groupManager = igwColorMapCore::GetInstance()->GetGroupManager();
//    m_groupManager->loadGroups(file.readAll());
//    file.close();
    auto ColorMapManager = igwColorMapManager::GetInstance();
    vtkDiscretizableColorTransferFunction* stc = ColorMapManager->GetColorFunction();

    auto transferFunctionPresets = igwTransferFunctionPresets::GetInstance();

    stc->SetColorSpaceToDiverging();


    stc->Modified();
    bool a = stc->GetIndexedLookup();

    vtkPiecewiseFunction* pwf = ColorMapManager->GetPiecewiseFunction();




//    vtkPiecewiseFunction* pwf = ColorMapManager->GetPiecewiseFunction();


    ui->ColorEditor->initialize(stc, true, nullptr, false);
    ui->OpacityEditor->initialize(stc, false, pwf, true);
    ui->DefaultPresetsComboBox->blockSignals(true);
    ui->DefaultPresetsComboBox->setItemDelegate(new igwColorMapDelegate(ui->DefaultPresetsComboBox));
    ui->DefaultPresetsComboBox->addItem(tr("Select a color map from default presets"), -1);
    QStandardItemModel* model = qobject_cast<QStandardItemModel*>(ui->DefaultPresetsComboBox->model());
    QStandardItem* item = model->item(0);
    item->setFlags(item->flags() & ~Qt::ItemIsEnabled);
//    auto transferFunctionPresets = igwTransferFunctionPresets::GetInstance();

    for (unsigned int index = 0; index < transferFunctionPresets->GetNumberOfPresets(); ++index)
    {
      auto presetName = QString::fromStdString(transferFunctionPresets->GetPresetName(index));
        if (m_groupManager->presetRankInGroup(presetName, "Default") != -1){
            ui->DefaultPresetsComboBox->addItem(presetName, index);
        }
    }
    ui->DefaultPresetsComboBox->blockSignals(false);
//    ui->DefaultPresetsComboBox->addItem("cool to warm", 0);
}

igwColorMapEditorWidget::~igwColorMapEditorWidget()
{
    delete ui;
}




void igwColorMapEditorWidget::on_DefaultPresetsComboBox_currentIndexChanged(const QString &presetName)
{
    auto ColorMapManager = igwColorMapManager::GetInstance();
    vtkDiscretizableColorTransferFunction* stc = ColorMapManager->GetColorFunction();
    stc->RemoveAllPoints();
    if (ui->DefaultPresetsComboBox->currentIndex() == 0)
    {
      return;
    }
    this->blockSignals(true);
//    auto transferFunctionPresets = igwTransferFunctionPresets::GetInstance();

//    const Json::Value& preset = transferFunctionPresets->GetFirstPresetWithName(presetName.toStdString().c_str());
//    const char* key = "RGBPoints";
//    auto pointsValue = preset[key];
//    for (Json::ArrayIndex cc = 0, max = pointsValue.size() / 4; cc < max; ++cc)
//    {

//       stc->AddRGBPoint(pointsValue[4 * cc].asDouble(), pointsValue[4RescaleTransferFunction * cc + 1].asDouble(),
//                        pointsValue[4 * cc + 2].asDouble(),
//                        pointsValue[4 * cc + 3].asDouble());
//       if (preset["ColorSpace"] == "Diverging")
//           stc->SetColorSpaceToDiverging();
//       else if(preset["ColorSpace"] == "Lab"){
//           stc->SetColorSpaceToLab();
//       }
//       else if(preset["ColorSpace"] == "LabLabCIEDE2000"){
//           stc->SetColorSpaceToLabCIEDE2000();
//       }
//       else if(preset["ColorSpace"] == "RGB"){
//           stc->SetColorSpaceToRGB();
//       }
//       else if(preset["ColorSpace"] == "HSV"){
//           stc->SetColorSpaceToHSV();
//       }
//    }
//    stc->Modified();
    ColorMapManager->ApplyPreset(presetName.toStdString().c_str());
    this->blockSignals(false);
    Q_EMIT this->ChangedFinished();
}

void igwColorMapEditorWidget::ResetCombox()
{
    ui->DefaultPresetsComboBox->blockSignals(true);
    ui->DefaultPresetsComboBox->setCurrentIndex(-1);
    ui->DefaultPresetsComboBox->blockSignals(false);
}

void igwColorMapEditorWidget::on_saveAsPreset_clicked()
{
    QDialog dialog(this);
    Ui::SavePresetOptions options;
    options.setupUi(&dialog);
    options.saveColors->setChecked(true);
    if (dialog.exec() != QDialog::Accepted)
    {
        return;
    }
//    Json::Value preset = ;
    auto presets = igwTransferFunctionPresets::GetInstance();

    Json::Value preset = igwColorMapManager::GetInstance()->GetStateAsPreset();
    std::string presetName = presets->AddUniquePreset(preset, options.presetName->text().toUtf8().data());
//    preset["Name"] = presetName;

    m_groupManager->addToGroup("Default", QString::fromStdString(presetName));
    m_groupManager->addToGroup("User", QString::fromStdString(presetName));
    Q_EMIT SaveStateAsPresets();
}

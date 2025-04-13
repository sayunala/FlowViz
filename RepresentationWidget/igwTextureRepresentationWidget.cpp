#include "igwTextureRepresentationWidget.h"
#include "ui_igwTextureRepresentationWidget.h"

#include "Representation/igwTextureRepresentation.h"
#include "vtkSurfaceLICInterface.h"

#include "vtkPointData.h"
#include "vtkDataArray.h"
#include "vtkDataSet.h"

// 同步 Slider 和 LineEdit
#define THOUSAND 1000
#define HANDRED 100

igwTextureRepresentationWidget::igwTextureRepresentationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::igwTextureRepresentationWidget)
{
    ui->setupUi(this);
}

igwTextureRepresentationWidget::~igwTextureRepresentationWidget()
{
    delete ui;
}

void igwTextureRepresentationWidget::SetRepresentation(igwRenderedRepresentation *rep)
{
    this->m_igwTextureRep = igwTextureRepresentation::SafeDownCast(rep);
    this->m_LICInterface = this->m_igwTextureRep->GetLICInterface();
    this->Init();
//    this->InitDataArrayCombox();
}

void igwTextureRepresentationWidget::Init()
{
    this->InitIntegratorTab();

    this->InitRenderTab();

    this->InitMaskTab();

    this->InitNoiseTab();
}

//--------------------Init Integrator tab---------------------
void igwTextureRepresentationWidget::InitDataArrayComboBox()
{

    ui->vector_comboBox->blockSignals(true);

    vtkDataSet* dataSet = m_igwTextureRep->GetDataSet();
    vtkPointData* pointData = dataSet->GetPointData();
    int numberOfArrays = pointData->GetNumberOfArrays();
    vtkDataArray* array;
    for (int i = 0; i < numberOfArrays; i++)
    {
        array = pointData->GetArray(i);
//        if (array->GetNumberOfComponents() == 1)
        ui->vector_comboBox->addItem(QString(pointData->GetArrayName(i)));
    }

    ui->vector_comboBox->blockSignals(false);
    const char* arrayName = m_igwTextureRep->GetPointColorArrayName();
    ui->vector_comboBox->setCurrentText(QString(arrayName));
}

void igwTextureRepresentationWidget::InitIntegratorTab()
{

    double stepSize = this->m_LICInterface->GetStepSize();
    double numberOfSteps = this->m_LICInterface->GetNumberOfSteps();

    ui->stepSize_Edit->setText(QString::number(stepSize));
    ui->stepNum_Edit->setText(QString::number(numberOfSteps));

    this->InitDataArrayComboBox();
}


void igwTextureRepresentationWidget::InitRenderTab()
{


    ui->highColor_Slider->setValue(this->m_LICInterface->GetHighColorContrastEnhancementFactor() * THOUSAND);
    ui->highLIC_Slider->setValue(this->m_LICInterface->GetHighLICContrastEnhancementFactor() * THOUSAND);
    ui->lowColor_Slider->setValue(this->m_LICInterface->GetLowColorContrastEnhancementFactor() * THOUSAND);
    ui->lowLIC_Slider->setValue(this->m_LICInterface->GetLowLICContrastEnhancementFactor() * THOUSAND);
    ui->antiAlias_Slider->setValue(this->m_LICInterface->GetAntiAlias());
    ui->mapOffset_Slider->setValue(this->m_LICInterface->GetMapModeBias() * HANDRED);
    ui->LICIntensity_Slider->setValue(this->m_LICInterface->GetLICIntensity() * HANDRED);
}

void igwTextureRepresentationWidget::InitMaskTab()
{

    ui->maskThreshold_lineEdit->setText(QString::number(this->m_LICInterface->GetMaskThreshold()));
    ui->maskIntensity_Slider->setValue(this->m_LICInterface->GetMaskIntensity() * HANDRED);

}

void igwTextureRepresentationWidget::InitNoiseTab()
{
    ui->noiseTextureSize_Slider->setValue(this->m_LICInterface->GetNoiseTextureSize());
    ui->noiseGrainSize_Slider->setValue(this->m_LICInterface->GetNoiseGrainSize());
    ui->minNoiseValue_Slider->setValue(m_LICInterface->GetMinNoiseValue() * HANDRED);
    ui->maxNoiseValue_Slider->setValue(this->m_LICInterface->GetMaxNoiseValue() * HANDRED);
    ui->impulseNoiseProbability_Slider->setValue(this->m_LICInterface->GetImpulseNoiseProbability() * HANDRED);
    ui->impulseNoiseBackgroundValue_Slider->setValue(this->m_LICInterface->GetImpulseNoiseBackgroundValue() *HANDRED);
    ui->numOfNoiseLevel_Slider->setValue(this->m_LICInterface->GetNoiseGeneratorSeed());
}

void igwTextureRepresentationWidget::EnableLICContrastUI(int val)
{
    ui->highLIC_lineEdit->setEnabled(val);
    ui->highLIC_Slider->setEnabled(val);
    ui->lowLIC_lineEdit->setEnabled(val);
    ui->lowLIC_Slider->setEnabled(val);
}

void igwTextureRepresentationWidget::EnableColorContrastUI(int val)
{
    ui->highColor_lineEdit->setEnabled(val);
    ui->highColor_Slider->setEnabled(val);
    ui->lowColor_lineEdit->setEnabled(val);
    ui->lowColor_Slider->setEnabled(val);
}

void igwTextureRepresentationWidget::EnableBlendUI(int val)
{
    ui->LICIntensity_Slider->setEnabled(val);
    ui->LICIntensity_lineEdit->setEnabled(val);
}

void igwTextureRepresentationWidget::EnableMapUI(int val)
{
    ui->mapOffset_lineEdit->setEnabled(val);
    ui->mapOffset_Slider->setEnabled(val);
}

//---------------------积分器Tab UI Slot------------------------
void igwTextureRepresentationWidget::on_normalVector_checkBox_stateChanged(int arg1)
{
    m_igwTextureRep->SetNormalizeVectors(arg1);
}


void igwTextureRepresentationWidget::on_enhancedLIC_checkBox_stateChanged(int arg1)
{
    m_igwTextureRep->SetEnhancedLIC(arg1);
}


void igwTextureRepresentationWidget::on_stepSize_Edit_textChanged(const QString &arg1)
{
    m_igwTextureRep->SetStepSize(arg1.toDouble());
}


void igwTextureRepresentationWidget::on_stepNum_Edit_textChanged(const QString &arg1)
{
    m_igwTextureRep->SetNumberOfSteps(arg1.toInt());
}

//---------------------渲染Tab UI Slot------------------------
void igwTextureRepresentationWidget::on_colorMode_comboBox_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        // 设置颜色模式
        this->m_igwTextureRep->SetColorMode(vtkSurfaceLICInterface::COLOR_MODE_BLEND);
        EnableBlendUI(1);
        EnableMapUI(0);
        break;
    case 1:
        // 设置颜色模式
        this->m_igwTextureRep->SetColorMode(vtkSurfaceLICInterface::COLOR_MODE_MAP);
        EnableBlendUI(0);
        EnableMapUI(1);
        break;
    default:
        break;
    }
}


void igwTextureRepresentationWidget::on_enhanceContrast_comboBox_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        // 关闭对比度增强
        this->m_igwTextureRep->SetEnhanceContrast(vtkSurfaceLICInterface::ENHANCE_CONTRAST_OFF);
        this->EnableColorContrastUI(0);
        this->EnableLICContrastUI(0);
        break;
    case 1:
        this->m_igwTextureRep->SetEnhanceContrast(vtkSurfaceLICInterface::ENHANCE_CONTRAST_LIC);
        this->EnableColorContrastUI(0);
        this->EnableLICContrastUI(1);
        break;
    case 2:
        this->m_igwTextureRep->SetEnhanceContrast(vtkSurfaceLICInterface::ENHANCE_CONTRAST_COLOR);
        this->EnableColorContrastUI(1);
        this->EnableLICContrastUI(0);
        break;
    default:
        this->m_igwTextureRep->SetEnhancedLIC(vtkSurfaceLICInterface::ENHANCE_CONTRAST_BOTH);
        this->EnableColorContrastUI(1);
        this->EnableLICContrastUI(1);
        break;
    }
}


void igwTextureRepresentationWidget::on_antiAlias_lineEdit_textChanged(const QString &arg1)
{
    int value = arg1.toInt();
    ui->antiAlias_Slider->setValue(value);
    //this->m_LICInterface->SetAntiAlias(value);
    m_igwTextureRep->SetAntiAlias(arg1.toDouble());
}


void igwTextureRepresentationWidget::on_antiAlias_Slider_valueChanged(int value)
{
    ui->antiAlias_lineEdit->setText(QString::number(value));
    //this->m_LICInterface->SetAntiAlias(value);
    m_igwTextureRep->SetAntiAlias(value);
}

void igwTextureRepresentationWidget::on_highLIC_Slider_valueChanged(int value)
{
    double result = double(value) / THOUSAND;
    ui->highLIC_lineEdit->setText(QString::number(result));
    m_igwTextureRep->SetHighLICContrastEnhancementFactor(result);
}


void igwTextureRepresentationWidget::on_highLIC_lineEdit_textChanged(const QString &arg1)
{
    double value = arg1.toDouble() * THOUSAND;
    ui->highLIC_Slider->setValue(value );
    m_igwTextureRep->SetHighLICContrastEnhancementFactor(arg1.toDouble());
}


void igwTextureRepresentationWidget::on_lowLIC_Slider_valueChanged(int value)
{
    double result = double(value) / THOUSAND;
    ui->lowLIC_lineEdit->setText(QString::number(result));
    m_igwTextureRep->SetLowLICContrastEnhancementFactor(result);
}


void igwTextureRepresentationWidget::on_lowLIC_lineEdit_textEdited(const QString &arg1)
{
    double value = arg1.toDouble() * THOUSAND;
    ui->lowLIC_Slider->setValue(value );
    m_igwTextureRep->SetLowLICContrastEnhancementFactor(arg1.toDouble());
}


void igwTextureRepresentationWidget::on_highColor_Slider_valueChanged(int value)
{
    double result = double(value) / THOUSAND;
    ui->highColor_lineEdit->setText(QString::number(result));
    m_igwTextureRep->SetHighColorContrastEnhancementFactor(result);
}


void igwTextureRepresentationWidget::on_highColor_lineEdit_textChanged(const QString &arg1)
{
    double value = arg1.toDouble() * THOUSAND;
    ui->highColor_Slider->setValue(value);
    m_igwTextureRep->SetHighColorContrastEnhancementFactor(arg1.toDouble());
}


void igwTextureRepresentationWidget::on_lowColor_Slider_valueChanged(int value)
{
    double result = double(value) / THOUSAND;
    ui->lowColor_lineEdit->setText(QString::number(result));
    m_igwTextureRep->SetLowColorContrastEnhancementFactor(result);
}


void igwTextureRepresentationWidget::on_lowColor_lineEdit_textChanged(const QString &arg1)
{
    double value = arg1.toDouble() * THOUSAND;
    ui->lowColor_Slider->setValue(value);
    m_igwTextureRep->SetLowColorContrastEnhancementFactor(arg1.toDouble());
}


void igwTextureRepresentationWidget::on_LICIntensity_Slider_valueChanged(int value)
{
    double result = double(value) / HANDRED;
    ui->LICIntensity_lineEdit->setText(QString::number(result));
    m_igwTextureRep->SetLICIntensity(result);
}


void igwTextureRepresentationWidget::on_LICIntensity_lineEdit_textChanged(const QString &arg1)
{
    double value = arg1.toDouble() * HANDRED;
    ui->LICIntensity_Slider->setValue(value);
    m_igwTextureRep->SetLICIntensity(arg1.toDouble());
}


void igwTextureRepresentationWidget::on_mapOffset_Slider_valueChanged(int value)
{
    double result = double(value) / HANDRED;
    ui->mapOffset_lineEdit->setText(QString::number(result));
    m_igwTextureRep->SetMapModeBias(result);
}


void igwTextureRepresentationWidget::on_mapOffset_lineEdit_textChanged(const QString &arg1)
{
    double value = arg1.toDouble() * HANDRED;
    ui->mapOffset_Slider->setValue(value);
    m_igwTextureRep->SetMapModeBias(arg1.toDouble());
}



//---------------------噪声Tab UI Slot------------------------
void igwTextureRepresentationWidget::on_noiseTextureSize_Slider_valueChanged(int value)
{

    ui->noiseTextureSize_lineEdit->setText(QString::number(value));
    m_igwTextureRep->SetNoiseTextureSize(value);
}


void igwTextureRepresentationWidget::on_noiseTextureSize_lineEdit_textChanged(const QString &arg1)
{
    int value = arg1.toInt();
    ui->noiseTextureSize_Slider->setValue(value);
    m_igwTextureRep->SetNoiseTextureSize(value);
}



void igwTextureRepresentationWidget::on_noiseGrainSize_Slider_valueChanged(int value)
{
    ui->noiseGrainSize_lineEdit->setText(QString::number(value));
    m_igwTextureRep->SetNoiseGrainSize(value);
}


void igwTextureRepresentationWidget::on_noiseGrainSize_lineEdit_textChanged(const QString &arg1)
{
    int value = arg1.toInt();
    ui->noiseGrainSize_Slider->setValue(value);
    m_igwTextureRep->SetNoiseGrainSize(value);
}



void igwTextureRepresentationWidget::on_minNoiseValue_Slider_valueChanged(int value)
{
    double result = double(value) / HANDRED;
    ui->minNoiseValue_lineEdit->setText(QString::number(result));
    m_igwTextureRep->SetMinNoiseValue(result);
}


void igwTextureRepresentationWidget::on_minNoiseValue_lineEdit_textChanged(const QString &arg1)
{
    double value = arg1.toDouble() * HANDRED;
    ui->minNoiseValue_Slider->setValue(value);
    m_igwTextureRep->SetMinNoiseValue(arg1.toDouble());
}


void igwTextureRepresentationWidget::on_maxNoiseValue_Slider_valueChanged(int value)
{
    double result = double(value) / HANDRED;
    ui->maxNoiseValue_lineEdit->setText(QString::number(result));
    m_igwTextureRep->SetMaxNoiseValue(result);
}


void igwTextureRepresentationWidget::on_maxNoiseValue_lineEdit_textChanged(const QString &arg1)
{
    double value = arg1.toDouble() * HANDRED;
    ui->maxNoiseValue_Slider->setValue(value);
    m_igwTextureRep->SetMaxNoiseValue(arg1.toDouble());
}


void igwTextureRepresentationWidget::on_numOfNoiseLevel_Slider_valueChanged(int value)
{
    ui->numOfNoiseLevel_lineEdit->setText(QString::number(value));
    m_igwTextureRep->SetNumberOfNoiseLevels(value);
}


void igwTextureRepresentationWidget::on_numOfNoiseLevel_lineEdit_textChanged(const QString &arg1)
{
    int value = arg1.toInt();
    ui->numOfNoiseLevel_Slider->setValue(value);
    m_igwTextureRep->SetNumberOfNoiseLevels(value);
}


void igwTextureRepresentationWidget::on_impulseNoiseProbability_Slider_valueChanged(int value)
{
    double result = double(value) / HANDRED;
    ui->impulseNoiseProbability_lineEdit->setText(QString::number(result));
    m_igwTextureRep->SetImpulseNoiseProbability(result);
}


void igwTextureRepresentationWidget::on_impulseNoiseProbability_lineEdit_textChanged(const QString &arg1)
{
    double value = arg1.toDouble() * HANDRED;
    ui->impulseNoiseProbability_Slider->setValue(value);
    m_igwTextureRep->SetImpulseNoiseProbability(arg1.toDouble());
}


void igwTextureRepresentationWidget::on_impulseNoiseBackgroundValue_Slider_valueChanged(int value)
{
    double result = double(value) / HANDRED;
    ui->impulseNoiseBackgroundValue_lineEdit->setText(QString::number(result));
    m_igwTextureRep->SetImpulseNoiseBackgroundValue(result);
}


void igwTextureRepresentationWidget::on_impulseNoiseBackgroundValue_lineEdit_textChanged(const QString &arg1)
{
    double value = arg1.toDouble() * HANDRED;
    ui->impulseNoiseBackgroundValue_Slider->setValue(value);
    m_igwTextureRep->SetImpulseNoiseBackgroundValue(arg1.toDouble());
}


void igwTextureRepresentationWidget::on_random_Slider_valueChanged(int value)
{
    ui->random_lineEdit->setText(QString::number(value));
    m_igwTextureRep->SetNoiseGeneratorSeed(value);
}


void igwTextureRepresentationWidget::on_random_lineEdit_textChanged(const QString &arg1)
{
    int value = arg1.toInt();
    ui->random_Slider->setValue(value);
    m_igwTextureRep->SetNoiseGeneratorSeed(value);
}


void igwTextureRepresentationWidget::on_noiseTexture_checkBox_stateChanged(int arg1)
{
    ui->noiseTexture_groupBox->setEnabled(arg1);
    m_igwTextureRep->SetGenerateNoiseTexture(arg1);
}

void igwTextureRepresentationWidget::on_noiseType_comboBox_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        m_igwTextureRep->SetNoiseType(vtkSurfaceLICInterface::NOISE_TYPE_UNIFORM);
        break;
    case 1:
        m_igwTextureRep->SetNoiseType(vtkSurfaceLICInterface::NOISE_TYPE_GAUSSIAN);
        break;
    case 2:
        m_igwTextureRep->SetNoiseType(vtkSurfaceLICInterface::NOISE_TYPE_PERLIN);
        break;
    default:
        break;
    }
}

//---------------------表面遮盖Tab UI Slot------------------------

void igwTextureRepresentationWidget::on_maskThreshold_lineEdit_textChanged(const QString &arg1)
{
    double value = arg1.toDouble();

    m_igwTextureRep->SetMaskThreshold(arg1.toDouble());
}


void igwTextureRepresentationWidget::on_maskIntensity_Slider_valueChanged(int value)
{
    double result = double(value) / HANDRED;
    ui->maskIntensity_lineEdit->setText(QString::number(result));
    m_igwTextureRep->SetMaskIntensity(result);
}


void igwTextureRepresentationWidget::on_maskIntensity_lineEdit_textChanged(const QString &arg1)
{
    double value = arg1.toDouble() * HANDRED;
    ui->maskIntensity_Slider->setValue(value);
    m_igwTextureRep->SetMaskIntensity(arg1.toDouble());
}


void igwTextureRepresentationWidget::on_maskOnSurface_checkBox_stateChanged(int arg1)
{
    m_igwTextureRep->SetMaskOnSurface(arg1);
    ui->maskIntensity_lineEdit->setEnabled(arg1);
    ui->maskIntensity_Slider->setEnabled(arg1);
    ui->maskThreshold_lineEdit->setEnabled(1);
}

void igwTextureRepresentationWidget::ApplySetting()
{
    Q_EMIT this->Applied();
}




void igwTextureRepresentationWidget::on_vector_comboBox_currentTextChanged(const QString &arg1)
{
    this->m_igwTextureRep->SetInputArrayToProcess(0, 0, 0, vtkDataObject::FIELD_ASSOCIATION_POINTS, arg1.toStdString().c_str());
}


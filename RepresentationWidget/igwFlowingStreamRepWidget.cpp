#include "igwFlowingStreamRepWidget.h"
#include "ui_igwFlowingStreamRepWidget.h"

#include "Representation/igwFlowingStreamLinesRepresentation.h"
#include "vtkPointData.h"
#include "vtkDataSet.h"
#include "vtkDataArray.h"


igwFlowingStreamRepWidget::igwFlowingStreamRepWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::igwFlowingStreamRepWidget)
{
    ui->setupUi(this);


}

igwFlowingStreamRepWidget::~igwFlowingStreamRepWidget()
{
    delete ui;
}

void igwFlowingStreamRepWidget::SetRepresentation(igwRenderedRepresentation *rep)
{
    this->m_igwFlowingStreamLinesRepresentation = igwFlowingStreamLinesRepresentation::SafeDownCast(rep);
    this->Init();
    this->InitDataArrayCombox();
}

void igwFlowingStreamRepWidget::on_particle_numEdit_returnPressed()
{
    int particle_num = ui->particle_numEdit->text().toInt();
    m_ParticleNum = particle_num;

    m_igwFlowingStreamLinesRepresentation->SetNumberOfParticles(m_ParticleNum);

    //ui->particle_numEdit->setText(QString::number(m_ParticleNum));
}

void igwFlowingStreamRepWidget::on_max_timeEdit_returnPressed()
{
    int max_time = ui->max_timeEdit->text().toInt();
    m_MaxTime = max_time;

    m_igwFlowingStreamLinesRepresentation->SetMaxTimeToLive(m_MaxTime);

}

void igwFlowingStreamRepWidget::on_stepEdit_returnPressed()
{
    m_igwFlowingStreamLinesRepresentation->SetStepLength(ui->stepEdit->text().toDouble());
}

void igwFlowingStreamRepWidget::on_alphaEdit_textChanged(const QString &alpha)
{   ui->alphaSlider->blockSignals(true);
    ui->alphaSlider->setValue(alpha.toDouble() * 100);
    ui->alphaSlider->blockSignals(false);
}


void igwFlowingStreamRepWidget::on_alphaSlider_sliderMoved(int position)
{
    ui->alphaEdit->blockSignals(true);
    double alpha = double(position) / 100;
    ui->alphaEdit->setText(QString::number(alpha));
    ui->alphaEdit->blockSignals(false);
}

void igwFlowingStreamRepWidget::on_alphaSlider_sliderReleased()
{
    double alpha = double(ui->alphaSlider->value()) / 100;

    m_igwFlowingStreamLinesRepresentation->SetAlpha(alpha);
}

void igwFlowingStreamRepWidget::on_alphaEdit_returnPressed()
{
     m_igwFlowingStreamLinesRepresentation->SetAlpha(ui->alphaEdit->text().toDouble());
}

void igwFlowingStreamRepWidget::on_alphaSlider_valueChanged(int value)
{
    ui->alphaEdit->blockSignals(true);
    double alpha = double(value) / 100;
    ui->alphaEdit->setText(QString::number(alpha));
    ui->alphaEdit->blockSignals(false);
}

void igwFlowingStreamRepWidget::ApplySetting()
{
    this->on_alphaEdit_returnPressed();
    this->on_max_timeEdit_returnPressed();
    this->on_particle_numEdit_returnPressed();
    this->on_stepEdit_returnPressed();
    Q_EMIT this->Applied();
}

void igwFlowingStreamRepWidget::InitDataArrayCombox()
{

    ui->DataArrayComboBox->blockSignals(true);
    vtkDataSet* dataSet = m_igwFlowingStreamLinesRepresentation->GetDataSet();
    vtkPointData* pointData = dataSet->GetPointData();
    int numberOfArrays = pointData->GetNumberOfArrays();
    for (int i = 0; i < numberOfArrays; i++)
    {
        ui->DataArrayComboBox->addItem(QString(pointData->GetArrayName(i)));
    }
    ui->DataArrayComboBox->blockSignals(false);
    const char* arrayName = m_igwFlowingStreamLinesRepresentation->GetPointColorArrayName();
    ui->DataArrayComboBox->setCurrentText(QString(arrayName));
}

void igwFlowingStreamRepWidget::Init()
{
    // Init vtkStreamLinesMapper
    m_Alpha = m_igwFlowingStreamLinesRepresentation->GetAlpha();
    m_Step = m_igwFlowingStreamLinesRepresentation->GetStepLength();
    m_MaxTime = m_igwFlowingStreamLinesRepresentation->GetMaxTimeToLive();
    m_ParticleNum = m_igwFlowingStreamLinesRepresentation->GetNumberOfParticles();

    // Init UI
    ui->alphaEdit->setText(QString::number(m_Alpha));
    ui->stepEdit->setText(QString::number(m_Step));
    ui->max_timeEdit->setText(QString::number(m_MaxTime));
    ui->particle_numEdit->setText(QString::number(m_ParticleNum));
}

void igwFlowingStreamRepWidget::on_DataArrayComboBox_currentIndexChanged(const QString &arrayName)
{
    m_igwFlowingStreamLinesRepresentation->SetInputArrayToProcess(0, 0, 0, vtkDataObject::FIELD_ASSOCIATION_POINTS, arrayName.toStdString().c_str());

}


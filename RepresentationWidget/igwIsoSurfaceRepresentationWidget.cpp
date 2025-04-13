#include "igwIsoSurfaceRepresentationWidget.h"
#include "ui_igwIsoSurfaceRepresentationWidget.h"

#include "Representation/igwIsoSurfaceRepresentation.h"
#include "vtkDataSet.h"
#include "vtkPointData.h"
#include "vtkDataArray.h"
#include "vtkDoubleArray.h"

igwIsoSurfaceRepresentationWidget::igwIsoSurfaceRepresentationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::igwIsoSurfaceRepresentationWidget)
{
    ui->setupUi(this);

}

igwIsoSurfaceRepresentationWidget::~igwIsoSurfaceRepresentationWidget()
{
    delete ui;
}

void igwIsoSurfaceRepresentationWidget::SetRepresentation(igwRenderedRepresentation *rep)
{
    this->m_igwIsoSurfaceRepresentation = igwIsoSurfaceRepresentation::SafeDownCast(rep);
    this->NumberOfContours = m_igwIsoSurfaceRepresentation->GetNumberOfContoursApi();

    // combox在ContoursTable之前初始化
    this->InitDataArrayComboBox();
    this->InitContoursTable();

}


void igwIsoSurfaceRepresentationWidget::on_deleteButton_clicked()
{
    int row = ui->ContourtableWidget->currentRow();
    ui->ContourtableWidget->removeRow(row);
}

void igwIsoSurfaceRepresentationWidget::on_addLineButton_clicked()
{
    int step = ui->spinBox->value();
    int preRowCount = ui->ContourtableWidget->rowCount();
    ui->ContourtableWidget->setRowCount( preRowCount + step);

    //获取数组范围
    QString arrayName = ui->DataArrayComboBox->currentText();

    double* range = m_igwIsoSurfaceRepresentation->GetArrayRange(vtkDataObject::FIELD_ASSOCIATION_POINTS,arrayName.toStdString().c_str());

    for(int i = 0; i < step; i++){
        QDoubleSpinBox* spinItem =  new QDoubleSpinBox;
        spinItem->setRange(range[0], range[1]);
        spinItem->setValue((range[0] + range[1]) / 2);
        spinItem->setWrapping(true);
        spinItem->setDecimals(6);
        ui->ContourtableWidget->setCellWidget(preRowCount + i, 0, spinItem);
    }
//    ui->ContourtableWidget->insertRow(11);
}

void igwIsoSurfaceRepresentationWidget::on_clearButton_clicked()
{
    ui->ContourtableWidget->clear();
    ui->ContourtableWidget->setRowCount(0);
}

void igwIsoSurfaceRepresentationWidget::on_DataArrayComboBox_currentTextChanged(const QString &arrayName)
{
    m_igwIsoSurfaceRepresentation->SetInputArrayToProcess(0, 0, 0, vtkDataObject::FIELD_ASSOCIATION_POINTS, arrayName.toStdString().c_str());


    double* range = m_igwIsoSurfaceRepresentation->GetArrayRange(vtkDataObject::FIELD_ASSOCIATION_POINTS, arrayName.toStdString().c_str());
    m_igwIsoSurfaceRepresentation->GenerateValues(NumberOfContours, range);

    InitContoursTable();
}

void igwIsoSurfaceRepresentationWidget::ApplySetting()
{

    this->UpdateContours();
    Q_EMIT Applied();
}


void igwIsoSurfaceRepresentationWidget::InitContoursTable()
{

    double numberOfContours = m_igwIsoSurfaceRepresentation->GetNumberOfContoursApi();

    double* values =  m_igwIsoSurfaceRepresentation->GetValues();
    ui->ContourtableWidget->setRowCount(numberOfContours);

    // 获取数组范围.
    QString arrayName = ui->DataArrayComboBox->currentText();

    double* range = m_igwIsoSurfaceRepresentation->GetArrayRange(vtkDataObject::FIELD_ASSOCIATION_POINTS, arrayName.toStdString().c_str());

    QString rangeText = QString("[") +QString::number(range[0], 'f') + QString(',') + QString::number(range[1], 'f') + QString(']');
    ui->RangeLabel->setText(rangeText);
    for(int i = 0; i < numberOfContours; i++){
        QDoubleSpinBox* spinItem =  new QDoubleSpinBox;
        spinItem->setRange(range[0], range[1]);
        spinItem->setValue(values[i]);
        spinItem->setWrapping(true);
        spinItem->setDecimals(6);
        ui->ContourtableWidget->setCellWidget(i, 0, spinItem);
    }
}

void igwIsoSurfaceRepresentationWidget::InitDataArrayComboBox()
{
    ui->DataArrayComboBox->blockSignals(true);

    vtkDataSet* dataSet = m_igwIsoSurfaceRepresentation->GetDataSet();
    vtkPointData* pointData = dataSet->GetPointData();
    int numberOfArrays = pointData->GetNumberOfArrays();
    vtkDataArray* array;
    for (int i = 0; i < numberOfArrays; i++)
    {
        array = pointData->GetArray(i);
        if (array->GetNumberOfComponents() == 1)
        ui->DataArrayComboBox->addItem(QString(pointData->GetArrayName(i)));
    }

    ui->DataArrayComboBox->blockSignals(false);
    const char* arrayName = m_igwIsoSurfaceRepresentation->GetPointColorArrayName();
    ui->DataArrayComboBox->setCurrentText(QString(arrayName));
}

void igwIsoSurfaceRepresentationWidget::UpdateContours()
{
    m_igwIsoSurfaceRepresentation->SetNumberOfContoursApi(ui->ContourtableWidget->rowCount());
    for(int i = 0; i < ui->ContourtableWidget->rowCount(); i++){
        m_igwIsoSurfaceRepresentation->SetValue(i, static_cast<QDoubleSpinBox*>(ui->ContourtableWidget->cellWidget(i, 0))->value());
    }
    m_igwIsoSurfaceRepresentation->Modified();
}

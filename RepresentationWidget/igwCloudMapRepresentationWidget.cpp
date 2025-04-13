#include "igwCloudMapRepresentationWidget.h"
#include "ui_igwCloudMapRepresentationWidget.h"

#include "ColorMap/igwColorMapEditorWidget.h"
#include "Representation/igwCloudMapRepresentation.h"
#include "igwPlaneParametersWidget.h"

#include "vtkEventQtSlotConnect.h"
#include "vtkImplicitPlaneWidget.h"
#include "vtkProperty.h"
#include "vtkDataSet.h"
#include "vtkPointData.h"
#include "vtkDataArray.h"
igwCloudMapRepresentationWidget::igwCloudMapRepresentationWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::igwCloudMapRepresentationWidget)
{
    ui->setupUi(this);


//    ui->PlaneWidget = new igwPlaneParametersWidget();

    this->ConnectSignalAndSlot();
}

igwCloudMapRepresentationWidget::~igwCloudMapRepresentationWidget()
{
    delete ui;
}

void igwCloudMapRepresentationWidget::SetigwCloudMapRepresentation(igwCloudMapRepresentation *rep)
{
    this->m_igwCloudMapRepresentation = rep;
    m_Connect = vtkEventQtSlotConnect::New();
    m_Connect->Connect(m_igwCloudMapRepresentation->GetImplicitPlaneWidget(),
                       vtkCommand::EndInteractionEvent, this, SLOT(PlaneWidgetEndInterActorSlot()));
    ui->PlaneWidget->SetPlane(rep->GetPlane());

    ui->PlaneWidget->SetVisibility(rep->GetPlaneVisibility());

    // 根据rep 初始化下拉框
    this->InitDataArrayComboBox();
}

void igwCloudMapRepresentationWidget::SetNormalToXAxis()
{
    this->m_igwCloudMapRepresentation->SetNormalToXAxis();

    Q_EMIT this->Applied();
}

void igwCloudMapRepresentationWidget::SetNormalToYAxis()
{
    this->m_igwCloudMapRepresentation->SetNormalToYAxis();
    Q_EMIT this->Applied();
}

void igwCloudMapRepresentationWidget::SetNormalToZAxis()
{
    this->m_igwCloudMapRepresentation->SetNormalToZAxis();
    Q_EMIT this->Applied();
}

void igwCloudMapRepresentationWidget::SetPlaneEnable(int type)
{
    double opacity = (type == 0) ? 0.0 : 1.0;
    switch (type) {
    case 0:
        this->m_igwCloudMapRepresentation->PlaneWidgetOff();
        break;
    default:
        this->m_igwCloudMapRepresentation->PlaneWidgetOn();
        break;
    }
    this->m_igwCloudMapRepresentation->SetPlaneOpacity(opacity);
    this->m_igwCloudMapRepresentation->SetPlaneVisibility(opacity);
    Q_EMIT this->Applied();
}

void igwCloudMapRepresentationWidget::SetPlaneNormal(double x, double y, double z)
{
    this->m_igwCloudMapRepresentation->SetPlaneNormal(x, y, z);
    Q_EMIT this->Applied();
}

void igwCloudMapRepresentationWidget::SetPlaneOrigin(double x, double y, double z)
{
    this->m_igwCloudMapRepresentation->SetPlaneOrigin(x, y, z);
    Q_EMIT this->Applied();
}

void igwCloudMapRepresentationWidget::PlaneWidgetEndInterActorSlot()
{

    double* origin = m_igwCloudMapRepresentation->GetPlaneOrigin();
    double* normal = m_igwCloudMapRepresentation->GetPlaneNormal();
    Q_EMIT this->UpdatePlaneParametersWidget(origin[0], origin[1], origin[2], normal[0], normal[1], normal[2]);

}

void igwCloudMapRepresentationWidget::ApplySetting()
{
    Q_EMIT Applied();
}

void igwCloudMapRepresentationWidget::ConnectSignalAndSlot()
{
    // Set The Normal

    QObject::connect(this->ui->PlaneWidget, SIGNAL(XNormalButton_clicked()), this, SLOT(SetNormalToXAxis()));
    QObject::connect(this->ui->PlaneWidget, SIGNAL(YNormalButton_clicked()), this, SLOT(SetNormalToYAxis()));
    QObject::connect(this->ui->PlaneWidget, SIGNAL(ZNormalButton_clicked()), this, SLOT(SetNormalToZAxis()));

    QObject::connect(this->ui->PlaneWidget, SIGNAL(showPlaneCheckBox_stateChanged(int)),
                     this, SLOT(SetPlaneEnable(int)));

    QObject::connect(this->ui->PlaneWidget, SIGNAL(OriginChanged(double,double,double)),
                     this, SLOT(SetPlaneOrigin(double,double,double)));
    QObject::connect(this->ui->PlaneWidget, SIGNAL(NormalChanged(double,double,double)),
                     this, SLOT(SetPlaneNormal(double,double,double)));

    QObject::connect(this, SIGNAL(UpdatePlaneParametersWidget(double,double,double,double,double,double)),
                     this->ui->PlaneWidget, SLOT(UpdatePlane(double,double,double,double,double,double)));

}

void igwCloudMapRepresentationWidget::InitDataArrayComboBox()
{
    ui->DataArrayComboBox->blockSignals(true);
    vtkDataSet* dataSet = m_igwCloudMapRepresentation->GetDataSet();
    vtkPointData* pointData = dataSet->GetPointData();
    int numberOfArrays = pointData->GetNumberOfArrays();
    for (int i = 0; i < numberOfArrays; i++)
    {

        ui->DataArrayComboBox->addItem(QString(pointData->GetArrayName(i)));
    }
    ui->DataArrayComboBox->blockSignals(false);
    const char* arrayName = m_igwCloudMapRepresentation->GetPointColorArrayName();
    ui->DataArrayComboBox->setCurrentText(QString(arrayName));

}

void igwCloudMapRepresentationWidget::on_DataArrayComboBox_currentIndexChanged(const QString &arrayName)
{
    m_igwCloudMapRepresentation->SetInputArrayToProcess(0, 0, 0, vtkDataObject::FIELD_ASSOCIATION_POINTS, arrayName.toStdString().c_str());
    Q_EMIT this->Applied();
}


#include "igwCloudMapRepresentationDialog.h"
#include "ui_igwCloudMapRepresentationDialog.h"
#include "ColorMap/igwColorMapEditorWidget.h"
#include "igwPlaneParametersWidget.h"
#include "vtkEventQtSlotConnect.h"
#include "vtkImplicitPlaneWidget.h"
#include "Representation/igwCloudMapRepresentation.h"
#include "vtkProperty.h"
igwCloudMapRepresentationDialog::igwCloudMapRepresentationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::igwCloudMapRepresentationDialog)
{
    ui->setupUi(this);
    ui->tabWidget->clear();

    m_igwPlaneParametersWidget = new igwPlaneParametersWidget;

    ui->tabWidget->addTab(m_igwPlaneParametersWidget, "Setting");


    this->ConnectSignalAndSlot();
}

igwCloudMapRepresentationDialog::~igwCloudMapRepresentationDialog()
{
    delete ui;
    delete m_igwColorMapEditorWidget;
    delete m_igwPlaneParametersWidget;
}

void igwCloudMapRepresentationDialog::SetigwCloudMapRepresentation(igwCloudMapRepresentation *rep)
{
    this->m_igwCloudMapRepresentation = rep;
    m_Connect = vtkEventQtSlotConnect::New();
    m_Connect->Connect(m_igwCloudMapRepresentation->GetImplicitPlaneWidget(),
                       vtkCommand::EndInteractionEvent, this, SLOT(PlaneWidgetEndInterActorSlot()));
    m_igwPlaneParametersWidget->SetPlane(rep->GetPlane());

    m_igwPlaneParametersWidget->SetVisibility(rep->GetPlaneVisibility());
}

void igwCloudMapRepresentationDialog::SetNormalToXAxis()
{
    this->m_igwCloudMapRepresentation->SetNormalToXAxis();

    Q_EMIT this->Applied();
}

void igwCloudMapRepresentationDialog::SetNormalToYAxis()
{
    this->m_igwCloudMapRepresentation->SetNormalToYAxis();
    Q_EMIT this->Applied();
}

void igwCloudMapRepresentationDialog::SetNormalToZAxis()
{
    this->m_igwCloudMapRepresentation->SetNormalToZAxis();
    Q_EMIT this->Applied();
}

void igwCloudMapRepresentationDialog::SetPlaneEnable(int type)
{
    double opacity = (type == 0) ? 0.0 : 1.0;
    this->m_igwCloudMapRepresentation->SetPlaneOpacity(opacity);
    this->m_igwCloudMapRepresentation->SetPlaneVisibility(opacity);
    Q_EMIT this->Applied();
}

void igwCloudMapRepresentationDialog::SetPlaneNormal(double x, double y, double z)
{
    this->m_igwCloudMapRepresentation->SetPlaneNormal(x, y, z);
    Q_EMIT this->Applied();
}

void igwCloudMapRepresentationDialog::SetPlaneOrigin(double x, double y, double z)
{
    this->m_igwCloudMapRepresentation->SetPlaneOrigin(x, y, z);
    Q_EMIT this->Applied();
}

void igwCloudMapRepresentationDialog::PlaneWidgetEndInterActorSlot()
{

    double* origin = m_igwCloudMapRepresentation->GetPlaneOrigin();
    double* normal = m_igwCloudMapRepresentation->GetPlaneNormal();
    Q_EMIT this->UpdatePlaneParametersWidget(origin[0], origin[1], origin[2], normal[0], normal[1], normal[2]);

}

void igwCloudMapRepresentationDialog::ConnectSignalAndSlot()
{
    // Set The Normal

    QObject::connect(this->m_igwPlaneParametersWidget, SIGNAL(XNormalButton_clicked()), this, SLOT(SetNormalToXAxis()));
    QObject::connect(this->m_igwPlaneParametersWidget, SIGNAL(YNormalButton_clicked()), this, SLOT(SetNormalToYAxis()));
    QObject::connect(this->m_igwPlaneParametersWidget, SIGNAL(ZNormalButton_clicked()), this, SLOT(SetNormalToZAxis()));

    QObject::connect(this->m_igwPlaneParametersWidget, SIGNAL(showPlaneCheckBox_stateChanged(int)),
                     this, SLOT(SetPlaneEnable(int)));

    QObject::connect(this->m_igwPlaneParametersWidget, SIGNAL(OriginChanged(double,double,double)),
                     this, SLOT(SetPlaneOrigin(double,double,double)));
    QObject::connect(this->m_igwPlaneParametersWidget, SIGNAL(NormalChanged(double,double,double)),
                     this, SLOT(SetPlaneNormal(double,double,double)));

    QObject::connect(this, SIGNAL(UpdatePlaneParametersWidget(double,double,double,double,double,double)),
                     this->m_igwPlaneParametersWidget, SLOT(UpdatePlane(double,double,double,double,double,double)));

}

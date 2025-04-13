#include "igwPlaneParametersWidget.h"
#include "ui_igwPlaneParametersWidget.h"
#include "vtkPlane.h"

#include <QRegExpValidator>
igwPlaneParametersWidget::igwPlaneParametersWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::igwPlaneParametersWidget)
{
    ui->setupUi(this);
    this->Plane = vtkPlane::New();
    this->InitUI();
    //QObject::connect(ui->showPlaneCheckBox, SIGNAL(stateChanged(int)), this, SIGNAL(showOutlineCheckBox_stateChanged(int)));
}

igwPlaneParametersWidget::~igwPlaneParametersWidget()
{
    delete ui;
    delete this->m_Validator;
}

void igwPlaneParametersWidget::SetPlane(vtkPlane *plane)
{
    this->Plane = plane;
    double* origin = this->Plane->GetOrigin();
    double* normal = this->Plane->GetNormal();
    this->SetOrigin(origin[0], origin[1], origin[2]);
    this->SetNormal(normal[0], normal[1], normal[2]);
}

void igwPlaneParametersWidget::SetVisibility(bool visibility)
{
    this->Visibility  = visibility;
    ui->showPlaneCheckBox->setChecked(visibility);
}

void igwPlaneParametersWidget::on_XNormalButton_clicked()
{

    this->SetNormal(1.0, 0.0, 0.0);

    Q_EMIT this->XNormalButton_clicked();
}


void igwPlaneParametersWidget::on_YNormalButton_clicked()
{
//    this->Plane->SetNormal(0, 1, 0);
    this->SetNormal(0.0, 1.0, 0.0);

    Q_EMIT YNormalButton_clicked();
}


void igwPlaneParametersWidget::on_ZNormalButton_clicked()
{
//    this->Plane->SetNormal(0, 0, 1);
    this->SetNormal(0.0, 0.0, 1.0);

    Q_EMIT ZNormalButton_clicked();
}


void igwPlaneParametersWidget::on_showPlaneCheckBox_stateChanged(int arg1)
{
    Q_EMIT this->showPlaneCheckBox_stateChanged(arg1);
}

void igwPlaneParametersWidget::InitUI()
{
    QString exp = "[0-9\\.-]+$";
    QRegExp rege(exp);
    m_Validator = new QRegExpValidator(rege);
    ui->OriginXEdit->setValidator(m_Validator);
    ui->OriginYEdit->setValidator(m_Validator);
    ui->OriginZEdit->setValidator(m_Validator);
    ui->NormalXEdit->setValidator(m_Validator);
    ui->NormalYEdit->setValidator(m_Validator);
    ui->NormalZEdit->setValidator(m_Validator);

    ui->OriginXEdit->setText(QString::number(m_PlaneOrigin[0]));
    ui->OriginYEdit->setText(QString::number(m_PlaneOrigin[1]));
    ui->OriginZEdit->setText(QString::number(m_PlaneOrigin[2]));
    ui->NormalXEdit->setText(QString::number(m_PlaneNormal[0]));
    ui->NormalYEdit->setText(QString::number(m_PlaneNormal[1]));
    ui->NormalZEdit->setText(QString::number(m_PlaneNormal[2]));
}

void igwPlaneParametersWidget::SetNormal(double x, double y, double z)
{
    m_PlaneNormal[0] = x;
    m_PlaneNormal[1] = y;
    m_PlaneNormal[2] = z;

    ui->NormalXEdit->setText(QString::number(m_PlaneNormal[0]));
    ui->NormalYEdit->setText(QString::number(m_PlaneNormal[1]));
    ui->NormalZEdit->setText(QString::number(m_PlaneNormal[2]));
    if(this->Plane)
    this->Plane->SetNormal(x, y, z);
}

void igwPlaneParametersWidget::SetOrigin(double x, double y, double z)
{
    m_PlaneOrigin[0] = x;
    m_PlaneOrigin[1] = y;
    m_PlaneOrigin[2] = z;

    ui->OriginXEdit->setText(QString::number(m_PlaneOrigin[0]));
    ui->OriginYEdit->setText(QString::number(m_PlaneOrigin[1]));
    ui->OriginZEdit->setText(QString::number(m_PlaneOrigin[2]));
    if(this->Plane)
    this->Plane->SetOrigin(x, y, z);
}


void igwPlaneParametersWidget::on_NormalXEdit_editingFinished()
{
    m_PlaneNormal[0] = ui->NormalXEdit->text().toDouble();
    this->SetNormal(m_PlaneNormal[0], m_PlaneNormal[1], m_PlaneNormal[2]);
    Q_EMIT this->NormalChanged(m_PlaneNormal[0], m_PlaneNormal[1], m_PlaneNormal[2]);
}

void igwPlaneParametersWidget::on_NormalYEdit_editingFinished()
{
    m_PlaneNormal[1] = ui->NormalYEdit->text().toDouble();
    this->SetNormal(m_PlaneNormal[0], m_PlaneNormal[1], m_PlaneNormal[2]);
    Q_EMIT this->NormalChanged(m_PlaneNormal[0], m_PlaneNormal[1], m_PlaneNormal[2]);
}

void igwPlaneParametersWidget::on_NormalZEdit_editingFinished()
{
    m_PlaneNormal[2] = ui->NormalZEdit->text().toDouble();
    this->SetNormal(m_PlaneNormal[0], m_PlaneNormal[1], m_PlaneNormal[2]);
    Q_EMIT this->NormalChanged(m_PlaneNormal[0], m_PlaneNormal[1], m_PlaneNormal[2]);
}


void igwPlaneParametersWidget::on_OriginXEdit_editingFinished()
{
    m_PlaneOrigin[0] = ui->OriginXEdit->text().toDouble();
    this->SetOrigin(m_PlaneOrigin[0], m_PlaneOrigin[1], m_PlaneOrigin[2]);
    Q_EMIT this->OriginChanged(m_PlaneOrigin[0], m_PlaneOrigin[1], m_PlaneOrigin[2]);
}


void igwPlaneParametersWidget::on_OriginYEdit_editingFinished()
{
    m_PlaneOrigin[1] = ui->OriginYEdit->text().toDouble();
    this->SetOrigin(m_PlaneOrigin[0], m_PlaneOrigin[1], m_PlaneOrigin[2]);
    Q_EMIT this->OriginChanged(m_PlaneOrigin[0], m_PlaneOrigin[1], m_PlaneOrigin[2]);
}


void igwPlaneParametersWidget::on_OriginZEdit_editingFinished()
{
    m_PlaneOrigin[2] = ui->OriginZEdit->text().toDouble();
    this->SetOrigin(m_PlaneOrigin[0], m_PlaneOrigin[1], m_PlaneOrigin[2]);
    Q_EMIT this->OriginChanged(m_PlaneOrigin[0], m_PlaneOrigin[1], m_PlaneOrigin[2]);
}

void igwPlaneParametersWidget::UpdatePlane(double ox, double oy, double oz, double nx, double ny, double nz)
{
    this->SetNormal(nx, ny, nz);
    this->SetOrigin(ox, oy, oz);
}


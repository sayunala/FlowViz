#include "igwLineParametersWidget.h"
#include "ui_igwLineParametersWidget.h"
#include "vtkLineWidget.h"
#include <QRegExpValidator>
igwLineParametersWidget::igwLineParametersWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::igwLineParametersWidget)
{
    ui->setupUi(this);
    this->InitUI();
}

igwLineParametersWidget::~igwLineParametersWidget()
{
    delete ui;
}

void igwLineParametersWidget::SetLineWidget(vtkLineWidget *lineWidget)
{
    this->LineWidget = lineWidget;
    this->SetPoint1(this->LineWidget->GetPoint1());
    this->SetPoint2(this->LineWidget->GetPoint2());
}

void igwLineParametersWidget::SetVisibility(bool visibility)
{
    this->Visibility = visibility;
    ui->showLineCheckBox->setChecked(visibility);
}

void igwLineParametersWidget::on_XAxisButton_clicked()
{
    this->LineWidget->SetAlignToXAxis();
    this->LineWidget->PlaceWidget();
    this->SetPoint1(this->LineWidget->GetPoint1());
    this->SetPoint2(this->LineWidget->GetPoint2());
    Q_EMIT this->LineWidgetChanged();
}


void igwLineParametersWidget::on_YAxisButton_clicked()
{
    this->LineWidget->SetAlignToYAxis();
    this->LineWidget->PlaceWidget();
    this->SetPoint1(this->LineWidget->GetPoint1());
    this->SetPoint2(this->LineWidget->GetPoint2());
    Q_EMIT this->LineWidgetChanged();
}


void igwLineParametersWidget::on_ZAxisButton_clicked()
{
    this->LineWidget->SetAlignToZAxis();
    this->LineWidget->PlaceWidget();
    this->SetPoint1(this->LineWidget->GetPoint1());
    this->SetPoint2(this->LineWidget->GetPoint2());
    Q_EMIT this->LineWidgetChanged();
}


void igwLineParametersWidget::on_Point1XEdit_editingFinished()
{
    Point1[0] = ui->Point1XEdit->text().toDouble();
    this->SetPoint1(Point1[0], Point1[1], Point1[2]);
    Q_EMIT this->LineWidgetChanged();
}


void igwLineParametersWidget::on_Point1YEdit_editingFinished()
{
    Point1[1] = ui->Point1YEdit->text().toDouble();
    this->SetPoint1(Point1[0], Point1[1], Point1[2]);
    Q_EMIT this->LineWidgetChanged();
}


void igwLineParametersWidget::on_Point1ZEdit_editingFinished()
{
    Point1[2] = ui->Point1ZEdit->text().toDouble();
    this->SetPoint1(Point1[0], Point1[1], Point1[2]);
    Q_EMIT this->LineWidgetChanged();
}


void igwLineParametersWidget::on_Point2XEdit_editingFinished()
{
    Point2[0] = ui->Point2XEdit->text().toDouble();
    this->SetPoint2(Point2[0], Point2[1], Point2[2]);
    Q_EMIT this->LineWidgetChanged();
}


void igwLineParametersWidget::on_Point2YEdit_editingFinished()
{
    Point2[1] = ui->Point2YEdit->text().toDouble();
    this->SetPoint2(Point2[0], Point2[1], Point2[2]);
    Q_EMIT this->LineWidgetChanged();
}


void igwLineParametersWidget::on_Point2ZEdit_editingFinished()
{
    Point2[2] = ui->Point2ZEdit->text().toDouble();
    this->SetPoint2(Point2[0], Point2[1], Point2[2]);
    Q_EMIT this->LineWidgetChanged();
}

void igwLineParametersWidget::updateLineWidgetSlot()
{
    this->SetPoint1(LineWidget->GetPoint1());
    this->SetPoint2(LineWidget->GetPoint2());
}

void igwLineParametersWidget::InitUI()
{
    QString exp = "[0-9\\.-]+$";
    QRegExp rege(exp);
    m_Validator = new QRegExpValidator(rege);
    ui->Point1XEdit->setValidator(m_Validator);
    ui->Point1YEdit->setValidator(m_Validator);
    ui->Point1ZEdit->setValidator(m_Validator);
    ui->Point2XEdit->setValidator(m_Validator);
    ui->Point2YEdit->setValidator(m_Validator);
    ui->Point2ZEdit->setValidator(m_Validator);

    ui->Point1XEdit->setText(QString::number(Point1[0]));
    ui->Point1YEdit->setText(QString::number(Point1[1]));
    ui->Point1ZEdit->setText(QString::number(Point1[2]));
    ui->Point2XEdit->setText(QString::number(Point2[0]));
    ui->Point2YEdit->setText(QString::number(Point2[1]));
    ui->Point2ZEdit->setText(QString::number(Point2[2]));
}

void igwLineParametersWidget::SetPoint1(double point[])
{
    Point1[0] = point[0];
    Point1[1] = point[1];
    Point1[2] = point[2];

    ui->Point1XEdit->setText(QString::number(Point1[0]));
    ui->Point1YEdit->setText(QString::number(Point1[1]));
    ui->Point1ZEdit->setText(QString::number(Point1[2]));
    this->LineWidget->SetPoint1(Point1);
}

void igwLineParametersWidget::SetPoint1(double x, double y, double z)
{
    Point1[0] = x;
    Point1[1] = y;
    Point1[2] = z;

    ui->Point1XEdit->setText(QString::number(Point1[0]));
    ui->Point1YEdit->setText(QString::number(Point1[1]));
    ui->Point1ZEdit->setText(QString::number(Point1[2]));
    this->LineWidget->SetPoint1(Point1);
}

void igwLineParametersWidget::SetPoint2(double point[])
{
    Point2[0] = point[0];
    Point2[1] = point[1];
    Point2[2] = point[2];

    ui->Point2XEdit->setText(QString::number(Point2[0]));
    ui->Point2YEdit->setText(QString::number(Point2[1]));
    ui->Point2ZEdit->setText(QString::number(Point2[2]));
    this->LineWidget->SetPoint2(Point2);
}

void igwLineParametersWidget::SetPoint2(double x, double y, double z)
{
    Point2[0] = x;
    Point2[1] = y;
    Point2[2] = z;

    ui->Point2XEdit->setText(QString::number(Point2[0]));
    ui->Point2YEdit->setText(QString::number(Point2[1]));
    ui->Point2ZEdit->setText(QString::number(Point2[2]));
    this->LineWidget->SetPoint2(Point2);
}


void igwLineParametersWidget::on_showLineCheckBox_stateChanged(int arg1)
{
    if (arg1 == 0)
    {
        this->LineWidget->Off();
        this->Visibility = false;
    }
    else
    {
        this->LineWidget->On();
        this->Visibility = true;
    }

}


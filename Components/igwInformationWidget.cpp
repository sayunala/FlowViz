#include "igwInformationWidget.h"
#include "ui_igwInformationWidget.h"

igwInformationWidget::igwInformationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::igwInformationWidget)
{
    ui->setupUi(this);
}

igwInformationWidget::~igwInformationWidget()
{
    delete ui;
}

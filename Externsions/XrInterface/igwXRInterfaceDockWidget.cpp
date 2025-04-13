#include "igwXRInterfaceDockWidget.h"
#include "ui_igwXRInterfaceDockWidget.h"

#include "vtkNew.h"

#include "igwXRInterfaceHelper.h"
struct igwXRInterfaceDockWidget::igwInternals
{

  vtkNew<igwXRInterfaceHelper> Helper;

  bool XREnabled = false;
  bool Attached = false;
};
igwXRInterfaceDockWidget::igwXRInterfaceDockWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::igwXRInterfaceDockWidget)
    ,Internals(new igwXRInterfaceDockWidget::igwInternals)
{
    std::cout << "Init XR InterfaceDockWidget " << std::endl;
    this->setWindowTitle(QString::fromLatin1("HoloLens 2"));
    ui->setupUi(this);
}

igwXRInterfaceDockWidget::~igwXRInterfaceDockWidget()
{
    delete ui;
}

void igwXRInterfaceDockWidget::on_SendToXRBtn_clicked()
{
    this->Internals->Helper->SendToXR();
}


void igwXRInterfaceDockWidget::on_ShowViewBtn_clicked()
{
    this->Internals->Helper->ShowXRView();
}

void igwXRInterfaceDockWidget::Init()
{



}


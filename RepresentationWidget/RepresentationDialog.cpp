#include "RepresentationDialog.h"
#include "ui_RepresentationDialog.h"
#include "ColorMap/igwColorMapEditorWidget.h"

RepresentationDialog::RepresentationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RepresentationDialog)
{
    ui->setupUi(this);
    ui->tabWidget->clear();
    this->setAttribute(Qt::WA_DeleteOnClose, true);
    QObject::connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(ApplySetting()));
}

RepresentationDialog::~RepresentationDialog()
{
    delete ui;

}

void RepresentationDialog::AddWidget(QWidget *widget, const QString &name)
{
    ui->tabWidget->addTab(widget, name);

}

void RepresentationDialog::ApplySetting()
{
    std::cout << "OK!" << std::endl;
    Q_EMIT this->SettingApplied();
}

#include "igwMeshRepresentationWidget.h"
#include "ui_igwMeshRepresentationWidget.h"

#include "Representation/igwMeshRepresentation.h".h"
#include "vtkDataSet.h"
#include "vtkPointData.h"
#include "vtkDataArray.h"
#include "vtkDoubleArray.h"
#include "vtkEventQtSlotConnect.h"
#include "igwCommand.h"

#include "igwMeshTableModel.h"
#include <QDoubleSpinBox>
#include <QLineEdit>
igwMeshRepresentationWidget::igwMeshRepresentationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::igwMeshRepresentationWidget)
{
    ui->setupUi(this);
    Model = new igwMeshTableModel(ui->meshTableView);


    ui->meshTableView->setSelectionBehavior(QAbstractItemView::SelectItems);
//    ui->meshTableView->horizontalHeader()->setSectionResizeMode(
//       QHeaderView::Stretch);
//    ui->meshTableView->verticalHeader()->setSectionResizeMode(
//       QHeaderView::Stretch);

    ui->meshTableWidget->horizontalHeader()->setSectionResizeMode(
       QHeaderView::Stretch);
    ui->meshTableWidget->verticalHeader()->setSectionResizeMode(
       QHeaderView::Stretch);


}

igwMeshRepresentationWidget::~igwMeshRepresentationWidget()
{
    delete ui;
}

void igwMeshRepresentationWidget::SetRepresentation(igwRenderedRepresentation *rep)
{
    this->m_igwMeshRepresentation= igwMeshRepresentation::SafeDownCast(rep);

    ui->meshColSpinBox->setValue(this->m_igwMeshRepresentation->GetCol());
    ui->meshRowSpinBox->setValue(this->m_igwMeshRepresentation->GetRow());
    InitMeshTable();
    this->InitMeshTableModel();
    ui->meshTableView->setModel(this->Model);
}

void igwMeshRepresentationWidget::ApplySetting()
{

    Q_EMIT Applied();
}

void igwMeshRepresentationWidget::InitMeshTable()
{
    int row = this->m_igwMeshRepresentation->GetRow();//获取到行数
    int col = this->m_igwMeshRepresentation->GetCol();//获取到列数
    ui->meshTableWidget->setRowCount(row);
    ui->meshTableWidget->setColumnCount(col);
    vtkDataArray* array = this->m_igwMeshRepresentation->GetCellArray();

    // 构造表格，默认值全为0;
    for(int i = 0; i < row; ++i){
        for(int j = 0; j < col; ++j)
        {
            QDoubleSpinBox* spinItem =  new QDoubleSpinBox(ui->meshTableWidget);
            double val = array->GetTuple1(i*col + j);

            spinItem->setDecimals(3);
            spinItem->setRange(0, DBL_MAX);
            spinItem->setSuffix(ui->SuffixComboBox->currentText());
            spinItem->setWrapping(true);
            spinItem->setValue(val);
            ui->meshTableWidget->setCellWidget(i, j, spinItem);
//            QObject::connect(spinItem, &QDoubleSpinBox::valueChanged,
//                             this, &igwMeshRepresentationWidget::ApplySetting);
            QObject::connect(spinItem, SIGNAL(valueChanged(double)), this, SLOT(UpdateMeshData(double)));
        }

    }
//    ui->meshTableWidget->resizeColumnsToContents();

}

void igwMeshRepresentationWidget::InitMeshTableModel()
{
    int row = this->m_igwMeshRepresentation->GetRow();
    int col = this->m_igwMeshRepresentation->GetCol();
    vtkDataArray* array = this->m_igwMeshRepresentation->GetCellArray();
    this->Model->InitData(array, row, col);

}

void igwMeshRepresentationWidget::on_meshRowSpinBox_valueChanged(int m)
{
    this->m_igwMeshRepresentation->SetYResolution(m);
    this->InitMeshTable();

    ui->meshTableWidget->update();

    vtkDataArray* array = m_igwMeshRepresentation->GetCellArray();
    int row = m;
    int col = m_igwMeshRepresentation->GetCol();
    this->Model->ResetDataModel(array, row, col);
    Q_EMIT Applied();
}


void igwMeshRepresentationWidget::on_meshColSpinBox_valueChanged(int n)
{
    this->m_igwMeshRepresentation->SetXResolution(n);
    this->InitMeshTable();

    vtkDataArray* array = m_igwMeshRepresentation->GetCellArray();
    int row = m_igwMeshRepresentation->GetRow();
    int col = n;
    this->Model->ResetDataModel(array, row, col);

    ui->meshTableWidget->update();
    Q_EMIT Applied();
}

void igwMeshRepresentationWidget::UpdateMeshData(double newdata)
{
    QDoubleSpinBox* spinBox = dynamic_cast<QDoubleSpinBox *>(sender());
    if(spinBox == nullptr) return ;
    // 获取当前位置的网格
    QModelIndex index = ui->meshTableWidget->indexAt(dynamic_cast<QWidget*>(spinBox->parent())->pos());
    int row = index.row();
    int column = index.column();

    int col_count = ui->meshColSpinBox->value();

    vtkDataArray* array = this->m_igwMeshRepresentation->GetCellArray();
    array->SetTuple1(row * col_count + column, newdata);
    m_igwMeshRepresentation->GetDataSet()->Modified();
//    m_igwMeshRepresentation->Update();
}

void igwMeshRepresentationWidget::UpdateMeshTableWidget(vtkObject*, unsigned long, void*, void*)
{
    int row = m_igwMeshRepresentation->GetRow();
    int col = m_igwMeshRepresentation->GetCol();


    vtkDataArray* array = this->m_igwMeshRepresentation->GetCellArray();

    for(int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            QDoubleSpinBox* spinbox = static_cast<QDoubleSpinBox*>(ui->meshTableWidget->cellWidget(i, j));
            spinbox->blockSignals(true);
            spinbox->setValue(array->GetTuple1(i * col + j));
            spinbox->blockSignals(false);
        }
    }
    this->UpdateMeshTableModel();
    this->Model->ResetDataModel(array, row, col);
}

void igwMeshRepresentationWidget::UpdateMeshTableModel()
{

//    this->Model->reset();
}

void igwMeshRepresentationWidget::on_SuffixComboBox_currentIndexChanged(const QString &suffix)
{
    int row = m_igwMeshRepresentation->GetRow();
    int col = m_igwMeshRepresentation->GetCol();

    for(int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            QDoubleSpinBox* spinbox = static_cast<QDoubleSpinBox*>(ui->meshTableWidget->cellWidget(i, j));
            spinbox->blockSignals(true);
            spinbox->setSuffix(suffix);
            spinbox->blockSignals(false);
        }
    }
}


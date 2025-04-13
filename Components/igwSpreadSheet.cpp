#include "igwSpreadSheet.h"
#include "ui_igwSpreadSheet.h"

#include "vtkQtTableView.h"
#include "vtkDataSet.h"
#include "vtkTable.h"
#include "vtkAttributeDataToTableFilter.h"
#include "vtkAnnotationLink.h"
#include "vtkQtTableRepresentation.h"
#include "vtkDataRepresentation.h"
#include "vtkQtTableModelAdapter.h"
#include "vtkViewUpdater.h"

#include "vtkQtView.h"
#include "vtkView.h"

#include "../Widgets/igwSaveSpreadSheetReaction.h"
#include "igwActiveObjects.h"
#include "igwSpreadSheetModel.h"
igwSpreadSheet::igwSpreadSheet(QWidget *parent):
    QWidget(parent),
    ui(new Ui::igwSpreadSheet)
{
    ui->setupUi(this);


    igwActiveObjects * activeObjects = &igwActiveObjects::GetInstance();
    QObject::connect(activeObjects, SIGNAL(dataChanged(vtkDataObject*)), this, SLOT(dataSetUpdate(vtkDataObject*)));

    this->InitTableModel();

    ui->ExportSpreadsheet->setDefaultAction(ui->actionExportSpreadSheet);
    new igwSaveSpreadSheetReaction(ui->ExportSpreadsheet->defaultAction());
    //this->TableAdapter->SetVTKDataObject(igwActiveObjects::GetInstance().GetActiveData());

    connect(ui->spinBoxPrecision, SIGNAL(valueChanged(int)), this, SLOT(displayPrecisionChanged(int)));
}

igwSpreadSheet::~igwSpreadSheet()
{
    delete ui;
//    delete TableAdapter;

}
#define VTK_CREATE(type, name) vtkSmartPointer<type> name = vtkSmartPointer<type>::New()
void igwSpreadSheet::SetDataSet(vtkDataSet *data)
{
    vtkNew<vtkAttributeDataToTableFilter>  toTable;

    toTable->SetInputData(data);
    toTable->SetFieldAssociation(vtkDataObject::FIELD_ASSOCIATION_POINTS);
    toTable->Update();
    vtkTable* table = toTable->GetOutput();

    this->TableAdapter->SetVTKDataObject(table);
    this->TableAdapter->SetSplitMultiComponentColumns(true);

}

void igwSpreadSheet::dataSetUpdate(vtkDataObject *data)
{

    this->DataToTable->SetInputData(data);

    this->DataToTable->Update();



    this->TableAdapter->SetVTKDataObject(this->DataToTable->GetOutput());
    this->TableAdapter->SetSplitMultiComponentColumns(true);
    this->TableAdapter->reset();
}

void igwSpreadSheet::displayPrecisionChanged(int precision)
{
    this->TableAdapter->SetDecimalPrecision(precision);
}

void igwSpreadSheet::InitTableModel()
{


    this->TableAdapter = new igwSpreadSheetModel(this);
    DataToTable = vtkSmartPointer<vtkAttributeDataToTableFilter>::New();

    vtkDataObject* dataSet = igwActiveObjects::GetInstance().GetActiveData();
    if(dataSet == nullptr)
    {
        return ;
    }
    this->DataToTable->SetInputData(dataSet);
    this->DataToTable->SetFieldAssociation(vtkDataObject::FIELD_ASSOCIATION_POINTS);
    this->DataToTable->AddMetaDataOn();
    this->DataToTable->GenerateOriginalIdsOn();
    this->DataToTable->Update();

    this->TableAdapter->SetVTKDataObject(this->DataToTable->GetOutput());
    this->TableAdapter->SetSplitMultiComponentColumns(true);

    ui->tableView->setModel(this->TableAdapter);
//    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}


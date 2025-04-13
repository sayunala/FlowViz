#ifndef IGWSPREADSHEET_H
#define IGWSPREADSHEET_H

#include "vtkSmartPointer.h"


#include <QWidget>
#include <vtkQtTreeView.h>

class vtkQtTableView;
class vtkDataSet;
class igwSpreadSheetModel;
class vtkTable;
class vtkAttributeDataToTableFilter;
class vtkQtTableModelAdapter;
namespace Ui {
class igwSpreadSheet;
}

class igwSpreadSheet : public QWidget
{
    Q_OBJECT

public:
    explicit igwSpreadSheet(QWidget *parent = nullptr);
    ~igwSpreadSheet();

    void SetDataSet(vtkDataSet* data);

protected slots:
    void dataSetUpdate(vtkDataObject* data);

    void displayPrecisionChanged(int precision);
protected:

    void InitTableModel();
    igwSpreadSheetModel* TableAdapter;

    vtkSmartPointer<vtkAttributeDataToTableFilter> DataToTable;

private:
    Ui::igwSpreadSheet *ui;

};

#endif // IGWSPREADSHEET_H

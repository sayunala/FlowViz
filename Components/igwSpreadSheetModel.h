#ifndef IGWSPREADSHEETMODEL_H
#define IGWSPREADSHEETMODEL_H

#include "vtkQtTableModelAdapter.h"
#include "vtkQtTreeView.h"
class vtkTable;
class igwSpreadSheetModel : public vtkQtTableModelAdapter
{
    Q_OBJECT
public:
    igwSpreadSheetModel(QObject* parent = nullptr);

    void SetDecimalPrecision(int precision);

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    ~igwSpreadSheetModel() = default;

private:
    int DecimalPrecision;

    igwSpreadSheetModel(const igwSpreadSheetModel&) = delete;
    void operator=(const igwSpreadSheetModel&) = delete;
};

#endif // IGWSPREADSHEETMODEL_H

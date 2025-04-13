#include "igwSpreadSheetModel.h"

igwSpreadSheetModel::igwSpreadSheetModel(QObject* parent)
    :vtkQtTableModelAdapter(parent)
{
    this->DecimalPrecision = 6;
}

void igwSpreadSheetModel::SetDecimalPrecision(int precision)
{
    this->DecimalPrecision = precision;
    this->reset();
}



QVariant igwSpreadSheetModel::data(const QModelIndex &index, int role) const
{
    QVariant result = vtkQtTableModelAdapter::data(index, role);
    if (role == Qt::DisplayRole)
    {
        return QString::number(result.toDouble(), 'g', this->DecimalPrecision);
    }
    return result;

}

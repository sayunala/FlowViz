#include "igwMeshTableModel.h"

#include "vtkNew.h"
#include "ColorMap/igwColorMapManager.h"
#include "vtkUnsignedCharArray.h"


#include <QList>
#include <QPixmap>
#include <QImage>


igwMeshTableModel::igwMeshTableModel(QObject *parent, int row, int col)
    : QAbstractTableModel(parent), m_Row(row), m_Column(col)
{
    this->ColorMaps.reserve(m_Row*m_Column);
}

igwMeshTableModel::~igwMeshTableModel()
{

}

//QVariant igwMeshTableModel::headerData(int section, Qt::Orientation orientation, int role) const
//{
//    // FIXME: Implement me!
////    Q_UNUSED(section);
////    if (orientation == Qt::Vertical)
////    {
////      return QVariant();
////    }
////    switch (role)
////    {
////      case Qt::DisplayRole:
////        return "Presets";
////    }
//    return section;
//}

int igwMeshTableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_Row;
    // FIXME: Implement me!
}

int igwMeshTableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_Column;
    // FIXME: Implement me!
}

QVariant igwMeshTableModel::data(const QModelIndex &index, int role) const
{

    if (!index.isValid())
        return QVariant();
    int currentRow = index.row();
    int currentCol = index.column();
    switch (role) {
    case Qt::DisplayRole:
    case Qt::ToolTipRole:
    case Qt::StatusTipRole:
    case Qt::EditRole:
        return QVariant();

    case Qt::BackgroundColorRole:
        return ColorMap(currentRow, currentCol);
    default:
        break;
    }
    // FIXME: Implement me!
    return QVariant();
}

void igwMeshTableModel::ResetDataModel(vtkDataArray *array, int row, int col)
{
    this->beginResetModel();
    this->value = array;
    this->ColorMaps.clear();
    this->ColorMaps.reserve(array->GetNumberOfTuples());
    this->m_Row = row;
    this->m_Column = col;
    this->render();
    this->endResetModel();
}

void igwMeshTableModel::InitData(vtkDataArray *array, int row, int col)
{
    this->value = array;

    this->ColorMaps.reserve(array->GetNumberOfTuples());
    this->m_Row = row;
    this->m_Column = col;
    this->render();
}

void igwMeshTableModel::render()
{
    vtkColorTransferFunction* stc = igwColorMapManager::GetInstance()->GetColorFunction();
    vtkSmartPointer<vtkUnsignedCharArray> colors;
    colors.TakeReference(vtkUnsignedCharArray::SafeDownCast(
                            stc->MapScalars(value, VTK_COLOR_MODE_MAP_SCALARS, 0 )));
    for(int cc = 0; cc < m_Column * m_Row; ++cc)
    {
        unsigned char* ptr = colors->GetPointer(4 * cc);
        this->ColorMaps.push_back(QColor());
        this->ColorMaps[cc] = QColor(qRgb(ptr[0], ptr[1], ptr[2]));
    }

}

const QColor &igwMeshTableModel::ColorMap(const int& currentRow, const int& currentCol) const
{

    int index = currentRow * m_Column + currentCol;
    this->ColorMaps.reserve(index + 1);
    return this->ColorMaps[index];
}


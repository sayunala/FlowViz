#ifndef IGWMESHTABLEMODEL_H
#define IGWMESHTABLEMODEL_H

#include <QAbstractTableModel>
class QPixmap;
class QColor;
class vtkDataArray;
class igwMeshTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:

    explicit igwMeshTableModel(QObject *parent = nullptr, int row = 5, int col = 5);
    ~igwMeshTableModel();
    // Header:
//    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void ResetDataModel(vtkDataArray* array, int row, int col);
    void InitData(vtkDataArray* array, int row, int col);
private:
    void render();
    const QColor& ColorMap(const int& currentRow, const int& currentCol) const;

    //显示的值
    vtkDataArray *value;
    //将值显示为颜色实现网格颜色的改变
    mutable QList<QColor> ColorMaps;
    int m_Column;
    int m_Row;
};

#endif // IGWMESHTABLEMODEL_H

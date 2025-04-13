#ifndef IGWDATATREEMODEL_H
#define IGWDATATREEMODEL_H

#include <QStandardItemModel>
#include <QAbstractItemModel>
#include <vtkSmartPointer.h>

class vtkDataObject;
class igwRenderedRepresentation;
class igwRenderView;
//struct DataManage
//{
//    DataManage() {}
//    vtkSmartPointer<vtkDataObject> DataObject;
//    QList<> Reps;
//};
class igwDataTreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
friend class igwTreeItem;
    enum ItemType{
        Invalid = -1,
        Root,
        Data,
        Rep
    };

    explicit igwDataTreeModel(QObject *parent = nullptr);
    virtual igwDataTreeModel::~igwDataTreeModel();
    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

//    // Basic functionality:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

//    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

//    // Add data:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
//    bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;

//    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
//    bool removeColumns(int column, int column, const QModelIndex &parent = QModelIndex()) override;

    void appendChild(const QModelIndex& index, igwTreeItem* item);

public  Q_SLOTS:
    /**
     * @brief addData: 有新数据时添加item
     * @param data: 新数据
     */
    void addData(vtkDataObject* data);

//    void addDatas(std::vector<vtkDataObject *>data);
    /**
     * @brief addRepresentation: 云图、流线、等值线等可视化节点
     * @param rep
     */
    bool addRepresentation(const QModelIndex& index, igwRenderedRepresentation* rep);


    void setView(igwRenderView* view);

//    bool removeColumns(int column, int column,,
//                       const QModelIndex &parent = QModelIndex()) override;
    igwTreeItem* getItem(const QModelIndex& index) const;
private:
    friend class igwTreeItem;
    igwTreeItem* RootItem;
    QStringList Headers;
    vtkSmartPointer<igwRenderView> View;

    QList<QPersistentModelIndex> m_checkedList;
//    QList<vtkSmartPointer<igwRenderedRepresentation>> Reps;


};

#endif // IGWDATATREEMODEL_H

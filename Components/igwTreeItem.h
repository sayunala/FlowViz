#ifndef igwTreeItemS_H
#define igwTreeItemS_H

#include "vtkObject.h"

#include <QVariant>
#include <QVector>
#include "igwDataTreeModel.h"
#include "vtkDataObject.h"
#include "vtkObject.h"
#include "vtkSmartPointer.h"
class igwTreeItem
{

public:
    explicit igwTreeItem(const QVector<QVariant> &data, igwTreeItem *parent = nullptr,
                         vtkObject* object = nullptr, igwDataTreeModel::ItemType type = igwDataTreeModel::Data);
    ~igwTreeItem();

    igwTreeItem *child(int number);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    void appendChild(igwTreeItem *child);
    bool insertChildren(int position, int count, int columns);
    bool insertColumns(int position, int columns);
    igwTreeItem *parent();
    bool removeChildren(int position, int count);
    bool removeColumns(int position, int columns);
    int childNumber() const;
    bool setData(int column, const QVariant &value);

    void setCheckState(Qt::CheckState state);

//    void addChild(pqPi)
    vtkObject* getObject(){return Object;};

    QVector<igwTreeItem*> childItems;
    QVector<QVariant> itemData;
    igwTreeItem *parentItem;

    igwDataTreeModel::ItemType Type;
    vtkSmartPointer<vtkObject> Object; // 用于存放vtkDataObjet
    vtkSmartPointer<igwRenderedRepresentation> Representation;

    Qt::CheckState CheckState = Qt::Checked;
};



#endif // igwTreeItemS_H

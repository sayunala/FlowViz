#include "igwTreeItem.h"
#include "../Representation/igwRenderedSurfaceRepresentation.h"
#include "igwActiveObjects.h"
igwTreeItem::igwTreeItem(const QVector<QVariant> &data, igwTreeItem *parent,
                         vtkObject* object, igwDataTreeModel::ItemType type)
    : itemData(data)
    ,parentItem(parent)
    ,Type(type)
{
    this->Object = object;
    this->Representation;
//    switch (Type) {
//    case igwDataTreeModel::Data:

//        break;
//    default:
//        break;
//    }
}

igwTreeItem::~igwTreeItem()
{
    igwRenderView* view = igwActiveObjects::GetInstance().GetActiveView();
    view->RemoveRepresentation(Representation);
    qDeleteAll(childItems);
}

igwTreeItem *igwTreeItem::child(int number)
{
    if (number < 0 || number >= childItems.size())
        return nullptr;
    return childItems.at(number);
}



int igwTreeItem::childCount() const
{
    return childItems.count();
}


int igwTreeItem::childNumber() const
{
    if (parentItem)
        return parentItem->childItems.indexOf(const_cast<igwTreeItem*>(this));
    return 0;
}


QVariant igwTreeItem::data(int column) const
{
    if (column < 0 || column >= itemData.size())
        return QVariant();
    return itemData.at(column);
}

void  igwTreeItem::appendChild(igwTreeItem *child)
{
    child->parentItem = this;
    childItems.push_back(child);
}

bool igwTreeItem::insertChildren(int position, int count, int columns)
{
    if (position < 0 || position > childItems.size())
        return false;

    for (int row = 0; row < count; ++row) {
        QVector<QVariant> data(columns);
        igwTreeItem *item = new igwTreeItem(data, this);
        childItems.insert(position, item);
    }

    return true;
}

bool igwTreeItem::removeChildren(int position, int count)
{
    if (position < 0 || position + count > childItems.size())
        return false;

    for (int row = 0; row < count; ++row)
    {
        delete childItems.takeAt(position);
    }


    return true;
}


igwTreeItem *igwTreeItem::parent()
{
    return parentItem;
}


bool igwTreeItem::insertColumns(int position, int columns)
{
    if (position < 0 || position > itemData.size())
        return false;

    for (int column = 0; column < columns; ++column)
        itemData.insert(position, QVariant());

    for (igwTreeItem *child : qAsConst(childItems))
        child->insertColumns(position, columns);

    return true;
}



bool igwTreeItem::setData(int column, const QVariant &value)
{
    if (column < 0 || column >= itemData.size())
        return false;

    itemData[column] = value;
    return true;
}

void igwTreeItem::setCheckState(Qt::CheckState state)
{
    CheckState = state;
    if(CheckState == Qt::Unchecked)
    {
        Representation->SetVisibility(false);
    }
    else
    {
        Representation->SetVisibility(true);
    }
}

int igwTreeItem::columnCount() const
{
    return itemData.count();
}




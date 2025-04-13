#include "igwDataTreeModel.h"

#include "igwTreeItem.h"
#include <iostream>
#include "vtkDataObject.h"
#include "vtkDataSet.h"
#include "vtkUnstructuredGrid.h"
#include "vtkPointData.h"

#include "../Representation/igwRenderView.h"
#include "../Representation/igwRenderedSurfaceRepresentation.h"
#include "../ColorMap/igwColorMapManager.h"
#include "igwActiveObjects.h"
igwDataTreeModel::igwDataTreeModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    Headers << QString::fromLocal8Bit("名称")
            << QString::fromLocal8Bit("编号");
//            << QString::fromLocal8Bit("透明度");


    QVector<QVariant> rootData;
    foreach (QString header, Headers)
        rootData << header;
    RootItem = new igwTreeItem(rootData, nullptr, nullptr, Root);
}

igwDataTreeModel::~igwDataTreeModel()
{
    std::cout << "delete Model" << std::endl;
    delete RootItem;// 移除RootItem
}
QVariant igwDataTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!

    if (orientation == Qt::Horizontal)
    {
       if(role == Qt::DisplayRole)
       {
           return Headers.at(section);
       }
    }
    return QVariant();

}

QModelIndex igwDataTreeModel::index(int row, int column, const QModelIndex &parent) const
{

    // FIXME: Implement me!
//    return QStandardItemModel::index(row, column, parent);
    if(parent.isValid() && parent.column() != 0)
    {
        return QModelIndex();
    }
    igwTreeItem* parentItem = getItem(parent);
    if(parentItem == nullptr)
    {
        return QModelIndex();
    }

    igwTreeItem* childItem = parentItem->child(row);
    if(childItem != nullptr)
    {
        return createIndex(row, column, childItem);

    }
    return QModelIndex();


}

QModelIndex igwDataTreeModel::parent(const QModelIndex &index) const
{

//    return QStandardItemModel::parent(index);
    if (!index.isValid())
        return QModelIndex();

    igwTreeItem *childItem = getItem(index);
    igwTreeItem *parentItem = childItem ? childItem->parent() : nullptr;

    if (parentItem == RootItem || !parentItem)
        return QModelIndex();

    return createIndex(parentItem->childNumber(), 0, parentItem);



}

int igwDataTreeModel::rowCount(const QModelIndex &parent) const
{
//    return QStandardItemModel::rowCount(parent);
    const igwTreeItem* parentItem = getItem(parent);

    return parentItem ? parentItem->childCount() : 0;

}

int igwDataTreeModel::columnCount(const QModelIndex &parent) const
{

    return Headers.length();

}

QVariant igwDataTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    igwTreeItem * item;
    item = static_cast<igwTreeItem*>(index.internalPointer());
    if (role == Qt::CheckStateRole && index.column()==0) //判断显示的对象是checkbox，并且位于第一列
    {
        return item->CheckState;         //如果没有显示checkbox没被选中
    }
    switch (role) {
    case Qt::DisplayRole:

        return item->data(index.column());
        break;
    default:
        break;
    }
//     FIXME: Implement me!
    return QVariant();
//    return QStandardItemModel::data(index, role);
}

bool igwDataTreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        // FIXME: Implement me!
        igwTreeItem * item;
        item = static_cast<igwTreeItem*>(index.internalPointer());
        if (role==Qt::CheckStateRole && index.column()==0)
        {
//            if (value==Qt::Unchecked)
//            {

//                emit(dataChanged(index, index));
//            }
//            else if(value==Qt::Checked)
//            {
//                m_checkedList.append(index);
//                emit(dataChanged(index, index));
//            }
            int state = value.toInt();
            item->setCheckState(static_cast<Qt::CheckState>(state));
            int childCount = rowCount();
            if (childCount > 0)                    //判断是否有子节点
            {
                for (int i=0;i<childCount;i++)
                {
                   QModelIndex child = this->index(i, 0, index); //获得子节点的index
                   setData(child, value, Qt::CheckStateRole);    //递归，将子节点的checkbox设为选中状态
                }
            }
        }

        emit dataChanged(index, index, QVector<int>() << role);
        igwActiveObjects::GetInstance().GetActiveView()->Render();
//        View->Render();
        return true;
    }
    return false;
}

igwTreeItem *igwDataTreeModel::getItem(const QModelIndex &index) const
{
    if(!index.isValid())
    {
        return RootItem;
    }
    igwTreeItem* item = static_cast<igwTreeItem*>(index.internalPointer());
    if(item != nullptr)
    {
        return item;
    }
    return RootItem;
}

Qt::ItemFlags igwDataTreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;
    if(index.column() == 0)
    {
        return Qt::ItemIsUserCheckable |  QAbstractItemModel::flags(index);
    }
    return QAbstractItemModel::flags(index); // FIXME: Implement me!
}

bool igwDataTreeModel::insertRows(int row, int count, const QModelIndex &parent)
{
    igwTreeItem *parentItem = getItem(parent);
    bool success;

    beginInsertRows(parent, row, row + count - 1);
    success = parentItem->insertChildren(row, count, RootItem->columnCount());
    endInsertRows();

    return success;
}

bool igwDataTreeModel::removeRows(int row, int count, const QModelIndex &parent)
{
    igwTreeItem *parentItem = getItem(parent);
    bool success = true;

    beginRemoveRows(parent, row, row + count - 1);

    success = parentItem->removeChildren(row, count);

    endRemoveRows();

    return success;
}

void igwDataTreeModel::appendChild(const QModelIndex &index, igwTreeItem *item)
{
    igwTreeItem* parent = getItem(index);
    int row = parent->childItems.size();
    this->beginInsertRows(index, row, row);
    // 设置item 第二列编号
    item->setData(1, row);
    parent->appendChild(item);
    this->endInsertRows();
}

void igwDataTreeModel::addData(vtkDataObject *data)
{
    if(data == nullptr)
    {
        return ;
    }

    QVector<QVariant> stringData;
    std::string name = data->GetObjectName();
    stringData << QString::fromStdString(name)
               << 0
               << QString::fromLocal8Bit("100%");

    igwTreeItem* item = new igwTreeItem(stringData);
    item->Object = data;

    item->Type = igwDataTreeModel::Data;

    item->Representation = vtkSmartPointer<igwRenderedSurfaceRepresentation>::New();
    item->Representation->SetInputData(vtkDataObject::SafeDownCast(item->Object));
    item->Representation->SetDataSet(vtkDataSet::SafeDownCast(item->Object));
    item->Representation->SetLookupTable(igwColorMapManager::GetInstance()->GetColorFunction());


//    item->Representation->SetInputArrayToProcess(0, 0, 0, vtkDataObject::FIELD_ASSOCIATION_POINTS, "velocity");


    item->Representation->Update();

    vtkView* view = igwActiveObjects::GetInstance().GetActiveView();
    igwRenderView* renderView = igwRenderView::SafeDownCast(view);
    renderView->AddRepresentation(item->Representation);
    renderView->Print(std::cout);
    this->appendChild(QModelIndex(), item);

//    igwRenderView::SafeDownCast(view)->Render();
    renderView->Render();
//    view->Render();
}

bool igwDataTreeModel::addRepresentation(const QModelIndex& index, igwRenderedRepresentation *rep)
{
    if(rep == nullptr)
    {
        return false;
    }

    igwTreeItem* parentItem = getItem(index);
    if(parentItem->Type != igwDataTreeModel::Data)
    {
        std::cout << "Current Item Is Not Data" << std::endl;
        return false;
    }

    QVector<QVariant> stringData;
    std::string name = rep->GetObjectName();
    stringData << QString::fromStdString(name)
               << 0
               << QString::fromLocal8Bit("100%");
    igwTreeItem* item = new igwTreeItem(stringData);

    item->Type = igwDataTreeModel::Rep;
    item->Representation = rep;


    // 构造Representation;
    item->Representation->SetInputData(vtkDataObject::SafeDownCast(parentItem->Object));
//    item->Representation->SetDataSet(vtkDataSet::SafeDownCast(parentItem->Object));
    item->Representation->Update();
    item->Object = item->Representation->GetOutput();
    vtkView* view = igwActiveObjects::GetInstance().GetActiveView();
    view->AddRepresentation(item->Representation);


    this->appendChild(index, item);
    igwRenderView::SafeDownCast(view)->Render();
//    view->Render();
    return true;
}

void igwDataTreeModel::setView(igwRenderView *view)
{
    if(this->View == view)
    {
        return ;
    }
    this->View = view;


}




//bool igwDataTreeModel::insertColumns(int column, int count, const QModelIndex &parent)
//{
//    beginInsertColumns(parent, column, column + count - 1);
//    // FIXME: Implement me!
//    return true;
//    endInsertColumns();
//}

//bool igwDataTreeModel::removeColumns(int column, int count, const QModelIndex &parent)
//{
//    beginRemoveColumns(parent, column, column + count - 1);
//    // FIXME: Implement me!
//    return true;
//    endRemoveColumns();
//}


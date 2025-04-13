#include "igwDataTreeWidget.h"
#include "ui_igwDataTreeWidget.h"

#include "igwActiveObjects.h"

#include "vtkQtTreeModelAdapter.h"
#include "vtkQtTreeView.h"
#include "vtkDataSetAttributes.h"
#include "vtkDataObject.h"

#include "igwTreeItem.h"
#include <QMenu>
#include <QStandardItemModel>
#include <QMessageBox>
igwDataTreeWidget::igwDataTreeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::igwDataTreeWidget)
{
    ui->setupUi(this);

    Model = new igwDataTreeModel(ui->treeView);

    ui->treeView->setModel(Model);
    ui->treeView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);

    QObject::connect(ui->treeView->selectionModel(), &QItemSelectionModel::currentChanged,
                     this, &igwDataTreeWidget::onTreeViewSelected);

    QObject::connect(&igwActiveObjects::GetInstance(), &igwActiveObjects::viewChanged,
                     this, &igwDataTreeWidget::setActiveView);
    QObject::connect(ui->treeView,
                     &QTreeView::customContextMenuRequested,
                     this,
                     &igwDataTreeWidget::onCustomContextMenuRequested);
}

igwDataTreeWidget::~igwDataTreeWidget()
{
    delete ui;
}

void igwDataTreeWidget::onTreeViewSelected(const QModelIndex &current, const QModelIndex &previous)
{
    std::cout << current.row() << "column" << current.column() << std::endl;
    igwTreeItem* item = Model->getItem(current); //获取当前选中item
    if(item != nullptr)
    {
        std::cout << item << std::endl;
    }
    vtkObject* object = item->getObject();
    igwRenderedRepresentation *rep = item->Representation;
    if(object == nullptr)
    {
        return ;
    }

    switch (item->Type) {
    case igwDataTreeModel::Root:
        igwActiveObjects::GetInstance().SetActiveData(vtkDataObject::SafeDownCast(object));
        break;
    case igwDataTreeModel::Data:
        igwActiveObjects::GetInstance().SetActiveData(vtkDataObject::SafeDownCast(object));
        igwActiveObjects::GetInstance().SetAvtiveRepresentation(rep);
        break;
    case igwDataTreeModel::Rep:
        igwActiveObjects::GetInstance().SetActiveData(vtkDataObject::SafeDownCast(object));
        igwActiveObjects::GetInstance().SetAvtiveRepresentation(rep);
    default:
        break;
    }
//    igwActiveObjects::GetInstance().SetActiveData(vtkDataObject::SafeDownCast(object));
//    igwActiveObjects::GetInstance().SetAvtiveRepresentation(rep);
}

void igwDataTreeWidget::onLoadData(vtkDataObject *object)
{

    if(object == nullptr)
    {
        return;
    }
    igwActiveObjects::GetInstance().SetActiveData(object);
    Model->addData(object);

}

bool igwDataTreeWidget::onAddRepresentation(igwRenderedRepresentation *rep)
{
    QModelIndex index = ui->treeView->selectionModel()->currentIndex();
    return Model->addRepresentation(index, rep);

}

void igwDataTreeWidget::setActiveView(igwRenderView *view)
{

    Model->setView(view);
}

void igwDataTreeWidget::onCustomContextMenuRequested(const QPoint &pos)
{
    QModelIndex index = ui->treeView->indexAt(pos);
       if (!index.isValid()) {
           return;
       }

       QMenu contextMenu(tr("Context Menu"), this);

       QAction action1(QString::fromLocal8Bit("删除"), this);
       connect(&action1, &QAction::triggered, [index, this]() {
           this->Model->removeRow(index.row(), index.parent());
       });
       contextMenu.addAction(&action1);

       QAction action2(QString::fromLocal8Bit("设置"), this);
       connect(&action2, &QAction::triggered, [index, this]()
       {

           igwTreeItem* item =  this->Model->getItem(index);
           if(item == nullptr) return;
           item->getObject();

       });
       contextMenu.addAction(&action2);

       contextMenu.exec(ui->treeView->viewport()->mapToGlobal(pos));
}

void igwDataTreeWidget::onSettingActionTriggered()
{

}

#ifndef IGWDATATREEWIDGET_H
#define IGWDATATREEWIDGET_H

#include <QWidget>

#include "vtkQtTreeModelAdapter.h"
#include "vtkQtTreeView.h"
#include "vtkSmartPointer.h"
#include "igwDataTreeModel.h"
#include "../Representation/igwRenderView.h"
namespace Ui {
class igwDataTreeWidget;
}

class igwDataTreeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit igwDataTreeWidget(QWidget *parent = nullptr);
    ~igwDataTreeWidget();

public slots:
    virtual void onTreeViewSelected(const QModelIndex &, const QModelIndex &);// 选中行
    virtual void onLoadData(vtkDataObject* object);// 数据加载

    //
    virtual bool onAddRepresentation(igwRenderedRepresentation* rep);
    virtual void setActiveView(igwRenderView* view);

    virtual void onCustomContextMenuRequested(const QPoint &pos);
    virtual void onSettingActionTriggered();
private:
    Ui::igwDataTreeWidget *ui;
    QPointer<igwDataTreeModel> Model;

};

#endif // IGWDATATREEWIDGET_H

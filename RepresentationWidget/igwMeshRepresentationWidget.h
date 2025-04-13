#ifndef igwMeshRepresentationWidget_H
#define igwMeshRepresentationWidget_H

#include <QWidget>
#include <QPointer>
class igwMeshRepresentation;
class igwRenderedRepresentation;
class vtkEventQtSlotConnect;
class igwMeshTableModel;
class vtkObject;
namespace Ui {
class igwMeshRepresentationWidget;
}

class igwMeshRepresentationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit igwMeshRepresentationWidget(QWidget *parent = nullptr);
    ~igwMeshRepresentationWidget();

    void SetRepresentation(igwRenderedRepresentation* rep);

    vtkEventQtSlotConnect *EventQtSlotConnect() const;

private slots:

    void ApplySetting();

    void on_meshRowSpinBox_valueChanged(int m);

    void on_meshColSpinBox_valueChanged(int n);

    // 表格值修改槽函数
    void UpdateMeshData(double );

    // 数据更新时更新表格的槽函数，通过vtkEventsQSlotConnect与 MeshDataUpdateEvent连接
    void UpdateMeshTableWidget(vtkObject*, unsigned long, void*, void*);

    // 更新meshTableView的Model的背景色，实现网格背景色的变化
    void UpdateMeshTableModel();

    void on_SuffixComboBox_currentIndexChanged(const QString &suffix);

Q_SIGNALS:
    void Applied();

private:

    void InitMeshTable();
    void InitMeshTableModel();
    Ui::igwMeshRepresentationWidget *ui;

    igwMeshRepresentation* m_igwMeshRepresentation;
    igwMeshTableModel* Model;


//    Q_PROPERTY(vtkEventQtSlotConnect *EventQtSlotConnect READ EventQtSlotConnect CONSTANT)
};

#endif // igwMeshRepresentationWidget_H

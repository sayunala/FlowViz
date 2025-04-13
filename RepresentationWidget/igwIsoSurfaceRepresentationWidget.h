#ifndef IGWISOSURFACEREPRESENTATIONWIDGET_H
#define IGWISOSURFACEREPRESENTATIONWIDGET_H

#include <QWidget>
class igwIsoSurfaceRepresentation;
class igwRenderedRepresentation;
namespace Ui {
class igwIsoSurfaceRepresentationWidget;
}

class igwIsoSurfaceRepresentationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit igwIsoSurfaceRepresentationWidget(QWidget *parent = nullptr);
    ~igwIsoSurfaceRepresentationWidget();

    void SetRepresentation(igwRenderedRepresentation* rep);

private slots:

    //删除行槽函数
    void on_deleteButton_clicked();

    //增加行槽函数
    void on_addLineButton_clicked();

    void on_clearButton_clicked();

    //属性下拉框
    void on_DataArrayComboBox_currentTextChanged(const QString &arrayName);

    void ApplySetting();

Q_SIGNALS:
    void Applied();

private:
    /**
     * @brief 初始化等值面表
     */
    void InitContoursTable();

    /**
     * @brief InitDataArrayComboBox: 初始化物理量选择下拉框
     */
    void InitDataArrayComboBox();


    /**
     * @brief UpdateContours: Update the Contours。
     * @brief UpdateContours: 更新生成的等值面。
     */
    void UpdateContours();

    Ui::igwIsoSurfaceRepresentationWidget *ui;

    igwIsoSurfaceRepresentation* m_igwIsoSurfaceRepresentation;

    int NumberOfContours;


};

#endif // IGWISOSURFACEREPRESENTATIONWIDGET_H

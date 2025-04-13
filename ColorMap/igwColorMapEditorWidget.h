#ifndef IGWCOLORMAPEDITORWIDGET_H
#define IGWCOLORMAPEDITORWIDGET_H
/**********************************************
* @projectName   iGreatWorks
* @file          igwColorMapEditorWidget.h
* @brief         颜色编辑组件，包含透明度和颜色编辑UI
* @author        ZYB
* @date          2023-09-23
* @version       1.0
**********************************************/

#include <QWidget>
#include <vtkDiscretizableColorTransferFunction.h>
#include "igwPresetGroupsManager.h"

namespace Ui {
class igwColorMapEditorWidget;
}

class igwColorMapEditorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit igwColorMapEditorWidget(QWidget *parent = 0);
    ~igwColorMapEditorWidget();
    QSize sizeHint() const{

        return size();
    }
Q_SIGNALS:
    /**
     * @brief 该信号触发表明，颜色已经改变需要重新渲染整个界面
     */
    void ChangedFinished();

    /**
     * @brief SaveStateAsPresets 该信号触发表示，要把当前选中的颜色保存为预设的信号，在表格中可以看到
     */
    void SaveStateAsPresets();
private slots:
    /**
     * @brief 修改下拉框选中的槽函数
     * @param presetName
     */
    void on_DefaultPresetsComboBox_currentIndexChanged(const QString &presetName);

    /**
     * @brief 重置颜色选取下拉框
     */
    void ResetCombox();

    /**
     * @brief 保存预设按钮响应槽函数
     */
    void on_saveAsPreset_clicked();

private:
    Ui::igwColorMapEditorWidget *ui;

    vtkSmartPointer<vtkPiecewiseFunction> pwf;
    igwPresetGroupsManager* m_groupManager;
};

#endif // IGWCOLORMAPEDITORWIDGET_H

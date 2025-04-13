#ifndef REPRESENTATIONDIALOG_H
#define REPRESENTATIONDIALOG_H

#include <QDialog>

class igwColorMapEditorWidget;

namespace Ui {
class RepresentationDialog;
}

class RepresentationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RepresentationDialog(QWidget *parent = nullptr);
    ~RepresentationDialog();
    void AddWidget(QWidget* widget, const QString& name);

private slots:
    /**
     * @brief ApplySetting: 窗口编辑完成，OK点击之后的槽函数，发送 SettingApplied信号，
     * 之后Widget收到 SettingApplied信号之后调用Widget中的ApplySetting函数，在Widget中
     * ApplySetting函数会发送Applied信号，主窗口监听到Applied信号后刷新VTK窗口
     */
    void ApplySetting();
Q_SIGNALS:
    /**
     * @brief SettingApplied:当OK点击之后发送 SettingApplied信号通知主窗口
     */
    void SettingApplied();
private:
    Ui::RepresentationDialog *ui;

};

#endif // REPRESENTATIONDIALOG_H

#ifndef IGWLINEPARAMETERSWIDGET_H
#define IGWLINEPARAMETERSWIDGET_H

#include <QWidget>
class QRegExpValidator;
class vtkLineWidget;
namespace Ui {
class igwLineParametersWidget;
}

class igwLineParametersWidget : public QWidget
{
    Q_OBJECT

public:
    explicit igwLineParametersWidget(QWidget *parent = nullptr);
    ~igwLineParametersWidget();
    void SetLineWidget(vtkLineWidget* lineWidget);

    void SetVisibility(bool visibility);
private slots:
    void on_XAxisButton_clicked();

    void on_YAxisButton_clicked();

    void on_ZAxisButton_clicked();

    void on_Point1XEdit_editingFinished();

    void on_Point1YEdit_editingFinished();

    void on_Point1ZEdit_editingFinished();

    void on_Point2XEdit_editingFinished();

    void on_Point2YEdit_editingFinished();

    void on_Point2ZEdit_editingFinished();

    void updateLineWidgetSlot();

    void on_showLineCheckBox_stateChanged(int arg1);

Q_SIGNALS:
    void LineWidgetChanged();

private:
    void InitUI();

    void SetPoint1(double []);
    void SetPoint1(double x, double y, double z);

    void SetPoint2(double []);
    void SetPoint2(double x, double y, double z);
    Ui::igwLineParametersWidget *ui;
    QRegExpValidator* m_Validator;
    vtkLineWidget* LineWidget;
    double Point1[3];
    double Point2[3];

    bool Visibility;
};

#endif // IGWLINEPARAMETERSWIDGET_H

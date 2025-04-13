#ifndef IGWPLANEPARAMETERSWIDGET_H
#define IGWPLANEPARAMETERSWIDGET_H

#include <QWidget>
class vtkPlane;
class QRegExpValidator;
namespace Ui {
class igwPlaneParametersWidget;
}

class igwPlaneParametersWidget : public QWidget
{
    Q_OBJECT

public:
    explicit igwPlaneParametersWidget(QWidget *parent = nullptr);
    ~igwPlaneParametersWidget();

    /**
     * @brief SetPlane: Set the Plane.
     * @param plane
     */
    void SetPlane(vtkPlane* plane);

    void SetVisibility(bool visibility);

private slots:

    void on_XNormalButton_clicked();

    void on_YNormalButton_clicked();

    void on_ZNormalButton_clicked();

    void on_showPlaneCheckBox_stateChanged(int arg1);

    void on_NormalXEdit_editingFinished();

    void on_NormalYEdit_editingFinished();

    void on_NormalZEdit_editingFinished();

    void on_OriginXEdit_editingFinished();

    void on_OriginYEdit_editingFinished();

    void on_OriginZEdit_editingFinished();

    /**
     * @brief UpdatePlane
     */
    void UpdatePlane(double ox, double oy, double oz, double nx, double ny, double nz);

Q_SIGNALS:
    /**
     * @brief XNormalButton_clicked: 平面对齐X，Y，Z三个轴的信号
     */
    void XNormalButton_clicked();
    void YNormalButton_clicked();
    void ZNormalButton_clicked();

    void showPlaneCheckBox_stateChanged(int arg1);

    void OriginChanged(double x, double y, double z);

    void NormalChanged(double x, double y, double z);

private:
    /**
     * @brief InitUI: Init the Plane UI
     * @brief InitUI: 初始化UI相关的参数
     */
    void InitUI();

    /**
     * @brief SetNormal: Set the Plane Normal.
     * @brief SetNormal: 设置平面法线.
     */
    void SetNormal(double x, double y, double z);

    /**
     * @brief SetOrigin: Set the Plane Origin.
     * @brief SetOrigin: 设置平面经过的点.
     */
    void SetOrigin(double x, double y, double z);

    Ui::igwPlaneParametersWidget *ui;
    vtkPlane* Plane;
    QRegExpValidator* m_Validator;

    double m_PlaneNormal[3];//切面法线
    double m_PlaneOrigin[3];//切面过的点

    bool Visibility;
};

#endif // IGWPLANEPARAMETERSWIDGET_H

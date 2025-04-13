#ifndef IGWFLOWINGSTREAMREPWIDGET_H
#define IGWFLOWINGSTREAMREPWIDGET_H

#include <QWidget>
class igwFlowingStreamLinesRepresentation;
class igwRenderedRepresentation;
namespace Ui {
class igwFlowingStreamRepWidget;
}

class igwFlowingStreamRepWidget : public QWidget
{
    Q_OBJECT

public:
    explicit igwFlowingStreamRepWidget(QWidget *parent = nullptr);
    ~igwFlowingStreamRepWidget();

    void SetRepresentation(igwRenderedRepresentation* rep);
private slots:

    /**
     * @brief on_particle_numEdit_returnPressed: 粒子数量编辑槽函数
     */
    void on_particle_numEdit_returnPressed();

    /**
     * @brief on_max_timeEdit_returnPressed: 粒子存活时间编辑槽函数
     */
    void on_max_timeEdit_returnPressed();

    /**
     * @brief on_stepEdit_returnPressed: 步长编辑槽函数
     */
    void on_stepEdit_returnPressed();

    /**
     * @brief on_alphaEdit_textChanged: alpha 编辑槽函数
     * @param arg1
     */
    void on_alphaEdit_textChanged(const QString &arg1);


    void on_alphaSlider_sliderMoved(int position);

    void on_alphaSlider_sliderReleased();

    void on_alphaEdit_returnPressed();

    void on_alphaSlider_valueChanged(int value);


    void ApplySetting();
    void on_DataArrayComboBox_currentIndexChanged(const QString &arg1);

Q_SIGNALS:
    void Applied();
private:
    /**
     * @brief InitDataArrayCombox: 初始化属性选择下拉框
     */
    void InitDataArrayCombox();

    /**
     * @brief Init: 在setRepresentation中被调用用于同步Representation中的参数
     */
    void Init();

    Ui::igwFlowingStreamRepWidget *ui;

    igwFlowingStreamLinesRepresentation* m_igwFlowingStreamLinesRepresentation;

    double m_Alpha;
    double m_Step;
    int m_MaxTime;
    int m_ParticleNum;
};

#endif // IGWFLOWINGSTREAMREPWIDGET_H

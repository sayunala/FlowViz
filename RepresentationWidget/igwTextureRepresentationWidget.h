#ifndef igwTextureRepresentationWidgetWIDGET_H
#define igwTextureRepresentationWidgetWIDGET_H

#include <QWidget>

class igwTextureRepresentation;
class igwRenderedRepresentation;
class vtkSurfaceLICInterface;
namespace Ui {
class igwTextureRepresentationWidget;
}

class igwTextureRepresentationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit igwTextureRepresentationWidget(QWidget *parent = nullptr);
    ~igwTextureRepresentationWidget();

    void SetRepresentation(igwRenderedRepresentation *rep);

protected:
    /**
     * @brief Init : Init UI
     */
    void Init();

    // Init the Tab Widgets
    void InitDataArrayComboBox();
    void InitIntegratorTab();

    void InitRenderTab();
    void InitMaskTab();
    void InitNoiseTab();


    void EnableLICContrastUI(int val);

    void EnableColorContrastUI(int val);

    void EnableBlendUI(int val);

    void EnableMapUI(int val);
private slots:

    //---------------------积分器Tab UI Slot------------------------
    void on_normalVector_checkBox_stateChanged(int arg1);

    void on_enhancedLIC_checkBox_stateChanged(int arg1);



    //---------------------渲染Tab------------------------
    void on_colorMode_comboBox_currentIndexChanged(int index);

    void on_enhanceContrast_comboBox_currentIndexChanged(int index);

    void on_antiAlias_lineEdit_textChanged(const QString &arg1);

    void on_antiAlias_Slider_valueChanged(int value);

    void on_highLIC_Slider_valueChanged(int value);

    void on_highLIC_lineEdit_textChanged(const QString &arg1);

    void on_lowLIC_Slider_valueChanged(int value);

    void on_lowLIC_lineEdit_textEdited(const QString &arg1);

    void on_highColor_Slider_valueChanged(int value);

    void on_highColor_lineEdit_textChanged(const QString &arg1);

    void on_lowColor_Slider_valueChanged(int value);

    void on_lowColor_lineEdit_textChanged(const QString &arg1);

    void on_LICIntensity_Slider_valueChanged(int value);

    void on_LICIntensity_lineEdit_textChanged(const QString &arg1);

    void on_mapOffset_Slider_valueChanged(int value);

    void on_mapOffset_lineEdit_textChanged(const QString &arg1);

    //---------------------噪声Tab------------------------
    void on_noiseTextureSize_Slider_valueChanged(int value);

    void on_noiseTextureSize_lineEdit_textChanged(const QString &arg1);

    void on_noiseGrainSize_Slider_valueChanged(int value);

    void on_noiseGrainSize_lineEdit_textChanged(const QString &arg1);

    void on_minNoiseValue_Slider_valueChanged(int value);

    void on_minNoiseValue_lineEdit_textChanged(const QString &arg1);

    void on_maxNoiseValue_Slider_valueChanged(int value);

    void on_maxNoiseValue_lineEdit_textChanged(const QString &arg1);

    void on_numOfNoiseLevel_Slider_valueChanged(int value);

    void on_numOfNoiseLevel_lineEdit_textChanged(const QString &arg1);

    void on_impulseNoiseProbability_Slider_valueChanged(int value);

    void on_impulseNoiseProbability_lineEdit_textChanged(const QString &arg1);

    void on_impulseNoiseBackgroundValue_Slider_valueChanged(int value);

    void on_impulseNoiseBackgroundValue_lineEdit_textChanged(const QString &arg1);

    void on_random_Slider_valueChanged(int value);

    void on_random_lineEdit_textChanged(const QString &arg1);

    void on_noiseTexture_checkBox_stateChanged(int arg1);

    void on_noiseType_comboBox_currentIndexChanged(int index);

    void ApplySetting();

    //---------------------表面遮盖Tab------------------------
    void on_maskThreshold_lineEdit_textChanged(const QString &arg1);

    void on_maskIntensity_Slider_valueChanged(int value);

    void on_maskIntensity_lineEdit_textChanged(const QString &arg1);

    void on_maskOnSurface_checkBox_stateChanged(int arg1);

    void on_stepSize_Edit_textChanged(const QString &arg1);

    void on_stepNum_Edit_textChanged(const QString &arg1);

    void on_vector_comboBox_currentTextChanged(const QString &arg1);

Q_SIGNALS:
    void Applied();
private:


    Ui::igwTextureRepresentationWidget *ui;

    igwTextureRepresentation* m_igwTextureRep;
    vtkSurfaceLICInterface* m_LICInterface;
};

#endif // igwTextureRepresentationWidgetWIDGET_H

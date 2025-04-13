/**********************************************
* @projectName   IGreatWorks
* @file          igwPresetToPixmap.h
* @brief         将颜色预设转换为像素图，供颜色选择下拉框和颜色选择对话框使用
* @author        ZYB
* @date          2023-09-23
* @version       1.0
**********************************************/

#ifndef IGWPRESETTOPIXMAP_H
#define IGWPRESETTOPIXMAP_H

#include <QObject>
#include <QScopedPointer>
#include <vtk_jsoncpp_fwd.h>
class vtkPiecewiseFunction;
class vtkScalarsToColors;
class QPixmap;
class QSize;

class igwPresetToPixmap : public QObject
{
    Q_OBJECT
    typedef QObject Superclass;
public:
    explicit igwPresetToPixmap(QObject *parent = nullptr);
    ~igwPresetToPixmap() override;

    /**
     * @brief render 将预设转换为像素图
     * @param preset 预设的Json::Value表达
     * @param resolution 分辨率
     * @return
     */
    QPixmap render(const Json::Value& preset, const QSize& resolution) const;

protected:
    /**
     * Renders a color transfer function preset.
     */
    /**
     * @brief renderColorTransferFunction 将颜色和透明度转换为像素图
     * @param stc vtkScalarsToColors对象在指针，主要用于颜色映射
     * @param pf vtkPiecewiseFunction对象，主要用于透明度渲染
     * @param resolution 分辨率
     * @return
     */
    QPixmap renderColorTransferFunction(
      vtkScalarsToColors* stc, vtkPiecewiseFunction* pf, const QSize& resolution) const;

//    /**
//     * Renders a color transfer function preset.
//     */
//    QPixmap renderIndexedColorTransferFunction(
//      vtkScalarsToColors* stc, const QSize& resolution) const;
private:
  Q_DISABLE_COPY(igwPresetToPixmap)
  class igwInternals;
  QScopedPointer<igwInternals> Internals;
};

#endif // IGWPRESETTOPIXMAP_H

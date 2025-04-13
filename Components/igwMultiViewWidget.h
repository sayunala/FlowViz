#ifndef IGWMULTIVIEWWIDGET_H
#define IGWMULTIVIEWWIDGET_H

#include <QWidget>
#include <QVector>
#include <QPointer>
#include <QMap>
class igwViewFrame;
class igwHierarchicalGridWidget;
class igwView;
class igwViewManager;
namespace Ui {
class igwMultiViewWidget;
}

class igwMultiViewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit igwMultiViewWidget(QWidget *parent = nullptr);
    ~igwMultiViewWidget();

    void createViewFrame(const std::vector<igwView*>& views);

    igwViewFrame *newFrame(igwView* view);

    void ConnectFrameToView(igwViewFrame* frame, igwView* view);




public Q_SLOTS:

    // 水平 | 垂直 | 关闭按钮 | 最大化
    void standardButtonPressed(int);

protected Q_SLOTS:

    void makeActive(igwViewFrame* frame);

    void markActive(igwView* view);
    void markActive(igwViewFrame *frame);
private:
    Ui::igwMultiViewWidget *ui;
    QVector<QPointer<igwViewFrame>> Frames;

    QMap<igwView*, QPointer<igwViewFrame>> ViewFrames;       // 为一个View 分配一个固定的Frame
    QPointer<igwHierarchicalGridWidget> Container;
    QPointer<igwViewFrame> ActiveFrame;                     // 当前激活的View Frame
    int CurrentLoaction;

    std::vector<igwView*> Views;                            // 存储全部的view实例

    igwViewManager* ViewManager;

};

#endif // IGWMULTIVIEWWIDGET_H

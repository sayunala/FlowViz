#include "igwMultiViewWidget.h"
#include "ui_igwMultiViewWidget.h"

#include <QLabel>
#include "Widgets/igwHierarchicalGridLayout.h"
#include "Widgets/igwHierarchicalGridWidget.h"
#include "igwViewFrame.h"
#include "igwView.h"
#include "igwVtkView.h"

#include "igwActiveObjects.h"
#include "Representation/igwRenderView.h"
#include "Representation/igwRenderViewBase.h"

#include "Core/igwApplicationCore.h"
#include "Core/igwViewManager.h"
static const int iGreakWorks_DEFAULT_LAYOUT_SPACING = 4;
igwMultiViewWidget::igwMultiViewWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::igwMultiViewWidget)
{
    ui->setupUi(this);
    this->Container = new igwHierarchicalGridWidget(this);
    this->Container->setObjectName("Container");
    this->Container->setAutoFillBackground(true);
    igwHierarchicalGridLayout* layout = new igwHierarchicalGridLayout(Container);
    layout->setSpacing(iGreakWorks_DEFAULT_LAYOUT_SPACING);



    //创建默认的frame
    igwView* view = new igwVtkView(this);

    ViewManager = igwApplicationCore::GetInstance()->GetViewManager();
    if(ViewManager != nullptr);
    ViewManager->addView(view);

    auto frame = newFrame(view);
    this->ViewFrames.insert(view, frame);
    layout->addWidget(frame);

    this->makeActive(frame);
    // 增加 Frame容器
    ui->verticalLayout_2->setContentsMargins(0,0,0,0);
    ui->verticalLayout_2->addWidget(this->Container);


//    this->createViewFrame({new igwVtkView(this)});
}


igwMultiViewWidget::~igwMultiViewWidget()
{
    delete ui;
    delete this->Container;
}

void igwMultiViewWidget::createViewFrame(const std::vector<igwView*>& views)
{
    for(auto view : views)
    {
        if(!this->ViewFrames.contains(view))
        {
            this->ViewFrames.insert(view, this->newFrame(view));
        }
    }
}

igwViewFrame *igwMultiViewWidget::newFrame(igwView *view)
{
    igwViewFrame* frame = new igwViewFrame();
    QObject::connect(frame, &igwViewFrame::buttonPressed, this, &igwMultiViewWidget::standardButtonPressed);
//    QObject::connect(frame)
    ConnectFrameToView(frame, view);

    // 先使用空的View 进行测试
    if(view == nullptr)
    {
        QWidget* empty_frame = new QWidget(frame);
        empty_frame->setLayout(new QVBoxLayout(empty_frame));
        empty_frame->layout()->addWidget(new QLabel("empty frame"));
        frame->setCentralWidget(empty_frame);
    }

    return frame;
}

void igwMultiViewWidget::ConnectFrameToView(igwViewFrame *frame, igwView *view)
{
    if(view != nullptr)
    {
        // 从 view 中获取 widget 并填充
        QWidget* viewWidget = view->widget();
        frame->setCentralWidget(viewWidget);
    }
}

void igwMultiViewWidget::standardButtonPressed(int button)
{
    igwViewFrame* frame = qobject_cast<igwViewFrame*>(this->sender());
    QVariant index = frame ? frame->property("FRAME_INDEX") : QVariant();
    vtkView* view = igwRenderView::New();

    auto f = newFrame(new igwVtkView(view, nullptr));
    if(!index.isValid())
    {
        return ;
    }
    igwHierarchicalGridLayout* ly = qobject_cast<igwHierarchicalGridLayout*>(Container->layout());
    switch (button) {
    case igwViewFrame::SplitHorizontal:
        ly->splitHorizontal(index.toInt(), 0.5);
        ly->addWidget(f);
        break;
    case igwViewFrame::SplitVertical:
        ly->splitVertical(index.toInt(), 0.5);
        ly->addWidget(f);
        break;
    case igwViewFrame::Close:
        std::cout << index.toInt() << std::endl;
        if(index.toInt() != 0)
        {
            int location = index.toInt();

            ly->removeLocation(location); // 删除location位置的 igwViewFrame
        }
    default:
        break;
    }
}

void igwMultiViewWidget::makeActive(igwViewFrame *frame)
{
    if(this->ActiveFrame!=frame)
    {
        igwView* view = nullptr;
        if(frame!=nullptr)
        {
            view = this->ViewFrames.key(frame);

        }
        // 目前只支持igwRenderView，后续会增加新的view
        view->getVtkView()->Print(std::cout);
        igwActiveObjects::GetInstance().SetActiveView(igwRenderView::SafeDownCast(view->getVtkView()));
        this->markActive(frame);
    }
}

void igwMultiViewWidget::markActive(igwView *view)
{

}

void igwMultiViewWidget::markActive(igwViewFrame *frame)
{

    if(this->ActiveFrame)
    {

    }
    this->ActiveFrame = frame;
//    if(frame)
//    {
//        frame
//    }
}

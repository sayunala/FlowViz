#include "igwViewFrame.h"
#include "ui_igwViewFrame.h"


#include <QAction>
#include <QApplication>
#include <QDrag>
#include <QHBoxLayout>
#include <QLabel>
#include <QMenu>
#include <QMimeData>
#include <QMouseEvent>
#include <QPainter>
#include <QStyle>
#include <QToolBar>
#include <QToolButton>
#include <QVBoxLayout>
#include <QToolBar>

#include "vtksys/SystemInformation.hxx"

const int ICON_SIZE = 20;

igwViewFrame::igwViewFrame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::igwViewFrame),
    Buttons(NoButton),
    UniqueID(QUuid::createUuid())
{
    ui->setupUi(this);

    this->ToolBar = new QToolBar(this);
    this->ToolBar->setObjectName("ToolBar");
    this->ToolBar->setIconSize(QSize(ICON_SIZE,ICON_SIZE));
    this->ToolBar->layout()->setSpacing(0);
    this->ToolBar->layout()->setContentsMargins(0,0,0,0);

    QObject::connect(ui->TitleBar, &QWidget::customContextMenuRequested,this,&igwViewFrame::customContextMenuRequested);
    ui->TitleBar->installEventFilter(this);

    //创建标准按钮
    this->StandardToolButtons[SplitVertical] = this->createButton(
      new QAction(QIcon(":/igwWidgets/Icons/Widgets/Resources/Icons/igwSplitVertical.svg"), tr("Split Vertical Axis"), this));
    this->StandardToolButtons[SplitHorizontal] = this->createButton(
      new QAction(QIcon(":/igwWidgets/Icons/Widgets/Resources/Icons/igwSplitHorizontal.svg"), tr("Split Horizontal Axis"), this));
    this->StandardToolButtons[Maximize] =
      this->createButton(new QAction(QIcon(this->style()->standardIcon(QStyle::SP_TitleBarMaxButton)),
                           tr("Maximize"), this));
    this->StandardToolButtons[Restore] = this->createButton(
      new QAction(
        QIcon(this->style()->standardIcon(QStyle::SP_TitleBarNormalButton)), tr("Restore"), this));
    this->StandardToolButtons[Close] = this->createButton(
      new QAction(
        QIcon(this->style()->standardIcon(QStyle::SP_TitleBarCloseButton)), tr("Close"), this));

    ui->TitleBarLayout->insertWidget(0, this->ToolBar);
    Q_FOREACH(QToolButton* button, this->StandardToolButtons)
    {
        ui->TitleBarLayout->addWidget(button);
    }

    this->ContexMenu = new QMenu(ui->TitleBar);
    this->ContexMenu->setObjectName("FrameContexMenu");
    this->ContexMenu->addAction(this->StandardToolButtons[SplitHorizontal]->defaultAction());
    this->ContexMenu->addAction(this->StandardToolButtons[SplitVertical]->defaultAction());
    this->ContexMenu->addAction(this->StandardToolButtons[Close]->defaultAction());
    this->setStandardButtons(SplitHorizontal | SplitVertical | Close);

    ui->TitleLabel->installEventFilter(this);


}


void igwViewFrame::setStandardButtons(StandardButtons buttons)
{
  if (this->Buttons != buttons)
  {
    this->Buttons = buttons;
    for (StandardToolButtonsMap::iterator iter = this->StandardToolButtons.begin();
         iter != this->StandardToolButtons.end(); ++iter)
    {
      iter.value()->setVisible(this->Buttons & iter.key());
    }
  }
}

//-----------------------------------------------------------------------------
QToolButton* igwViewFrame::createButton(QAction* action)
{
  QToolButton* toolButton = new QToolButton(this);
  toolButton->setDefaultAction(action);
  toolButton->setObjectName(action->objectName());
  toolButton->setIcon(action->icon());
  toolButton->setIconSize(QSize(ICON_SIZE, ICON_SIZE));

  QObject::connect(
    toolButton, SIGNAL(triggered(QAction*)), this, SLOT(buttonClicked()), Qt::QueuedConnection);
  return toolButton;
}

void igwViewFrame::finishedDrag(igwViewFrame *source)
{

}

//-----------------------------------------------------------------------------
void igwViewFrame::buttonClicked()
{
  QToolButton* toolButton = qobject_cast<QToolButton*>(this->sender());
  if (toolButton)
  {
    StandardButton key = this->StandardToolButtons.key(toolButton, NoButton);
    if (key != NoButton)
    {
      Q_EMIT this->buttonPressed(key);
    }
  }
}

void igwViewFrame::customContextMenuRequested(const QPoint &pos)
{
    this->setFocus(Qt::OtherFocusReason);
    this->ContexMenu->exec(ui->TitleBar->mapToGlobal(pos));
}


void igwViewFrame::setCentralWidget(QWidget *widget, igwView *view)
{
    this->CentralWidget = widget;
    while(QLayoutItem* item = ui->CentralWidgetFrameLayout->takeAt(0))
    {
        delete item;
    }
    if(this->CentralWidget)
    {
        ui->CentralWidgetFrameLayout->addWidget(this->CentralWidget);
    }

}

QWidget* igwViewFrame::centralWidget()
{
    return this->CentralWidget;
}

bool igwViewFrame::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress)
    {
      QMouseEvent* mouseEvent = reinterpret_cast<QMouseEvent*>(event);
      if (mouseEvent->button() == Qt::LeftButton)
      {
        this->DragStartPosition = mouseEvent->pos();
      }
    }
    else if (event->type() == QEvent::MouseMove)
    {
      QMouseEvent* mouseEvent = reinterpret_cast<QMouseEvent*>(event);
      if ((mouseEvent->buttons() & Qt::LeftButton) &&
        (mouseEvent->pos() - this->DragStartPosition).manhattanLength() >=
          QApplication::startDragDistance())
      {
        this->drag();
        return true;
      }
    }
    else if (event->type() == QEvent::DragEnter)
    {
      QDragEnterEvent* de = reinterpret_cast<QDragEnterEvent*>(event);
      this->dragEnter(de);
      return true;
    }
    else if (event->type() == QEvent::Drop)
    {
      QDropEvent* de = reinterpret_cast<QDropEvent*>(event);
      this->drop(de);
      return true;
    }
    return false;
}
void igwViewFrame::drag()
{
  vtksys::SystemInformation sysInfo;
  QPixmap pixmap(":/pqWidgets/Icons/pqWindow16.png");

  QMimeData* mimeData = new QMimeData;
  mimeData->setText(QString("application/paraview3/%1").arg(sysInfo.GetProcessId()));

  QPointer<QDrag> dragObj = new QDrag(this);
  dragObj->setMimeData(mimeData);
  dragObj->setHotSpot(QPoint(pixmap.width() / 2, pixmap.height() / 2));
  dragObj->setPixmap(pixmap);
  if (dragObj->exec() == Qt::MoveAction)
  {

    Q_EMIT this->finishDrag(this);
  }

}


void igwViewFrame::dragEnter(QDragEnterEvent* evt)
{
  vtksys::SystemInformation sysInfo;
  QString mimeType = QString("application/paraview3/%1").arg(sysInfo.GetProcessId());
  if (evt->source() != this && evt->mimeData()->hasText() && evt->mimeData()->text() == mimeType)
  {
    evt->acceptProposedAction();
  }
}


void igwViewFrame::drop(QDropEvent* evt)
{
  vtksys::SystemInformation sysInfo;
  igwViewFrame* source = qobject_cast<igwViewFrame*>(evt->source());
  QString mimeType = QString("application/paraview3/%1").arg(sysInfo.GetProcessId());
  if (source && source != this && evt->mimeData()->hasText() && evt->mimeData()->text() == mimeType)
  {
    this->connect(source, SIGNAL(finishDrag(igwViewFrame*)), SLOT(finishedDrag(igwViewFrame*)));
    evt->acceptProposedAction();
  }
}

igwViewFrame::~igwViewFrame()
{
    delete ui;
}

#include "igwRenderViewSelectionReaction.h"

#include "../Components/igwActiveObjects.h"
#include "vtkObject.h"
#include "vtkWeakPointer.h"
#include "vtkCommand.h"
#include "vtkRenderWindowInteractor.h"

QPointer<igwRenderViewSelectionReaction> igwRenderViewSelectionReaction::ActiveReaction;

igwRenderViewSelectionReaction::igwRenderViewSelectionReaction(
        QAction* parentAction, igwRenderView* view, SelectionMode mode)
    :SuperClass(parentAction),
    View(view),
    Mode(mode),
    ZoomCursor(QCursor(QPixmap((const char**)zoom_xpm)))
{

    QObject::connect(parentAction, SIGNAL(triggered(bool)), this, SLOT(actionTriggered(bool)));

    for (size_t i = 0; i < sizeof(this->ObserverIds) / sizeof(this->ObserverIds[0]); ++i)
    {
        this->ObserverIds[i] = 0;
    }
    // 追踪当前激活的View
    if(view == nullptr)
    {

        igwActiveObjects* activeObjects = &igwActiveObjects::GetInstance();

        QObject::connect(activeObjects, SIGNAL(viewChanged(igwRenderView*)), this, SLOT(setView(igwRenderView*)));
        this->setView(activeObjects->GetActiveView());
    }
}

igwRenderViewSelectionReaction::~igwRenderViewSelectionReaction()
{
    this->ClearupObservers();
}

void igwRenderViewSelectionReaction::actionTriggered(bool val)
{

    QAction* actn = this->parentAction();
    if (actn->isCheckable())
    {
      if (val)
      {

        this->beginSelection();
      }
      else
      {
        this->endSelection();
      }
    }
    else
    {
      this->beginSelection();
      this->endSelection();
    }
}

//void igwRenderViewSelectionReaction::updateEnableState()
//{

//}

void igwRenderViewSelectionReaction::setView(igwRenderView *view)
{
    if(this->View != view)
    {
        this->endSelection();
    }
    this->View = view;
    this->parentAction()->setEnabled(this->View != nullptr);
}

void igwRenderViewSelectionReaction::beginSelection()
{

    if(this->View == nullptr)
    {
        return;
    }

    if(igwRenderViewSelectionReaction::ActiveReaction == this)
    {
        return ;
    }

    igwRenderViewSelectionReaction::ActiveReaction = this;

    switch (this->Mode) {
    case SelectionMode::SELECT_SURFACE_CELLS:

        break;
    case SelectionMode::ZOOM_TO_BOX:
//        this->View->

        this->View->SetInteractorMode(igwRenderView::InteractionModes::INTERACTION_MODE_ZOOM);
    default:
        break;
    }

    switch (this->Mode) {
    case SelectionMode::ZOOM_TO_BOX:
          this->ObservedObject = this->View->GetInteractor();
          this->ObserverIds[0] = this->ObservedObject->AddObserver(
            vtkCommand::LeftButtonReleaseEvent, this, &igwRenderViewSelectionReaction::SelectionChanged);
          break;
    default:
        break;
    }

    this->parentAction()->setChecked(true);
}

void igwRenderViewSelectionReaction::endSelection()
{
    if(this->View == nullptr)
    {
        return ;
    }

    if (igwRenderViewSelectionReaction::ActiveReaction != this )
    {
      return;
    }

    igwRenderViewSelectionReaction::ActiveReaction = nullptr;

    //重置交互方式
    this->View->SetInteractorMode(igwRenderView::InteractionModes::INTERACTION_MODE_3D);

    this->ClearupObservers();
    this->parentAction()->setChecked(false);


}

void igwRenderViewSelectionReaction::SelectionChanged(vtkObject *, unsigned long, void *callData)
{

    if (igwRenderViewSelectionReaction::ActiveReaction != this)
    {

      return;
    }

    switch (this->Mode) {

    // Waiting for Implement....
    case SelectionMode::ZOOM_TO_BOX:

        break;
    default:
        break;
    }
    this->endSelection();
}

void igwRenderViewSelectionReaction::ClearupObservers()
{
    for (size_t i = 0; i < sizeof(this->ObserverIds) / sizeof(this->ObserverIds[0]); ++i)
    {
        if(this->ObservedObject != nullptr && this->ObserverIds[i] > 0)
        {
            this->ObservedObject->RemoveObserver(this->ObserverIds[i]);
        }
        this->ObserverIds[i] = 0;
    }
    this->ObservedObject = nullptr;
}

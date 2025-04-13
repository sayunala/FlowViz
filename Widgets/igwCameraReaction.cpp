#include "igwCameraReaction.h"
#include "Representation/igwRenderView.h"
#include "../Components/igwActiveObjects.h"
igwCameraReaction::igwCameraReaction(QAction* parent, Mode mode)
    :SupperClass(parent), ReactionMode(mode)
{

}

igwCameraReaction::~igwCameraReaction()
{

}

void igwCameraReaction::ResetCamera()
{
    igwRenderView* view = igwActiveObjects::GetInstance().GetActiveView();
    if(view)
    {
        view->ResetCamera();
    }
}

void igwCameraReaction::ResetPositiveX()
{
    igwRenderView* view = igwActiveObjects::GetInstance().GetActiveView();
    if(view)
    {
        view->ResetViewDirectionToPositiveX();
    }
}

void igwCameraReaction::ResetPositiveY()
{
    igwRenderView* view = igwActiveObjects::GetInstance().GetActiveView();
    if(view)
    {
        view->ResetViewDirectionToPositiveY();
    }
}

void igwCameraReaction::ResetPositiveZ()
{
    igwRenderView* view = igwActiveObjects::GetInstance().GetActiveView();
    if(view)
    {
        view->ResetViewDirectionToPositiveZ();
    }
}

void igwCameraReaction::ResetNegativeX()
{
    igwRenderView* view = igwActiveObjects::GetInstance().GetActiveView();
    if(view)
    {
        view->ResetViewDirectionToNegativeX();
    }
    std::cout << "Pos x" << std::endl;
}

void igwCameraReaction::ResetNegativeY()
{
    igwRenderView* view = igwActiveObjects::GetInstance().GetActiveView();
    if(view)
    {
        view->ResetViewDirectionToNegativeY();
    }
}

void igwCameraReaction::ResetNegativeZ()
{
    igwRenderView* view = igwActiveObjects::GetInstance().GetActiveView();
    if(view)
    {
        view->ResetViewDirectionToNegativeZ();
    }
}

void igwCameraReaction::ZoomInCamera()
{
    igwRenderView* view = igwActiveObjects::GetInstance().GetActiveView();
    if(view)
    {
        view->ZoomIn();
    }
}

void igwCameraReaction::ZoomOutCamera()
{
    igwRenderView* view = igwActiveObjects::GetInstance().GetActiveView();
    if(view)
    {
        view->ZoomOut();
    }

}

void igwCameraReaction::RotateCameraClockWise()
{
    igwRenderView* view = igwActiveObjects::GetInstance().GetActiveView();
    view->AdjustRoll(90);
}

void igwCameraReaction::RotateCameraCounterClock()
{
    igwRenderView* view = igwActiveObjects::GetInstance().GetActiveView();
    view->AdjustRoll(-90);
}

void igwCameraReaction::ShowAxes(bool value)
{
    igwRenderView* view = igwActiveObjects::GetInstance().GetActiveView();
    view->ShowAxes(value);
}

void igwCameraReaction::onTriggered(bool value)
{
    switch (this->ReactionMode) {

    case Mode::RESET_CAMERA:
        this->ResetCamera();
        break;

    case Mode::RESET_POSITIVE_X:
        this->ResetPositiveX();
        break;

    case Mode::RESET_POSITIVE_Y:
        this->ResetPositiveY();
        break;

    case Mode::RESET_POSITIVE_Z:
        this->ResetPositiveZ();
        break;

    case Mode::RESET_NEGATIVE_X:
        this->ResetNegativeX();
        break;

    case Mode::RESET_NEGATIVE_Y:
        this->ResetNegativeY();
        break;

    case Mode::RESET_NEGATIVE_Z:
        this->ResetNegativeZ();
        break;

    case Mode::ZOOM_IN_CAMERA:
        this->ZoomInCamera();
        break;

    case Mode::ZOOM_OUT_CAMERA:
        this->ZoomOutCamera();
        break;

    case Mode::ROTATE_CAMERA_CLOCK:
        this->RotateCameraClockWise();
        break;

    case Mode::ROTATE_CAMERA_CORNTERCLOCK:
        this->RotateCameraCounterClock();
        break;

    case Mode::SHOW_AXES:

        this->ShowAxes(value);

        break;
    }

}

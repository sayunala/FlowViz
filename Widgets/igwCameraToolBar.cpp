#include "igwCameraToolBar.h"
#include "ui_igwCameraToolBar.h"

#include "igwCameraReaction.h"
#include "igwSelectionReaction.h""
#include "igwRenderViewSelectionReaction.h"
#include "../Components/igwActiveObjects.h"
#include "igwSaveScreenShotReaction.h"
igwCameraToolBar::igwCameraToolBar(QWidget *parent) :
    QToolBar(parent),
    ui(new Ui::igwCameraToolBar)
{
    ui->setupUi(this);

    new igwCameraReaction(ui->actionPositiveX, igwCameraReaction::Mode::RESET_POSITIVE_X);
    new igwCameraReaction(ui->actionNegativeX, igwCameraReaction::Mode::RESET_NEGATIVE_X);
    new igwCameraReaction(ui->actionPositiveY, igwCameraReaction::Mode::RESET_POSITIVE_Y);
    new igwCameraReaction(ui->actionNegativeY, igwCameraReaction::Mode::RESET_NEGATIVE_Y);
    new igwCameraReaction(ui->actionPositiveZ, igwCameraReaction::Mode::RESET_POSITIVE_Z);
    new igwCameraReaction(ui->actionNegativeZ, igwCameraReaction::Mode::RESET_NEGATIVE_Z);
    new igwCameraReaction(ui->actionCameraZoomin, igwCameraReaction::Mode::ZOOM_IN_CAMERA);
    new igwCameraReaction(ui->actionCameraZoomOut, igwCameraReaction::Mode::ZOOM_OUT_CAMERA);
    new igwCameraReaction(ui->actionResetCamera, igwCameraReaction::Mode::RESET_CAMERA);
    new igwCameraReaction(ui->actionRotateCameraClock, igwCameraReaction::Mode::ROTATE_CAMERA_CLOCK);
    new igwCameraReaction(ui->actionRotateCamreaCounterClock, igwCameraReaction::Mode::ROTATE_CAMERA_CORNTERCLOCK);
    new igwCameraReaction(ui->actionShowAxes, igwCameraReaction::Mode::SHOW_AXES);

    new igwRenderViewSelectionReaction(
        ui->actionZoomToBox, igwActiveObjects::GetInstance().GetActiveView(), igwRenderViewSelectionReaction::SelectionMode::ZOOM_TO_BOX);
    new igwSaveScreenShotReaction(ui->actionSaveScreenShot, false);
    new igwSaveScreenShotReaction(ui->actionScreenShot, true);

}

igwCameraToolBar::~igwCameraToolBar()
{
    delete ui;
}

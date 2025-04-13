#ifndef IGWCAMERAREACTION_H
#define IGWCAMERAREACTION_H

#include "igwReaction.h"

class igwCameraReaction : public igwReaction
{
    Q_OBJECT
    typedef igwReaction SupperClass;

public:
    enum class Mode{
        RESET_CAMERA,
        RESET_POSITIVE_X,
        RESET_POSITIVE_Y,
        RESET_POSITIVE_Z,
        RESET_NEGATIVE_X,
        RESET_NEGATIVE_Y,
        RESET_NEGATIVE_Z,
        ZOOM_IN_CAMERA,
        ZOOM_OUT_CAMERA,
        ROTATE_CAMERA_CLOCK,
        ROTATE_CAMERA_CORNTERCLOCK,
        SHOW_AXES
    };

    igwCameraReaction(QAction* parent, Mode mode);
    ~igwCameraReaction() override;

    static void ResetCamera();

    static void ResetPositiveX();
    static void ResetPositiveY();
    static void ResetPositiveZ();
    static void ResetNegativeX();
    static void ResetNegativeY();
    static void ResetNegativeZ();

    static void ZoomInCamera();
    static void ZoomOutCamera();

    /**
     * @brief RotateCameraClockWise
     */
    static void RotateCameraClockWise();
    static void RotateCameraCounterClock();

    static void ShowAxes(bool value);
protected:
    void onTriggered(bool value) override;


private:
    Q_DISABLE_COPY(igwCameraReaction);
    Mode ReactionMode;

};

#endif // IGWCAMERAREACTION_H

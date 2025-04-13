#include "igwVCRToolBar.h"
#include "ui_igwVCRToolBar.h"

#include "igwVCRControl.h"
#include "Core/igwApplicationCore.h"
#include "Components/igwAnimationManager.h"
igwVCRToolBar::igwVCRToolBar(QWidget *parent) :
    QToolBar(parent),
    ui(new Ui::igwVCRToolBar)
{
    ui->setupUi(this);

    igwVCRControl* controller = new igwVCRControl(this);
    this->Controller = controller;
    this->Controller->setAnimationScene(igwApplicationCore::GetInstance()->GetAnimationManager()->getScene());
    this->Controller->setIgwAnimationScene(igwApplicationCore::GetInstance()->GetAnimationManager()->getIgwScene());
    QObject::connect(ui->actionVCRPlay, SIGNAL(triggered()), controller, SLOT(onPlay()));
     QObject::connect(ui->actionVCRReverse, SIGNAL(triggered()), controller, SLOT(onReverse()));
     QObject::connect(ui->actionVCRFirstFrame, SIGNAL(triggered()), controller, SLOT(onFirstFrame()));
     QObject::connect(
       ui->actionVCRPreviousFrame, SIGNAL(triggered()), controller, SLOT(onPreviousFrame()));
     QObject::connect(ui->actionVCRNextFrame, SIGNAL(triggered()), controller, SLOT(onNextFrame()));
     QObject::connect(ui->actionVCRLastFrame, SIGNAL(triggered()), controller, SLOT(onLastFrame()));
     QObject::connect(ui->actionVCRLoop, SIGNAL(toggled(bool)), controller, SLOT(onLoop(bool)));

     QObject::connect(controller, SIGNAL(enabled(bool)), ui->actionVCRPlay, SLOT(setEnabled(bool)));
     QObject::connect(controller, SIGNAL(enabled(bool)), ui->actionVCRReverse, SLOT(setEnabled(bool)));
     QObject::connect(
       controller, SIGNAL(enabled(bool)), ui->actionVCRFirstFrame, SLOT(setEnabled(bool)));
     QObject::connect(
       controller, SIGNAL(enabled(bool)), ui->actionVCRPreviousFrame, SLOT(setEnabled(bool)));
     QObject::connect(
       controller, SIGNAL(enabled(bool)), ui->actionVCRNextFrame, SLOT(setEnabled(bool)));
     QObject::connect(
       controller, SIGNAL(enabled(bool)), ui->actionVCRLastFrame, SLOT(setEnabled(bool)));
     QObject::connect(controller, SIGNAL(enabled(bool)), ui->actionVCRLoop, SLOT(setEnabled(bool)));
     QObject::connect(
       controller, SIGNAL(timeRanges(double, double)), this, SLOT(setTimeRanges(double, double)));
     QObject::connect(controller, SIGNAL(loop(bool)), ui->actionVCRLoop, SLOT(setChecked(bool)));
     QObject::connect(controller, SIGNAL(playing(bool, bool)), this, SLOT(onPlaying(bool, bool)));
}

igwVCRToolBar::~igwVCRToolBar()
{
    delete ui;
}

void igwVCRToolBar::onPlaying(bool playing, bool reversed)
{
    QAction* const actn = reversed ? this->ui->actionVCRReverse : this->ui->actionVCRPlay;
     QString actnName = reversed ? tr("Reverse") : tr("Play");
     const char* slotFn = reversed ? SLOT(onReverse()) : SLOT(onPlay());

     // goal of action depends on context. ex: play/reverse vs pause
     if (playing)
     {
       // remap the signals to controller
       disconnect(actn, SIGNAL(triggered()), this->Controller, slotFn);
       connect(actn, SIGNAL(triggered()), this->Controller, SLOT(onPause()));
       actn->setIcon(QIcon(":/igwWidgets/Icons/Widgets/Resources/Icons/igwVcrPause.svg"));
       actn->setText(tr("Pa&use"));
     }
     else
     {
       // remap the signals to controller
       connect(actn, SIGNAL(triggered()), this->Controller, slotFn);
       disconnect(actn, SIGNAL(triggered()), this->Controller, SLOT(onPause()));
       actn->setIcon(QIcon(QString(":/igwWidgets/Icons/Widgets/Resources/Icons/igwVcr%1.svg").arg(actnName)));
       actn->setText(QString("&%1").arg(actnName));
     }

}

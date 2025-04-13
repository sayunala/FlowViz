#include "igwAnimationTimeToolBar.h"


#include "Components/igwAnimationTimeWidget.h"
#include "Core/igwApplicationCore.h"
#include "Components/igwAnimationManager.h"
igwAnimationTimeWidget *igwAnimationTimeToolBar::animationTImeWidget() const
{
    return this->AnimationTimeWidget;
}

void igwAnimationTimeToolBar::constructor()
{
    this->setWindowTitle("时间控制");
    this->AnimationTimeWidget = new igwAnimationTimeWidget(this);
    this->addWidget(this->AnimationTimeWidget);
    this->AnimationTimeWidget->setAnimationScene(igwApplicationCore::GetInstance()->GetAnimationManager()->getIgwScene());
//    this->connect(igwApplicationCore::GetInstance()->GetAnimationManager(), SLOT(activ))
}

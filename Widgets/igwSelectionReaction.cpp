#include "igwSelectionReaction.h"
#include <QActionGroup>

igwSelectionReaction::igwSelectionReaction(QAction* parent, QActionGroup* modifierGroup)
    :igwReaction(parent), ModifierGroup(modifierGroup)
{
    if(modifierGroup)
    {
        QObject::connect(modifierGroup, SIGNAL(triggered(QAction*)), this, SLOT(modifiersChanged()));
    }
}

int igwSelectionReaction::getSelectionModifier()
{
  if (this->ModifierGroup)
  {

    Q_FOREACH (QAction* maction, this->ModifierGroup->actions())
    {
      if (maction->isChecked() && maction->data().isValid())
      {
        return maction->data().toInt();
      }
    }
  }
  return 0;
}

void igwSelectionReaction::uncheckSelectionModifiers()
{
  if (this->ModifierGroup)
  {
    Q_FOREACH (QAction* act, this->ModifierGroup->actions())
    {
      act->setChecked(false);
    }
  }
}

void igwSelectionReaction::disableSelectionModifiers(bool disable)
{
  if (this->ModifierGroup)
  {
    this->ModifierGroup->setEnabled(!disable);
    if (disable)
    {
      this->uncheckSelectionModifiers();
    }
  }
}

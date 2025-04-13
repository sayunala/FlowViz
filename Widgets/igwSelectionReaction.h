#ifndef IGWSELECTIONREACTION_H
#define IGWSELECTIONREACTION_H

#include "igwReaction.h"
#include <QPointer>
#include <QAction>
class igwSelectionReaction : public igwReaction
{

    Q_OBJECT

public:
    igwSelectionReaction(QAction* parent, QActionGroup* modiferGroup = nullptr);

protected Q_SLOTS:
  /**
   * called when modifier group is changed.
   */
  virtual void modifiersChanged() {}

protected: // NOLINT(readability-redundant-access-specifiers)
  /**
   * Get the current state of selection modifier, if any
   */
  virtual int getSelectionModifier();

  /**
   * Uncheck selection modifiers, if any
   */
  virtual void uncheckSelectionModifiers();

  /**
   * Disable/Enable selection modifiers, if any
   */
  virtual void disableSelectionModifiers(bool disable);

  QPointer<QActionGroup> ModifierGroup;

private:
  Q_DISABLE_COPY(igwSelectionReaction)
};

#endif // IGWSELECTIONREACTION_H

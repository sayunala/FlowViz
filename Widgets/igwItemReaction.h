#ifndef IGWITEMREACTION_H
#define IGWITEMREACTION_H

#include <QObject>

#include "igwReaction.h"


class igwItemReaction : public igwReaction
{
    Q_OBJECT
    typedef igwReaction SupperClass;

public:
    enum class Mode{
        DELETE_ITEM,
        SHOW_SETTING_WIDGET,
        HIDE_ITEM,
        CHANGE_ITEM_COLOR
    };

    igwItemReaction(QAction* parent, Mode mode);
    ~igwItemReaction() override;

    static void DeleteItem();

    static void ShowSettingWidget();

    static void HideItem();

    static void ChangeItemColor();

protected:
    void onTriggered(bool value) override;


private:
    Q_DISABLE_COPY(igwItemReaction);
    Mode ReactionMode;

};


#endif // IGWITEMREACTION_H

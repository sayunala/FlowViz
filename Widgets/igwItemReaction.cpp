#include "igwItemReaction.h"

igwItemReaction::igwItemReaction(QAction* parent, Mode mode)
{

}
igwItemReaction::~igwItemReaction(){}
void igwItemReaction::DeleteItem()
{

}

void igwItemReaction::ShowSettingWidget()
{

}

void igwItemReaction::HideItem()
{

}

void igwItemReaction::ChangeItemColor()
{

}


void igwItemReaction::onTriggered(bool value)
{
    switch (this->ReactionMode) {

    case Mode::DELETE_ITEM:
        this->DeleteItem();
        break;

    case Mode::SHOW_SETTING_WIDGET:
        this->ShowSettingWidget();
        break;

    case Mode::HIDE_ITEM:
        this->HideItem();
        break;

    case Mode::CHANGE_ITEM_COLOR:
        this->ChangeItemColor();
        break;
    }

}

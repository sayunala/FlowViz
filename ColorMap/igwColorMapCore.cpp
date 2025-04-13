#include "igwColorMapCore.h"

#include <QJsonDocument>
#include <QFile>
igwColorMapCore* igwColorMapCore::Instance = nullptr;
igwColorMapCore::igwColorMapCore(QObject *parent) : QObject(parent)
{
    QFile file(":/Color/ColorMap/ColorManager/pqPresetGroups.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QJsonParseError error;
//        QJsonDocument document = QJsonDocument::fromJson(file.readAll(), &error);
    GroupManager = new igwPresetGroupsManager(this);
    GroupManager->loadGroups(file.readAll());
    file.close();
}

igwColorMapCore *igwColorMapCore::GetInstance()
{
    if(igwColorMapCore::Instance == nullptr)
        igwColorMapCore::Instance = new igwColorMapCore();
    return igwColorMapCore::Instance;
}

igwColorMapCore::~igwColorMapCore(){
    delete GroupManager;
    delete igwColorMapCore::Instance;
}

igwPresetGroupsManager *igwColorMapCore::GetGroupManager(){

    return GroupManager;
}

#ifndef IGWCOLORMAPCORE_H
#define IGWCOLORMAPCORE_H
/**********************************************
* @projectName   iGreatWorks
* @file          igwColorMapCore.h
* @brief         igwColorMapCore是颜色编辑的核心，创建了igwPresetGroupsManager实例对象，
*                使用igwColorMapCore::GetInstance()获取igwColorMapCore，且不能创建
*                igwColorMapCore对象
* @author        ZYB
* @date          2023-09-23
* @version       1.0
**********************************************/


#include <QObject>
#include "igwPresetGroupsManager.h"

class igwColorMapCore : public QObject
{
    Q_OBJECT
public:
    explicit igwColorMapCore(QObject *parent = nullptr);
    static igwColorMapCore* GetInstance();
    ~igwColorMapCore();
    /**
     * @brief GetGroupManager
     * @return igwPresetGroupsManager对象，用于获取预设颜色的分组管理类
     */
    igwPresetGroupsManager* GetGroupManager();

signals:

public slots:
private:
    static igwColorMapCore* Instance;
    igwPresetGroupsManager* GroupManager;//预设颜色分组管理类的实例对象

};

#endif // IGWCOLORMAPCORE_H

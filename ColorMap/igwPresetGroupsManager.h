
/**********************************************
* @projectName   IGreatWorks
* @file          igwPresetGroupsManager.h
* @brief         是一个用于管理igwPresetDialog 中显示的彩色映射预设组的对象。
*                igwPresetGroupsManager 由 igwColorMapCore 创建并注册为管理器。
* @author        ZYB
* @date          2023-09-23
* @version       1.0
**********************************************/

#ifndef igwPresetGroupsManager_h
#define igwPresetGroupsManager_h



#include <QList>
#include <QMap>
#include <QObject>

/**
 * igwPresetGroupsManager is an object to manage the groups of color map
 * presets displayed in the pqPresetDialog.  A igwPresetGroupsManager is
 * created by the igwColorMapCore .
 *
 * The group manager loads the groups of presets from a json file with this format:
 * @code{json}
 * [
 *   {
 *     "groupName": "default",
 *     "presets": [
 *       "Cool to Warm",
 *       "Cool to Warm (Extended)",
 *       "Black-Body Radiation",
 *       "X Ray",
 *       "Inferno (matplotlib)",
 *       "Black, Blue and White",
 *       "Blue Orange (divergent)",
 *       "Viridis (matplotlib)",
 *       "Gray and Red",
 *       "Linear Green (Gr4L)",
 *       "Cold and Hot",
 *       "Blue - Green - Orange",
 *       "Rainbow Desaturated",
 *       "Yellow - Gray - Blue",
 *       "Rainbow Uniform",
 *       "jet"
 *     ]
 *   },
 *   {
 *     "groupName": "myTestGroup",
 *     "presets": [
 *       "Reds",
 *       "Blues",
 *       "Greens",
 *       "Oranges",
 *       "Br0rYl",
 *       "erdc_blue2yellow"
 *     ]
 *   }
 * ]
 * @endcode
 */
class igwPresetGroupsManager : public QObject
{
  Q_OBJECT
  typedef QObject Superclass;

public:
  /**
   * Create a new groups manager.  Custom applications should use the one created
   */
    /**
   * @brief igwPresetGroupsManager 构造函数，只能被igwColorMapCore创建一个
   * @param p
   */
  igwPresetGroupsManager(QObject* p);
  ~igwPresetGroupsManager() override;

  /**
   * Returns the number of groups the manager knows of.
   */
  /**
   * @brief 返回manager知道的组的数量。
   * @return
   */
  int numberOfGroups();
  /**
   * Returns the number of presets in the given group.
   */
  /**
   * @brief numberOfPresetsInGroup 返回给定组的预设数量
   * @param groupName
   * @return
   */
  int numberOfPresetsInGroup(const QString& groupName);

  /**
   * Returns the rank (index) of the given preset in the given group.
   * Returns -1 if the preset is not in the group (the preset dialog relies on this).
   */
  /**
   * @brief presetRankInGroup 返回给定预设在给定组中的下标（index）
   * @param presetName
   * @param groupName
   * @return
   */
  int presetRankInGroup(const QString& presetName, const QString& groupName);

  /**
   * Returns a list of the group names the manager knows of.
   */
  /**
   * @brief groupNames 返回所有manager知道的名字。
   * @return
   */
  QList<QString> groupNames();

  /**
   * Returns the name of the ith group in the manager's list of groups.
   */
  /**
   * @brief groupName 返回所有分组中第i个分组的name
   * @param i
   * @return
   */
  QString groupName(int i);

  /**
   * Load groups from the given JSON string (for the format see the class
   * documentation) and add the groups to the groups in the manager.  This
   * is an append operation so the groups already in the manager will not be removed.
   * If the json string has a group with the same name as one already in the
   * manager, then the color maps in that group will be appended to the existing group.
   */
  /**
   * @brief loadGroups 从json字符串中载入所有分组组
   * @param json
   */
  void loadGroups(const QString& json);

  /**
   * Clears all groups in the manager and then loads groups from the given JSON string
   * (see loadGroups).  This is an override operation instead of the append provided by
   * loadGroups.
   */
  /**
   * @brief 将所有分组替换为json 字符串中的分组
   * @param json
   */
  void replaceGroups(const QString& json);

  /**
   * Load the groups from the settings
   * Return true if loading was successful
   */
  /**
   * @brief loadGroupsFromSettings 从设置中载入分组 待实现
   * @return
   */
  bool loadGroupsFromSettings();

  /**
   * Adds a preset to a group.
   * Creates the group if it does not exist
   */
  /**
   * @brief 给一个组中增加一个预设
   * @param groupName
   * @param presetName
   */
  void addToGroup(const QString& groupName, const QString& presetName);

  /**
   * Removes a preset from a group.
   */
  /**
   * @brief removeFromGroup 从一个分组中移除一个预设
   * @param groupName
   * @param presetName
   */
  void removeFromGroup(const QString& groupName, const QString& presetName);

  /**
   * Removes a preset from all groups.
   */
  /**
   * @brief removeFromAllGroups 从所有分组中移除一个预设
   * @param presetName
   */
  void removeFromAllGroups(const QString& presetName);

public Q_SLOTS: // NOLINT(readability-redundant-access-specifiers)
  /**
   * Save groups to settings
   */
  //void saveGroupsToSettings();

Q_SIGNALS:
  /**
   * Fired whenever loadGroups or replaceGroups is called and new group information
   * is available.
   */
  /**
   * @brief groupsUpdated 当loadGroups 和 replaceGroups 被调用时触发该信号
   */
  void groupsUpdated();

private:
  QList<QString> GroupNames;
  QMap<QString, QList<QString>> Groups;

  /**
   * Clears all groups the manager knows.
  /**
   * @brief clearGroups 清除manger 拥有的所有组
   */
  void clearGroups();
};

#endif

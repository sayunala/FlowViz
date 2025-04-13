
#ifndef igwPresetDialog_h
#define igwPresetDialog_h

/**********************************************
* @projectName   IGreatWorks
* @file          igwPresetDialog.h
* @brief         修改自ParaView源码，主要用于实现颜色选取的对话框，同时提供预设颜色的导入与导出
* @author        ZYB
* @date          2023-09-23
* @version       1.0
**********************************************/

#include <QDialog>
#include <QModelIndex>
#include <QScopedPointer>    // for QScopedPointer
#include <vtk_jsoncpp_fwd.h> // for forward declarations

class QModelIndex;

/**
 * igwPresetDialog is the dialog used by to show the user with a choice of color
 * maps/opacity maps/presets to choose from. The Dialog can be customized to
 * show only indexed (or non-indexed) color maps using igwPresetDialog::Modes.
 * Application code should observe the igwPresetDialog::applyPreset() signal to
 * perform the applying of the preset to a specific transfer function proxy.
 * This class works with vtkSMTransferFunctionPresets, which acts as the preset
 * manager for the application with support to inspect existing presets as well
 * as updating them.
 */
class igwPresetDialog : public QDialog
{
  Q_OBJECT
  typedef QDialog Superclass;

public:
  /**
   * Used to control what kinds of presets are shown in the dialog.
   * This merely affects the presets that are hidden from the view.
   */
  enum Modes
  {
    SHOW_ALL,
    SHOW_INDEXED_COLORS_ONLY,
    SHOW_NON_INDEXED_COLORS_ONLY
  };

  igwPresetDialog(QWidget* parent = nullptr, Modes mode = SHOW_ALL);
  ~igwPresetDialog() override;

  /**
   * Set the current mode (which type of presets are displayed)
   */
  /**
   * @brief 设置那种类型的预设需要被显示
   * @param mode = SHOW_ALL/SHOW_INDEXED_COLORS_ONLY/SHOW_NON_INDEXED_COLORS_ONLY
   */
  void setMode(Modes mode);

  /**
   * Set the current preset using its name.
   */
  /**
   * @brief 使用name设置当前预置颜色
   * @param presetName
   */
  void setCurrentPreset(const char* presetName);

  /**
   * Return current preset, if any.
   */
  /**
   * @brief currentPreset 返回当前的预置的json格式
   * @return
   */
  const Json::Value& currentPreset();

  /**
   * Returns true if the user requested to load colors for the current preset.
   */
  /**
   * @brief 如果用户要求载入当前预设的颜色，则返回 true。
   * @return
   */
  bool loadColors() const;

  /**
   * Returns true if the user requested to load opacities for the current
   * preset.
   */
  /**
   * @brief 如果用户要求加载当前预设的不透明度，则返回 true。 预设的不透明度，则返回 true。
   * @return
   */
  bool loadOpacities() const;

  /**
   * Returns true if the user requested to load annotations for the current
   * preset.
   */
  bool loadAnnotations() const;

  /**
   * Returns the specified regularExpression.
   */
  QRegularExpression regularExpression();

  /**
   * Returns true if the user requested to preserve/use the preset data range.
   * If false, the user is expecting the current transfer function range to be
   * maintained.
   */
  bool usePresetRange() const;

  /**
   * Set when user can choose to load colors along with the default state.
   */
  /**
   * @brief setCustomizableLoadColors 设置用户何时可以选择在默认状态下加载颜色。
   * @param state
   * @param defaultValue
   */
  void setCustomizableLoadColors(bool state, bool defaultValue = true);

  /**
   * Set when user can choose to load annotations along with the default state.
   */
  void setCustomizableLoadAnnotations(bool state, bool defaultValue = true);

  /**
   * Set when user can choose a regexp to load annotations along with the default state.
   */

  void setCustomizableAnnotationsRegexp(bool state, bool defaultValue = false);

  /**
   * Set when user can choose to load opacities along with the default state.
   */
  void setCustomizableLoadOpacities(bool state, bool defaultValue = true);

  /**
   * Set when user can choose to load usePresetRange along with the default state.
   */
  void setCustomizableUsePresetRange(bool state, bool defaultValue = false);

Q_SIGNALS:
  void applyPreset(const Json::Value& preset);

protected Q_SLOTS:
  void updateEnabledStateForSelection();
  void updateForSelectedIndex(const QModelIndex& proxyIndex);
  void triggerApply(const QModelIndex& proxyIndex = QModelIndex());
  void removePreset(const QModelIndex& idx = QModelIndex());
  /**
   * @brief importPresets 导入预设颜色的槽函数，导入指定格式的颜色到表格中
   *
   */
  void importPresets();
  /**
   * @brief exportPresets 导出预设颜色的槽函数，将颜色导出为json格式
   */
  void exportPresets();

  void setPresetIsAdvanced(int newState);
public Q_SLOTS:
  void ResetTable();
private Q_SLOTS:
//  void updateGroups();
//  void updateFiltering();


private: // NOLINT(readability-redundant-access-specifiers)
  Q_DISABLE_COPY(igwPresetDialog)
  class pqInternals;
  const QScopedPointer<pqInternals> Internals;
};

#endif

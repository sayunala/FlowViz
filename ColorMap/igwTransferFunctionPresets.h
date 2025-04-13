
/**
 * @class   igwTransferFunctionPresets
 * @brief   管理颜色，透明度预设的类
 * igwTransferFunctionPresets 是管颜色、透明度预设的管理器，包括内置颜色，和用户颜色
 * igwTransferFunctionPresets 设计为单例模式, 可以通过`GetInstance()` 静态函数获得
 * 公有 API。修改自ParaView源码
*/
#ifndef igwTransferFunctionPresets_h
#define igwTransferFunctionPresets_h

#include "vtkObject.h"


#include "vtkSmartPointer.h"        // for ivars
#include <vector>                   // for vector
#include <vtk_jsoncpp_fwd.h>        // for forward declarations

class vtkPVXMLElement;
class  igwTransferFunctionPresets : public vtkObject
{
public:
  // Used to return information about the imported presets to the caller of ImportPresets
  struct ImportedPreset
  {
    std::string name;
    struct
    {
      bool isValid = false;
      std::vector<std::string> groups;
    } potentialGroups;
  };

  static igwTransferFunctionPresets* New();
  vtkTypeMacro(igwTransferFunctionPresets, vtkObject);
  void PrintSelf(ostream& os, vtkIndent indent) override;

  /**
   * Get singleton instance.
   */
  static igwTransferFunctionPresets* GetInstance();

  /**
   * Returns the number of presets current available (including builtin and
   * custom).
   */
  /**
   * @brief GetNumberOfPresets 获取可以使用的预置数量。
   * @return
   */
  unsigned int GetNumberOfPresets();

  /**
   * Gets the raw text for a preset given its index. The preset is provided as a JSON string.
   * Returns an empty string when not available.
   */
  /**
   * @brief GetPresetAsString 获取预设的原始json字符串
   * @param index
   * @return
   */
  std::string GetPresetAsString(unsigned int index);

  /**
   * Add a new preset. If name provided already exists, this will override the
   * existing preset (even for builtin presets).
   * \c preset must be a valid JSON string. If not, this will return failure.
   */
  /**
   * @brief AddPreset 增加新的预设，新预设将覆盖同名预设，提供的preset必须是有效的json字符串
   * @param name
   * @param preset
   * @return
   */
  bool AddPreset(const char* name, const std::string& preset);

  /**
   * Remove a preset. This has no effect for builtin presets.
   */
  /**
   * @brief RemovePreset 移除用户预设
   * @param index
   * @return
   */
  bool RemovePreset(unsigned int index);

  ///@{
  /**
   * Returns a preset JSON given the name. Since multiple presets can have the
   * same name, this returns the 'first' preset with the specified name.
   * idx is set to the index of the found preset,-1 if none.
   */
  /**
   * @brief GetFirstPresetWithName 返回给定 name 的第一个预设格式为，JSON对象.
   * 如果有同名则返回第一个preset，idx是该preset在所有preset中的下标(索引)
   * @param name
   * @param idx
   * @return
   */
  const Json::Value& GetFirstPresetWithName(const char* name, int& idx);
  const Json::Value& GetFirstPresetWithName(const char* name);
  ///@}

  /**
   * Returns a preset at a given index.
   */
  /**
   * @brief GetPreset 获取给定索引(下标)的预设，格式为 JSON对象格式
   * @param index
   * @return
   */
  const Json::Value& GetPreset(unsigned int index);

  /**
   * Returns the name for a preset at the given index.
   */
  /**
   * @brief GetPresetName 返回给定索引(下标)的预设name
   * @param index
   * @return
   */
  std::string GetPresetName(unsigned int index);

  /**
   * Returns true if a present with given name exists.
   */
  /**
   * @brief HasPreset 给定预设名，判断该预设是否存在
   * @param name
   * @return
   */
  bool HasPreset(const char* name);

  /**
   * Returns true if the preset has opacities i.e. values for a piecewise function.
   */
  bool GetPresetHasOpacities(const Json::Value& preset);
  bool GetPresetHasOpacities(unsigned int index)
  {
    return this->GetPresetHasOpacities(this->GetPreset(index));
  }

  /**
   * Returns true is the preset has indexed colors.
   */
  bool GetPresetHasIndexedColors(const Json::Value& preset);
  bool GetPresetHasIndexedColors(unsigned int index)
  {
    return this->GetPresetHasIndexedColors(this->GetPreset(index));
  }

  /**
   * Returns true is the preset has annotations.
   */
  bool GetPresetHasAnnotations(const Json::Value& preset);
  bool GetPresetHasAnnotations(unsigned int index)
  {
    return this->GetPresetHasAnnotations(this->GetPreset(index));
  }

  /**
   * Set the Json::Value object for preset 'name' if such a preset was found in the custom presets.
   * Return true if preset was correctly set, false otherwise.
   */
  /**
   * @brief SetPreset 如果在在定义预设中找到name的预设，将预设设置为参数提供的preset
   * @param name
   * @param preset
   * @return
   */
  bool SetPreset(const char* name, const Json::Value& preset);

  /**
   * Add a preset give the Json::Value object.
   */
  /**
   * @brief AddPreset 使用 Json::Value对象增加一个新的预设
   * @param name preset的name
   * @param preset 的预设
   * @return
   */
  bool AddPreset(const char* name, const Json::Value& preset);

  /**
   * Same as AddPreset() expect it create a unique name using the prefix
   * provided. If no prefix is specified, "Preset" will be used as the prefix.
   */
  /**
   * @brief AddUniquePreset 类似AddPreset(),只是该函数保证新增的预设的名字并不重复
   * @param preset 预设的Json::Value表达
   * @param prefix 预设名
   * @return
   */
  std::string AddUniquePreset(const Json::Value& preset, const char* prefix = nullptr);

  /**
   * Returns true if the preset is a builtin preset.
   * The preset is identified by its index.
   */
  /**
   * @brief IsPresetBuiltin 判断一个预设是否为内置类型
   * @param index
   * @return
   */
  bool IsPresetBuiltin(unsigned int index);

  /**
   * Rename a preset.
   */
  bool RenamePreset(unsigned int index, const char* newname);

  ///@{
  /**
   * Load presets from a file. All presets are added to "custom" presets list
   * and are considered as non-builtin.
   */
  /**
   * @brief ImportPresets * 从文件中加载预设色彩。所有预设都会添加到 "自定义 "预设列表中，
   * 并被视为非内置预设。
   * @param filename
   * @return
   */
  bool ImportPresets(const char* filename);
  bool ImportPresets(const char* filename, std::vector<ImportedPreset>* importedPresets);
  bool ImportPresets(const Json::Value& presets);
  bool ImportPresets(const Json::Value& presets, std::vector<ImportedPreset>* importedPresets);
  ///@}

  /**
   * Reload the presets from the configuration file.
   */
  void ReloadPresets();

protected:
  igwTransferFunctionPresets();
  ~igwTransferFunctionPresets() override;

private:
  igwTransferFunctionPresets(const igwTransferFunctionPresets&) = delete;
  void operator=(const igwTransferFunctionPresets&) = delete;

  class vtkInternals;
  vtkInternals* Internals;

  static vtkSmartPointer<igwTransferFunctionPresets> Instance;
};

#endif

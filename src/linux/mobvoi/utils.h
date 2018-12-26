// Copyright 2018 Mobvoi Inc. All Rights Reserved.

#ifndef LINUX_INTERFACE_UTILS_H_
#define LINUX_INTERFACE_UTILS_H_

#include <map>
#include <set>
#include <string>

namespace mobvoi {
namespace sdk {

class Utils {
 public:
  typedef std::map<std::string, std::set<std::string>> PinyinTable;

  /**
   * 设置联系人列表，生成对应的模糊匹配拼音映射表
   *
   * @param contact_list 联系人姓名列表。
   *
   * @return 对应的拼音映射表。
   */
  static PinyinTable GenerateContactPinyinTable(
          const std::set<std::string> &contact_list);

  /**
   * 查找联系人的模糊拼音匹配列表
   *
   * @param table   GenerateContactPinyinTable返回的映射表。
   * @param contact 联系人姓名。
   *
   * @return 联系人模糊匹配查找结果。
   */
  static std::set<std::string> GetHomophoneList(const PinyinTable &table,
                                                std::string contact);
};

}  // namespace sdk
}  // namespace mobvoi

#endif  // LINUX_INTERFACE_UTILS_H_

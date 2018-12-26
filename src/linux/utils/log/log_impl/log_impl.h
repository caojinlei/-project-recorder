// Copyright 2018 VW-Mobvoi Inc. All Rights Reserved.
// Author: qinhuang@vw-mobvoi.com (Qin Huang)

#ifndef LINUX_UTILS_LOG_LOG_IMPL_LOG_IMPL_H_
#define LINUX_UTILS_LOG_LOG_IMPL_LOG_IMPL_H_

#include <string>
#include <sstream>

namespace Selene {

class LogImpl {
 public:
  explicit LogImpl(const std::string& function, const std::string& tag,
                   const std::string& type);
  virtual ~LogImpl();
  std::ostream& stream();

 protected:
  static const char* const kDebug;
  static const char* const kInfo;
  static const char* const kWarning;
  static const char* const kError;
  static const char* const kFatal;

 protected:
  std::ostringstream oss_;
  std::string function_;
  std::string tag_;
  std::string type_;
};  // LogImpl

}  // namespace Selene

#endif  // LINUX_UTILS_LOG_LOG_IMPL_LOG_IMPL_H_

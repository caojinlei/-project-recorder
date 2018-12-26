// Copyright 2018 VW-Mobvoi Inc. All Rights Reserved.
// Author: qinhuang@vw-mobvoi.com (Qin Huang)

#ifndef LINUX_UTILS_LOG_BLOG_BLOG_H_
#define LINUX_UTILS_LOG_BLOG_BLOG_H_

#include <string>

#include "log/log_impl/log_impl.h"

namespace Selene {

class Blog : public LogImpl {
 public:
  explicit Blog(const std::string& function, const std::string& tag,
                const std::string& type);
  virtual ~Blog();

 protected:
  void PrintTag(std::ostream& oss);
  void PrintFunction(std::ostream& oss);
  void Print(const std::string& str);
};  // Blog

}  // namespace Selene

#endif  // LINUX_UTILS_LOG_BLOG_BLOG_H_

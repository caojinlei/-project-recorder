// "Copyright [2018] <Qin Huang>"  [copyright]
// Author: huangqinemail@163.com (Qin Huang)

#ifndef LINUX_UTILS_LOG_LOG_H_
#define LINUX_UTILS_LOG_LOG_H_

#include "log/blog/blog.h"

#define LOGD(tag) Selene::Blog(__FUNCTION__, (tag), "TRACE").stream()
#define LOGI(tag) Selene::Blog(__FUNCTION__, (tag), "DEBUG").stream()
#define LOGW(tag) Selene::Blog(__FUNCTION__, (tag), "WARNING").stream()
#define LOGE(tag) Selene::Blog(__FUNCTION__, (tag), "ERROR").stream()
#define LOGF(tag) Selene::Blog(__FUNCTION__, (tag), "FATAL").stream()

#define ENTER_FUNC(tag) LOGD(tag) << "Enter >>>"
#define EXIT_FUNC(tag) LOGD(tag) << "<<< Exit"

#endif  // LINUX_UTILS_LOG_LOG_H_

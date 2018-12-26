// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef LG_LOGGER_H_
#define LG_LOGGER_H_

#include <iostream>
#include <string>

namespace mobvoi {
namespace lg {

#define LOGDEBUG(logger, msg) logger.Debug(__FILE__, __LINE__, msg)

#define LOGINFO(logger, msg) logger.Info(__FILE__, __LINE__, msg)

#define LOGWARN(logger, msg) logger.Warn(__FILE__, __LINE__, msg)

#define LOGERROR(logger, msg) logger.Error(__FILE__, __LINE__, msg)

// #define LOGFATAL(logger, msg) logger.Fatal(__FILE__, __LINE__, msg)

class Logger {
 public:
  explicit Logger(const std::string &app);

  Logger(const std::string &app, const std::string &id);

  ~Logger();

  std::string GetId() const;

  void Debug(const std::string &msg) const;

  void Debug(const char *file, int line, const std::string &msg) const;

  void Info(const std::string &msg) const;

  void Info(const char *file, int line, const std::string &msg) const;

  void Warn(const std::string &msg) const;

  void Warn(const char *file, int line, const std::string &msg) const;

  void Error(const std::string &msg) const;

  void Error(const char *file, int line, const std::string &msg) const;

  // void Fatal(const std::string &msg) const;

  // void Fatal(const char *file, int line, const std::string &msg) const;

 public:
  bool enable_debug;

 private:
  std::string appname_;

  std::string id_;

 private:
  void Log(const char *file, int line, int severity,
           const std::string &msg) const;
};

}  // namespace lg
}  // namespace mobvoi

#endif  // LG_LOGGER_H_

// Copyright 2018 VW-Mobvoi Inc. All Rights Reserved.
// Author: qinhuang@vw-mobvoi.com (Qin Huang)

#include "log/log_impl/log_impl.h"

#include <iostream>

namespace Selene {

const char* const LogImpl::kDebug = "DEBUG";
const char* const LogImpl::kInfo = "INFO";
const char* const LogImpl::kWarning = "WARNING";
const char* const LogImpl::kError = "ERROR";
const char* const LogImpl::kFatal = "FATAL";

LogImpl::LogImpl(const std::string& function, const std::string& tag,
                 const std::string& type)
    : function_(function), tag_(tag), type_(type) {}

LogImpl::~LogImpl() {}

std::ostream& LogImpl::stream() { return oss_; }

}  // namespace Selene

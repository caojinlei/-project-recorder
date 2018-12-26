// Copyright 2018 VW-Mobvoi Inc. All Rights Reserved.
// Author: qinhuang@vw-mobvoi.com (Qin Huang)

#include "log/blog/blog.h"

#include <boost/log/trivial.hpp>
#include <boost/format.hpp>

#include <iostream>
#include <string>

namespace Selene {

Blog::Blog(const std::string& function, const std::string& tag,
           const std::string& type)
    : LogImpl(function, tag, type) {}

Blog::~Blog() {
  std::ostringstream oss;

  PrintTag(oss);
  PrintFunction(oss);

  oss << oss_.str();
  Print(oss.str());
}

void Blog::PrintTag(std::ostream& oss) {
  if (!tag_.empty()) oss << boost::format("[%1%]") % tag_;
}

void Blog::PrintFunction(std::ostream& oss) {
  if (!function_.empty()) oss << boost::format("[%1%]") % function_;
}

void Blog::Print(const std::string& str) {
#if 0
  if (type_ == kDebug)
    BOOST_LOG_TRIVIAL(debug) << str;
  else if (type_ == kInfo)
    BOOST_LOG_TRIVIAL(info) << str;
  else if (type_ == kWarning)
    BOOST_LOG_TRIVIAL(warning) << str;
  else if (type_ == kError)
    BOOST_LOG_TRIVIAL(error) << str;
  else if (type_ == kFatal)
    BOOST_LOG_TRIVIAL(fatal) << str;
  else
    BOOST_LOG_TRIVIAL(trace) << str;
#endif

  std::cerr << str << std::endl;
  assert(type_ != kFatal);
}

}  // namespace Selene

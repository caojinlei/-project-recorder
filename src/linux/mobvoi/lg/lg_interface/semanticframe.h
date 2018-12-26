// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef INTERFACE_SEMANTICFRAME_H_
#define INTERFACE_SEMANTICFRAME_H_

#include <ctime>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "lg_interface/date_time.h"

namespace mobvoi {
namespace lg {

enum class MeasurementUnit {
  kMeter,
  kKiloMeter,
  kRMB,
  kUSD,
};

enum class PropertyType {
  kCanonicalValue,
  kTimePeriod,
  kTimePoint,
  kTimeAfter,
  kTimeBefore,
  kTimeAround,
  kMeasurementAfter,
  kMeasurementBefore,
  kMeasurementAround,
  kMeasurementRange,
};

class LuDateTime {
 public:
  LuDateTime() :
    year(-1), month(-1), day(-1), hour(-1), minute(-1), second(-1) {}

  inline std::tm ToTM() const {
    std::tm date = {0};
    date.tm_year = year > 0 ? year - 1900 : 0;
    date.tm_mon = month > 0 ? month - 1 : 0;
    date.tm_mday = day > 0 ? day : 1;
    date.tm_hour = hour > 0 ? hour : 0;
    date.tm_min = minute > 0 ? minute : 0;
    date.tm_sec = second > 0 ? second : 0;

    return date;
  }

  inline std::time_t ToTime() const {
    std::tm date = ToTM();
    return mktime(&date);
  }

 public:
  int year;
  int month;
  int day;
  int hour;
  int minute;
  int second;
};

class PropertyValue {
 public:
  virtual ~PropertyValue() {}

  virtual PropertyValue* Clone() const {
    return new PropertyValue;
  }

  virtual PropertyValue& operator=(const PropertyValue& that) {
    return *this;
  }
};

class CanonicalValue : public PropertyValue {
 public:
  ~CanonicalValue() {}

  CanonicalValue* Clone() const;

  CanonicalValue& operator=(const CanonicalValue& that);

 public:
  std::string   value;
};

class TimeRange : public PropertyValue {
 public:
  ~TimeRange() {}

  TimeRange* Clone() const;

  TimeRange& operator=(const TimeRange& that);

 public:
  LuDateTime    begin;
  LuDateTime    end;
};

class TimePoint : public PropertyValue {
 public:
  ~TimePoint() {}

  TimePoint* Clone() const;

  TimePoint& operator=(const TimePoint& that);

 public:
  LuDateTime    time;
};

class MeasurementPoint : public PropertyValue {
 public:
  ~MeasurementPoint() {}

  MeasurementPoint* Clone() const;

  MeasurementPoint& operator=(const MeasurementPoint& that);
 public:
  double          value;
  MeasurementUnit unit;
};

class Property {
 public:
  ~Property() {}

  bool IsCanonicalProperty() const {
    return type == PropertyType::kCanonicalValue;
  }

  bool IsTimeProperty() const {
    return type == PropertyType::kTimeAfter
        || type == PropertyType::kTimeAround
        || type == PropertyType::kTimeBefore
        || type == PropertyType::kTimePeriod
        || type == PropertyType::kTimePoint;
  }

  bool IsMeasurementProperty() const {
    return type == PropertyType::kMeasurementAfter
        || type == PropertyType::kMeasurementAround
        || type == PropertyType::kMeasurementBefore
        || type == PropertyType::kMeasurementRange;
  }

  Property& operator=(const Property& that);

  static Property NewCanonical(const std::string& normalValue);

  static Property NewTimeRange(const LuDateTime& begin, const LuDateTime& end);

  static Property NewTimePoint(
      const LuDateTime& point,
      const PropertyType& type = PropertyType::kTimePoint);

 public:
  PropertyType                    type;
  std::shared_ptr<PropertyValue>  value;
};

class Slot {
 public:
  Slot() : turnid(-1), negative(false) {}
  std::string GetCanonicalValue() const;
  bool TryGetCanonicalValue(std::string* pstr) const;

  Slot& operator=(const Slot& that);

 public:
  int                   turnid;
  std::string           name;
  std::string           value;
  std::pair<int, int>   span;
  std::vector<Property> properties;
  bool                  negative;
};

class Slots {
 public:
  std::vector<std::shared_ptr<Slot>> Find(const std::string& name) const;

  bool Add(std::shared_ptr<Slot> slot);

  Slots& operator=(const Slots& that);

 private:
  std::vector<std::shared_ptr<Slot>> root_;
};

class SemanticFrame {
 public:
  std::string source;
  std::string domain;
  std::string intent;
  double      score;
  Slots       slots;

 public:
  SemanticFrame& operator=(const SemanticFrame& that);
};

}  // namespace lg
}  // namespace mobvoi

#endif  // INTERFACE_SEMANTICFRAME_H_

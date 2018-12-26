// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef INTERFACE_DATE_TIME_H_
#define INTERFACE_DATE_TIME_H_

#include <sys/time.h>

#include <ctime>
#include <string>

namespace mobvoi {
class Date;

using std::string;

class DateTime {
 public:
     static DateTime DateTimeFromUtc(const std::tm& utc);

     static DateTime DateTimeFromLocal(const std::tm& local);

 public:
    // Construct a date with current time.
    DateTime();

    // Construct a date from RFC 3339 formatted string.
    explicit DateTime(const string& date);

    // Construct a date from an epoch time.
    explicit DateTime(time_t time);

    // Construct a date from a timeval.
    explicit DateTime(const struct timeval& local);

    // Copy constructor.
    DateTime(const DateTime& date);

    // Standard destructor.
    ~DateTime();

    // Convert the date to an RFC 3330 encoded string.
    string ToString() const;

    // Convert the date to local time.
    void GetLocalTime(std::tm* out) const;

    // Convert the date to universal time
    void GetUniversalTime(std::tm* out) const;

    void GetTimeval(struct timeval* value) const;

    time_t ToEpochTime() const;

    bool IsValid() const;

    int Compare(const DateTime& date) const;

    bool operator==(const DateTime& date) const;

    bool operator<(const DateTime& date) const;

    bool operator>(const DateTime& date) const;

    bool operator!=(const DateTime& date) const;

    bool operator<=(const DateTime& date) const;

    bool operator>=(const DateTime& date) const;

    DateTime& operator=(const DateTime& that);

 protected:
    explicit DateTime(const std::tm& local);

    friend class Date;

 private:
    struct timeval t_;

    static const time_t kInvalidEpoch;
};

class Date {
 public:
    explicit Date(const DateTime& date_time);

    // @param date string in format "YYYY-MM-DD"
    explicit Date(const string& date);

    Date(const Date& date);

    Date();

    ~Date();

    Date& operator=(const Date& that);

    // @return string in format "YYYY-MM-DD"
    string ToString() const;

 private:
    DateTime date_time_;
};

}  // namespace mobvoi

#endif  // INTERFACE_DATE_TIME_H_

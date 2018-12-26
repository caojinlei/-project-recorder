// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef INTERFACE_ADDRESS_H_
#define INTERFACE_ADDRESS_H_

#include <string>

namespace mobvoi {

struct Address {
 public:
  std::string country;        // country or region
  std::string state;          // state or province
  std::string city;           // city
  std::string town;           // town
  std::string street;         // street
  std::string zipcode;        // postal zone or zip code

  std::string full_address;   // full address

 public:
  Address();

  ~Address();

  Address& operator=(const Address& that);

  bool IsEmpty() const;
};

}  // namespace mobvoi

#endif  // INTERFACE_ADDRESS_H_

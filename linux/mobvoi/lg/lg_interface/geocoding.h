// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef INTERFACE_GEOCODING_H_
#define INTERFACE_GEOCODING_H_

namespace mobvoi {


// Structure for geo, based on WGS 84 datum.
class Geocoding {
 public:
  Geocoding();

  Geocoding(double lat, double lon);

  Geocoding(double lat, double lon, double alt);

  Geocoding(const Geocoding& geo);

  ~Geocoding();

  Geocoding& operator=(const Geocoding& that);

  bool operator==(const Geocoding& geo) const;

  bool operator!=(const Geocoding& geo) const;

  // Orthodromic distance between two geo points
  double DistanceTo(const Geocoding& geo) const;

  bool Equal(const Geocoding& geo, double deviation = 0.0) const;

  bool FlatEqual(const Geocoding& geo, double deviation = 0.0) const;

 public:
  double latitude;   // latitude in decimal degrees.
  double longitude;  // longitude in decimal degrees.
  double altitude;   // altitude in meters.
};

}  // namespace mobvoi

#endif  // INTERFACE_GEOCODING_H_

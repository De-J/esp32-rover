#ifndef User_H
#define User_H

class Rover {

  TinyGPSPlus loc;
  QMC5883LCompass compass;

public:
  Rover();

  bool encode(char c);
  int getHeading(void);
  double lat(void);
  double lng(void);
};

struct UserLocation {
private:
  double Lat, Lng;

public:
  UserLocation();
  void encode(String raw);
  
  double lat() {
    return Lat;
  }
  double lng() {
    return Lng;
  }
};


class User {
  UserLocation location;

public:
  void encode(String raw);
  double lat(void);
  double lng(void);
};
#endif

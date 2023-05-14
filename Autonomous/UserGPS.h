#ifndef UserGPS_H
#define UserGPS_H

#include <math.h> // for pow() function
#include <WString.h> // for String class

struct UserGPSLocation {
  friend class UserGPS;

  private:
    double Lat, Lng; 

  public:
    UserGPSLocation();
    double lat() { return Lat; }
    double lng() { return Lng; }
};


class UserGPS {
  UserGPSLocation location;
  
  public:
    void encode(String raw);
};
#endif

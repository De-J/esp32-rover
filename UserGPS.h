#ifndef UserGPS_H
#define UserGPS_H

struct UserGPSLocation {
  friend class UserGPS;

  private:
    double Lat, Lng; 

  public:

    double lat() { return Lat; }
    double lng() { return Lng; }
};


class UserGPS {
  UserGPSLocation location;
  
  public:
    void encode(String raw);
};
#endif

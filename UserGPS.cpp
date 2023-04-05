#include "UserGPS.h"

UserGPSLocation::UserGPSLocation() 
	: Lat(0)
	, Lng(0) {}

void UserGPS::encode(String raw) {
  bool latNegative = false, lngNegative = false;
  int i = 0, exp = 1, diff = 0;
  
  if (raw[0] == '-') {
    latNegative = true;
    i = 1;
  }

  // i < 11 condition is applied because un-applying MIGHT make the serial monitor unresponsive.
  while (raw[i] != ' ' && i < 11) {
    if (raw[i] != '.') {
      int digit = raw[i] - '0';
      double val = digit * pow(10, exp--);
      location.Lat += val;
    }
    i++;
  }

  if (raw[i + 1] == '-') {
    lngNegative = true;
    i += 2;
  } else i++;

  // Check if longitude has 3 digits before decimal
  int j = i;
  // diff < 4 is also applied because un-applying MIGHT make the serial monitor unresponsive.
  while (raw[j] != '.' && diff < 4) { 
    j++; 
    diff++;
  }
  
  exp = (diff > 2) ? 2 : 1;
  
  // applying i < 23 DEFINITELY prevents the serial monitor from becoming unresponsive.
  while (i < raw.length() && i < 23) {
    if (raw[i] != '.') {
      int digit = raw[i] - '0';
      double val = digit * pow(10, exp--);
      location.Lng += val;
    }
    i++;
  }
  location.Lat *= (latNegative) ? -1 : 1;
  location.Lng *= (lngNegative) ? -1 : 1;
}

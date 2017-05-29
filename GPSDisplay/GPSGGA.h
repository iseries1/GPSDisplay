/*
 * Author Michael Burmeister
 * Date May 21, 2017
 * Version 1.0
 * Description Store Global Positioning System Fix Data
 */

#ifndef _GPSGGA_H_
#define _GPSGGA_H_

class GPSGGA
 {
  private:
   int Seconds;
   int Minutes;
   int Hours;
   float Latitude;
   float Longitude;
   int Fix;
   int Sats;
   float HDOP;
   float Altitude;
   float WGS84;
   char Skip[5];
   char Data[15];
   float getDegrees(char *, int);
   void setTime(float t);

  public:
  GPSGGA();
  GPSGGA(char *);
  void Parse(char *);
  float getLatitude();
  float getLongitude();
  int getFix();
  int getSats();
  void getPosition(float*, float*);
  void getTime(int *, int *, int *);
  
 };
 
#endif


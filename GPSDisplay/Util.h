/*
 * Author Michael Burmeister
 * Date May 18, 2017
 * Version 1.0
 * Description Calculate GPS Distances
 */

#ifndef _UTIL_H
#define _UTIL_H

class GpsCalc
{
  private:
  const float Yards = 6967840;
  
  public:
  GpsCalc();
  float getDistance(float, float, float, float);
  bool Checkit(char *);
  
};

extern GpsCalc Gps;

class NextionClass
{
  private:
  char Buffer[50];
  char Format[50];
  
  public:
  NextionClass();
  void txt(char *, char *);
  void txt(char *, int);
  void txt(char *, float);
  void val(char *, int );
  void pco(char *, int );
  void cmd(char *);
};

extern NextionClass Nextion;

#endif

/*
 * Author Michael Burmeister
 * Date May 22, 2017
 * Version 1.0
 * Description GeoGraphic Position
 */

#ifndef _GPSGLL_H
#define _GPSGLL_H

 class GPSGLL
 {
  private:
    char Data[15];
    float Latitude;
    float Longitude;
    char Status;
    int Hours;
    int Minutes;
    int Seconds;
    float getDegrees(char *, int);
    void setTime(char *, int);

  public:
    GPSGLL();
    GPSGLL(char *);
    void Parse(char *);
    float getLatitude();
    float getLongitude();
    char getStatus();
    void getPosition(float *, float *);
    void getTime(int *, int *, int *);
 };

 #endif
 

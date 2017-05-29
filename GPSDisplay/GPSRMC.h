/*
 * Author Michael Burmeister
 * Date May 22, 2017
 * Version 1.0
 * Description Recommended Minimum Navigation Information
 */

#ifndef _GPSRMC_H
#define _GPSRMC_H

 class GPSRMC
 {
   private:
     char Data[15];
     int Year;
     int Month;
     int Day;
     int Hours;
     int Minutes;
     int Seconds;
     char Status;
     float Latitude;
     float Longitude;
     float Speed;
     float Angle;
     float Magnetic;
     void setTime(char *, int);
     void setDate(char *, int);
     float getDegrees(char *, int);

   public:
     GPSRMC();
     GPSRMC(char *);
     void Parse(char *);   
     float getLatitude();
     float getLongitude();
     void getPosition(float *, float *);
     void getDateTime(int *, int *, int *, int *, int *, int *);
 };

 #endif
 


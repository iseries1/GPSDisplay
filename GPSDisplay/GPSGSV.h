/*
 * Author Michael Burmeister
 * Date May 22, 2017
 * Version 1.0
 * Description Satetllites in View
 */

#ifndef _GPSGSV_H
#define _GPSGSV_H

 class GPSGSV
 {
  private:
    int Total=50;
    char Data[15];
    int Sent;
    int Sof;
    int Sats;
    int SNum[50];
    int Elevation[50];
    int Azimuth[50];
    int SNR[50];
    int getIndex(int);

  public:
    GPSGSV();
    GPSGSV(char *);
    void Parse(char *);
    int getSats(void);
    int getSNum(int);
    int getSNR(int);
    int getElevation(int);
    int getAzimuth(int);
    void sortSNR(void);
 };

 #endif
 

/*
 * Author Michael Burmeister
 * Date May 22, 2017
 * Version 1.0
 * Description GPS DOP and active Satellites
 */

#ifndef _GPSGSA_H
#define _GPSGSA_H

 class GPSGSA
 {
  private:
    char Data[15];
    char Selection[2];
    int Fix;
    int Sats[12];
    float PDOP;
    float HDOP;
    float VDOP;

  public:
    GPSGSA();
    GPSGSA(char *);
    void Parse(char *);
    bool Check(int);

 };

 #endif
 


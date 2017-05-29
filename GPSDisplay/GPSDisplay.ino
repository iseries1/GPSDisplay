/*
 * Author Michael Burmeister
 * Date May 23, 2017
 * Version 1.0
 * Description Display WaveShare GPS Data
 *
*/

#include <Arduino.h>
#include "GPSGGA.h"
#include "GPSGSV.h"
#include "GPSGSA.h"
#include "GPSGLL.h"
#include "GPSRMC.h"
#include "Util.h"

void runDisplay(void);

 char Data[128];
 int Index = 0;
 char c;
 GPSGGA GGA;
 GPSGSV GSV;
 GPSGSA GSA;
 GPSGLL GLL;
 GPSRMC RMC;
 
 int wait;
 unsigned long tm;
 int val;
 int Hrs, Mins, Secs;
 int Yr, Mn, Dy;
 float Lat, Lon;

void setup() {
  Serial.begin(115200);
  Serial1.begin(9600); // Nextion Panel
  Serial2.begin(38400); // WaveShare
  delay(5000);
  
  memset(Data, 0, sizeof(Data));
  Index = 0;
  wait = 0;
  tm = millis();
  
}

void loop() {
  if (millis() > tm)
    wait = wait + millis() - tm;
  tm = millis();
    
  if (Serial2.available() > 0)
  {
    while (Serial2.available() > 0)
    {
      c = Serial2.read();
//      Serial.write(c);
      if (c == '\n')
      {
        Data[Index] = 0;
        if (!Gps.Checkit(Data))
          Data[3] = 0;

        if (memcmp(&Data[3], "GGA", 3) == 0)
          GGA.Parse(Data);
        if (memcmp(&Data[3], "GSV", 3) == 0)
          GSV.Parse(Data);
        if (memcmp(&Data[3], "GLL", 3) == 0)
          GLL.Parse(Data);
        if (memcmp(&Data[3], "RMC", 3) == 0)
          RMC.Parse(Data);
        if (memcmp(&Data[3], "GSA", 3) == 0)
          GSA.Parse(Data);
        Index = 0;
      }
      else
      {
        Data[Index++] = c;
        if (Index >= 128)
          Index = 0;
      }
    }
  }
  
  if (wait > 1000)
  {
    runDisplay();
    wait = 0;
  }
}

void runDisplay()
{
  int t;
  
  RMC.getDateTime(&Yr, &Mn, &Dy, &Hrs, &Mins, &Secs);
  Hrs = Hrs - 5;  // Region Value Plus Daylight Savings Time
  RMC.getPosition(&Lat, &Lon);
  Nextion.txt("Latitude", Lat);
  Nextion.txt("Longitude", Lon);
  Nextion.val("Fix", GGA.getFix());
  Nextion.val("Sats", GGA.getSats());
  sprintf(Data, "%2d/%2.2d/20%d", Mn, Dy, Yr);
  Nextion.txt("Date", Data);
  sprintf(Data, "%2d:%2.2d:%2.2d", Hrs, Mins, Secs);
  Nextion.txt("Time", Data);
  if (GSV.getSats() > 1)
  {
    t = GSV.getSNum(1);
    if (GSA.Check(t))
      Nextion.pco("S1", 1024);
    else
      Nextion.pco("S1", 31);
    Nextion.txt("Sat1", GSV.getSNum(1));
    Nextion.val("S1", GSV.getSNR(1));
  }
  else
  {
    Nextion.pco("S1", 31);
    Nextion.txt("Sat1", 0);
    Nextion.val("S1", 0);
  }
  
  if (GSV.getSats() > 2)
  {
    t = GSV.getSNum(2);
    if (GSA.Check(t))
      Nextion.pco("S2", 1024);
    else
      Nextion.pco("S2", 31);
    Nextion.txt("Sat2", GSV.getSNum(2));
    Nextion.val("S2", GSV.getSNR(2));
  }
  else
  {
    Nextion.pco("S2", 31);
    Nextion.txt("Sat2", 0);
    Nextion.val("S2", 0);
  }
 
  if (GSV.getSats() > 3)
  {
    t = GSV.getSNum(3);
    if (GSA.Check(t))
      Nextion.pco("S3", 1024);
    else
      Nextion.pco("S3", 31);
    Nextion.txt("Sat3", GSV.getSNum(3));
    Nextion.val("S3", GSV.getSNR(3));
  }
  else
  {
    Nextion.pco("S3", 31);
    Nextion.txt("Sat3", 0);
    Nextion.val("S3", 0);
  }
  if (GSV.getSats() > 4)
  {
    t = GSV.getSNum(4);
    if (GSA.Check(t))
      Nextion.pco("S4", 1024);
    else
      Nextion.pco("S4", 31);
    Nextion.txt("Sat4", GSV.getSNum(4));
    Nextion.val("S4", GSV.getSNR(4));
  }
  else
  {
    Nextion.pco("S4", 31);
    Nextion.txt("Sat4", 0);
    Nextion.val("S4", 0);
  }
  
  if (GSV.getSats() > 5)
  {
    t = GSV.getSNum(5);
    if (GSA.Check(t))
      Nextion.pco("S5", 1024);
    else
      Nextion.pco("S5", 31);
    Nextion.txt("Sat5", GSV.getSNum(5));
    Nextion.val("S5", GSV.getSNR(5));
  }
  else
  {
    Nextion.pco("S5", 31);
    Nextion.txt("Sat5", 0);
    Nextion.val("S5", 0);
  }

  if (GSV.getSats() > 6)
  {
    t = GSV.getSNum(6);
    if (GSA.Check(t))
      Nextion.pco("S6", 1024);
    else
      Nextion.pco("S6", 31);
    Nextion.txt("Sat6", GSV.getSNum(6));
    Nextion.val("S6", GSV.getSNR(6));
  }
  else
  {
    Nextion.pco("S6", 31);
    Nextion.txt("Sat6", 0);
    Nextion.val("S6", 0);
  }

  if (GSV.getSats() > 7)
  {
    t = GSV.getSNum(7);
    if (GSA.Check(t))
      Nextion.pco("S7", 1024);
    else
      Nextion.pco("S7", 31);
    Nextion.txt("Sat7", GSV.getSNum(7));
    Nextion.val("S7", GSV.getSNR(7));
  }
  else
  {
    Nextion.pco("S7", 31);
    Nextion.txt("Sat7", 0);
    Nextion.val("S7", 0);
  }

  if (GSV.getSats() > 8)
  {
    t = GSV.getSNum(8);
    if (GSA.Check(t))
      Nextion.pco("S8", 1024);
    else
      Nextion.pco("S8", 31);
    Nextion.txt("Sat8", GSV.getSNum(8));
    Nextion.val("S8", GSV.getSNR(8));
  }
  else
  {
    Nextion.pco("S8", 31);
    Nextion.txt("Sat8", 0);
    Nextion.val("S8", 0);
  }

  if (GSV.getSats() > 9)
  {
    t = GSV.getSNum(9);
    if (GSA.Check(t))
      Nextion.pco("S9", 1024);
    else
      Nextion.pco("S9", 31);
    Nextion.txt("Sat9", GSV.getSNum(9));
    Nextion.val("S9", GSV.getSNR(9));
  }
  else
  {
    Nextion.pco("S9", 31);
    Nextion.txt("Sat9", 0);
    Nextion.val("S9", 0);
  }

  if (GSV.getSats() > 10)
  {
    t = GSV.getSNum(1);
    if (GSA.Check(t))
      Nextion.pco("S10", 1024);
    else
      Nextion.pco("S10", 31);
    Nextion.txt("Sat10", GSV.getSNum(10));
    Nextion.val("S10", GSV.getSNR(10));
  }
  else
  {
    Nextion.pco("S10", 31);
    Nextion.txt("Sat10", 0);
    Nextion.val("S10", 0);
  }

  if (GSV.getSats() > 11)
  {
    t = GSV.getSNum(11);
    if (GSA.Check(t))
      Nextion.pco("S11", 1024);
    else
      Nextion.pco("S11", 31);
    Nextion.txt("Sat11", GSV.getSNum(11));
    Nextion.val("S11", GSV.getSNR(11));
  }
  else
  {
    Nextion.pco("S11", 31);
    Nextion.txt("Sat11", 0);
    Nextion.val("S11", 0);
  }

  if (GSV.getSats() > 12)
  {
    t = GSV.getSNum(12);
    if (GSA.Check(t))
      Nextion.pco("S12", 1024);
    else
      Nextion.pco("S12", 31);
    Nextion.txt("Sat12", GSV.getSNum(12));
    Nextion.val("S12", GSV.getSNR(12));
  }
  else
  {
    Nextion.pco("S12", 31);
    Nextion.txt("Sat12", 0);
    Nextion.val("S12", 0);
  }
}


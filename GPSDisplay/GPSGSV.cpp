/*
 * Author Michael Burmeister
 * Date May 22, 2017
 * Version 1.0
 * Description Satetllites in View
 */

#include <Arduino.h>
#include <string.h>
#include <stdlib.h>

#include "GPSGSV.h"

/*
 * Constructor
 */
GPSGSV::GPSGSV()
{
  for (int i=0;i<Total;i++)
  {
    SNum[i] = 0;
    Elevation[i] = 0;
    Azimuth[i] = 0;
    SNR[i] = 0;
  }
  Sent = 0;
  Sof = 0;
  Sats = 0;
}

/*
 * Break down new GPS Packet
 */
GPSGSV::GPSGSV(char *s)
{
  Parse(s);
}

/*
 * Break down GPS Packet into class
 */
void GPSGSV::Parse(char *s)
{
  char C = ',';
  int i, j, k, x, u;
// Serial.println(s);
  j = strchr(s, C) - s;
  i = j + 1;
  j = strchr(&s[i], C) - s;
  memcpy(Data, &s[i], j - i);
  Data[j - i] = 0;
  Sent = atoi(Data);
  i = j + 1;
  j = strchr(&s[i], C) - s;
  memcpy(Data, &s[i], j - i);
  Data[j - i] = 0;
  Sof = atoi(Data);
  i = j + 1;
  j = strchr(&s[i], C) - s;
  memcpy(Data, &s[i], j - i);
  Data[j - i] = 0;
  Sats = atoi(Data);
  // process up to 4 satellites 
  for (k = 0; k < 4; k++)
  {
    i = j + 1;
    j = strchr(&s[i], C) - s;
    memcpy(Data, &s[i], j - i);
    Data[j - i] = 0;
    u = atoi(Data);
    x = getIndex(u);
    SNum[x] = u;
    i = j + 1;
    j = strchr(&s[i], C) - s;
    memcpy(Data, &s[i], j - i);
    Data[j - i] = 0;
    Elevation[x] = atoi(Data);
    i = j + 1;
    j = strchr(&s[i], C) - s;
    memcpy(Data, &s[i], j - i);
    Data[j - i] = 0;
    Azimuth[x] = atoi(Data);
    i = j + 1;
    j = strchr(&s[i], C) - s;
    if (j < 0)
    {
      j = strchr(&s[i], '*') - s;
      C = '*';
    }
    if (j > i)
    {
      memcpy(Data, &s[i], j - i);
      Data[j - i] = 0;
      SNR[x] = atoi(Data);
    }
    else
    {
      SNR[x] = 0;
    }
//    Serial.print("Parse:");Serial.print(SNum[k+x]);Serial.print("-");Serial.print(Elevation[k+x]);Serial.print("-");Serial.print(Azimuth[k+x]);
//    Serial.print("-");Serial.println(SNR[k+x]);
    if (C == '*')
      k = 4;
  }
}

/*
 * Get number of Satellites
 */
int GPSGSV::getSats()
{
  return Sats;
}

/*
 * Get Satellite Reference number
 */
int GPSGSV::getSNum(int i)
{
  if (i > 0)
    return SNum[i-1];
  else
    return 0;
}

/*
 * Get Signal to Noise Ratio for satellite
 */
int GPSGSV::getSNR(int i)
{
  if (i > 0)
    return SNR[i-1];
  else
    return 0;
}

/*
 * Get Height of satellite 
 */
int GPSGSV::getElevation(int i)
{
  if (i > 0)
    return Elevation[i-1];
  else
    return 0;
}

/*
 * Get Angle of satellite
 */
int GPSGSV::getAzimuth(int i)
{
  if (i > 0)
    return Azimuth[i-1];
  else
    return 0;
}

/*
 * Get Satellite Postion in Array
 */
int GPSGSV::getIndex(int sn)
{
  int i;
  for (i=0;i<Total;i++)
  {
    if (SNum[i] == sn)
      return i;
    if (SNum[i] == 0)
      return i;
  }
  return 0;
}

/*
 * Sort Satellites by Signal to Noise
 */
void GPSGSV::sortSNR()
{
  int x, j;
  for (int i=0;i<Sats-1;i++)
  {
    x = i;
    for (j=i+1;j<Sats;j++)
      if (SNR[x] < SNR[j])
        x = j;
    j = SNR[i];
    SNR[i] = SNR[x];
    SNR[x] = j;
    j = SNum[i];
    SNum[i] = SNum[x];
    SNum[x] = j;
    j = Elevation[i];
    Elevation[i] = Elevation[x];
    Elevation[x] = j;
    j = Azimuth[i];
    Azimuth[i] = Azimuth[x];
    Azimuth[x] = j;
  }
}


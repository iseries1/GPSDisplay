/*
 * Author Michael Burmeister
 * Date May 22, 2017
 * Version 1.0
 * Description Recommended Minimum Navigation Information
 */

#include <Arduino.h>
#include <string.h>
#include <stdlib.h>

#include "GPSRMC.h"

/*
 * Constructor
 */
GPSRMC::GPSRMC()
{
  Year = 0;
  Month = 0;
  Day = 0;
  Hours = 0;
  Minutes = 0;
  Seconds = 0;
  Status = 'V';
  Latitude = 0.0f;
  Longitude = 0.0f;
  Speed = 0.0f;
  Angle = 0.0f;
  Magnetic = 0.0f;
}

/*
 * Break down GPS data into class
 */
void GPSRMC::Parse(char *s)
{
  char C = ',';
  int i, j;

  j = strchr(s, C) - s;
  i = j + 1;
  j = strchr(&s[i], C) - s;
  setTime(&s[i], j - i);
  i = j + 1;
  j = strchr(&s[i], C) - s;
  Status = s[i];
  i = j + 1;
  j = strchr(&s[i], C) - s;
  if (j > i)
    Latitude = getDegrees(&s[i], j - i);
  i = j + 1;
  j = strchr(&s[i], C) - s;
  if (s[i] == 'S')
    Latitude = -Latitude;
  i = j + 1;
  j = strchr(&s[i], C) - s;
  Longitude = getDegrees(&s[i], j - i);
  i = j + 1;
  j = strchr(&s[i], C) - s;
  if (s[i] == 'W')
    Longitude = -Longitude;
  i = j + 1;
  j = strchr(&s[i], C) - s;
  memcpy(Data, &s[i], j - i);
  Data[j - i] = 0;
  Speed = atof(Data);
  i = j + 1;
  j = strchr(&s[i], C) - s;
  if (j > i)
  {
    memcpy(Data, &s[i], j - i);
    Data[j - i] = 0;
    Angle = atof(Data);
  }
  else
    Angle = 0.0f;
  i = j + 1;
  j = strchr(&s[i], C) - s;
  if (j > i)
    setDate(&s[i], j - i);
  i = j + 1;
  j = strchr(&s[i], C) - s;
  if (j > i)
  {
    memcpy(Data, &s[i], j - i);
    Data[j - i] = 0;
    Magnetic = atof(Data);
  }
  else
     Magnetic = 0.0f;
  i = j + 1;
  j = strchr(&s[i], C) - s;
  if (j < 0)
    j = strchr(&s[i], '*') - s;
  if (s[i] == 'E')
    Magnetic = -Magnetic;
}

/*
 * Break down new GPS data
 */
GPSRMC::GPSRMC(char *s)
{
  Parse(s);
}

/*
 * get Latitude
 */
float GPSRMC::getLatitude()
{
  return Latitude;
}

/*
 * get Longitude
 */
float GPSRMC::getLongitude()
{
  return Longitude;
}

/*
 * get GPS Position latitude, longitude
 */
void GPSRMC::getPosition(float *lat, float *lon)
{
  *lat = Latitude;
  *lon = Longitude;
}

/*
 * Get parsed GPS Date/Time
 */
void GPSRMC::getDateTime(int *yr, int *mx, int *dy, int *hr, int *mn, int *sc)
{
  *yr = Year;
  *mx = Month;
  *dy = Day;
  *hr = Hours;
  *mn = Minutes;
  *sc = Seconds;
}

/*
 * Convert Degrees, Minutes, and Seconds into decimal Degrees
 */
float GPSRMC::getDegrees(char *s, int i)
{
  float deg, mins;
  
  memcpy(Data, s, i);
  Data[i] = 0;

  if (Data[0] == '0')
  {
    mins = atof(&Data[3]);
    Data[3] = 0;
  }
  else
  {
    mins = atof(&Data[2]);
    Data[2] = 0;
  }
  deg = atof(Data);
  deg = deg + mins / 60;
  return deg;
}

/*
 * Parse GPS Time value
 */
void GPSRMC::setTime(char *s, int i)
{
  memcpy(Data, s, i);
  Data[i] = 0;
  float T = atof(Data);
  int t = (int)T;
  Seconds = t % 100;
  t = t / 100;
  Minutes = t % 100;
  t = t / 100;
  Hours = t;
}

/*
 * Parse GPS Date value
 */
void GPSRMC::setDate(char *s, int i)
{
  memcpy(Data, s, i);
  Data[i] = 0;
  int d = atoi(Data);
  Year = d % 100;
  d = d / 100;
  Month = d % 100;
  d = d / 100;
  Day = d;
}


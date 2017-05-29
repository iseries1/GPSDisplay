/*
 * Author Michael Burmeister
 * Date May 22, 2017
 * Version 1.0
 * Description GeoGraphic Position
 */

#include <Arduino.h>
#include <string.h>
#include <stdlib.h>

#include "GPSGLL.h"

/*
 * Constructor
 */
GPSGLL::GPSGLL()
{
  Latitude = 0.0f;
  Longitude = 0.0f;
  Status = 'V';
}

/*
 * Break down GPS packet into class
 */
void GPSGLL::Parse(char *s)
{
  char C = ',';
  int i, j, k;

  j = strchr(s, C) - s;
  i = j + 1;
  j = strchr(&s[i], C) - s;
  if (j > i)
    Latitude = getDegrees(&s[i], j - i);
  else
    Latitude = 0.0f;
  i = j + 1;
  j = strchr(&s[i], C) - s;
  if (j > i)
    if (s[i] == 'N')
      Latitude = -Latitude;
  i = j + 1;
  j = strchr(&s[i], C) - s;
  if (j > i)
    Longitude = getDegrees(&s[i], j - i);
  else
    Longitude = 0.0f;
  i = j + 1;
  j = strchr(&s[i], C) - s;
  if (j > i)
    if (s[i] == 'W')
      Longitude = -Longitude;
  i = j + 1;
  j = strchr(&s[i], C) - s;
  setTime(&s[i], j - i);
  i = j + 1;
  j = strchr(&s[i], '*') - s;
  Status = s[i];
}

/*
 * Break down new GPS packet
 */
GPSGLL::GPSGLL(char *s)
{
  Parse(s);
}

/*
 * Get latitude
 */
float GPSGLL::getLatitude()
{
  return Latitude;
}

/*
 * get longitude
 */
float GPSGLL::getLongitude()
{
  return Longitude;
}

/*
 * Get GPS status
 */
char GPSGLL::getStatus()
{
  return Status;
}

/*
 * Convert Degrees, Minutes, Seconds into decimal degrees
 */
float GPSGLL::getDegrees(char *s, int i)
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
 * Get GPS Postion Latitude, Longitude
 */
void GPSGLL::getPosition(float *lat, float *lon)
{
  *lat = Latitude;
  *lon = Longitude;
}

/*
 * Get Parsed GPS Time
 */
void GPSGLL::getTime(int *hrs, int *mins, int *sec)
{
  *hrs = Hours;
  *mins = Minutes;
  *sec = Seconds;
}

/*
 * Set Parsed GPS Time
 */
void GPSGLL::setTime(char *t, int i)
{
  memcpy(Data, t, i);
  Data[i] = 0;
  float x = atof(Data);
  Seconds = (int)x % 100;
  x = x / 100;
  Minutes = (int)x % 100;
  x = x / 100;
  Hours = (int)x % 100;
}



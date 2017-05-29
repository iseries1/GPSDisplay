/*
 * Author Michael Burmeister
 * Date May 21, 2017
 * Version 1.0
 * Description Store Global Positioning System Fix Data
 */

 #include <Arduino.h>
 #include <string.h>
 #include <stdlib.h>
 
 #include "GPSGGA.h"

 /*
  * Constructor
  */
 GPSGGA::GPSGGA()
 {
   Seconds = 0;
   Minutes = 0;
   Hours = 0;
   Longitude = 0.0f;
   Latitude = 0.0f;
   Fix = 0;
   Sats = 0;
   HDOP = 0.0f;
   Altitude = 0.0f;
   WGS84 = 0.0f;
 }

/*
 * Break down new GPS packet
 */
GPSGGA::GPSGGA(char *s)
{
  Parse(s);
}

/*
 * Break down GPS packet into class
 */
void GPSGGA::Parse(char *s)
{
  char C = ',';
  int i, j;

  j = strchr(s, C) - s;
  i = j + 1;
  j = strchr(&s[i], C) - s;
  memcpy(Data, &s[i], j - i);
  Data[j-i] = 0;
  float t = atof(Data);
  setTime(t);
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
    if (s[i] == 'E')
      Longitude = -Longitude;
  i = j + 1;
  j = strchr(&s[i], C) - s;
  memcpy(Data, &s[i], j - i);
  Data[j-i] = 0;
  Fix = atoi(Data);
  i = j + 1;
  j = strchr(&s[i], C) - s;
  memcpy(Data, &s[i], j - i);
  Data[j-i] = 0;
  Sats = atoi(Data);
  i = j + 1;
  j = strchr(&s[i], C) - s;
  memcpy(Data, &s[i], j - i);
  Data[j-i] = 0;
  HDOP = atof(Data);
  i = j + 1;
  j = strchr(&s[i], C) - s;
  memcpy(Data, &s[i], j - i);
  Data[j-i] = 0;
  if (j > i)
    Altitude = atof(Data);
  else
    Altitude = 0.0f;
  i = j + 1;
  j = strchr(&s[i], C) - s;
  Skip[0] = s[i];
  i = j + 1;
  j = strchr(&s[i], C) - s;
  memcpy(Data, &s[i], j - i);
  Data[j-i] = 0;
  if (j > i)
    WGS84 = atof(Data);
  else
    WGS84 = 0.0f;
  i = j + 1;
  j = strchr(&s[i], C) - s;
  Skip[1] = s[i];
}

/*
 * Convert degree minutes and seconds into degrees
 */
float GPSGGA::getDegrees(char *s, int i)
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
 * Get latitude
 */
float GPSGGA::getLatitude()
{
  return Latitude;
}

/*
 * get longitude
 */
float GPSGGA::getLongitude()
{
  return Longitude;
}

/*
 * get GPS fix status
 */
int GPSGGA::getFix()
{
  return Fix;
}

/*
 * get number Satellites in solution
 */
int GPSGGA::getSats()
{
  return Sats;
}

/*
 * get GPS position latitude, longitude
 */
void GPSGGA::getPosition(float *lat, float *lon)
{
  *lat = Latitude;
  *lon = Longitude;
}

/*
 * get parsed time
 */
void GPSGGA::getTime(int *hrs, int *mins, int *sec)
{
  *hrs = Hours;
  *mins = Minutes;
  *sec = Seconds;
}

/*
 * break down time
 */
void GPSGGA::setTime(float t)
{
  Seconds = (int)t % 100;
  t = t / 100;
  Minutes = (int)t % 100;
  t = t / 100;
  Hours = (int)t % 100;
}


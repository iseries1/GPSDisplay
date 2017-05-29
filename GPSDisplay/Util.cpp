/*
 * Author Michael Burmeister
 * Date May 18, 2017
 * Version 1.0
 * Description Uitility functions
 */

#include <Arduino.h>
#include <math.h>
#include "Util.h"

/*
 * Constructor
 */
GpsCalc::GpsCalc()
{
  
}

/*
 * Calculate the distance between two positions in decimal degrees
 */
float GpsCalc::getDistance(float flat, float flon, float tlat, float tlon)
{

  float dlat = tlat - flat;
  float dlon = tlon - flon;

  dlat = M_PI * dlat / 360;
  dlon = M_PI * dlon / 360;

  float flatr = M_PI * flat / 180;
  float tlatr = M_PI * tlat / 180;

  float i = sin(dlat) * sin(dlat) + cos(flatr) * cos(tlatr) * sin(dlon) * sin(dlon);
  float j = asin(sqrt(i)) * 2;
  j = j * Yards;
  return j;
}

/*
 * Calculate the Check Sum for the GPS packet
 */
bool GpsCalc::Checkit(char *d)
{
  int c = 0;
  int t = 0;
  int i;
  
  if (d[0] != '$')
    return false;
  for (i=1;i<80;i++)
  {
    if (d[i] == '*')
      break;
    c ^= d[i];
  }

  t = d[i+1]-'0';
  if (t > 9)
    t = t - 7;
  t = t << 4;
  i = d[i+2]-'0';
  if (i > 9)
    i = i - 7;
  t = t + i;
//  Serial.print(t,HEX);Serial.print(":");Serial.println(c,HEX);
  if (t == c)
    return true;
  else
    return false;
}

/*
 * build static class
 */
GpsCalc Gps;


/*
 * Nextion Class constructor
 */
NextionClass::NextionClass()
{
  
}

/*
 * Set Text value for object name
 */
void NextionClass::txt(char *f, char *v)
{
  strcpy(Format, f);
  strcat(Format, ".txt=\"%s\"");
  sprintf(Buffer, Format, v);
  cmd(Buffer);
}

/*
 * Set Text value for ojbect name
 */
void NextionClass::txt(char *f, int v)
{
  strcpy(Format, f);
  strcat(Format, ".txt=\"%d\"");
  sprintf(Buffer, Format, v);
  cmd(Buffer);
}

/*
 * Set Text value for object name
 */
void NextionClass::txt(char *f, float v)
{
  strcpy(Format, f);
  strcat(Format, ".txt=\"%f\"");
  sprintf(Buffer, Format, v);
  cmd(Buffer);
}

/*
 * Set Value for object name
 */
void NextionClass::val(char *f, int v)
{
  strcpy(Format, f);
  strcat(Format, ".val=%d");
  sprintf(Buffer, Format, v);
  cmd(Buffer);
}

/*
 * Set Picture Color for object name
 */
void NextionClass::pco(char *f, int v)
{
  strcpy(Format, f);
  strcat(Format, ".pco=%d");
  sprintf(Buffer, Format, v);
  cmd(Buffer);
}

/*
 * Send Command to Nextion panel
 */
void NextionClass::cmd(char *c)
{
  Serial1.print(c);
  Serial1.write(0xff);Serial1.write(0xff);Serial1.write(0xff);
  if (Serial1.available() > 0)
  {
    Serial.println(c);
    while (Serial1.available() >0)
    {
      char c = Serial1.read();
      Serial.print(c, HEX);
    }
    Serial.println();
  }
}

/*
 * Static Construtor for class
 */
NextionClass Nextion;


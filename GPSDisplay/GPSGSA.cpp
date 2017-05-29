/*
 * Author Michael Burmeister
 * Date May 22, 2017
 * Version 1.0
 * Description GPS DOP and active Satellites
 */

 #include <Arduino.h>
 #include <string.h>
 #include <stdlib.h>
 
 #include "GPSGSA.h"

/*
 * Constructor
 */
GPSGSA::GPSGSA()
{
  Selection[0] = 0;
  Selection[1] = 0;
  Fix = 0;
  for (int i = 0; i < 12; i++)
     Sats[i] = 0;
  PDOP = 0.0f;
  HDOP = 0.0f;
  VDOP = 0.0f;
}

/*
 * Break down GPS packet into class
 */
void GPSGSA::Parse(char *s)
{
  char C = ',';
  int i, j;

  j = strchr(s, C) - s;
  i = j + 1;
  j = strchr(&s[i], C) - s;
  Selection[0] = s[i];
  i = j + 1;
  j = strchr(&s[i], C) - s;
  memcpy(Data, &s[i], j - i);
  Data[j - i] = 0;
  Fix = atoi(Data);
  for (int k = 0; k < 12; k++)
  {
     i = j + 1;
     j = strchr(&s[i], C) - s;
     if (j > i)
     {
       memcpy(Data, &s[i], j - i);
       Data[j - i] = 0;
       Sats[k] = atoi(Data);
     }
     else
       Sats[k] = 0;
  }
  i = j + 1;
  j = strchr(&s[i], C) - s;
  if (j > i)
  {
    memcpy(Data, &s[i], j - i);
    Data[j - i] = 0;
    PDOP = atof(Data);
  }
  i = j + 1;
  j = strchr(&s[i], C) - s;
  if (j > i)
  {
    memcpy(Data, &s[i], j - i);
    Data[j - i] = 0;
    HDOP = atof(Data);
  }
  i = j + 1;
  j = strchr(&s[i], C) - s;
  if (j < 0)
    j = strchr(&s[i], '*') - s;
  if (j > i)
  {
    memcpy(Data, &s[i], j - i);
    Data[j - i] = 0;
    VDOP = atof(Data);
  }
}

/*
 * Break down new GPS packet
 */
GPSGSA::GPSGSA(char *s)
{
  Parse(s);
}

/*
 * Check if Satellite is part of solution
 */
bool GPSGSA::Check(int sn)
{
  for (int i=0;i<12;i++)
    if (Sats[i] == sn)
      return true;
  return false;
}



# GPSDisplay
Using a Nextion Panel and a Waveshare GPS display GPS position information

This is a proof of conscept project that displays GPS information on a Nextion 480X270 panel

Parts used:
Waveshare GPS for $20
Butterfly STM Arduino board $18
Nextion 4 inch panel NX4827T043 $45

The Butterfly MCU breaks down the GPS NEMA data into separate classes that are then used
to display the GPS data on a Nextion Display.

This project shows how to build a class and use it to parse the GPS data into the class.
It also shows how to build static classes that are used to send information to the Nextion
panel to be displayed.

Unfortunately the project doesn't quite work as the Nextion panel generates noise in the GPS
frequency and provents the GPS module from getting a fix.


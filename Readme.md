# LEDcube
8x8x8 LED Cube Firmware &amp; Hardware

## Schematic and Board files
The LEDcube schematic and board files are available in the "schematic" directory. The schematic and board files were created using ExpressPCB, available for download from the following link: https://www.expresspcb.com/. There is a PDF version of the schematic as well if you prefer not to use ExpressPCB.

## Firmware
Follow the steps below to build the source for the LEDcube.

This source can be built using two methods:
1. Using the Arduino IDE.
2. Using a containerized environment with Docker.


[Method 1] Arduino IDE
-----------------------------------------------
1. Install the latest version of the Arduino IDE: https://www.arduino.cc/en/Main/Software
2. Download the LEDcube source and open /Firmware/LEDcube/cube.ino with the Arduino IDE.
3. Press the build button in the Arduino IDE to build the source. If everything is correct, the build will complete without error.


[Method 2] Docker
-----------------------------------------------
1. Install Docker CE on your build system: https://docs.docker.com/install/
2. Install the Arduino Builder for Docker: https://hub.docker.com/r/photonicfusion/arduino_builder
3. Create a directory structure with top level named "LEDcube" and two sub-directories named "src" and "libs".
4. Download the LEDcube source and copy /Firmware/cube to the "src" directory.
5. Save one of the convenience scripts provided on the Arduino Builder to the LEDcube directory.
6. Run the convenience script to build the source.
7. If the build completed successfully, a .hex file will be located in the "src" directory.

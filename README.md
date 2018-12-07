# JCPower
JCPower is a wifi-connected, battery-powered power supply that supports variable voltage (1-20V), and current limiting (0-1A). This repository contains all source code, including tuning values - one JCPower was fully assembled and calibrated, so that the DAC/ADC values were accurate.

## Hardware
Circuit schematic, board, and component list is available on the (CircuitMaker page)[https://workspace.circuitmaker.com/Projects/Details/Jason-Cihelka-2/JCPOWER]

![JCPOWER Board](https://jcace.com/images/portfolio/board_view.jpg)

The [Particle Photon](https://www.particle.io/wifi/) board was chosen as the control board due to its builtin ADC/DACs, processing power, and ease of connection/sharing of data over Wifi.

## Software

### Board Firmware
Main firmware codebase can be found in the main.ino file. The only way to set current/voltage values is by sending a command through the Particle Cloud. This is done through the web (html) software.

The TI INA219 digital current monitor chip was selected to provide high-precision current measurements over I2C. Interface with this device was achived through this [GitHub library](https://github.com/pkourany/ina129Spark). *Note typo - library is called ina129Spark but it is actually for the ina219 device*

### Software
A simple web page was built in HTML to allow the user to send voltage and current commands, as well as monitor device readings and battery level. No styling was applied to the page for simplicity, it just has the base functionality to control the board.

![JCPower Site](https://i.imgur.com/dVagiyF.png)
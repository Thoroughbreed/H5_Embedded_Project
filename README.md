![Build succeeded][build-shield]
![Test passing][test-shield]
[![Issues][issues-shield]][issues-url]
[![Issues][closed-shield]][issues-url]
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![License][license-shield]][license-url]

# Intelligent house
#### H5 Embedded group project
<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>

- [Case](#case)
- [Requirements](#requirements)
- [Architecture diagram](#architecture-diagram)
- [Roadmap](#roadmap)
- [Summary and rundown](#summary-and-rundown)
- [Getting started](#getting-started)
- [Pin layout](#pin-layout)
  - [Home](#home)
  - [Alarm](#alarm)
  - [Climate](#climate)
- [MQTT Topics](#mqtt-topics)
- [Libraries](#libraries)
- [Components](#components)
- [HIPO Diagrams](#hipo-diagrams)
  - [Alarm](#alarm-1)
  - [Climate](#climate-1)
  - [Home](#home-1)
- [Flowcharts](#flowcharts)
  - [Alarm](#alarm-2)
  - [Climate](#climate-2)
  - [Home](#home-2)
- [License](#license)
- [Contact](#contact)
</details>

# Case
Build master and slave units for the *Intelligent house* - the master unit must be the "heart" of the communication, and control several functions around the house via the slave units.
* Perimeter alarm system
* Internal alarm system
* Climate control
* Gas detection
* Entry system
* User-friendly interaction
* General smart-home functions (lights, doors, etc.)
<p align="right">(<a href="#top">back to top</a>)</p>

# Requirements
- [X] Configure several different peripherals
- [X] Read values from sensors in a sensible manner
- [X] Control various aspects of the intelligent house
- [X] Configure some sort of HID (display, keypad etc.)
- [X] Present measurements for the user in a user-friendly manner
- [X] Have multiple boards communicate
- [ ] Create an endpoint for user friendly remote control
<p align="right">(<a href="#top">back to top</a>)</p>

# Architecture diagram
![architecture diagram](/Docs/Architecture-Diagram.drawio.png)

# Roadmap
- [ ] Create a custom mqtt-broker with API and database
- [X] Make a fully functional alarm/control system
- [X] Integrate access control (RFID/NFC)
- [X] Make it easily expandable
- [X] Integrate several different devices
- [X] Create a full three-layered log <sup>3</sup>
- [ ] Create mobile frontend to control the system
- [ ] Create frontend to control system and view status, historical data


#  Summary and rundown
The **IntelliHouse2000** is a all-in-one microcontroller combo that provides climate control, monitoring and alarm/entry functions for the entire house. You can have sensors in all rooms, and set the parameters for each sensor.
If an event is triggered while the alarm is armed, no apparent function will happen in the house, but the log will be updated and the user will get a message<sup>1</sup> with the event, timestamp and what sensor triggered it. If however the alarm is disarmed (that is, the user is home) **IntelliHouse2000** will take action on the event.
> If you forget to turn off your car in the garage, and the sensor detects rising CO<sub>2</sub> levels, the user will be warned, displays around the house will show the event, and the garage door will open incrementally until the sensor value returns to normal

> If the humidity in the house rises rapidly, the appropriate window will be opened incrementally until the sensor detects a drop in humidity. As an extra function<sup>2</sup> you can add weather sensor as well, so the window *doesn't* open if the humidity outside is higher than inside, or it rains.

> No matter what action have been taken (open doors, windows etc.) those will automatically close when the alarm system is armed. This happens with both perimeter and full arm.
<p align="right">(<a href="#top">back to top</a>)</p>


# Getting started
To add a device go to the appropriate section (e.g. Climate) and locate the header-file (ends with .h) - there you can see the pin-defines, where all you have to do it add your new device to that list like this: `#define NewSensor 8` where *NewSensor* is the "friendly name" of your sensor, and *8* is the pin-number you're using on the board.
Next thing is to "start" the sensor `DHT newDHT(NewSensor, Type)`where *newDHT* is the name of the object and *Type* is the type of sensor (e.g. DHT11).

Then all you do is to add the check to the source code
```
temperature2 = newDHT.readTemperature();
humidity2 = newDHT.readHumidity();
```

Make sure to read the setup for each device, some communicate by one-wire (like the DHT11), some use SPI *(Serial Peripheral Interface)*, some use I<sup>2</sup>C *(Called **Wire** in Arduino)* and others use analog input.

<p align="right">(<a href="#top">back to top</a>)</p>

# Pin layout

## Home
| Arduino pin | Component pin | Component name | Volt |
| :---------- | :------------ | :------------- | :--- |
| 5V          | POWER         | HC-SR501 PIR 1 | 5V   |
| 5           | OUTPUT        | HC-SR501 PIR 1 | 3.3V |
| 5V          | POWER         | HC-SR501 PIR 2 | 5V   |
| 6           | OUTPUT        | HC-SR501 PIR 2 | 3.3V |
| 7           |               | REED Relay     | 3.3V |
<p align="right">(<a href="#top">back to top</a>)</p>

## Alarm
| Arduino pin | Component pin | Component name | Volt |
| :---------- | :------------ | :------------- | :--- |
|             |               |                |      |
<p align="right">(<a href="#top">back to top</a>)</p>

## Climate
| Arduino pin | Component pin | Component name | Volt |
| :---------- | :------------ | :------------- | :--- |
| 2           | Signal        | DHT11          | 3,3  |
| 3           | Signal        | DHT11          | 3,3  |
| 4           | Signal        | DHT11          | 3,3  |
| A1          | Signal        | MQ-2           | 5,0  |
| 5           | Signal        | SG90           | 5,0  |

<p align="right">(<a href="#top">back to top</a>)</p>

# MQTT Topics
| Topics                               | Access   | Method  |
| :----------------------------------- | :------- | :------ |
| home/alarm/arm                       | External | Pub/Sub |
| home/alarm/alarm                     | External | Sub     |
| home/alarm/alarm                     | Internal | Pub     |
| home/climate/status/#                | External | Sub     |
| home/climate/status/[section]/[type] | Internal | Pub     |
| home/climate/servo                   | External | Pub     |
| home/log/[logLevel]/[type]           | Internal | Pub     |
| home/log/#                           | External | Sub     |

# Libraries
| Name               | Version | Component                    |
| ------------------ | ------- | ---------------------------- |
| Adafruit SSD1306   | 2.5.7   | OLED display                 |
| DHT sensor library | 1.4.4   | DHT11 sensor                 |
| NTPClient          | 3.2.1   |                              |
| Servo              | 1.1.8   | Servo motors                 |
| WiFiNINA           | 1.8.13  |                              |
| MQTT               | 2.5.0   |                              |
| Keypad             | 3.1.1   | 4x4 keypad                   |
| MFRC522            | 1.4.10  | RFID reader                  |
| Wire               | 1.8.2   | I<sup>2</sup>C communication |
| SPI                | 1.9.8   | SPI communication            |
<p align="right">(<a href="#top">back to top</a>)</p>


# Components
| Device              | Amount | Function                                                     | Controller |
| ------------------- | ------ | ------------------------------------------------------------ | ---------- |
| Arduino MKR1010     | 3      | Microcontroller                                              |            |
| DHT11               | 3      | Temperature and humidity sensor                              | Climate    |
| MQ-2                | 1      | Gas/air quality sensor                                       | Climate    |
| Servo               | 2      | Controlling window and garage door                           | Climate    |
| REED switch         | 1      | Intrusion detection, front door                              | Alarm      |
| HC-SR501 PIR sensor | 2      | Intrusion (motion) detection, living room                    | Alarm      |
| HC-SR04 Ultrasound  | 1      | Automatic doors                                              | Home/entry |
| RFID reader         | 1      | Entry system                                                 | Home/entry |
| 4x4 Keypad          | 1      | Entry system                                                 | Home/entry |
| 128x64 OLED         | 1      | Peripheral display around the house (time, temp, status etc. | Home/entry |
* The system is built for expansion, there is very little work in attaching multiple devices to the system, that could be more intrusion sensors, a buzzer, multiple displays etc.
<p align="right">(<a href="#top">back to top</a>)</p>

# HIPO Diagrams
<p align="right">(<a href="#top">back to top</a>)</p>

## Alarm
![alarm hipo diagram](/Docs/Alarm_HIPO.drawio.png)
<p align="right">(<a href="#top">back to top</a>)</p>

## Climate
![Climate Hipo diagram](/Docs/H5.Inteligenthus.Climate.hippo.drawio.png)
<p align="right">(<a href="#top">back to top</a>)</p>

## Home
<p align="right">(<a href="#top">back to top</a>)</p>


# Flowcharts

## Alarm
![alarm flowchart](/Docs/Alarm_FlowChart.drawio.png)
<p align="right">(<a href="#top">back to top</a>)</p>

## Climate
![Climate flowchart](/Docs/H5.Inteligentehus.Climate.drawio.png)
<p align="right">(<a href="#top">back to top</a>)</p>

## Home
![Home flowchart](/Docs/homeController_chart.png)
<p align="right">(<a href="#top">back to top</a>)</p>



# License
* Hardware: CC-BY-LA (Creative Commons)
* API: GPLv3
* Frontend: GPLv3
* Mobile: GPLv3
<p align="right">(<a href="#top">back to top</a>)</p>

# Contact
- Peter Hymøller - peterhym21@gmail.com
  - [Twitter](https://twitter.com/peter_hym)
- Nicolai Heuck - nicolaiheuck@gmail.com
- Jan Andreasen - jan@tved.it
  - [![Twitter][twitter-shield]][twitter-url]

Project Link: [https://github.com/Thoroughbreed/H5_Embedded_Project](https://github.com/Thoroughbreed/H5_Embedded_Project)
<p align="right">(<a href="#top">back to top</a>)</p>

<sup>1</sup> - Informs the user via mobile app over the MQTT protocol

<sup>2</sup> - Function not built in yet

<sup>3</sup> - Logs via MQTT to a database in the following layers: Debug, Info, Critical.


<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[build-shield]: https://img.shields.io/badge/Build-passed-brightgreen.svg
[test-shield]: https://img.shields.io/badge/Tests-passed-brightgreen.svg
[contributors-shield]: https://img.shields.io/github/contributors/Thoroughbreed/H5_Embedded_Project.svg?style=badge
[contributors-url]: https://github.com/Thoroughbreed/H5_Embedded_Project/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/Thoroughbreed/H5_Embedded_Project.svg?style=badge
[forks-url]: https://github.com/Thoroughbreed/H5_Embedded_Project/network/members
[issues-shield]: https://img.shields.io/github/issues/Thoroughbreed/H5_Embedded_Project.svg?style=badge
[closed-shield]: https://img.shields.io/github/issues-closed/Thoroughbreed/H5_Embedded_Project?label=%20
[issues-url]: https://github.com/Thoroughbreed/H5_Embedded_Project/issues
[license-shield]: https://img.shields.io/github/license/Thoroughbreed/H5_Embedded_Project.svg?style=badge
[license-url]: https://github.com/Thoroughbreed/H5_Embedded_Project/blob/master/LICENSE
[twitter-shield]: https://img.shields.io/twitter/follow/andreasen_jan?style=social
[twitter-url]: https://twitter.com/andreasen_jan

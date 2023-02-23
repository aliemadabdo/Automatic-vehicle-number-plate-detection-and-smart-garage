# Smart Garage System

## Project Overview:
The purpose of this project is to create a smart garage system that uses AI and IoT technology to automatically open the garage door when a recognized license plate is detected, and to allow users to remotely monitor available parking spaces using a mobile app. The system is designed for general smart garage owners and will be built using an ESP8266 microcontroller, multiple sensors, a Raspberry Pi, Node-RED, YOLOv5, and MQTT.

This project is developed by four trainees from [place where you took the training] as part of their training program. The project members are:

- [Name of trainee 1], Contact: [phone number or email]
- [Name of trainee 2], Contact: [phone number or email]
- [Name of trainee 3], Contact: [phone number or email]
- [Name of trainee 4], Contact: [phone number or email]

## System Architecture:
The smart garage system will consist of the following components:

- ESP8266 microcontroller with sensors for detecting available parking spaces
- Raspberry Pi for processing camera feed and running YOLOv5, and for communicating with multiple sensors and microcontrollers
- Node-RED for implementing a simple mobile app and MQTT broker
- YOLOv5 for license plate detection and recognition
- MQTT for communication between microcontroller, Raspberry Pi, and mobile app

## System Operation:
The smart garage system will operate as follows:

1. The ESP8266 microcontroller will continuously monitor the sensors for changes in parking space availability.
2. When a car enters or leaves a parking space, the ESP8266 microcontroller will send a signal to the Raspberry Pi via MQTT to update the parking space availability status on the mobile app.
3. The Raspberry Pi will process the camera feed using YOLOv5 to detect and recognize license plates.
4. If a recognized license plate is detected, the Raspberry Pi will send a signal via MQTT to the ESP8266 microcontroller to open the garage door.
5. Users can remotely monitor parking space availability and open the garage door using the mobile app.

## User Manual:
To use the smart garage system, follow these simple steps:

1. Download and install the mobile app on your smartphone or tablet.
2. Open the app and create an account if necessary.
3. The app will display the current availability status of the parking spaces in your garage.
4. To open the garage door, simply drive up to the door and wait for the system to recognize your license plate.
5. Once your license plate is recognized, the system will automatically open the garage door.
6. You can also manually open the garage door using the app by tapping the "Open Door" button.
7. To close the garage door, simply drive out of the garage and the door will automatically close.

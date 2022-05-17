# rest-remote-controller
## Overview
This project was started to have a simple REST API for a remote controlled awning, but could be used for other remote controlled devices as well with minor tewaks. The end goal was to be able to integrate it into Google Home/Alexa.
## Basic funtionality
The ESP8266 is connected with three pins to UP, DOWN and STOP buttons on a remote control and starts a REST API server that takes GET requests for the different functions to activate the dedicated pin for a short while to simulate a button press.

The REST API server handles routes for:
- up: activate the pin for UP command (GPIO16)
- stop: activate the pin for STOP command (GPIO14)
- down: activate the pin for DOWN command (GPIO12)
## Added features
Uses WiFiManager to allow for simple and dynamic WiFi setup via temporary local access point.
## Smart home integration
To be able to send commands, scripts were setup in Home Assistant using their cloud integration via Nabu Casa. This could alternatively be setup via IFTTT but since there is no authentication implemented I choose not to do this.

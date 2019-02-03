# Azure IoT Intro workshop
Content for the introductory workshop on Azure IoT delivered for FCT-UNL students in Feb. 04 2019

# Goals
- Understand IoT business use cases and applications
- Get to know the Azure IoT platform and its tools
- Learn how to connect a device, send device-to-cloud (D2C) and cloud-to-device (C2D) messages, and build custom dashboards
- Apply all you've learned with your devices at home and create your own IoT solutions!

# Main Topics
- Azure IoT Hub
- Azure Stream Analytics
- PowerBI

# Pre-requisites
- An Azure account:
https://docs.microsoft.com/en-us/learn/modules/create-an-azure-account/1-introduction

- A PowerBI account:
https://docs.microsoft.com/en-us/power-bi/service-self-service-signup-for-power-bi

# Setup

## 1) Install Visual Studio Code (VSC) and the IoT Hub Toolkit extension

https://code.visualstudio.com/download

https://marketplace.visualstudio.com/items?itemName=vsciot-vscode.azure-iot-toolkit

## 2) Sign-in to your Azure account in VSC

- Press F1 and write ```Azure: Sign In```

![VSC1 image](https://github.com/andren/iot-intro-workshop/blob/master/images/VSC1.png)

## 3) Create an IoT Hub and add a simulated device

- Follow this tutorial and stop when you reach "Run a sample application on Pi web simulator"
https://docs.microsoft.com/en-us/azure/iot-hub/iot-hub-raspberry-pi-web-simulator-get-started

- Take note of your IoT hub key (iothubowner) and your device key:

-----
In Azure each resource has an associated resource key, it is what gives you access to a given resource so it should be carefully handled. It can be regenerated in case it is compromised.

The *IoT Hub key* enables apps to manage the IoT Hub (check which devices it has, monitor messages, send C2D messages,...), just like the VSC extension we are going to use. The Hub key looks something like: ```HostName=<your_hub_name>.azure-devices.net;SharedAccessKeyName=iothubowner;SharedAccessKey=_____________=```
You will find it here:
![hubKey image](https://github.com/andren/iot-intro-workshop/blob/master/images/hubKey.png)


The device key is the unique identifier for each device. It looks like this:
```HostName=<your_hub_name>.azure-devices.net;DeviceId=<your_device_name>;SharedAccessKey=_____________=```
You will find it here:
![deviceKey image](https://github.com/andren/iot-intro-workshop/blob/master/images/deviceKey.png)

-----

## 4) Monitor for messages arriving to the IoT Hub with VSC

- F1 > ```Set IoT Hub connection string```

https://docs.microsoft.com/en-us/azure/iot-hub/iot-hub-live-data-visualization-in-power-bi

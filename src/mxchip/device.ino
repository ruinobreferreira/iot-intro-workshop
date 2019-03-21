#include "AZ3166WiFi.h"
#include "DevKitMQTTClient.h"

#include "Sensor.h" /* RGB_LED */
//#include "SystemVersion.h"
//#include "http_client.h"
//#include "telemetry.h"

static bool hasWifi = false;
static bool hasIoTHub = false;

void setup() {

  SensorInit();

  // put your setup code here, to run once:
  if (WiFi.begin() == WL_CONNECTED)
  {
    hasWifi = true;
    Screen.print(1, "Running...");

    if (!DevKitMQTTClient_Init())
    {
      hasIoTHub = false;
      return;
    }
    hasIoTHub = true;
  }
  else
  {
    hasWifi = false;
    Screen.print(1, "No Wi-Fi");
  }
}

static struct _tagRGB
{
  int red;
  int green;
  int blue;
} _rgb[] =
{
  { 255,   0,   0 },
  {   0, 255,   0 },
  {   0,   0, 255 },
};

static RGB_LED rgbLed;
static int color = 0;
static int led = 0;


static int delayValue = 5000;
static int messageId = 0;

void loop() {
  // put your main code here, to run repeatedly:

  char message[256];

  if(hasWifi && IsButtonClicked(USER_BUTTON_A))
  {
    delayValue = delayValue - 200;
    if ( delayValue < 500 )
      delayValue = 500;
  }
  else
  {
    if(hasWifi && IsButtonClicked(USER_BUTTON_B))
    {
      delayValue = delayValue + 200;
      if ( delayValue > 10000 )
        delayValue = 10000;
    }
  }

  if (hasIoTHub && hasWifi)
  {
    char buff[128];

    rgbLed.setColor(_rgb[2].red, _rgb[2].green, _rgb[2].blue);
    
    // replace the following line with your data sent to Azure IoTHub
    snprintf(
      buff, 
      128, 
      "{\"messageId\":\"%d\", \"deviceId\":\"MxChip\", \"temperature\": %f, \"humidity\": %f }", 
      messageId++,
      readTemperature(),
      readHumidity());

    if (DevKitMQTTClient_SendEvent(buff))
    {
      rgbLed.setColor(_rgb[1].red, _rgb[1].green, _rgb[1].blue);
      //Screen.print(1, "Sending...");
      strcpy(message, "Sent\n");
    }
    else
    {
      rgbLed.setColor(_rgb[0].red, _rgb[0].green, _rgb[0].blue);
      //Screen.print(1, "Failure...");
      strcpy(message, "Failure\n");
    }
  }

  char str[100];
  sprintf(str, "Wait %d ms...", delayValue);
  strcat(message, str);

  Screen.print(1, message);

  delay(100);
  rgbLed.turnOff();

  delay(delayValue);

  /*
  if (DevKitMQTTClient_ReceiveEvent())
  {
    strcpy(message, "Message received");
    delay(delayValue);
    Screen.print(1, message);
  }
  */
}

bool IsButtonClicked(unsigned char ulPin)
{
    pinMode(ulPin, INPUT);
    int buttonState = digitalRead(ulPin);
    if(buttonState == LOW)
    {
        return true;
    }
    return false;
}

HTS221Sensor *sensor;
DevI2C *i2c;

float readTemperature()
{
    sensor->reset();

    float temperature = 0;
    sensor->getTemperature(&temperature);

    return temperature;
}

float readHumidity()
{
    sensor->reset();

    float humidity = 0;
    sensor->getHumidity(&humidity);

    return humidity;
}

void SensorInit()
{
    i2c = new DevI2C(D14, D15);
    sensor = new HTS221Sensor(*i2c);
    sensor->init(NULL);
}

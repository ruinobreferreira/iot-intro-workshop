#include "AZ3166WiFi.h"
#include "DevKitMQTTClient.h"

#include "Sensor.h" /* RGB_LED */

static bool hasWifi = false;
static bool hasIoTHub = false;

static int counterA = 0;
static int counterB = 0;
static int updates = 0;

void setup() {

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

  updates = 0;

  char message[256];

  if(IsButtonClicked(USER_BUTTON_A))
  {
    counterA++;
    updates++;
  }
  else
  {
    if(IsButtonClicked(USER_BUTTON_B))
    {
      counterB++;
      updates++;
    }
  }

  if (hasIoTHub && hasWifi && (updates>0))
  {
    char buff[128];

    rgbLed.setColor(_rgb[2].red, _rgb[2].green, _rgb[2].blue);
    
    // replace the following line with your data sent to Azure IoTHub
    snprintf(
      buff, 
      128, 
      "{\"messageId\":\"%d\", \"deviceId\":\"MxChip\", \"counterA\": %d, \"counterB\": %d }", 
      messageId++,
      counterA,
      counterB);

    if (DevKitMQTTClient_SendEvent(buff))
    {
      rgbLed.setColor(_rgb[1].red, _rgb[1].green, _rgb[1].blue);
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
  sprintf(str, "MS@PixelsCamp\nClicks %d %d...\nSOMOS XBOX", counterA, counterB);

  Screen.print(1, str);

  delay(1000);
  rgbLed.turnOff();

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

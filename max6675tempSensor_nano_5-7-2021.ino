#include <max6675.h>
#include <Wire.h>

double tempCalibrationOffsetCelsius = -1.75;
double tempCalibrationOffsetF = tempCalibrationOffsetCelsius*1.8;

//for display
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//cannot change these pins. native to arduino type for SPI communication
int pinSO = 12; //SO (aka MISO pin)
int pinCS = 10; //CS (aka chip select aka SS)
int pinSCK = 13;

MAX6675 ts(pinSCK, pinCS, pinSO);
 
void setup()
{

  pinMode(pinCS, OUTPUT);
  Serial.begin(9600);
  // wait for MAX chip to stabilize
  //delay(500);

  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64. Changed D to C
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
}
 
void loop()
{

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.setTextSize(2);
  display.println(F("Temp:"));
  display.setTextSize(1);
  display.println();
  display.setTextSize(2);
  display.print(ts.readCelsius() + tempCalibrationOffsetCelsius);
  display.println(F(" C"));
  display.setTextSize(1);
  display.println();
  display.setTextSize(2);
  display.print(ts.readFahrenheit() + tempCalibrationOffsetF);
  display.println(F(" F"));
  display.display();
  
  Serial.print(ts.readCelsius());
  Serial.print(" C / ");
  Serial.print(ts.readFahrenheit());
  Serial.print(" F / ");
  Serial.println();

   // For the MAX6675 to update, you must delay AT LEAST 250ms between reads!
  delay(500);
}

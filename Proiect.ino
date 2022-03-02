#include <LiquidCrystal.h>
#define SAMPLE_TIME 100
#define SENSOR_PIN  A0

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

void setup() 
{
	Serial.begin(9600);
    lcd.begin(16, 2);
	
	pinMode(SENSOR_PIN, INPUT);
}

void loop() 
{
	int adcValue = analogRead(A0);
	double voltage = 5.0/1023.0 * (double)adcValue;
	double temperature = voltage * 100.0;
	
	lcd.setCursor(0, 0);
	lcd.print("Temp = " + String(temperature) + " *C");
	
	delay(SAMPLE_TIME);
}

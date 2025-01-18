// Existing includes and definitions remain unchanged
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd1(0x27, 16, 2);
LiquidCrystal_I2C lcd2(0x26, 16, 2);

Servo myservo1;
Servo myservo2;

int pos = 0;
int led1 = 11;
int led2 = 13;
int led3 = 12;
int led4 = 10;
int buz = 6;
int IR1 = 2;
int IR2 = 4;
int IR3 = 3;
int IR4 = 5;
int Slot = 10;
int var = 0;

// Motor driver pins
const int motorIn1 = 0;  // Direction pin 1
const int motorIn2 = 1;  // Direction pin 2
const int motorENA = 7; // Speed control pin (PWM)

// Button pins
const int buttonUp = A0;   // Button to elevate the lift
const int buttonDown = A1; // Button to descend the lift

void setup()
{
	lcd1.init();
	lcd1.backlight();
	lcd2.init();
	lcd2.backlight();

	// LED pins
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
    pinMode(led4, OUTPUT);
    pinMode(buz, OUTPUT);

    // IR pins
	pinMode(IR1, INPUT);
    pinMode(IR2, INPUT);
    pinMode(IR3, INPUT);
    pinMode(IR4, INPUT);

	myservo1.attach(9);
	myservo1.write(0);
	myservo2.attach(8);
	myservo2.write(0);

	// Motor driver pins
    pinMode(motorIn1, OUTPUT);
    pinMode(motorIn2, OUTPUT);
    pinMode(motorENA, OUTPUT);

    // Button pins
    pinMode(buttonUp, INPUT_PULLUP);
    pinMode(buttonDown, INPUT_PULLUP);

	lcd1.setCursor(0, 0);
	lcd1.print("     ARDUINO    ");
	lcd1.setCursor(0, 1);
	lcd1.print(" PARKING SYSTEM ");
	delay(2000);
	lcd1.clear();
	lcd2.setCursor(0, 0);
	lcd2.print("     ARDUINO    ");
	lcd2.setCursor(0, 1);
	lcd2.print(" PARKING SYSTEM 2 ");
	delay(2000);
	lcd2.clear();
}

void loop()
{

	if (digitalRead(IR1) == LOW && Slot > 0)
	{
		{
			lcd1.setCursor(0, 0);
			lcd1.print("    CAR    ");
			lcd1.setCursor(0, 1);
			lcd1.print("  detected  ");
			digitalWrite(led2, HIGH);
			tone(buz, 1000);
			delay(1000);
			noTone(buz);
			lcd1.clear();
			for (pos = 0; pos <= 90; pos += 1)
			{ // goes from 0 degrees to 90 degrees
				// in steps of 1 degree
				myservo1.write(pos); // tell servo to go to position in variable 'pos'
				tone(buz, 200);
				if (pos % 15 == 0)
				{
					noTone(buz);
				};
				delay(15); // waits 15ms for the servo to reach the position
			}
			lcd1.setCursor(0, 0);
			lcd1.print("  please  ");
			lcd1.setCursor(0, 1);
			lcd1.print("  enter ");
			digitalWrite(led2, LOW);
			digitalWrite(led1, HIGH);

			delay(3000);

			lcd1.clear();
			while (digitalRead(IR2) == HIGH)
			{
				delay(10);
			}
			for (pos = 90; pos >= 0; pos -= 1)
			{ // goes from 90 degrees to 0 degrees
				myservo1.write(pos);
				tone(buz, 200); // tell servo to go to position in variable 'pos'
				delay(15);
				if (pos % 15 == 0)
				{
					noTone(buz);
				}; // waits 15ms for the servo to reach the position
			};
			Slot = Slot - 1;
		}
		digitalWrite(led1, LOW);
		noTone(buz);
		lcd1.setCursor(0, 0);
		lcd1.print("  car  ");
		lcd1.setCursor(0, 1);
		lcd1.print("  entered ");
		delay(3000);
		lcd1.clear();
	}

	if (digitalRead(IR1) == LOW && Slot == 0)
	{
		lcd1.setCursor(0, 0);
		lcd1.print("    SORRY :(    ");
		lcd1.setCursor(0, 1);
		lcd1.print("  Parking Full  ");
		digitalWrite(led2, HIGH);
		tone(buz, 1500);
		delay(3000);
		noTone(buz);
		lcd1.clear();
		digitalWrite(led2, LOW);
	}

	if (digitalRead(IR4) == LOW)
	{
		lcd2.setCursor(0, 0);
		lcd2.print(" Entry on the ");
		lcd2.setCursor(0, 1);
		lcd2.print("  other side   ");
		digitalWrite(led4, HIGH);
		tone(buz, 1500);
		delay(3000);
		noTone(buz);
		lcd2.clear();
		digitalWrite(led4, LOW);
	}

	if (digitalRead(IR2) == LOW)
	{
		lcd1.setCursor(0, 0);
		lcd1.print("    Opps    ");
		lcd1.setCursor(0, 1);
		lcd1.print("Please use exit");
		digitalWrite(led2, HIGH);
		tone(buz, 1500);
		delay(3000);
		noTone(buz);
		lcd1.clear();
		digitalWrite(led2, LOW);
	}

	if (digitalRead(IR3) == LOW && Slot < 10)
	{
		{
			lcd2.setCursor(0, 0);
			lcd2.print("    CAR    ");
			lcd2.setCursor(0, 1);
			lcd2.print("  detected  ");
			tone(buz, 1000);
			delay(1000);
			noTone(buz);
			lcd2.clear();
			for (pos = 0; pos <= 90; pos += 1)
			{ // goes from 0 degrees to 90 degrees
				// in steps of 1 degree
				myservo2.write(pos);
				tone(buz, 200);
				if (pos % 15 == 0)
				{
					noTone(buz);
				}; // tell servo to go to position in variable 'pos'
				delay(15); // waits 15ms for the servo to reach the position
			}
			lcd2.setCursor(0, 0);
			lcd2.print("  please  ");
			lcd2.setCursor(0, 1);
			lcd2.print("  leave ");
			delay(3000);
			lcd2.clear();
			while (digitalRead(IR4) == HIGH)
			{
				delay(10);
			}
			for (pos = 90; pos >= 0; pos -= 1)
			{ // goes from 90 degrees to 0 degrees
				myservo2.write(pos);
				tone(buz, 200);
				if (pos % 15 == 0)
				{
					noTone(buz);
				}; // tell servo to go to position in variable 'pos'
				delay(15); // waits 15ms for the servo to reach the position
			};
			Slot = Slot + 1;
		}
		lcd2.setCursor(0, 0);
		lcd2.print("  car  ");
		lcd2.setCursor(0, 1);
		lcd2.print("  left ");
		delay(3000);
		lcd2.clear();
	}
	
	// Lift control logic
    if (digitalRead(buttonUp) == LOW)
    { // If "Up" button is pressed
        digitalWrite(motorIn1, HIGH);
        digitalWrite(motorIn2, LOW);
        analogWrite(motorENA, 255); // Full speed
    }
    else if (digitalRead(buttonDown) == LOW)
    { // If "Down" button is pressed
        digitalWrite(motorIn1, LOW);
        digitalWrite(motorIn2, HIGH);
        analogWrite(motorENA, 255); // Full speed
    }
    else
    {
        // Stop the motor when no button is pressed
        digitalWrite(motorIn1, LOW);
        digitalWrite(motorIn2, LOW);
    }

	lcd1.setCursor(0, 0);
	lcd1.print("    WELCOME!    ");
	lcd1.setCursor(0, 1);
	lcd1.print("Slot Left: ");
	lcd1.print(Slot);
	lcd2.setCursor(0, 0);
	lcd2.print("    WELCOME!    ");
	lcd2.setCursor(0, 1);
	lcd2.print("Slot Left: ");
	lcd2.print(Slot);
}

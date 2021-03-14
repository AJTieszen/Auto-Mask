#include <Servo.h>

// Pin Numbers
#define ServoPin 3
#define ButtonPin 4
#define HallPin 0

// Constants
#define moveTime 500
#define hallSensitivity 3;

Servo servo;

bool maskOpen, maskHold, maskState;   // 1 = open, 0 = close; maskOpen -> Hall effect sensor, maskHold -> button, maskState -> current position
int hall, hallDefault;                // used to determine Hall effect sensor status



void setup() {
  Serial.begin(9600);

  open_mask();                        // Set mask to known state
  maskState = true;
  maskHold = true;
  maskOpen = false;

  hallDefault = analogRead(HallPin);  // store the Hall Effect sensor's "ambient" reading
}

void loop() {
  if(digitalRead(ButtonPin))          // Read button
  {
    maskHold = !maskHold;
    Serial.print("Pressed");
  }

//  hall = analogRead(HallPin);         // Read Hall-effect sensor
//  maskOpen = abs(hall - hallDefault) > hallSensitivity;

  if(maskOpen || maskHold)             // Open mask if not already open
  {
    if (!maskState)
    {
      open_mask();
      maskState = true;
    }
  }
  else                                 // Close mask if not already closed
  {
    if (maskState)
    {
      close_mask();
      maskState = false;
    }
  }

  delay(100);
}



void open_mask()
{
  servo.attach(ServoPin);
  servo.write(30);
  delay(moveTime);
  servo.detach();
}

void close_mask()
{
  servo.attach(ServoPin);
  servo.write(180);
  delay(moveTime);
  servo.detach();
}

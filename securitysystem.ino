//Adding Libraries to the code
#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>
#include <Stepper.h>
LiquidCrystal lcd (7,8,10,11,12,13); //adding pins to the LCD display
const int Revolution = 500; //the revolution of the stepper motor for both directions
const byte ROWS = 4; //Enable 4 rows on the keypad
const byte COLS = 4; //Enable 4 columns on the keypad

//Adding characters on the rows and columns section for the keypad
char keys[ROWS][COLS] = {
 {'1','2','3', 'A'}, //filled out row 1(1,2,3, A)
 {'4','5','6', 'B'}, //filled out row (4,5,6, B)
 {'7','8','9', 'C'}, //filled out row 3 (7,8,9,C)
 {'*','0','#', 'D'}, //filled out row (*,0,#,D)
};


byte rowPins[ROWS] = {53,51,49,47}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {45,43,41,39}; //connect to the column pinouts of the keypad


//Create variables for the keypad on the row, columns, column pins, and row pins
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

//servo motor
Servo myservo; //create a variable for the servo motor

//define servo pin
#define servoPin 52

//create a variable to store servo position
int angle = 0; //create a variable for the angle of servo motor
Stepper stepper(Revolution, 29,25,27,23); //pins for the stepper motor


void setup() {
 Serial.begin(9600); //counts the serial monitor by the amount of times
 lcd.begin(16, 2); //sets up the LCD 16x2
 lcd.print(" Security System "); //prints out security system on the LCD display
 lcd.setCursor(0, 1); //the statement is in column 1
 lcd.print(" ON "); //prints the statement to ON when turning on the security system
 delay(3000); //delays the two statements by 3 seconds
 lcd.clear(); //clears the two statements after 3 seconds
 myservo.attach(servoPin); //attach the servo pin onto the servo motor
 stepper.setSpeed(70); //speed of the stepper motor in both directions
}


void loop () {
 lcd.clear(); //clears the two statements after 3 seconds
 lcd.setCursor(0,0); //sets the cursor at position (0,0)
 lcd.print("Enter Password"); //prints out “enter password” on the LCD display
 myservo.write(0); //no angle on the servo motor is turning
 char num = keypad.getKey(); //create a character variable for the keypad
 Serial.println(num); //prints out the digit that is assigned in the keypad

 //while loop on pressing an assigned key digit on the keypad
 while (num == NO_KEY)
 {
 num = keypad.getKey();
 }
  
//if statement on pressing an assigned digit on the keypad
if (num == '2') {
 lcd.clear(); //clears the two statements after 3 seconds
 lcd.setCursor(0,0); //sets the cursor at position (0,0)
 lcd.print("Access Granted"); //gives access granted after pressing the correct digit
 delay(2000); //delays by 2 seconds
 lcd.clear(); //clears the statement after 2 seconds
 lcd.print("Unlocking"); //prints out “unlocking” on the LCD display
 delay(2000); //delays by 2 seconds
 myservo.write(90); //turn the servo motor at 90 degrees when unlocking the door
 stepper.step(Revolution); //turn the step revolution from an assigned integer
 delay(5000); //delays by 5 seconds
 lcd.clear(); //clear the display after 5 seconds
 lcd.setCursor(0,0); //sets the cursor at position (0,0)
 lcd.print("Closing"); //closes the security system
 delay(1000); //delays at 1 second
 stepper.step(-500); //the stepper motor goes back to 500 rpm

}
  
  
//if key does not equal password, deny access
else {
 lcd.clear(); //clears the display from the previous statement
 lcd.setCursor(0,0); //sets the cursor at position (0,0)
 lcd.print("Access Denied"); //prints a statement “Access denied” if pressing the wrong digit
 delay (1000); //delays the statement for 1 second
}
  
}

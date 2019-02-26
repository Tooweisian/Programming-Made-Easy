/*Wei-Jie Zhou, MYP Project 2018-2019 Class
 * LC A 6th Hour Interdisc
 * Start of Program
*/

//This is a Library. Libraries are prewritten code to perform a certain task. The Library <SoftwareSerial.h> Allows the car itself to talk with the phone and computer.
#include <SoftwareSerial.h>

//Variables
//https://www.arduino.cc/en/Reference/SoftwareSerialRead
SoftwareSerial BT(10, 11); // RX | TX

//These Pins are the input and output; This is used to control the direction of each motor. I have indicated where each motor is located in the board.
//Motor A; Bottom RIGHT Wheel
const int motorPin1  = 6; // Pin 14 of L293
const int motorPin2  = 7; // Pin 10 of L293
//Motor B; Bottom LEFT Wheel
const int motorPin3  = 9; // Pin  7 of L293
const int motorPin4  = 8; // Pin  2 of L293
//Motor C; Top LEFT Wheel
const int motorPin5  = 2; //Pin 14 of L293
const int motorPin6  = 3; //Pin 10 of L293
//Motor D
const int motorPin7  = 4; //Pin 7 of L293
const int motorPin8  = 5; //Pin 2 of L293

// command read from Bluetooth or terminal
char input = '9'; 

void setup() {
    Serial.begin(9600);
    BT.begin(9600);  //Default Baud for comm, it may be different for your Module. 
    Serial.println("TYPE TO START");
}

void setMotorPower() {
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, LOW);
    digitalWrite(motorPin5, LOW);
    digitalWrite(motorPin6, LOW);
    digitalWrite(motorPin7, LOW);
    digitalWrite(motorPin8, LOW);
    
    
    // 1, activate motor
    if ( input == '1' ) {
        digitalWrite(motorPin1, LOW);
        digitalWrite(motorPin2, HIGH);
        digitalWrite(motorPin3, HIGH);
        digitalWrite(motorPin4, LOW);
        digitalWrite(motorPin5, HIGH);
        digitalWrite(motorPin6, LOW);
        digitalWrite(motorPin7, LOW);
        digitalWrite(motorPin8, HIGH);
    }
    // 2, reverse motor 
    else if ( input == '2') {
        digitalWrite(motorPin1, HIGH);
        digitalWrite(motorPin2, LOW);
        digitalWrite(motorPin3, LOW);
        digitalWrite(motorPin4, HIGH);
        digitalWrite(motorPin5, LOW);
        digitalWrite(motorPin6, HIGH);
        digitalWrite(motorPin7, HIGH);
        digitalWrite(motorPin8, LOW);   
    }
    //else if BT reads 3, turn left
    else if (input == '3') {
        digitalWrite(motorPin1, LOW);
        digitalWrite(motorPin2, HIGH);
        digitalWrite(motorPin3, LOW);
        digitalWrite(motorPin4, HIGH);
        digitalWrite(motorPin5, LOW);
        digitalWrite(motorPin6, HIGH);
        digitalWrite(motorPin7, LOW);
        digitalWrite(motorPin8, HIGH);
    }
    //else if BT read 4, turn right
    else if (input == '4') {
        digitalWrite(motorPin1, HIGH);
        digitalWrite(motorPin2, LOW);
        digitalWrite(motorPin3, HIGH);
        digitalWrite(motorPin4, LOW);
        digitalWrite(motorPin5, HIGH);
        digitalWrite(motorPin6, LOW);
        digitalWrite(motorPin7, HIGH);
        digitalWrite(motorPin8, LOW);
    }
}
 
void loop(){
    // read command from bluetooth.
    if (BT.available()>0){
        char r = BT.read();
        if ( r=='1' || r=='2' || r=='3' || r=='4'|| r=='9' ) {
          input = r; 
        }
    }
    // read command from termial
    if (Serial.available()>0) {
        //https://www.arduino.cc/en/Serial/Read
        char r = Serial.read();
        //BT.write(input);
        if ( r=='1' || r=='2' || r=='3' || r=='4'|| r=='9' ) {
          input = r; 
        }
    }

    Serial.write(input);
    // set motor power 
    setMotorPower();
    
    // run one second, then read again
    delay(100); 
}


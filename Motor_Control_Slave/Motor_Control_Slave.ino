/*
 * Motor Control/Slave Bluetooth
 */

#define EnA 11 //Arm Motor
#define EnB 3  //Camera Motor
#define In1 7  //Arm Motor
#define In2 6  //Arm Motor
#define In3 5  //Camera Motor
#define In4 4  //Camera Motor
#define Sw1 2  //Orange Left Switch
#define Sw2 10 //Yellow Right Switch
#define Sw3 12 //Green Up Switch
#define Sw4 13 //Blue Down Switch

#include <AltSoftSerial.h>
AltSoftSerial BTserial;

boolean DEBUG = true;

// Variables used for incoming data
 
const byte maxDataLength = 20;          // maxDataLength is the maximum length allowed for received data.
char receivedChars[maxDataLength+1] ;
boolean newData = false;               // newData is used to determine if there is a new command
int vertical_limit = 0; //Motor limits start at neutral position.
int horizontal_limit = 0;

void setup() {
  // Pin initializations
  pinMode(EnA, OUTPUT);
  pinMode(EnB, OUTPUT);
  
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);
  
  pinMode(Sw1, INPUT);
  pinMode(Sw2, INPUT);
  pinMode(Sw3, INPUT);
  pinMode(Sw3, INPUT);


  if (DEBUG)
  {
      // open serial communication for debugging and show the sketch name and the date compiled
      Serial.begin(38400);
      Serial.println(__FILE__);
      Serial.println(__DATE__);
      Serial.println(" ");
  }

  //  open software serial connection to the Bluetooth module.
  BTserial.begin(38400); 
  if (DEBUG)  {   Serial.println(F("AltSoftSerial started at 38400"));     }

  newData = false;
}

void loop() {
  analogWrite(EnA, 192);     //Set initial motor speed
  analogWrite(EnB, 255);
  recvWithStartEndMarkers();                // check to see if we have received any new commands
  if (newData)  {   processCommand();  }    // if we have a new command do something
}

void processCommand()
{
    newData = false;
    if (DEBUG)  {   Serial.print("recieved data = ");  Serial.println(receivedChars);         }
    if      (strcmp ("1000",receivedChars) == 0) { up();   }
    else if (strcmp ("0100",receivedChars) == 0) { left();    }
    else if (strcmp ("0001",receivedChars) == 0) { down();    }
    else if (strcmp ("0010",receivedChars) == 0) { right();    }
    else if (strcmp ("1100",receivedChars) == 0) { leftUp();    }
    else if (strcmp ("1010",receivedChars) == 0) { rightUp();    }
    else if (strcmp ("0101",receivedChars) == 0) { leftDown();    }
    else if (strcmp ("0011",receivedChars) == 0) { rightDown();    }
    else if (strcmp ("0000",receivedChars) == 0) { motorStop();    }
    else if (strcmp ("1110",receivedChars) == 0) { motorStop(); Serial.println("ERROR: Input not accepted");   }
    else if (strcmp ("1101",receivedChars) == 0) { motorStop(); Serial.println("ERROR: Input not accepted");   }
    else if (strcmp ("1011",receivedChars) == 0) { motorStop(); Serial.println("ERROR: Input not accepted");   }
    else if (strcmp ("0111",receivedChars) == 0) { motorStop(); Serial.println("ERROR: Input not accepted");   }
    else if (strcmp ("1001",receivedChars) == 0) { motorStop(); Serial.println("ERROR: Input not accepted");   }
    else if (strcmp ("0110",receivedChars) == 0) { motorStop(); Serial.println("ERROR: Input not accepted");   }
    else if (strcmp ("1111",receivedChars) == 0) { motorStop(); Serial.println("ERROR: Input not accepted");   }
    
}

void recvWithStartEndMarkers() 
{
     static boolean recvInProgress = false;
     static byte ndx = 0;
     char startMarker = '<';
     char endMarker = '>';
     if (BTserial.available() > 0) 
     {
          char rc = BTserial.read();
          if (recvInProgress == true) 
          {
               if (rc != endMarker) 
               {
                    if (ndx < maxDataLength) { receivedChars[ndx] = rc; ndx++;  }
               }
               else 
               {
                     receivedChars[ndx] = '\0'; // terminate the string
                     recvInProgress = false;
                     ndx = 0;
                     newData = true;
               }
          }
          else if (rc == startMarker) { recvInProgress = true; }
     }
}

void up(){
  if(digitalRead(Sw3) == LOW){ //Switch is pressed, stop motor
    analogWrite(EnB, 255);
    digitalWrite(In3, HIGH);
    digitalWrite(In4, HIGH);
    Serial.println("Vertical limit switch reached");
  } 
  else if(digitalRead(Sw3) == HIGH){ //Switch is not pressed, turn on motor
    analogWrite(EnB, 255);
    digitalWrite(In3, LOW);
    digitalWrite(In4, HIGH);
  }
}

void down(){
  if(digitalRead(Sw4) == LOW){
    analogWrite(EnB, 255);
    digitalWrite(In3, HIGH);
    digitalWrite(In4, HIGH);
    Serial.println("Vertical limit switch reached");
  }
  else if(digitalRead(Sw4) == HIGH){
    analogWrite(EnB, 128);
    digitalWrite(In3, HIGH);
    digitalWrite(In4, LOW);
  }
}

void left(){
  if(digitalRead(Sw1) == LOW){
    analogWrite(EnA, 255);
    digitalWrite(In1, HIGH);
    digitalWrite(In2, HIGH);
    Serial.println("Horizontal limit switch reached");
  } 
  else if(digitalRead(Sw1) == HIGH){
    analogWrite(EnA, 192);
    digitalWrite(In1, LOW);
    digitalWrite(In2, HIGH);
  }
}

void right(){
  if(digitalRead(Sw2) == LOW){
    analogWrite(EnA, 255);
    digitalWrite(In1, HIGH);
    digitalWrite(In2, HIGH);
    Serial.println("Horizontal limit switch reached");
  } 
  else if(digitalRead(Sw2) == HIGH){
    analogWrite(EnA, 192);
    digitalWrite(In1, HIGH);
    digitalWrite(In2, LOW);
  }
}

void leftUp(){ //Diagonal movement
  if(digitalRead(Sw3) == LOW and digitalRead(Sw1) == LOW){ //All OFF
      analogWrite(EnA, 255);
      analogWrite(EnB, 255);
      digitalWrite(In3, HIGH);
      digitalWrite(In4, HIGH);
      digitalWrite(In1, HIGH);
      digitalWrite(In2, HIGH);
      Serial.println("Horizontal limit switch reached");
      Serial.println("Vertical limit switch reached");
  } 
  else if(digitalRead(Sw3) == HIGH and digitalRead(Sw1) == HIGH){ //Up ON Left ON
    analogWrite(EnA, 192);
    analogWrite(EnB, 255);
    digitalWrite(In1,LOW);
    digitalWrite(In2,HIGH);
    digitalWrite(In3,LOW);
    digitalWrite(In4,HIGH);
      }
  else if(digitalRead(Sw1) == HIGH and digitalRead(Sw3) == LOW){ //Up OFF Left ON
    analogWrite(EnA, 192);
    analogWrite(EnB, 255);
    digitalWrite(In1,LOW);
    digitalWrite(In2,HIGH);
    digitalWrite(In3,HIGH);
    digitalWrite(In4,HIGH);
    Serial.println("Vertical limit switch reached");
    }
  else if(digitalRead(Sw1) == LOW and digitalRead(Sw3) == HIGH){ //Up ON Left OFF
    analogWrite(EnA, 255);
    analogWrite(EnB, 255);
    digitalWrite(In1,HIGH);
    digitalWrite(In2,HIGH);
    digitalWrite(In3,LOW);
    digitalWrite(In4,HIGH);
    Serial.println("Horizontal limit switch reached");
  }
}

void rightUp(){
  if(digitalRead(Sw3) == LOW and digitalRead(Sw2) == LOW){ //All OFF
    analogWrite(EnA, 255);
    analogWrite(EnB, 255);
    digitalWrite(In3, HIGH);
    digitalWrite(In4, HIGH);
    digitalWrite(In1, HIGH);
    digitalWrite(In2, HIGH);
    Serial.println("Horizontal limit switch reached");
    Serial.println("Vertical limit switch reached");
  } 
  else if(digitalRead(Sw3) == HIGH and digitalRead(Sw2) == HIGH){ //Up ON Right ON
    analogWrite(EnA, 192);
    analogWrite(EnB, 255);
    digitalWrite(In1, HIGH);
    digitalWrite(In2, LOW);
    digitalWrite(In3, LOW);
    digitalWrite(In4, HIGH);
  }
  else if(digitalRead(Sw2) == HIGH and digitalRead(Sw3) == LOW){ //Up OFF Right ON
    analogWrite(EnA, 192);
    analogWrite(EnB, 255);
    digitalWrite(In1, HIGH);
    digitalWrite(In2, LOW);
    digitalWrite(In3, HIGH);
    digitalWrite(In4, HIGH);
    Serial.println("Vertical limit switch reached");
  }
  else if(digitalRead(Sw2) == LOW and digitalRead(Sw3) == HIGH){ //Up ON Right OFF
    analogWrite(EnA, 255);
    analogWrite(EnB, 255);
    digitalWrite(In1, HIGH);
    digitalWrite(In2, HIGH);
    digitalWrite(In3, LOW);
    digitalWrite(In4, HIGH);
    Serial.println("Horizontal limit switch reached");
  }
}

void leftDown(){
  if(digitalRead(Sw4) == LOW and digitalRead(Sw1) == LOW){ //All OFF
    analogWrite(EnA, 255);
    analogWrite(EnB, 128);
    digitalWrite(In3, HIGH);
    digitalWrite(In4, HIGH);
    digitalWrite(In1, HIGH);
    digitalWrite(In2, HIGH);
    Serial.println("Horizontal limit switch reached");
    Serial.println("Vertical limit switch reached");
  } 
  else if(digitalRead(Sw4) == HIGH and digitalRead(Sw1) == HIGH){ //Down ON Left ON
    analogWrite(EnA, 192);
    analogWrite(EnB, 128);
    digitalWrite(In1,LOW);
    digitalWrite(In2,HIGH);
    digitalWrite(In3,HIGH);
    digitalWrite(In4,LOW);
      }
  else if(digitalRead(Sw1) == HIGH and digitalRead(Sw4) == LOW){ //Down OFF Left ON
    analogWrite(EnA, 192);
    digitalWrite(In1,LOW);
    digitalWrite(In2,HIGH);
    digitalWrite(In3,HIGH);
    digitalWrite(In4,HIGH);
    Serial.println("Vertical limit switch reached");
    }
  else if(digitalRead(Sw1) == LOW and digitalRead(Sw4) == HIGH){ //Down ON Left OFF
    analogWrite(EnA, 255);
    analogWrite(EnB, 128);
    digitalWrite(In1,HIGH);
    digitalWrite(In2,HIGH);
    digitalWrite(In3,HIGH);
    digitalWrite(In4,LOW);
    Serial.println("Horizontal limit switch reached");
  }
}

void rightDown(){
  if(digitalRead(Sw4) == LOW and digitalRead(Sw2) == LOW){ //All OFF
    analogWrite(EnA, 255);
    analogWrite(EnB, 128);
    digitalWrite(In3, HIGH);
    digitalWrite(In4, HIGH);
    digitalWrite(In1, HIGH);
    digitalWrite(In2, HIGH);
    Serial.println("Horizontal limit switch reached");
    Serial.println("Vertical limit switch reached");
  } 
  else if(digitalRead(Sw4) == HIGH and digitalRead(Sw2) == HIGH){ //All ON
    analogWrite(EnA, 192);
    analogWrite(EnB, 128);
    digitalWrite(In1, LOW);
    digitalWrite(In2, HIGH);
    digitalWrite(In3, HIGH);
    digitalWrite(In4, LOW);
  }
  else if(digitalRead(Sw2) == HIGH and digitalRead(Sw4) == LOW){ //Down Off Right ON
    analogWrite(EnA, 192);
    analogWrite(EnB, 128);
    digitalWrite(In1, LOW);
    digitalWrite(In2, HIGH);
    digitalWrite(In3, HIGH);
    digitalWrite(In4, HIGH);
    Serial.println("Vertical limit switch reached");
  }
  else if(digitalRead(Sw2) == LOW and digitalRead(Sw4) == HIGH){ //Down ON Right OFF
    analogWrite(EnA, 255);
    analogWrite(EnB, 128);
    digitalWrite(In1, HIGH);
    digitalWrite(In2, HIGH);
    digitalWrite(In3, HIGH);
    digitalWrite(In4, LOW);
    Serial.println("Horizontal limit switch reached");
  }
}

void motorStop(){
  digitalWrite(In1, HIGH);
  digitalWrite(In2, HIGH);
  digitalWrite(In3, HIGH);
  digitalWrite(In4, HIGH);
  Serial.println("Motors Stopped");
}

//MxR Motor Control

#define EnA 11 //Camera Motor
#define EnB 3  //Arm Motor
#define In1 7  //Camera Motor
#define In2 6  //Camera Motor
#define In3 5  //Arm Motor
#define In4 4  //Arm Motor
#define Sw1 2
#define Sw2 10
#define Sw3 12
#define Sw4 13

void setup() {
  pinMode(EnA, OUTPUT);
  pinMode(EnB, OUTPUT);
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);
  pinMode(Sw1, INPUT);
  pinMode(Sw2, INPUT);

}

void loop() {
  char input;             //user input
  int vertical_limit = 0; //Motor limits start at neutral position.
  int horizontal_limit = 0;
  Serial.begin(38400);
  while(1){
    analogWrite(EnA, 100);     //Set motor speed
    analogWrite(EnB, 100);
    input = Serial.read();                          //Read user input
    Serial.println(input);                          //Print user input

    if(input == 'a'){                              //User input is up                      
      vertical_limit++;                            //Add to vertical limit
      if(vertical_limit >= 10){                     //If vertical limit is reached stop motors
        Serial.println("Reached vertical limit");
        vertical_limit = 10;
        digitalWrite(In1, LOW);
        digitalWrite(In2, LOW);
      }
      else{                                         //else move motor up
        Serial.println("Moving up");
        digitalWrite(In1, HIGH);
        digitalWrite(In2, LOW); 
        delay(1000);
        digitalWrite(In1, LOW);
        digitalWrite(In2, LOW);
        Serial.println("Motors Stopped"); 
      }
    }
  
    if(input == 'd'){                               //User input is down                      
      vertical_limit--;                             //Subtract from vertical limit
      if(vertical_limit <= -10){                     //If vertical limit is reached stop motors
        Serial.println("Reached vertical limit");
        vertical_limit = -10;
        digitalWrite(In1, LOW);
        digitalWrite(In2, LOW);
      }
      else{                                         //else move motor down
        Serial.println("Moving down");
        digitalWrite(In1, LOW);
        digitalWrite(In2, HIGH);
        delay(1000);
        digitalWrite(In1, LOW);
        digitalWrite(In2, LOW);
        Serial.println("Motors Stopped");     
      }
    }
  
    if(input == 's'){                                //User input is left                      
      horizontal_limit--;                            //Subtract from horizontal limit
      if(horizontal_limit <= -10){                    //If horizontal limit is reached stop motors
        Serial.println("Reached horizontal limit");
        horizontal_limit = -10;
        digitalWrite(In3, LOW);
        digitalWrite(In4, LOW);
        
      }
      else{                                          //else move motor left
        Serial.println("Moving left");
        digitalWrite(In3, HIGH);
        digitalWrite(In4, LOW);
        delay(1000);
        digitalWrite(In3, LOW);
        digitalWrite(In4, LOW);
        Serial.println("Motors Stopped");   
      }
    }
  
    if(input == 'w'){                                //User input is right                      
      horizontal_limit++;                            //Add to horizontal limit
      if(horizontal_limit >= 10){                     //If horizontal limit is reached stop motors
        Serial.println("Reached horizontal limit");
        horizontal_limit = 10;
        digitalWrite(In3, LOW);
        digitalWrite(In4, LOW);
      }
      else{                                          //else move motor right
        Serial.println("Moving right");
        digitalWrite(In3, LOW);
        digitalWrite(In4, HIGH);
        delay(1000);
        digitalWrite(In3, LOW);
        digitalWrite(In4, LOW);
        Serial.println("Motors Stopped");   
      }
    }
    if(input == 'q'){
      vertical_limit++;
      horizontal_limit--;
      if(vertical_limit >= 10 or horizontal_limit <=-10){
         Serial.println("Reached limits");
         digitalWrite(In1, LOW);
         digitalWrite(In2, LOW); 
         digitalWrite(In3, LOW);
         digitalWrite(In4, LOW);
      }
      else{
        Serial.println("Moving left and up");
        digitalWrite(In1, HIGH);
        digitalWrite(In2, LOW);
        digitalWrite(In3, LOW);
        digitalWrite(In4, HIGH);
        delay(1000);
        digitalWrite(In1, LOW);
        digitalWrite(In2, LOW); 
        digitalWrite(In3, LOW);
        digitalWrite(In4, LOW);
        Serial.println("Motors Stopped"); 
      }
    }
    if(input == 'e'){
      vertical_limit++;
      horizontal_limit++;
      if(vertical_limit >= 10 or horizontal_limit >=10){
         Serial.println("Reached limits");
         digitalWrite(In1, LOW);
         digitalWrite(In2, LOW); 
         digitalWrite(In3, LOW);
         digitalWrite(In4, LOW);
      }
      else{
        Serial.println("Moving right and up");
        digitalWrite(In1, HIGH);
        digitalWrite(In2, LOW);
        digitalWrite(In3, HIGH);
        digitalWrite(In4, LOW);
        delay(1000);
        digitalWrite(In1, LOW);
        digitalWrite(In2, LOW); 
        digitalWrite(In3, LOW);
        digitalWrite(In4, LOW);
        Serial.println("Motors Stopped"); 
      }
    }
    if(input == 'z'){
      vertical_limit--;
      horizontal_limit--;
      if(vertical_limit <= -10 or horizontal_limit <=-10){
         Serial.println("Reached limits");
         digitalWrite(In1, LOW);
         digitalWrite(In2, LOW); 
         digitalWrite(In3, LOW);
         digitalWrite(In4, LOW);
      }
      else{
        Serial.println("Moving left and down");
        digitalWrite(In1, LOW);
        digitalWrite(In2, HIGH);
        digitalWrite(In3, LOW);
        digitalWrite(In4, HIGH);
        delay(1000);
        digitalWrite(In1, LOW);
        digitalWrite(In2, LOW); 
        digitalWrite(In3, LOW);
        digitalWrite(In4, LOW);
        Serial.println("Motors Stopped"); 
      }
    }
    if(input == 'x'){
      vertical_limit--;
      horizontal_limit++;
      if(vertical_limit <= -10 or horizontal_limit >=10){
         Serial.println("Reached limits");
         digitalWrite(In1, LOW);
         digitalWrite(In2, LOW); 
         digitalWrite(In3, LOW);
         digitalWrite(In4, LOW);
      }
      else{
        Serial.println("Moving right and down");
        digitalWrite(In1, LOW);
        digitalWrite(In2, HIGH);
        digitalWrite(In3, HIGH);
        digitalWrite(In4, LOW);
        delay(1000);
        digitalWrite(In1, LOW);
        digitalWrite(In2, LOW); 
        digitalWrite(In3, LOW);
        digitalWrite(In4, LOW);
        Serial.println("Motors Stopped"); 
      }
    }
  }
}

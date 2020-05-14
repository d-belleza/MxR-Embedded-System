#define PWMA 11 //Camera Motor
#define PWMB 3  //Arm Motor
#define In1 7  //Camera Motor
#define In2 6  //Camera Motor
#define In3 5  //Arm Motor
#define In4 4  //Arm Motor
#define Sw1 2
#define Sw2 13

void setup() {
  // put your setup code here, to run once:
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);
  pinMode(Sw1, INPUT);
  pinMode(Sw2, INPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(Sw1) == LOW or digitalRead(Sw2) == LOW){
    analogWrite(PWMA, 255);
    digitalWrite(In1, HIGH);
    digitalWrite(In2, HIGH);
  }
  else if(digitalRead(Sw1) == HIGH and digitalRead(Sw2) == HIGH){
    analogWrite(PWMA, 255);
    digitalWrite(In1, HIGH);
    digitalWrite(In2, LOW);
  }
}

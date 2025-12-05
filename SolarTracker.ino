//Include the servo motor library
 #include <Servo.h>
 //Define the LDR sensor pins
 //ldrback-----Vcc-Green GND-Yellow D0-Orange
 //ldrfrnt-----Vcc-Grey GND-Purple D0-Blue
 #define LDR1 A0
 #define LDR2 A1
 //Define the error value. You can change it as you like
 #define error 10
 int speedpin = 3;
 int dir1=4;
 int dir2=5;
 int max,min;
 int mode; //blinds open 
//Starting point of the servo motor
 int Spoint =  90;
 //Create an object for the servo motor
 Servo servo;
 void setup() {
  servo.attach(9);//Include servo motor PWM pin
  servo.write(Spoint);//initial 90 value
  delay(100);
  Serial.begin(9600);
  pinMode(speedpin, OUTPUT);
  pinMode(dir1, OUTPUT);
  pinMode(dir2,OUTPUT);
  analogWrite(speedpin,50);
  digitalWrite(dir1,LOW);//blind open
  digitalWrite(dir2,LOW);//blind open
  Serial.println("open");
  digitalWrite(dir1,LOW);
  digitalWrite(dir2,HIGH);
  delay(2000);
  Serial.println("OF");
  digitalWrite(dir1,LOW);
  digitalWrite(dir2,LOW);
  delay(1500);
  mode=1;//windows open
  max=1020;
  min=90;
 }
 void loop() {
  int ldr1 = analogRead(LDR1);//Get the LDR sensor value
  int ldr2 = analogRead(LDR2);//Get the LDR sensor value
  int value = abs(ldr1 - ldr2);//Get the difference of these values
  if (value > error) {
    if (ldr1 > ldr2) {
      Spoint = --Spoint;
    }
    if (ldr1 < ldr2) {
      Spoint = ++Spoint;
    }
  }
  servo.write(Spoint);//Write value to motor
  Spoint=constrain(Spoint,30,150);
  delay(70);
  Serial.println(ldr1);
  Serial.println(ldr2);
  if(ldr1>max && ldr2>max && mode==0)
  {
     Serial.println("Blinds are opening");
     digitalWrite(dir1,LOW);
     digitalWrite(dir2,HIGH);
     mode=1;
     delay(1500);
     digitalWrite(dir1,LOW);
     digitalWrite(dir2,LOW);
  }
  else if((ldr1< min || ldr2< min) && mode==1)
  {
    Serial.println("Blinds are closing");
    digitalWrite(dir1,HIGH);
    digitalWrite(dir2,LOW);
    mode=0;
    delay(1500);
    digitalWrite(dir1,LOW);
     digitalWrite(dir2,LOW);
  }
  else
  {
     Serial.println("OFF");
     digitalWrite(dir1,LOW);
     digitalWrite(dir2,LOW);
  }
}

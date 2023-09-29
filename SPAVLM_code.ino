#include <Ultrasonic.h>
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
#define RELAY_PIN1 19 
#define RELAY_PIN2 22
BluetoothSerial SerialBT;
int received=0;// received value will be stored in this variable
char receivedChar='b';// received value will be stored as CHAR in this variable

const char turnON1 ='a';
const char turnOFF1 ='b';
const char turnON2 ='c';
const char turnOFF2 ='d';
const int LEDpin = 18;


int motor1Pin1 = 27; 
int motor1Pin2 = 26; 
int enable1Pin = 14;

int trigPin =12;
int echoPin =13;

int motor2Pin1 = 25; 
int motor2Pin2 = 32; 
int enable2Pin = 33;
Ultrasonic ultrasonic(trigPin,echoPin);


int distance,d;
const int freq = 30000;
const int pwmChannel1 = 0;
const int pwmChannel2 = 0;
const int resolution = 8;
int dutyCycle = 170;

void setup() {
  Serial.begin(115200);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);

  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enable2Pin, OUTPUT);
  
  ledcSetup(pwmChannel1, freq, resolution);
  ledcAttachPin(enable1Pin, pwmChannel1);
  ledcWrite(pwmChannel1, dutyCycle);

  ledcSetup(pwmChannel2, freq, resolution);
  ledcAttachPin(enable2Pin, pwmChannel2);
  ledcWrite(pwmChannel2, dutyCycle);

  //Code for relay
  SerialBT.begin("SPAVLM_Boi"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  Serial.println("To turn ON send: a");//print on serial monitor  
  Serial.println("To turn OFF send: b"); //print on serial monitor 
  pinMode(LEDpin, OUTPUT);
  pinMode(RELAY_PIN1, OUTPUT); // Set relay pin as output
  pinMode(RELAY_PIN2, OUTPUT); // Set relay pin as output


}

void loop() {
  distance=ultraread();
  ll: forward();
    delay(1000);
     
 distance=ultraread();
 if(distance<50)
 {
   Stop();
   delay(1000);
   turnRight();
   turnRight();
   delay(1500);
   distance=ultraread();
   if(distance>50)
   {
    goto ll;
   }
   else
   {
    turnLeft();
    turnLeft();
    delay(1500);
    turnLeft();
    turnLeft();
    delay(1500);
     distance=ultraread();
     if(distance>50)
     {
      goto ll;
     }
     else
     {
      turnLeft();
      turnLeft();
      delay(1500);
     }
   }
 }
}
  
   

  
//    receivedChar =(char)SerialBT.read();

//  if (Serial.available()) {3
//    SerialBT.write(Serial.read());
  
//  if (SerialBT.available())
//  {
//    
//    SerialBT.print("Received:");// write on BT app
//    SerialBT.println(receivedChar);// write on BT app      
//    Serial.print ("Received:");//print on serial monitor
//    Serial.println(receivedChar);//print on serial monitor    
//    //SerialBT.println(receivedChar);//print on the app    
//    //SerialBT.write(receivedChar); //print on serial monitor
//
//
//    
//    if(receivedChar == turnON1)
//    {
//     digitalWrite(RELAY_PIN1, HIGH); // Turn on the relay
//     SerialBT.println("LED ON:");// write on BT app
//     Serial.println("LED ON:");//write on serial monitor
//     digitalWrite(LEDpin, HIGH);// turn the LED ON
//       
//    }
//    if(receivedChar == turnOFF1)
//    {
//     digitalWrite(RELAY_PIN1, LOW); // Turn off the relay
//     SerialBT.println("LED OFF:");// write on BT app
//     Serial.println("LED OFF:");//write on serial monitor
//      digitalWrite(LEDpin, LOW);// turn the LED off 
//    }    
//    
//    if(receivedChar == turnON2)
//    {
//     digitalWrite(RELAY_PIN2, HIGH); // Turn on the relay
//     SerialBT.println("LED ON:");// write on BT app
//     Serial.println("LED ON:");//write on serial monitor
//     digitalWrite(LEDpin, HIGH);// turn the LED ON
//       
//    }
//    if(receivedChar == turnOFF2)
//    {
//     digitalWrite(RELAY_PIN2, LOW); // Turn off the relay
//     SerialBT.println("LED OFF:");// write on BT app
//     Serial.println("LED OFF:");//write on serial monitor
//      digitalWrite(LEDpin, LOW);// turn the LED off 
//    }    
//  }  
//  }
//  }
    



void Stop(){ //stop
digitalWrite(motor1Pin1, LOW); //Left Motor backword Pin 
digitalWrite(motor1Pin2, LOW); //Left Motor forword Pin 
digitalWrite(motor2Pin1, LOW); //Right Motor forword Pin 
digitalWrite(motor2Pin2, LOW); //Right Motor backword Pin 
digitalWrite(RELAY_PIN1, HIGH); // Turn off the relay
}


void forward(){
digitalWrite(motor1Pin1, HIGH); //Left Motor backword Pin 
digitalWrite(motor1Pin2, LOW); //Left Motor forword Pin 
digitalWrite(motor2Pin1, LOW); //Right Motor forword Pin 
digitalWrite(motor2Pin2, HIGH); //Right Motor backword Pin 
digitalWrite(RELAY_PIN1, LOW); // Turn on the relay
}


void turnRight(){ 
digitalWrite(RELAY_PIN1, HIGH);//turnRight
digitalWrite(motor1Pin1, HIGH); //Left Motor backword Pin 
digitalWrite(motor1Pin2, LOW); //Left Motor forword Pin 
digitalWrite(motor2Pin1, HIGH); //Right Motor forword Pin 
digitalWrite(motor2Pin2, LOW); //Right Motor backword Pin 
 // Turn off the relay
}

void turnLeft(){ 
digitalWrite(RELAY_PIN1, HIGH);//turnLeft
digitalWrite(motor1Pin1, LOW); //Left Motor backword Pin 
digitalWrite(motor1Pin2, HIGH); //Left Motor forword Pin 
digitalWrite(motor2Pin1, LOW); //Right Motor forword Pin 
digitalWrite(motor2Pin2, HIGH); //Right Motor backword Pin 
 // Turn off the relay
}

int ultraread()
{
  d= ultrasonic.read();
  Serial.print("Distance in CM: ");
  Serial.println(d); 
  return d;
}

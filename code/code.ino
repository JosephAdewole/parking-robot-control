#include <MsTimer2.h>

int vSpeed = 110;        // MAX 255
int turn_speed = 230;    // MAX 255
int turn_delay = 10;



//L293 Connection   
const int motorA1      = 10;
const int motorA2      = 8;
const int motorB1      = 12;
const int motorB2      = 13;

const int move_robot_pin   = 5;
const int take_picture_pin = 6;

//Sensor Connection
const int left_sensor_pin =A0;
const int right_sensor_pin =A1;

int left_sensor_state;
int right_sensor_state;

volatile bool is_take_picture = false;


void change(){
  is_take_picture = true;
  MsTimer2::stop();
}

bool check_move_robot(){
  if  (digitalRead(move_robot_pin) == 0 ){
    return false;
  }

  return true;
}


void setup(){
  
 MsTimer2::set(3000, change); // 3000ms (3 seconds) period
//  timer2::set(100, check_move_robot); // checks move_robot_pin every 100ms
  MsTimer2::start();

  
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  
  pinMode(take_picture_pin, OUTPUT);
  pinMode(move_robot_pin, INPUT);

  digitalWrite(take_picture_pin, LOW);

  Serial.begin(9600);
  delay(1000);
}


void loop() {
    while (is_take_picture) {
      Serial.println("stop motion for picture");
      stop_motor();      
      digitalWrite(take_picture_pin, HIGH);
      delay(1000);
      
      bool can_move = check_move_robot();
      
      while(can_move == false){
        can_move = check_move_robot();
       } //blocks here till pi is done with plate number recognition 
       
      Serial.println("picture taken");
      
      digitalWrite(take_picture_pin, LOW);
      is_take_picture = false;
      delay(500);
      
      MsTimer2::start();
     }
     
    left_sensor_state = analogRead(left_sensor_pin);
    right_sensor_state = analogRead(right_sensor_pin);
    
    if(right_sensor_state < 500 && left_sensor_state > 500)
    {
      Serial.println("turning right");
      turn_right();
    }
    
    if(right_sensor_state > 500 && left_sensor_state < 500)
    {
      Serial.println("turning left");
      turn_left();
      delay(turn_delay);
    }
    
    if(right_sensor_state < 500 && left_sensor_state < 500)
    {
      Serial.println("stop");
      stop_motor();
      delay(turn_delay);
    }
    
    if(right_sensor_state > 500 && left_sensor_state > 500){ 
        Serial.println("going forward");
        move_forward();
    }

}


void stop_motor(){
    digitalWrite(motorA2,LOW);
    digitalWrite(motorA1,LOW);                       
    digitalWrite(motorB2,LOW);
    digitalWrite(motorB1,LOW);
}

void move_forward(){
   digitalWrite(motorA2,HIGH);
        digitalWrite(motorA1,LOW);                       
        digitalWrite(motorB2,LOW);
        digitalWrite(motorB1,HIGH);
}

void turn_left(){
    digitalWrite (motorA1,HIGH);
    digitalWrite(motorA2,LOW);                       
    digitalWrite (motorB1,HIGH);
    digitalWrite(motorB2,LOW);
}

void turn_right(){
    digitalWrite (motorA1,LOW);
    digitalWrite(motorA2,HIGH);                       
    digitalWrite (motorB1,LOW);
    digitalWrite(motorB2,HIGH);
}

 

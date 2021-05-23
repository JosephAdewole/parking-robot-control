# Mawaqif Robot Control

The Robot has 2 of it's major functions handled here in the .\code.ino .\code.ino file.
These functions include:
1. Robot Line Following
2. Robot Checks Start, Robot Motion Pause, Robot Motion Continue  and Robot Final Stop

These functions are solved in this system by the Arduino code written in the file code.ino .

The Components used in this project include:
- Arduino UNO,
- Raspberry Pi 3b,
- L298 Motor Driver,
- ROBOT 2 WHEELS VEHICLE CHASSIS,
- IR Sensor x 2,
- male to female jumper wires,
- female to female jumper wires,
- 1k resistor ,
- Power Bank

# Robot Line Following

This function is based on the robot following a WHITE LINE on a BLACK parking lot ground.
2 IR Sensors on either sides of the front part of the robot watch for reflection. 
## We check for 4 conditions, at which we either:
1. Turn the robot right
2. Turn the robot left
3. Move the robot forward or
4. Stop the robot

### 1.  Turn the robot right
  If this value is less than 500 as read by the right sensor(right_sensor_state) and greater than 500 as read by the left sensor(left_sensor_state), the robot moves to the right, sinceit has detected the brighter surface(White Line) on the right side.
```
if(right_sensor_state < 500 && left_sensor_state > 500)
    {
      Serial.println("turning right");
      turn_right();
    } 
```
    
### 2.  Turn the robot left:
 If this value is greater than 500 as read by the right sensor(right_sensor_state) and less than 500 as read by the left sensor(left_sensor_state), the robot moves to the right, sinceit has detected the brighter surface(White Line) on the left side.
```
if(right_sensor_state > 500 && left_sensor_state < 500)
    {
      Serial.println("turning left");
      turn_left();
      delay(turn_delay);
    }
``` 
### 3.  Stop the robot
If this value is less than 500 as read by the right sensor(right_sensor_state) and also less than 500 as read by the left sensor(left_sensor_state), the robot **stops**. This is because the robot has sensed that there are refective surfaces on either side of it. In this system, this means that it has reached the very end of its Path.
```
if(right_sensor_state < 500 && left_sensor_state < 500)
    {
      Serial.println("stop");
      stop_motor();
      delay(turn_delay);
    }
```

### 4.  Move the robot forward 
When the white line which determines the path of the robot's motion is straight, however, the IR sensors do not detect an increase in reflection on any side. This means that the line on the floor is in the middle of the robot and the robot can continue to move forward.
```
if(right_sensor_state > 500 && left_sensor_state > 500){ 
        Serial.println("going forward");
        move_forward();
    }
```
### The functions below were called in the commands above. Basically, they all involve Writing a particular Speed(Voltage) to 4 pins which are connected to the L293 Motor Driver-  
```
const int motorA1      = 10;
 const int motorA2      = 8;
 const int motorB1      = 12;
 const int motorB2      = 13;
```

Below are the functions in question:
```
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


```
## Robot Checks Start, Robot Motion Pause to Take Picture, Robot Motion Continue and Robot Final Stop

Another important function of the robot is to ** Pause ** the motion of the Robot in order to let the Raspberry Pi Camera take a picture of a Licence plate.
After 3000 milliseconds of the robot motion( Assuming that each Parking Space is 3s apart from the next one), the robot stops to take a picture.
Now, the Arduino keeps checking the __move_robot_pin__  to know when the Raspberry Pi has sent a signal indicating that a picture has been taken and the robot can now move forward.
This is shown below:
```
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
     
```

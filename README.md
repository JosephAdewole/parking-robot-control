# Mawaqif Robot Control

The Robot has 2 of it's major functions handled here in the code.ino file.
These functions include:
1. Robot Line Following
2. Robot Checks Start, Robot Motion Pause, Robot Motion Continue  and Robot Final Stop

These functions are solved in this system by the Arduino code written in the file code.ino .

The Components used in this project include:
Arduino UNO,
Rspberry Pi 3b,
L298 Motor Driver,
ROBOT 2 WHEELS VEHICLE CHASSIS,
IR Sensor x 2,
male to female jumper wires,
female to female jumper wires,
1k resistor ,
Power Bank

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
 if(right_sensor_state > 500 && left_sensor_state < 500)
    {
      Serial.println("turning left");
      turn_left();
      delay(turn_delay);
    }
 
### 3.  Move the robot forward 


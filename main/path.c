#include <stdint.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "common_defines.h"
#include "ultrasonic.h"

//makes the robot following the left hand side of the maze
uint8_t decide_path(ultrasonic_sensor_parameters_t ultrasonicSensorParameters){
    if(ultrasonicSensorParameters.leftDistance > 20){
        return LEFT; 
    }

    if(ultrasonicSensorParameters.rightDistance && ultrasonicSensorParameters.frontDistance > 20){
        return FORWARD; 
    }

    if(ultrasonicSensorParameters.rightDistance > 20 && ultrasonicSensorParameters.frontDistance < 20){
        return RIGHT; 
    }
return 0; 
}
#ifndef _PATH_H__
#define _PATH_H_
#include <stdint.h>
#include "hc_sr_04_ultrasonic_sensor.h"


typedef enum {
    LEFT_TURN,
    RIGHT_TURN, 
    U_TURN
}driving_action_t; 

typedef struct{
    driving_action_t currentAction; 
    uint64_t timeSinceAction;
}direction_and_time_of_action_t; 

typedef struct{
    int numberOfActions;
    direction_and_time_of_action_t currentRunPath[50]; 
}actions_taken_by_robot_t;

void add_action_to_current_path(driving_action_t action, actions_taken_by_robot_t *actionsTakenByRobot); 
uint8_t is_making_an_action(actions_taken_by_robot_t actionsTakenByRobot, driving_action_t currentTurn); 
#endif
#include <stdint.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_timer.h>
#include "common_defines.h"
#include "ultrasonic.h"
#include "path.h"

void add_action_to_current_path(driving_action_t action, actions_taken_by_robot_t *actionsTakenByRobot){
    actionsTakenByRobot->currentRunPath[actionsTakenByRobot->numberOfActions].currentAction = action; 
    actionsTakenByRobot->currentRunPath[actionsTakenByRobot->numberOfActions].timeSinceAction = esp_timer_get_time();
    return; 
}

 //this function checks if the last turn made is the same as the robot wants to do now, and if that turn was made was less then 5 seconds ago.
//if thats the case, skip this turn action. This is for timing issues when comming back from a dead end. 
uint8_t is_making_an_action(actions_taken_by_robot_t actionsTakenByRobot, driving_action_t currentTurn){
    if((actionsTakenByRobot.currentRunPath[actionsTakenByRobot.numberOfActions-1].currentAction == currentTurn) && 
    (esp_timer_get_time() - actionsTakenByRobot.currentRunPath[actionsTakenByRobot.numberOfActions-1].timeSinceAction < 5000000)){
        printf("no turn to %d", currentTurn);
        return 0;
    }
    return 1;  
}
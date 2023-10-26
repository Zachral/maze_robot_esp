#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_err.h>
#include <esp_log.h>
#include <i2cdev.h> 
#include <esp_timer.h>
#include <stdbool.h>
#include "hc_sr_04_ultrasonic_sensor.h"
#include "servo.h"
#include "driver/mcpwm_prelude.h"
#include "common_defines.h"
#include "led.h"
#include "button.h"
#include "tcs3200_color_sensor.h"
#include "mpu6050.h"
#include "path.h"

static const char *MPU6050 = "mpu6050";

void app_main(void)
{
    actions_taken_by_robot_t actionsTakenByRobot; 
    actionsTakenByRobot.numberOfActions = 0; 
    ultrasonic_sensor_parameters_t ultrasonicSensorParameters; 
    mcpwm_cmpr_handle_t left_servo = left_servo_init(); 
    mcpwm_cmpr_handle_t right_servo = right_servo_init(); 
    mpu6050_dev_t mpu6050Sensor = { 0 };
    mpu6050_rotation_t rotation = { 0,0,0 };
    double gyroErrorZ  = 0.0, yaw = 0.0;
    uint64_t previousTime = esp_timer_get_time(); 
    uint64_t timeSinceLastSensorReading = 0; 
    TaskHandle_t flashLEDHandle = NULL; 
    bool isPressed = false; 
    led_init();
    xTaskCreate(flash_led, "Flash LED", 4096, NULL, 1, &flashLEDHandle);
    ultrasonic_init(&ultrasonicSensorParameters); 
    color_sensor_init(); 
    ESP_ERROR_CHECK(i2cdev_init());
    calibrate_mpu6050(mpu6050Sensor, &rotation, &gyroErrorZ); 
    vTaskDelete(flashLEDHandle);
    light_led(); 
    //runs until button is pressed, need to be handled better
    button_click(&isPressed); 
    turn_of_led(); 


    while (isPressed){
      drive_forward(left_servo, right_servo);  
      read_ultrasonic_sensors(&ultrasonicSensorParameters); 
      
      if(ultrasonicSensorParameters.leftDistance < 6){
        stabilize(left_servo, right_servo, LEFT); 
      }
      if(ultrasonicSensorParameters.rightDistance < 6){
        stabilize(left_servo, right_servo, RIGHT); 
      }

      if(ultrasonicSensorParameters.frontDistance < 9){; 
        vTaskDelay(pdMS_TO_TICKS(200)); 
        stop(left_servo, right_servo); 
        if(detect_red_color()){
          light_led();
          break; 
        }else{
          stop(left_servo,right_servo); 
          u_turn(left_servo,right_servo, ultrasonicSensorParameters, mpu6050Sensor, &rotation, &gyroErrorZ,&yaw, &previousTime);
          stop(left_servo,right_servo);
          add_action_to_current_path(U_TURN, &actionsTakenByRobot); 
          actionsTakenByRobot.numberOfActions++; 
          reset_ultrasonic_sensors(&ultrasonicSensorParameters); 
        }
      }


      if(esp_timer_get_time() - timeSinceLastSensorReading > 450000){  
        if((ultrasonicSensorParameters.leftDistance > 25) &&  is_making_an_action(actionsTakenByRobot, LEFT_TURN)){
            vTaskDelay(pdMS_TO_TICKS(1200));
            stop(left_servo,right_servo); 
            turn_left(left_servo, right_servo, mpu6050Sensor, &rotation, &gyroErrorZ, &yaw, &previousTime);
            stop(left_servo,right_servo);
            add_action_to_current_path(LEFT_TURN, &actionsTakenByRobot);
            actionsTakenByRobot.numberOfActions++; 
          }

        if((ultrasonicSensorParameters.rightDistance > 25) && is_making_an_action(actionsTakenByRobot, LEFT_TURN)){
            vTaskDelay(pdMS_TO_TICKS(1200));
            stop(left_servo,right_servo); 
            turn_right(left_servo, right_servo, mpu6050Sensor, &rotation, &gyroErrorZ, &yaw, &previousTime);
            stop(left_servo,right_servo); 
            add_action_to_current_path(RIGHT, &actionsTakenByRobot);
            actionsTakenByRobot.numberOfActions++; 
        }
      timeSinceLastSensorReading = esp_timer_get_time(); 
      }
      vTaskDelay(pdMS_TO_TICKS(10)); 
    }
    
}

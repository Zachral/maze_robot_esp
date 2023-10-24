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
#include "ultrasonic.h"
#include "servo.h"
#include "driver/mcpwm_prelude.h"
#include "common_defines.h"
#include "led.h"
#include "button.h"
#include "color_sensor.h"
#include "mpu6050.h"
#include "path.h"

//#define CONFIG_EXAMPLE_SDA_GPIO     GPIO_NUM_18
//#define CONFIG_EXAMPLE_SCL_GPIO     GPIO_NUM_19
//left trigger pin  5
//left echo pin 17
//front trigger pin 22
//front echo pin 23
//right trigger pin 32 
//right echo pin 33
//servo left 15
//servo right 13
//color sensor out 21
//color sensor s2 4
//color sensor s3 16
//color sensor s0 26
//color sensor s1 27
//button 14
//led led 25


static const char *MPU6050 = "mpu6050";

void app_main(void)
{
    ultrasonic_sensor_parameters_t ultrasonicSensorParameters; 
    mcpwm_cmpr_handle_t left_servo = left_servo_init(); 
    mcpwm_cmpr_handle_t right_servo = right_servo_init(); 
    mpu6050_dev_t mpu6050Sensor = { 0 };
    mpu6050_rotation_t rotation = { 0,0,0 };
    double gyroErrorZ  = 0.0, yaw = 0.0;
    uint64_t previousTime = esp_timer_get_time(); 
    TaskHandle_t flashLEDHandle = NULL; 
    TaskHandle_t ultrasonicSensorHandle = NULL; 
    uint8_t driveDirection; 
    bool isPressed = false; 
    led_init();
    xTaskCreate(flash_led, "Flash LED", 4096, NULL, 1, &flashLEDHandle);
    ultrasonic_init(&ultrasonicSensorParameters); 
    color_sensor_init(); 
    ESP_ERROR_CHECK(i2cdev_init());
    //calibrate_mpu6050(mpu6050Sensor, &rotation, &gyroErrorZ); 
    vTaskDelete(flashLEDHandle);
    light_led(); 
    //runs until button is pressed.
    button_click(&isPressed); 
    xTaskCreate(read_ultrasonic_sensors, "ultrasonic reading", 4096, &ultrasonicSensorParameters, 5, &ultrasonicSensorHandle); 
    turn_of_led(); 


    while (isPressed){
      drive_forward(left_servo, right_servo);  
      
      if(ultrasonicSensorParameters.leftDistance < 4){
        stabilize(left_servo, right_servo, LEFT); 
      }
      if(ultrasonicSensorParameters.rightDistance < 4){
        stabilize(left_servo, right_servo, RIGHT); 
      }

      if(ultrasonicSensorParameters.frontDistance < 9){
        TOGGLE_SENSOR_READING_STATE(); 
        drive_slowly_forward(left_servo, right_servo); 
        if(detect_red_color()){
          stop(left_servo, right_servo); 
          light_led();
          break; 
        }else{
          drive_backwards(left_servo,right_servo); 
          stop(left_servo,right_servo); 
          u_turn(left_servo,right_servo, ultrasonicSensorParameters, mpu6050Sensor, &rotation, &gyroErrorZ,&yaw, &previousTime);
          reset_ultrasonic_sensors(&ultrasonicSensorParameters); 
          ultrasonicSensorParameters.msLastTurn = esp_timer_get_time(); 
        }
        TOGGLE_SENSOR_READING_STATE(); 
      }
        
      if((ultrasonicSensorParameters.leftDistance > 25) || (ultrasonicSensorParameters.rightDistance > 25)){
        TOGGLE_SENSOR_READING_STATE();
        printf("Turn detected!\n");
        vTaskDelay(pdMS_TO_TICKS(1500)); 
        printf("CHECKING DRIVE PATH!"); 
        driveDirection = decide_path(ultrasonicSensorParameters);
        if(driveDirection == LEFT){
          stop(left_servo,right_servo); 
          turn_left(left_servo, right_servo, mpu6050Sensor, &rotation, &gyroErrorZ, &yaw, &previousTime);
        } 
        if(driveDirection == FORWARD){
          drive_forward(left_servo, right_servo);
        }
        if(driveDirection == RIGHT){
          stop(left_servo,right_servo); 
          turn_right(left_servo, right_servo, mpu6050Sensor, &rotation, &gyroErrorZ, &yaw, &previousTime); 
        }
        reset_ultrasonic_sensors(&ultrasonicSensorParameters); 
        ultrasonicSensorParameters.msLastTurn = esp_timer_get_time(); 
        TOGGLE_SENSOR_READING_STATE();  
      }
      
      vTaskDelay(pdMS_TO_TICKS(10)); 
    }
    
}
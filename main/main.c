#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_err.h>
#include <esp_log.h>
#include <i2cdev.h> 
#include <esp_timer.h>
#include "ultrasonic.h"
#include "servo.h"
#include "driver/mcpwm_prelude.h"
#include "common_defines.h"
#include "led.h"
#include "button.h"
#include "color_sensor.h"
#include "mpu6050.h"

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
    ultrasonic_sensor_t frontSensor;
    ultrasonic_sensor_t leftSensor;
    ultrasonic_sensor_t rightSensor; 
    uint8_t frontDistance = 90, leftDistance = 50, rightDistance = 50;
    mcpwm_cmpr_handle_t left_servo = left_servo_init(); 
    mcpwm_cmpr_handle_t right_servo = right_servo_init(); 
    mpu6050_dev_t dev = { 0 };
    mpu6050_rotation_t rotation = { 0,0,0 };
    uint64_t previousTime = esp_timer_get_time(); 
    double gyroErrorZ  = 0.0, yaw = 0.0;
    bool isPressed = false; 
    led_init();
    ultrasonic_init(&frontSensor, &leftSensor, &rightSensor); 
    color_sensor_init(); 
    ESP_ERROR_CHECK(i2cdev_init());
    calibrate_mpu6050(dev, &rotation, &gyroErrorZ); 
    light_led(); // to know when the calibration is done

    //runs until button is pressed.
    button_click(&isPressed); 
  
     while (isPressed){
    drive_forward(left_servo, right_servo); 
    printf("Forward!\n");
    vTaskDelay(pdMS_TO_TICKS(1000));
    turn_left(left_servo, right_servo, dev, &rotation, &gyroErrorZ, &yaw, &previousTime); 
    
 
    }
    
}
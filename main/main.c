#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_err.h>
#include <esp_log.h>
#include "ultrasonic.h"
#include "servo.h"
#include "driver/mcpwm_prelude.h"
#include "common_defines.h"
#include "led.h"
#include "button.h"
#include "color_sensor.h"

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


//servo pin left 

void app_main(void)
{
    ultrasonic_sensor_t frontSensor;
    ultrasonic_sensor_t leftSensor;
    ultrasonic_sensor_t rightSensor; 
    frontSensor.trigger_pin = GPIO_NUM_16;
    frontSensor.echo_pin = GPIO_NUM_17;
    leftSensor.trigger_pin = GPIO_NUM_18;
    leftSensor.echo_pin = GPIO_NUM_19;
    rightSensor.trigger_pin = GPIO_NUM_21;
    rightSensor.echo_pin = GPIO_NUM_22; 
    uint8_t frontDistance = 90, leftDistance = 50, rightDistance = 50;
    mcpwm_cmpr_handle_t left_servo = left_servo_init(); 
    mcpwm_cmpr_handle_t right_servo = right_servo_init(); 
    bool isPressed = false; 
    led_init();
    ultrasonic_init(&frontSensor, &leftSensor, &rightSensor); 
    color_sensor_init(); 

    //runs until button is pressed.
    // button_click(&isPressed); 
    // while (isPressed){
    // // read_ultrasonic_sensors(&frontSensor, &leftSensor, &rightSensor, &frontDistance, &leftDistance, &rightDistance);
    // // ESP_LOGI("Sensor reading: ", "Front sensor = %d     Left Sensor= %d     Right sensor = %d", frontDistance, leftDistance, rightDistance); 
    // // vTaskDelay(pdMS_TO_TICKS(500)); 
    // if(gpio_get_level(LED_PIN) == 0) light_led();  
     while (1){
        detect_red_color();
    }
    
}
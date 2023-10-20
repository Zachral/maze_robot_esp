#ifndef _LED_H__
#define _LED_H__

#include "driver/gpio.h" 
#include <freertos/task.h>

#define LED_PIN  25

void led_init();
void light_led();
void turn_of_led();
TaskFunction_t flash_led(); 

#endif
#ifndef _LED_H__
#define _LED_H__

#include "driver/gpio.h" 

#define LED_PIN  25

void led_init();
void light_led();
void turn_of_led();
void flash_led(); 

#endif
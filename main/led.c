#include "driver/gpio.h"
#include "common_defines.h"
#include "led.h"

void led_init(){
    gpio_set_direction(LED_PIN, GPIO_MODE_INPUT_OUTPUT); 
    gpio_set_level(LED_PIN, LOW); 
    return; 
}

void light_led(){
    gpio_set_level(LED_PIN, HIGH);
    return;
}

void turn_of_led(){
    gpio_set_level(LED_PIN, LOW); 
    return; 
}

void flash_led(){
    gpio_get_level(LED_PIN) == HIGH ? gpio_set_level(LED_PIN, LOW) : gpio_set_level(LED_PIN, HIGH);
    return; 
    }  
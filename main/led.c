#include "driver/gpio.h"
#include "common_defines.h"
#include "led.h"

void led_init(){
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT); 
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
    uint8_t pinState; 
    pinState = gpio_get_level(LED_PIN); 
    printf("Pin state is = %d\n", pinState);
    if(pinState == 0){
        gpio_set_level(LED_PIN, 1);
        printf("turning led on\n");
    }else{
        gpio_set_level(LED_PIN, 0);
        printf("turning led off\n");
    }  
    
return; 
 
}
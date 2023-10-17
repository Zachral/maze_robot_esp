#include <stdbool.h>
#include "driver/gpio.h"
#include "esp_err.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h> 
#include "button.h"
#include "common_defines.h"

esp_err_t button_click(bool *isPressed){
    ESP_ERROR_CHECK(gpio_reset_pin(BUTTON_PIN));
    ESP_ERROR_CHECK(gpio_set_pull_mode(BUTTON_PIN, GPIO_PULLUP_ONLY)); 
    ESP_ERROR_CHECK(gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT));
    int currentState = gpio_get_level(BUTTON_PIN), lastState = LOW; 
    printf("Doing task!\n");
    while(1){
        lastState = currentState;
        currentState = gpio_get_level(BUTTON_PIN); 
        printf("lastState = %d  current State = %d\n", lastState, currentState); 
        if(lastState == HIGH && currentState == LOW){
            printf("DELAYING\n"); 
            vTaskDelay(pdMS_TO_TICKS(20));
            currentState = gpio_get_level(BUTTON_PIN);
            printf("current state = %d\n", currentState); 
                if(currentState == LOW){
                    *isPressed = true; 
                    printf("Button is pressed! isPressed = %i", *isPressed);
                    return ESP_OK; 
                }
        }
    }
    return ESP_OK; 
}
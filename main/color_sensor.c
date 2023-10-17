#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "esp_err.h"
#include "color_sensor.h"
#include "common_defines.h"

esp_err_t color_sensor_init(){
    //set SX-pins as output
    ESP_ERROR_CHECK(gpio_set_direction(COLOR_SENSOR_S0_PIN, GPIO_MODE_OUTPUT));
    ESP_ERROR_CHECK(gpio_set_direction(COLOR_SENSOR_S1_PIN, GPIO_MODE_OUTPUT));
    ESP_ERROR_CHECK(gpio_set_direction(COLOR_SENSOR_S2_PIN, GPIO_MODE_OUTPUT));
    ESP_ERROR_CHECK(gpio_set_direction(COLOR_SENSOR_S3_PIN, GPIO_MODE_OUTPUT));

    //set out-pin to input
    ESP_ERROR_CHECK(gpio_set_direction(COLOR_SENSOR_OUT_PIN, GPIO_MODE_INPUT));

    //set the scaling
    ESP_ERROR_CHECK(gpio_set_level(COLOR_SENSOR_S0_PIN, HIGH));
    ESP_ERROR_CHECK(gpio_set_level(COLOR_SENSOR_S1_PIN, LOW));

return ESP_OK; 
}

void set_color_to_detect(uint8_t color){
    switch(color){
        case RED: 
            //sets sensor to detect red
            gpio_set_level(COLOR_SENSOR_S2_PIN, LOW);
            gpio_set_level(COLOR_SENSOR_S3_PIN, LOW);
            break;
        case GREEN:
            //sets sensor to detect green
            gpio_set_level(COLOR_SENSOR_S2_PIN, HIGH);
            gpio_set_level(COLOR_SENSOR_S3_PIN, HIGH); 
            break; 
        case BLUE:
            //sets sensor to detect green
            gpio_set_level(COLOR_SENSOR_S2_PIN, LOW);
            gpio_set_level(COLOR_SENSOR_S3_PIN, HIGH); 
            break; 
        default:
            break; 
    }
}

uint32_t read_color_sensor(uint8_t outPIN, uint8_t timeout){
    uint32_t pulseWidth = 0, maxIterations = pdMS_TO_TICKS(timeout) / 16; 
    uint8_t iterations = 0;
    
    //wait for the pulse before to end
    while(!gpio_get_level(COLOR_SENSOR_OUT_PIN)){
        if(iterations++ == maxIterations) return 0;
    }

    //wait for signal to go low
    while(gpio_get_level(COLOR_SENSOR_OUT_PIN)){
        if(iterations++ == maxIterations) return 0;
    }

    //start reading the low signal until it goes high
    while(!gpio_get_level(COLOR_SENSOR_OUT_PIN)){
        pulseWidth++; 
    }

    return pdTICKS_TO_MS(pulseWidth * 21 +16);
}

long Convert_input_frequency(long frequency, long in_min, long in_max, long out_min, long out_max) {
  return (frequency - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
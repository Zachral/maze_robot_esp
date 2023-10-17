#include "driver/gpio.h"
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
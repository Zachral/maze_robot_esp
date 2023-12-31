#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_err.h"
#include "tcs3200_color_sensor.h"
#include "common_defines.h"

esp_err_t color_sensor_init(){
    //set SX-pins as output
    ESP_ERROR_CHECK(gpio_set_direction(COLOR_SENSOR_S0_PIN, GPIO_MODE_OUTPUT));
    ESP_ERROR_CHECK(gpio_set_direction(COLOR_SENSOR_S1_PIN, GPIO_MODE_OUTPUT));
    ESP_ERROR_CHECK(gpio_set_direction(COLOR_SENSOR_S2_PIN, GPIO_MODE_OUTPUT));
    ESP_ERROR_CHECK(gpio_set_direction(COLOR_SENSOR_S3_PIN, GPIO_MODE_OUTPUT));

    //set out-pin to input
    ESP_ERROR_CHECK(gpio_set_direction(COLOR_SENSOR_OUT_PIN, GPIO_MODE_INPUT));

    //set the scaling to 20%
    ESP_ERROR_CHECK(gpio_set_level(COLOR_SENSOR_S0_PIN, HIGH));
    ESP_ERROR_CHECK(gpio_set_level(COLOR_SENSOR_S1_PIN, HIGH));
    printf("Sensor set up\n");
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

uint32_t read_color_sensor(){
    uint32_t pulseWidth = 0, maxIterations = pdMS_TO_TICKS(255) / 16; 
    uint8_t iterations = 0;
    //printf("Max iterations = %ld\n", maxIterations);
    //wait for the pulse before to end
    while(!gpio_get_level(COLOR_SENSOR_OUT_PIN)){
        //if(iterations++ == maxIterations) return 0;
        //printf("Waiting for signal to end    %d\n", iterations); 
    }

    //wait for signal to go low
    while(gpio_get_level(COLOR_SENSOR_OUT_PIN)){
        //if(iterations++ == maxIterations) return 0;
       // printf("Waiting for signal to go low    %d\n", iterations); 
    }

    //start reading the low signal until it goes high
    while(!gpio_get_level(COLOR_SENSOR_OUT_PIN)){
        pulseWidth++; 
       // printf("reading!   %ld\n", pulseWidth); 
    }

    return pdTICKS_TO_MS(pulseWidth);
}

long Convert_input_frequency(long frequency, long in_min, long in_max, long out_min, long out_max) {
  return (frequency - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int detect_red_color(){
    int redFrequency = 0, greenFrequency = 0, blueFrequency = 0, redColor = 0,  greenColor = 0, blueColor = 0; 

    set_color_to_detect(RED);
    redFrequency = read_color_sensor(); 
    redColor = Convert_input_frequency(redFrequency,410,830,255,0);
   // printf("redFrequency = %d   red color = %d\n", redFrequency, redColor); 
    vTaskDelay(pdMS_TO_TICKS(100)); 

    set_color_to_detect(GREEN);
    greenFrequency = read_color_sensor();
    greenColor = Convert_input_frequency(greenFrequency, 660, 1220, 255,0); 
    // printf("green Frequency = %d   green color = %d\n", greenFrequency, greenColor); 
    vTaskDelay(pdMS_TO_TICKS(100)); 

    set_color_to_detect(BLUE); 
    blueFrequency = read_color_sensor();
    blueColor = Convert_input_frequency(blueFrequency, 610, 810, 255, 0);
     //printf("blue Frequency = %d   blue color = %d\n", blueFrequency, blueColor); 
    vTaskDelay(pdMS_TO_TICKS(100)); 

    if(greenColor > redColor && greenColor > blueColor){ 
        printf("GREEN DETECTED\n");
        return 0;
    }
    if(blueColor > redColor && blueColor > greenColor){
        printf("BLUE DETECTED\n");
        return 0;
    }
    if(redColor > greenColor && redColor > blueColor){ 
        printf("RED DETECTED\n");
        return 1;
    }
    return 0; 

}
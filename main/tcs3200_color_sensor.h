#ifndef _TCS3200_COLOR_SENSOR_H__
#define _TCS3200_COLOR_SENSOR_H__

#include "driver/gpio.h"

#define COLOR_SENSOR_S0_PIN     GPIO_NUM_26
#define COLOR_SENSOR_S1_PIN     GPIO_NUM_27
#define COLOR_SENSOR_S2_PIN     GPIO_NUM_4
#define COLOR_SENSOR_S3_PIN     GPIO_NUM_16
#define COLOR_SENSOR_OUT_PIN    GPIO_NUM_21

esp_err_t color_sensor_init();
void set_color_to_detect(uint8_t color);
uint32_t read_color_sensor(); 
long Convert_input_frequency(long frequency, long in_min, long in_max, long out_min, long out_max);
int detect_red_color();  


#endif
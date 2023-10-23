/*
 * SPDX-FileCopyrightText: 2022-2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/mcpwm_prelude.h"
#include "servo.h"
#include "common_defines.h"
#include "mpu6050.h"


static const char *L = "Left servo";
static const char *R = "Right servo"; 
 
int servoSpeed = 40;

static inline uint32_t run_servos_at_speed(int servoSpeed){
    return (servoSpeed - SERVO_MIN_DEGREE) * (SERVO_MAX_PULSEWIDTH_US - SERVO_MIN_PULSEWIDTH_US) / (SERVO_MAX_DEGREE - SERVO_MIN_DEGREE) + SERVO_MIN_PULSEWIDTH_US;
}


mcpwm_cmpr_handle_t left_servo_init(){
    /*Initilizes left servo*/
    ESP_LOGI(L, "Create timer and operator");
    mcpwm_timer_handle_t left_servo_timer = NULL;
    mcpwm_timer_config_t left_servo_timer_config = {
        .group_id = 0,
        .clk_src = MCPWM_TIMER_CLK_SRC_DEFAULT,
        .resolution_hz = SERVO_TIMEBASE_RESOLUTION_HZ,
        .period_ticks = SERVO_TIMEBASE_PERIOD,
        .count_mode = MCPWM_TIMER_COUNT_MODE_UP,
    };
    ESP_ERROR_CHECK(mcpwm_new_timer(&left_servo_timer_config, &left_servo_timer));

    mcpwm_oper_handle_t left_servo_operator = NULL;
    mcpwm_operator_config_t left_servo_operator_config = {
        .group_id = 0, // operator must be in the same group to the timer
    };
    ESP_ERROR_CHECK(mcpwm_new_operator(&left_servo_operator_config, &left_servo_operator));

    ESP_LOGI(L, "Connect timer and operator");
    ESP_ERROR_CHECK(mcpwm_operator_connect_timer(left_servo_operator, left_servo_timer));

    ESP_LOGI(L, "Create comparator and generator from the operator");
    mcpwm_cmpr_handle_t left_servo_comparator = NULL;
    mcpwm_comparator_config_t left_servo_comparator_config = {
        .flags.update_cmp_on_tez = true,
    };
    ESP_ERROR_CHECK(mcpwm_new_comparator(left_servo_operator, &left_servo_comparator_config, &left_servo_comparator));

    mcpwm_gen_handle_t left_servo_generator = NULL;
    mcpwm_generator_config_t left_servo_generator_config = {
        .gen_gpio_num = LEFT_SERVO_GPIO,
    };
    ESP_ERROR_CHECK(mcpwm_new_generator(left_servo_operator, &left_servo_generator_config, &left_servo_generator));

    // set the initial compare value, so that the servo will spin to the center position
    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(left_servo_comparator, run_servos_at_speed(0)));

    ESP_LOGI(L, "Set generator action on timer and compare event");
    // go high on counter empty
    ESP_ERROR_CHECK(mcpwm_generator_set_action_on_timer_event(left_servo_generator,
                                                              MCPWM_GEN_TIMER_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, MCPWM_TIMER_EVENT_EMPTY, MCPWM_GEN_ACTION_HIGH)));
    // go low on compare threshold
    ESP_ERROR_CHECK(mcpwm_generator_set_action_on_compare_event(left_servo_generator,
                                                                MCPWM_GEN_COMPARE_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, left_servo_comparator, MCPWM_GEN_ACTION_LOW)));

    ESP_LOGI(L, "Enable and start timer");
    ESP_ERROR_CHECK(mcpwm_timer_enable(left_servo_timer));
    ESP_ERROR_CHECK(mcpwm_timer_start_stop(left_servo_timer, MCPWM_TIMER_START_NO_STOP));

    return left_servo_comparator;
}

mcpwm_cmpr_handle_t right_servo_init(){
    /*Initilizes Right servo*/
    ESP_LOGI(R, "Create timer and operator");
    mcpwm_timer_handle_t right_servo_timer = NULL;
    mcpwm_timer_config_t right_servo_timer_config = {
        .group_id = 1,
        .clk_src = MCPWM_TIMER_CLK_SRC_DEFAULT,
        .resolution_hz = SERVO_TIMEBASE_RESOLUTION_HZ,
        .period_ticks = SERVO_TIMEBASE_PERIOD,
        .count_mode = MCPWM_TIMER_COUNT_MODE_UP,
    };
    ESP_ERROR_CHECK(mcpwm_new_timer(&right_servo_timer_config, &right_servo_timer));

    mcpwm_oper_handle_t right_servo_operator = NULL;
    mcpwm_operator_config_t right_servo_operator_config = {
        .group_id = 1, // operator must be in the same group to the timer
    };
    ESP_ERROR_CHECK(mcpwm_new_operator(&right_servo_operator_config, &right_servo_operator));

    ESP_LOGI(R, "Connect timer and operator");
    ESP_ERROR_CHECK(mcpwm_operator_connect_timer(right_servo_operator, right_servo_timer));

    ESP_LOGI(R, "Create comparator and generator from the operator");
    mcpwm_cmpr_handle_t right_servo_comparator = NULL;
    mcpwm_comparator_config_t right_servo_comparator_config = {
        .flags.update_cmp_on_tez = true,
    };
    ESP_ERROR_CHECK(mcpwm_new_comparator(right_servo_operator, &right_servo_comparator_config, &right_servo_comparator));

    mcpwm_gen_handle_t right_servo_generator = NULL;
    mcpwm_generator_config_t right_servo_generator_config = {
        .gen_gpio_num = RIGHT_SERVO_GIPO,
    };
    ESP_ERROR_CHECK(mcpwm_new_generator(right_servo_operator, &right_servo_generator_config, &right_servo_generator));

    //set the initial compare value, so that the servo will spin to the center position
    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(right_servo_comparator, run_servos_at_speed(0)));

    ESP_LOGI(R, "Set generator action on timer and compare event");
    // go high on counter empty
    ESP_ERROR_CHECK(mcpwm_generator_set_action_on_timer_event(right_servo_generator,
                                                              MCPWM_GEN_TIMER_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, MCPWM_TIMER_EVENT_EMPTY, MCPWM_GEN_ACTION_HIGH)));
    // go low on compare threshold
    ESP_ERROR_CHECK(mcpwm_generator_set_action_on_compare_event(right_servo_generator,
                                                                MCPWM_GEN_COMPARE_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, right_servo_comparator, MCPWM_GEN_ACTION_LOW)));

    ESP_LOGI(R, "Enable and start timer");
    ESP_ERROR_CHECK(mcpwm_timer_enable(right_servo_timer));
    ESP_ERROR_CHECK(mcpwm_timer_start_stop(right_servo_timer, MCPWM_TIMER_START_NO_STOP));
    return right_servo_comparator;
    }


    /*Functions controlling the different drive functions*/
void drive_forward(mcpwm_cmpr_handle_t left_servo_comparator, mcpwm_cmpr_handle_t right_servo_comparator){
    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(left_servo_comparator, run_servos_at_speed(servoSpeed*2)));
    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(right_servo_comparator, run_servos_at_speed(servoSpeed - (servoSpeed *2)))); /*The right servo needs to run at a negative value to drive the robot forward*/
    return; 
}

void drive_slowly_forward(mcpwm_cmpr_handle_t left_servo_comparator, mcpwm_cmpr_handle_t right_servo_comparator){
    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(left_servo_comparator, run_servos_at_speed(servoSpeed*1.5)));
    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(right_servo_comparator, run_servos_at_speed(servoSpeed - (servoSpeed *1.5)))); /*The right servo needs to run at a negative value to drive the robot forward*/
    vTaskDelay(pdMS_TO_TICKS(500)); 
    return; 
}

void stop(mcpwm_cmpr_handle_t left_servo_comparator, mcpwm_cmpr_handle_t right_servo_comparator){
    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(left_servo_comparator, run_servos_at_speed(0)));
    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(right_servo_comparator, run_servos_at_speed(0))); 
    return; 
    }

void drive_backwards(mcpwm_cmpr_handle_t left_servo_comparator, mcpwm_cmpr_handle_t right_servo_comparator){
    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(left_servo_comparator, run_servos_at_speed(servoSpeed -(servoSpeed *2))));
    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(right_servo_comparator, run_servos_at_speed(servoSpeed*2))); 
    vTaskDelay(pdMS_TO_TICKS(500)); 
    return; 
    }

void turn_left(mcpwm_cmpr_handle_t left_servo_comparator, mcpwm_cmpr_handle_t right_servo_comparator, mpu6050_dev_t dev, mpu6050_rotation_t *rotation, double *gyroErrorZ, double *yaw, uint64_t *previousTime){
    *yaw = 0.0; //reset yaw as the degree of turn is only relevant in comparision to starting direction.
    printf("turn left!\n");
    while(*yaw < 70){
        calculate_yaw(dev, rotation, gyroErrorZ, yaw, previousTime);
        printf("Yaw = %.4f\n", *yaw);
        ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(left_servo_comparator, run_servos_at_speed(servoSpeed -(servoSpeed *2))));
        ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(right_servo_comparator, run_servos_at_speed(servoSpeed -(servoSpeed *2)))); 
    }
    return; 
    
}

void turn_right(mcpwm_cmpr_handle_t left_servo_comparator, mcpwm_cmpr_handle_t right_servo_comparator, mpu6050_dev_t dev, mpu6050_rotation_t *rotation, double *gyroErrorZ, double *yaw, uint64_t *previousTime){
    *yaw = 0.0; //reset yaw as the degree of turn is only relevant in comparision to starting direction.
    printf("turn right!\n");
    while (*yaw > -70){
        calculate_yaw(dev, rotation, gyroErrorZ, yaw, previousTime);
        printf("Yaw = %.4f\n", *yaw);
        ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(left_servo_comparator, run_servos_at_speed(servoSpeed *2)));
        ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(right_servo_comparator, run_servos_at_speed(servoSpeed *2))); 
    }
return; 
}

void u_turn(mcpwm_cmpr_handle_t left_servo_comparator, mcpwm_cmpr_handle_t right_servo_comparator, uint8_t leftSensor, uint8_t rightSensor,mpu6050_dev_t dev, mpu6050_rotation_t *rotation, double *gyroErrorZ, double *yaw, uint64_t *previousTime){
    *yaw = 0.0;
    printf("U turn!\n"); 
    if (leftSensor > rightSensor){
        while(*yaw < 70){
            calculate_yaw(dev, rotation, gyroErrorZ, yaw, previousTime); 
            ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(left_servo_comparator, run_servos_at_speed(servoSpeed -(servoSpeed *2))));
            ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(right_servo_comparator, run_servos_at_speed(servoSpeed -(servoSpeed *2)))); 
        }
        return; 
    } else{
        while(*yaw > -70){
            calculate_yaw(dev, rotation, gyroErrorZ, yaw, previousTime);
            ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(left_servo_comparator, run_servos_at_speed(servoSpeed *2)));
            ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(right_servo_comparator, run_servos_at_speed(servoSpeed *2))); 
        }
        return; 
    }
}

void stabilize(mcpwm_cmpr_handle_t left_servo_comparator, mcpwm_cmpr_handle_t right_servo_comparator,uint8_t side){
    switch (side){
    case LEFT:
        ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(left_servo_comparator, run_servos_at_speed(servoSpeed*2)));
        ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(right_servo_comparator, run_servos_at_speed(servoSpeed - (servoSpeed *1.5))));
        break;
    case RIGHT:
        ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(left_servo_comparator, run_servos_at_speed(servoSpeed*1.5)));
        ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(right_servo_comparator, run_servos_at_speed(servoSpeed - (servoSpeed *2))));
    default:
        drive_forward(left_servo_comparator, right_servo_comparator); 
        break;
    }
return; 
}
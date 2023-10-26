#ifndef _SERVO_H__
#define _SERVO_H__
#include "driver/mcpwm_prelude.h"
#include "mpu6050.h"
#include "hc_sr_04_ultrasonic_sensor.h"
// Please consult the datasheet of your servo before changing the following parameters
#define SERVO_MIN_PULSEWIDTH_US 500  // Minimum pulse width in microsecond
#define SERVO_MAX_PULSEWIDTH_US 2400  // Maximum pulse width in microsecond
#define SERVO_MIN_DEGREE        -180  // Minimum angle
#define SERVO_MAX_DEGREE        180   // Maximum angle

#define LEFT_SERVO_GPIO              15        // GPIO connects to the PWM signal line
#define RIGHT_SERVO_GIPO             13        // GPIO connects to the PWM signal line
#define SERVO_TIMEBASE_RESOLUTION_HZ 1000000  // 1MHz, 1us per tick
#define SERVO_TIMEBASE_PERIOD        20000    // 20000 ticks, 20ms
#define DEGREE_OF_TURN               55
#define DEGREE_U_TURN                115

mcpwm_cmpr_handle_t left_servo_init();
mcpwm_cmpr_handle_t right_servo_init(); 
void drive_forward(mcpwm_cmpr_handle_t left_servo_comparator, mcpwm_cmpr_handle_t right_servo_comparator); 
void drive_slowly_forward(mcpwm_cmpr_handle_t left_servo_comparator, mcpwm_cmpr_handle_t right_servo_comparator);
void stop(mcpwm_cmpr_handle_t left_servo_comparator, mcpwm_cmpr_handle_t right_servo_comparator);
void drive_backwards(mcpwm_cmpr_handle_t left_servo_comparator, mcpwm_cmpr_handle_t right_servo_comparator);
void turn_left(mcpwm_cmpr_handle_t left_servo_comparator, mcpwm_cmpr_handle_t right_servo_comparator, mpu6050_dev_t dev, mpu6050_rotation_t *rotation, double *gyroErrorZ, double *yaw, uint64_t *previousTime);
void turn_right(mcpwm_cmpr_handle_t left_servo_comparator, mcpwm_cmpr_handle_t right_servo_comparator, mpu6050_dev_t dev, mpu6050_rotation_t *rotation, double *gyroErrorZ, double *yaw, uint64_t *previousTime);
void u_turn(mcpwm_cmpr_handle_t left_servo_comparator, mcpwm_cmpr_handle_t right_servo_comparator, ultrasonic_sensor_parameters_t ultrasonicSensorParameters ,mpu6050_dev_t dev, mpu6050_rotation_t *rotation, double *gyroErrorZ, double *yaw, uint64_t *previousTime);
void stabilize(mcpwm_cmpr_handle_t left_servo_comparator, mcpwm_cmpr_handle_t right_servo_comparator,uint8_t side); 

#endif
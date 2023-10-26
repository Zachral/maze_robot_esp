
# Maze Solving Robot

## Table of Contents
- [Purpose](#purpose)
    - [Inital requeriments for the project](#initial-requirements-for-the-project)
      -[The robot should:](#the-robot-should)
      -[It is desirable that the robot would:](#it-is-desirable-that-the-robot-would)
- [Hardware](#hardware)
- [Background](#background)

## Purpose

This project aims to create a robot capable of independently navigating a maze, making path decisions at intersections, avoiding obstacles, and identifying the goal using color detection. It also seeks to optimize the path and provide real-time feedback via a dashboard.

### Inital requeriments for the project.

#### The robot should:

    Independently move itself.
    Choose a path at intersections.
    Avoid driving in circles.
    Avoid hitting walls in the maze.
    Save the path choices it makes.
    Distinguish between a regular wall and the goal using color detection.

#### It is desirable that the robot would:

    Optimize the path over multiple runs in the maze.
    Be able to be started and stopped via a dashboard.
    Real-time display the time for the attempt on the dashboard.


## Hardware

    Esp 32:                                   1 piece
    Hc-Sr04 Ultrasonic sensor:                3 pieces
    TCS3200 color sensor:                     1 piece
    Servo MSR-1.3-9 360°:                     2 pieces
    MPU6050 3-axis gyroscope/accelerometer:   1 piece 
    On/Off button:                            1 piece
    LED:                                      1 piece
    Wheels for servo:                         2 pieces
    360° rotating front wheel:                1 piece
    Half breadboard:                          1 piece
    Mini breadboard:                          2 pieces
    3xAAA battery pack:                       2 pieces
    Lego chassi

## Background

Wiring diagram: 

(Note that on the physical robot, the ESP32 is turned upside down to get access to the pins.)

![circuit](https://github.com/Zachral/maze_robot_esp/assets/101337887/a4b77c5f-a8fc-4ea3-92a7-6ecd24f4ad6a)



# Maze Solving Robot

## Table of Contents
- [Purpose](#purpose)
    - [Initial requeriments for the project](#initial-requirements-for-the-project) 
      - [The robot should:](#the-robot-should)
      - [It is desirable that the robot would:](#it-is-desirable-that-the-robot-would)
- [Hardware](#hardware)
- [Wiring diagram](#wiring-diagram)
- [Development process](#development-process)
- [Version control](#version-control)
- [Pictures and video](#pictures-and-video)
- [Improvements to be done](#improvements-to-be-done)

## Purpose
To develop and construct a robot that is capable of solving a maze. 

### Initial requeriments for the project

#### The robot should:

    Independently move itself.
    Choose a path at intersections.
    Avoid driving in circles.
    Avoid hitting walls in the maze.
    Save the path choices it makes.
    Distinguish between a regular wall and the goal using color detection.

#### It is desirable that the robot would:

    Optimize the path over multiple runs in the maze.
    Be able to be restarted and monitored via an online dashboard.
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

## Wiring diagram: 

![circuit](https://github.com/Zachral/maze_robot_esp/assets/101337887/a4b77c5f-a8fc-4ea3-92a7-6ecd24f4ad6a)

(Note that on the physical robot, the ESP32 is turned upside down to get access to the pins as can be seen in the pictures below)

## Development process

This project aims to create a robot capable of independently navigating a maze, making path decisions at intersections, avoiding obstacles, and identifying the goal using color detection. The first task was to identify what types of hardware needed to be used to achive the overall goal of the project. The initial phase consisted of breaking down the different functionalities needed into smaller pieces and structuring them in order of priority. After that, individual testing of the different sensors, servos and software algorithems were done. Then assembly and real life testing. 
Over the course of development, the following milestones were achieved:

    Successfully integrated three ultrasonic sensors for precise distance control
    Servos and buttons were configured to enable independent movement.
    A color sensor was added to detect the maze's "goal". 
    Extensive planning for chassis assembly using Legos.
    Initial driving tests in open space showed promise.
    Challenges arose when the robot encountered a simple maze, requiring adjustments and calibration mostly related to I/O timing.
    Challenges with servo reliability when turning were addressed by adding a gyroscope.
    The project outgrew the initial microcontroller, necessitating an upgrade to an ESP32.

## Version control

All source code for this project is managed and versioned on GitHub. Regular updates, commits, and modifications can be tracked in the repository's commit history.

## Pictures and video
    Front:
![front](https://github.com/Zachral/maze_robot_esp/assets/101337887/99bfc61b-288b-40ad-bd51-e27fc75cc724)

    Left:
![left](https://github.com/Zachral/maze_robot_esp/assets/101337887/eab01af1-e608-42d2-a64c-504b19f20a07)

    Right:
![Right](https://github.com/Zachral/maze_robot_esp/assets/101337887/546c1873-b4df-4cb5-a6ab-e4d97da09666)

    Top:
![top](https://github.com/Zachral/maze_robot_esp/assets/101337887/2d98c651-3458-4ba4-8330-3b9ab481a5f8)


    Driving video:
    The first part is the first real life driving test. The second from the beginning of the maze tests and the third part is when it solves the maze. 
[![Maze Solving Robot Video](https://img.youtube.com/vi/kiKUuKGGRBU/0.jpg)](https://www.youtube.com/watch?v=kiKUuKGGRBU)

## Improvements to be done
    Rewrite the stabilize function to use  use the yaw of the gyro instead of a delay to drive in a straight line. 
    Replace the servos with more reliable motors
    Replace the front ball wheel with a component that offers greater ground contact, increasing stability
    Add second batterypack to power sensors and the ESP32
    Add functionality to optimize the route after every run in the maze.
    Add Wifi and a dashboard for monitoring and restarting 

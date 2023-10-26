Maze solving robot!

Purpose of the robot:

To be able to solve a maze by finding the goal.

The robot should:

    Independently move itself.
    Choose a path at intersections.
    Avoid driving in circles.
    Avoid hitting walls in the maze.
    Save the path choices it makes.
    Distinguish between a regular wall and the goal using color detection.

It is desirable that the robot would:

    Optimize the path over multiple runs in the maze.
    Be able to be started and stopped via a dashboard.
    Real-time display the time for the attempt on the dashboard.

Hardware:

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

Wiring diagram: 
(Note that on the physical robot, the ESP32 is turned upside down to get access to the pins.)

![circuit](https://github.com/Zachral/maze_robot_esp/assets/101337887/a4b77c5f-a8fc-4ea3-92a7-6ecd24f4ad6a)


# object tracking camera
The repository consists of a project that was aimed at developing a camera mount system (essentially a gimbal) that automatically starts following a specific colored object once the object comes into its field

It consists of C++ source code with OpenCV library and Serial library and a Arduino code for controlling 2 servos for horizontal and vertical (2 DOF) directional motion of camera

the input from USB camera is directly connected to the Computer and processed, the appropriate directional signal is then created and sent to arduino through another USB to control the servos.

camcontrol.ino - arduino source code
main.cpp - testrun c++ source for controlling camera using keyboard arrow keys used for caliberating the arduino code
main2.cpp - integrated with opencv to perform autonomous function

youtube videos of project
https://www.youtube.com/watch?v=-w4BVShdlUQ
https://www.youtube.com/watch?v=bQpqbJkos_w

materials used-
2 - micro servo motors to control the horizontal and verical motion of the CAmera
1 - USB webcam mounted over a servo co trolled base
1 - arduino

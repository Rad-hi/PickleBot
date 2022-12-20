# PickleBot is an educational-purpose robot that aims to introduce you to the world of autonomous robots step by step

## Brief

This repo aims at introducing you to the world of robotics one step at a time. 

Having modular system design in mind, the goal is to test one feature at a time within its own folder, as a testable unit that one can experiment with, then as we advance, we find these same units (if useful, because sometimes we just experiment with some features) integrated into more advanced/comlex units/features that implement more powerful concepts.

The end goal is to arrive at a fully autonomous robot, using the cheapest and most widely available tools/components, as an effort to democratize knowledge, and specefically robotics.

The technical roadmap is still fuzzy, but we start from sensorless driving of our differential drive robot (most basic level), then we add an encoder to start closing the loop, but then we add a second encoder and we make our hacked together AB-encoder, then we add PID control to the wheels, then encoder-based Odometry, which will be complemented with an IMU to account for drift and wheel slip (etc), then we close the low level control chapter with a server/client communication (sockets) with a virtual ground station.

After this step is achieved, we move to the high level controller, where we start doing path planning, more advanced sensor fusion, Machine Learning and computer vision (using our smartphone as the camera that streams the video to our laptop).

The journey is long, and fairly optimistic, but I will try to give it what is needed of work.

## Resources:

- Get started with Arduino: Zero to Hero repo: https://github.com/Rad-hi/Robothon

- Everything ESP32: https://randomnerdtutorials.com/projects-esp32/

- Sensor Fusion (Matlab): https://www.youtube.com/playlist?list=PLn8PRpmsu08ryYoBpEKzoMOveSTyS-h4a

- Kalman Filters (Matlab): https://www.youtube.com/playlist?list=PLn8PRpmsu08pzi6EMiYnR-076Mh-q3tWr

- Autonomous Navigation (Matlab): https://www.youtube.com/playlist?list=PLn8PRpmsu08rLRGrnF-S6TyGrmcA2X7kg

- ROS: https://docs.ros.org/en/humble/index.html

- Odometry: https://ocw.mit.edu/courses/6-186-mobile-autonomous-systems-laboratory-january-iap-2005/resources/odomtutorial/

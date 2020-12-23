# A 2x2 Rubik's Cube Solver

## About
This application will help you solve your 2x2 Rubik's cube. You will be asked to input a scramble to the 2x2 on a 2D representation of the cube, and it will output a solution (at a speed that beats the current human world record!) to your scramble in [Rubik's cube move notation](https://ruwix.com/the-rubiks-cube/notation/).

## Dependencies
* clang or MSVC 2015+
* cmake
* [Cinder](libcinder.org)

## Installation and Quickstart
The GUI for this app is built on the Cinder C++ framework. The download for this framework can be found [here](https://libcinder.org/download).

The project can be easily run via most C++ IDEs. Clone the repository and build/run the "solver-app" configuration. Instructions on using the application can be found in the application GUI itself.

## Screenshots
The app upon opening

![open_app](https://i.ibb.co/KbZj2LC/Screen-Shot-2020-12-09-at-11-09-13-PM.png)

The app outputting a solution

![app_solution](https://i.ibb.co/SrwH7Hq/Screen-Shot-2020-12-09-at-11-10-47-PM.png)

The app upon receiving an invalid scramble

![app_invalid](https://i.ibb.co/M8BP3nf/Screen-Shot-2020-12-09-at-11-13-50-PM.png)

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

## The Algorithm
The graph is implicitly generated and while being searched for a solution via a modified BFS.
 
The graph begins with two starting nodes - The first node is a solved state in thesame orientation as the front-upper-left corner of the Rubik's cube. This reduces the search space immensely since we no longer need to consider the 24 "distinct" orientations of the same scramble--only the one that the cube is currently oriented in. The second node is the scrambled state given. We use these two nodes and generate the graph from both of them, hoping to find an intersection between the two generated graphs. The motivation behind this is that the number of nodes we will need to generate from two graphs of half the height will be far less than the number of nodes from a singular graph with the entire height.

BFS then proceeds from both of these two nodes simultaneously. We are careful not to generate scrambles from unnecessary moves by ensuring the same face is not manipulated twice in a row. For example, doing an F move directly followed by an F2 is redundant, since we could have simply done a single F' move to achieve that state. BFS stops when the two generated graphs intersect at a common state. The solution is then outputted by backtracking through the two paths that lead to this state.

## Screenshots
The app upon opening

![open_app](https://i.ibb.co/KbZj2LC/Screen-Shot-2020-12-09-at-11-09-13-PM.png)

The app outputting a solution

![app_solution](https://i.ibb.co/SrwH7Hq/Screen-Shot-2020-12-09-at-11-10-47-PM.png)

The app upon receiving an invalid scramble

![app_invalid](https://i.ibb.co/M8BP3nf/Screen-Shot-2020-12-09-at-11-13-50-PM.png)

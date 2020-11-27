#Final Project Proposal - A 2x2x2 Rubik's Cube Solver

##Overview
My final project will be a Cinder application that is able to compute a solution to any scramble of a 2x2x2 Rubik's cube. The user will be able to visually input a scramble of a 2x2x2 Rubik's cube. If the scramble is invalid (e.g. more than 4 stickers of one color, an impossible piece, etc.), the application will alert the user. If the scarmble is valid, the application will guide the user towards solving the cube with step-by-step instructions. The application can also be reset at any time to enter a new scramble.

##Background
From fifth to eighth grade, I was avidly interested in solving different types of twisty puzzles. I slowly became a part of the speedcubing community and traveled to compete in many contests. My favorite event to compete in was the 2x2x2 Rubik's cube and it was also my favorite cube to solve. Since each solve can potentially take less than 5 seconds, it is a cube that is relatively simple to master solving.

From some research that I've done, the 2x2x2 cube has about 3.6 million combinations. In order to determine how to go from a scrambled state to a solved state, my idea is to generate a connected graph from all possible states of the 2x2x2. From a specified scramble, the application can then perform a breadth-first search from the solved state of the cube to the scrambled state, and then output the shortest path. Based on my background in speedcubing, I believe I can construct the graph based on [Rubik's cube move notation](https://ruwix.com/the-rubiks-cube/notation/).

##Timeline
###Week 1
Be able to generate a graph of all the combinations of the 2x2 Rubik's cube and search for a solution. Also potentially create a CLI-based prototype of the application (type in scramble, output solution).

###Week 2
Create a basic Cinder framework for the user to input a scramble visually and convert the input into a recognizable format for the application to begin a search on. Also further optimize the searching algorithm to reduce search time.

###Week 3
Implement the ability to reset the state of the cube at any point in the application. Also implement some form of error checking and further optimize the cube.

##Extra Goals
Some extra goals that could be done if time allows are to implement some form of animation to replicate a real Rubik's cube. Another idea could be to support multiple puzzles such as the Skewb and Pyraminx (Since the standard 3x3x3 Rubik's cube has an insane amount of permutations, it likely can't be brute forced with a graph).
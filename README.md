# Algorithms for solving the traveling salesman problem (TSP)
An implementation of a set of algorithms for TSP solving.

## Table of contents
* [General info](#general-info)
* [Technologies](#technologies)
* [Setup](#setup)
* [Configuration](#configuration)

## General info
This project is dedicated to implementation of several most used and well-known algorithm for solving TSP. The list of implemented algorithms looks like this : 
 * Bruteforce
 * Branch and Bound
 * Simulated Annealing
 * Genetic 

### Branch and Bound
The implementation of the Branch and Bound algorithm in the project uses DFS (Depth-First Search) algorithm to look through the graph of solutions.

### Simulated Annealing
The simulated annealing algorithm, implemented in this project, is capable of using only linear annealing scheme with random neighborhood lookup algorithm.

This algorithm can be configured using the following parameters :
 * Starting temperature (double)
 * Epoch size (uint32_t)

### Genetic Algorithm
The genetic algorithm, which is used in this project, has only one algorithm for crossover (Order Crossover or OX), mutation (Swap) and selection (Roulette Wheel Algorithm).
	
This algorithm can be configured using the following parameters :
 * Crossover probability (float)
 * Mutation probability (float)
 * Population size (uint32_t)
 * Selection pool size (uint32_t)

## Technologies
Project is created with:
* C++: 20
* CMake: 3.12
* Make
	
## Setup
To run this project, build it locally using the following set of commands:

```
$ mkdir build && cd build
$ cmake ..
$ make
```

## Configuration
This project can be configured through an *.ini file. A sample file named sample.ini can be found in the root folder of this project.

To use the configuration instead of relying on the menu, run the application this way:

```
$ ./TSP <path_to_config>
```

### Output
If the configuration file is suplied, then the application will output the results of calculations into the file, specified in the configuration. The type of the output file should be *.csv and it cannot be changed at the moment. 

Typical output will contain the following information : 
 * The name of the test case (specified in the square brackets in the configuration file)
 * The time of execution (in microseconds)
 * The full path, the result of the execution
 * The cost of the path
 * 1 if the algorithm finished before the timeout, 0 otherwise
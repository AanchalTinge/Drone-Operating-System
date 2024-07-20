# Drone Operating System

This project involves creating a simple drone operating system in C++ with capabilities for navigation and mission planning. The system includes functionalities for takeoff, surveying, returning to home, and landing. It also implements a pathfinding algorithm to navigate through a graph of nodes.

## Features

- **Drone Operation Commands**: 
  - `takeoff()`: Simulates the drone taking off.
  - `land()`: Simulates the drone landing.
  - `returnToHome()`: Simulates the drone returning to its starting point.
  - `survey()`: Simulates the drone surveying a specified path.

- **Mission Planning**:
  - Uses Dijkstra's Algorithm to find the shortest path between two nodes on a graph.
  - The graph is fully connected with at least 100 nodes.

- **Multithreading**:
  - Implements multithreading to handle drone operations, mission planning, and surveying concurrently.

## Components

### 1. `DroneOperation` Class
- Handles drone commands using polymorphism.
- Commands include takeoff, land, return to home, and survey.

### 2. `MissionPlanning` Class
- Implements a graph search algorithm for pathfinding.
- Uses Dijkstra’s Algorithm to find the shortest path between nodes in a graph of 100+ nodes.

### 3. `Survey` Class
- Receives the path from the `MissionPlanning` class and simulates the surveying operation.

## Algorithms

### 1. **Dijkstra’s Algorithm**
- **Purpose**: Finds the shortest path between nodes in a weighted graph.
- **Time Complexity**: `O((V + E) * log(V))`, where `V` is the number of vertices and `E` is the number of edges.

### 2. **Multithreading**
- **Purpose**: Allows simultaneous execution of drone operations, mission planning, and surveying.
- **Implementation**: Uses `std::thread` for concurrency.
- **Complexity**: Time complexity varies based on the number of threads and tasks.

## Usage

1. **Compile the Code**: Use a C++ compiler to compile the source code.
2. **Run the Program**: Execute the compiled binary to simulate drone operations.
3. **Schedule Tasks**: The drone can be commanded to take off, survey, return home, or land.

## Example

1. **Initialization**:
   - Create instances of `DroneOperation`, `MissionPlanning`, and `Survey`.

2. **Execute Commands**:
   - Call `takeoff()` on the `DroneOperation` instance.
   - Use `MissionPlanning` to determine the path.
   - Call `survey()` with the path from `MissionPlanning`.
   - Finally, call `returnToHome()`.



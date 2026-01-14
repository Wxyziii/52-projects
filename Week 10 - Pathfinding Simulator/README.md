# Week 10: Pathfinding Simulator

## Project Overview
Implement and visualize pathfinding algorithms like A* and Dijkstra's on a grid-based map.

## Learning Objectives
- Graph traversal algorithms
- Heuristic-based search (A*)
- Priority queue usage
- Grid representation
- Path reconstruction
- Algorithm visualization

## Features to Implement
- [ ] Grid-based map representation
- [ ] A* pathfinding algorithm
- [ ] Dijkstra's algorithm
- [ ] Breadth-First Search (BFS)
- [ ] Depth-First Search (DFS)
- [ ] Wall/obstacle placement
- [ ] Start and end point selection
- [ ] Path visualization
- [ ] Step-by-step animation
- [ ] Cost calculation display
- [ ] Visited node highlighting

## Map Example
```
┌────────────────────────┐
│ S . . █ . . . . . . E │
│ . █ . █ . █████ . █ . │
│ . █ . . . . . . . █ . │
│ . █████ . █ █ . . █ . │
│ . . . . . █ . █████ . │
└────────────────────────┘
S = Start, E = End, █ = Wall, . = Path
```

## Algorithms to Implement
- **A***: Optimal with heuristic (Manhattan/Euclidean distance)
- **Dijkstra**: Optimal without heuristic
- **BFS**: Unweighted shortest path
- **DFS**: Simple exploration
- **Greedy Best-First**: Fast but not optimal

## Key Concepts
- Priority queue implementation
- Heuristic functions (Manhattan, Euclidean, Chebyshev)
- Graph representation (adjacency list/matrix)
- Path reconstruction with parent tracking
- Open and closed set management

## Extensions
- Add weighted terrain types
- Implement Jump Point Search (JPS)
- Add bidirectional search
- Create maze generation algorithms
- Support diagonal movement
- Add multiple path comparison
- Implement dynamic obstacle avoidance

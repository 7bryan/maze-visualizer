## Project Structure

```
maze-visualizer/
├── CMakeLists.txt
├── README.md
├── LICENSE
├── include/
│   ├── Maze.hpp
│   ├── MazeGenerator.hpp
│   ├── MazeSolver.hpp
│   └── Renderer.hpp
└── src/
    ├── main.cpp
    ├── Maze.cpp
    ├── MazeGenerator.cpp
    ├── MazeSolver.cpp
    └── Renderer.cpp
```

## Progress

### Foundation

- [x] CMake project
- [x] Basic executable

### Maze

- [ ] Cell representation
- [ ] Maze representation
- [ ] Neighbor detection
- [ ] Wall manipulation

### Generation

- [ ] DFS generation
- [ ] Iterative DFS generation
- [ ] Maze validation

### Rendering

- [ ] SFML window
- [ ] Maze rendering
- [ ] Start/end rendering

### Solving

- [ ] BFS
- [ ] DFS
- [ ] Path reconstruction

### Visualization

- [ ] Generation animation
- [ ] Solver animation
- [ ] Pause/resume
- [ ] Speed control

### Advanced

- [ ] Dijkstra
- [ ] A*
- [ ] Prim's
- [ ] Kruskal's

### Polish

- [ ] Statistics
- [ ] Random seed
- [ ] Maze size control
- [ ] Keyboard controls
- [ ] Documentation

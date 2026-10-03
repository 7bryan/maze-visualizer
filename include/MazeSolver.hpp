#pragma once
#include "Maze.hpp"
#include <vector>

class MazeSolver {
private:
  bool solveDFSHelper(Maze &maze, int r, int c,
                      std::vector<std::vector<bool>> &visited);

public:
  std::vector<std::vector<char>> DFSSolution;

  bool solveDFS(Maze &maze);
};

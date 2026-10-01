#include "../include/MazeGenerator.hpp"
#include <random>
#include <stack>
#include <vector>

void MazeGenerator::generate(Maze &maze) {
  std::stack<Maze::Cell> cellStack;

  int startR = 1;
  int startC = 1;

  maze.grid[startR][startC] = maze.EMPTY;
  cellStack.push({startR, startC});

  while (!cellStack.empty()) {
    Maze::Cell current = cellStack.top();
    std::vector<Maze::Cell> neighbors = maze.getNeighbors(current.r, current.c);

    if (!neighbors.empty()) {
      std::uniform_int_distribution<size_t> dist(0, neighbors.size() - 1);
      Maze::Cell next = neighbors[dist(maze.rng)];

      int wallR = current.r + (next.r - current.r) / 2;
      int wallC = current.c + (next.c - current.c) / 2;

      maze.grid[wallR][wallC] = maze.EMPTY;
      maze.grid[next.r][next.c] = maze.EMPTY;

      cellStack.push(next);
    } else {
      cellStack.pop();
    }
  }

  maze.grid[1][0] = 'S';
  maze.grid[maze.height - 2][maze.width - 1] = 'E';
}

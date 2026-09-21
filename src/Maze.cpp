#include "../include/Maze.hpp"
#include <chrono>
#include <vector>

Maze::Maze(int w, int h) {
  width = (w % 2 == 0) ? w + 1 : w;
  height = (h % 2 == 0) ? h + 1 : h;

  grid.assign(height, std::vector<char>(width, WALL));

  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  rng.seed(seed);
}

bool Maze::isValid(int r, int c) {
  return (r > 0 && r < height - 1 && c > 0 && c < width - 1 &&
          grid[r][c] == WALL);
}

std::vector<Maze::Cell> Maze::getNeighbors(int r, int c) {
  std::vector<Cell> neighbors;

  int dr[] = {-2, 2, 0, 0};
  int dc[] = {0, 0, -2, 2};

  for (int i = 0; i < 4; i++) {
    int nr = r + dr[i];
    int nc = c + dc[i];
    if (isValid(nr, nc)) {
      neighbors.push_back({nr, nc});
    }
  }

  return neighbors;
}

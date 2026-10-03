#include "../include/MazeSolver.hpp"

bool MazeSolver::solveDFSHelper(Maze &maze, int r, int c,
                                std::vector<std::vector<bool>> &visited) {
  if (r < 0 || c < 0 || r >= maze.height || c >= maze.width)
    return false;

  if (maze.grid[r][c] == maze.WALL || visited[r][c])
    return false;

  if (maze.grid[r][c] == 'E')
    return true;

  visited[r][c] = true;

  if (maze.grid[r][c] != 'S')
    DFSSolution[r][c] = '.';

  int dr[] = {-1, 1, 0, 0};
  int dc[] = {0, 0, -1, 1};

  for (int i = 0; i < 4; i++) {
    if (solveDFSHelper(maze, r + dr[i], c + dc[i], visited))
      return true;
  }

  if (maze.grid[r][c] != 'S')
    DFSSolution[r][c] = ' ';

  return false;
}

bool MazeSolver::solveDFS(Maze &maze) {
  DFSSolution = maze.grid;
  std::vector<std::vector<bool>> visited(
      maze.height,
      std::vector<bool>(maze.height, std::vector<bool>(maze.width, false)));

  int startR = 1;
  int startC = 0;

  return solveDFSHelper(maze, startR, startC, visited);
}

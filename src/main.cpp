#include <chrono>
#include <iostream>
#include <random>
#include <stack>
#include <vector>

enum class Direction { Up, Right, Down, Left };

const char WALL = '#';
const char PATH = ' ';

struct Cell {
  int r, c;
};

class MazeGenerator {
private:
  int width, height;
  std::vector<std::vector<char>> grid;
  std::mt19937 rng;

  std::vector<std::vector<char>> DFSsolution;

  bool isValid(int r, int c) {
    return (r > 0 && r < height - 1 && c > 0 && c < width - 1 &&
            grid[r][c] == WALL);
  }

  std::vector<Cell> getNeighbors(int r, int c) {
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

  bool solveDFSHelper(int r, int c, std::vector<std::vector<bool>> &visited) {
    if (r < 0 || c < 0 || r >= height || c >= width)
      return false;

    if (grid[r][c] == WALL || visited[r][c])
      return false;

    if (grid[r][c] == 'E')
      return true;

    visited[r][c] = true;

    if (grid[r][c] != 'S') {
      DFSsolution[r][c] = '.';
    }

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    for (int i = 0; i < 4; i++) {
      if (solveDFSHelper(r + dr[i], c + dc[i], visited)) {
        return true;
      }
    }

    // backtrack
    if (grid[r][c] != 'S') {
      DFSsolution[r][c] = ' ';
    }

    return false;
  }

public:
  MazeGenerator(int w, int h) {
    width = (w % 2 == 0) ? w + 1 : w;
    height = (h % 2 == 0) ? h + 1 : h;

    grid.assign(height, std::vector<char>(width, WALL));

    // Seed the random number generator
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    rng.seed(seed);
  }

  void generate() {
    std::stack<Cell> cellStack;

    // Start cell (must be odd coordinates)
    int startR = 1;
    int startC = 1;

    grid[startR][startC] = PATH;
    cellStack.push({startR, startC});

    while (!cellStack.empty()) {
      Cell current = cellStack.top();
      std::vector<Cell> neighbors = getNeighbors(current.r, current.c);

      if (!neighbors.empty()) {
        // Pick a random unvisited neighbor
        std::uniform_int_distribution<size_t> dist(0, neighbors.size() - 1);
        Cell next = neighbors[dist(rng)];

        // Carve through the wall separating current cell and next cell
        int wallR = current.r + (next.r - current.r) / 2;
        int wallC = current.c + (next.c - current.c) / 2;

        grid[wallR][wallC] = PATH;
        grid[next.r][next.c] = PATH;

        // Move to next cell
        cellStack.push(next);
      } else {
        // Backtrack if no unvisited neighbors exist
        cellStack.pop();
      }
    }

    // Create an Entrance and an Exit
    grid[1][0] = 'S';                  // Top-left entrance
    grid[height - 2][width - 1] = 'E'; // Bottom-right exit
  }

  void solveAndPrintDFS() {
    DFSsolution = grid;
    std::vector<std::vector<bool>> visited(height,
                                           std::vector<bool>(width, false));

    int startR = 1;
    int startC = 0;

    if (solveDFSHelper(startR, startC, visited)) {
      std::cout << "\nPath found using DFS:\n";
      for (int r = 0; r < height; ++r) {
        for (int c = 0; c < width; ++c) {
          std::cout << DFSsolution[r][c] << DFSsolution[r][c];
        }
        std::cout << "\n";
      }
    } else {
      std::cout << "\nNo path existed from the start to exit";
    }
  }

  void print() {
    std::cout << "Original Maze\n\n";
    for (int r = 0; r < height; ++r) {
      for (int c = 0; c < width; ++c) {
        std::cout << grid[r][c] << grid[r][c];
      }
      std::cout << "\n";
    }
  }
};

int main() {
  int width = 61;
  int height = 31;

  std::cout << "Generating a " << width << "x" << height << " maze\n\n";

  MazeGenerator maze(width, height);
  maze.generate();
  maze.print();
  maze.solveAndPrintDFS();
}

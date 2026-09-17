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
    grid[1][0] = PATH;                  // Top-left entrance
    grid[height - 2][width - 1] = PATH; // Bottom-right exit
  }

  void print() {
    for (int r = 0; r < height; ++r) {
      for (int c = 0; c < width; ++c) {
        std::cout << grid[r][c] << grid[r][c];
      }
      std::cout << "\n";
    }
  }
};

int main() {
  int width = 31;
  int height = 15;

  std::cout << "Generating a " << width << "x" << height << " maze\n\n";

  MazeGenerator maze(width, height);
  maze.generate();
  maze.print();
}

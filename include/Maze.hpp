#pragma once
#include <chrono>
#include <random>
#include <stack>
#include <vector>

class Maze {
  friend class MazeGenerator;

private:
  struct Cell {
    int r, c;
  };

  const char WALL = '#';
  const char EMPTY = ' ';

  int width, height;
  std::vector<std::vector<char>> grid;
  std::mt19937 rng;

  bool isValid(int r, int c);

  std::vector<Cell> getNeighbors(int r, int c);

public:
  Maze(int w, int h);
};

// class MazeGenerator {
// private:
//   struct Cell {
//     int r, c;
//   };

//   const char WALL, EMPTY;
//   std::vector<std::vector<char>> grid;
//   std::mt19937 rng;

//   bool isValid(int r, int c);

//   std::vector<Cell> getNeighbors(int r, int c);

//   bool solveDFSHelper(int r, int c, std::vector<std::vector<bool>>& visited);

// public:
//   MazeGenerator(int w, int h);

//   void generate();

//   void
// }

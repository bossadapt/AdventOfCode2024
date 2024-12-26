#include "cord.hpp"
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <tuple>
#include <vector>
struct ClawMachine {
  long long buttonAX;
  long long buttonAY;
  long long buttonBX;
  long long buttonBY;
  long long prizeX;
  long long prizeY;
};
using namespace std;
void findPossibleSkips(vector<string> *grid, Cord currentLocation,
                       vector<vector<long long>> *costs, long long currentCost,
                       Cord *end) {}
void recursiveFillMaze(vector<string> *grid, Cord currentLocation,
                       vector<vector<long long>> *costs, long long currentCost,
                       Cord *end) {
  long long nextCost = currentCost + 1;
  if (currentCost > costs->at(end->y).at(end->x)) {
    return;
  } else if (costs->at(currentLocation.y).at(currentLocation.x) <=
             currentCost) {
    // check if its been here before;
    return;
  } else if (costs->at(currentLocation.y).at(currentLocation.x) > currentCost) {
    costs->at(currentLocation.y).at(currentLocation.x) = currentCost;
  }
  // UP
  if (currentLocation.y - 1 >= 0 &&
      grid->at(currentLocation.y - 1).at(currentLocation.x) != '#') {
    Cord nextLocation = {currentLocation.x, currentLocation.y - 1};
    recursiveFillMaze(grid, nextLocation, costs, nextCost, end);
  }
  // DOWN
  if (currentLocation.y + 1 < grid->size() &&
      grid->at(currentLocation.y + 1).at(currentLocation.x) != '#') {
    Cord nextLocation = {currentLocation.x, currentLocation.y + 1};
    recursiveFillMaze(grid, nextLocation, costs, nextCost, end);
  }
  // LEFT
  if (currentLocation.x - 1 >= 0 &&
      grid->at(currentLocation.y).at(currentLocation.x - 1) != '#') {
    Cord nextLocation = {currentLocation.x - 1, currentLocation.y};
    recursiveFillMaze(grid, nextLocation, costs, nextCost, end);
  }
  // RIGHT
  if (currentLocation.x + 1 < grid->at(0).size() &&
      grid->at(currentLocation.y).at(currentLocation.x + 1) != '#') {
    Cord nextLocation = {currentLocation.x + 1, currentLocation.y};
    recursiveFillMaze(grid, nextLocation, costs, nextCost, end);
  }
}

int main(int argc, char const *argv[]) {
  ifstream file("example.txt");
  // ifstream file("question.txt");
  vector<string> grid;
  Cord start;
  Cord end;
  string curLine;
  // loading in the state of the machine
  while (getline(file, curLine)) {
    grid.push_back(curLine);
  }
  vector<vector<long long>> costs(
      grid.size(), std::vector<long long>(grid[0].size(), INT64_MAX));

  // find start and end
  bool startFound = false;
  bool endFound = false;
  for (int y = 0; y < grid.size(); y++) {
    for (int x = 0; x < grid[0].size(); x++) {
      if (!startFound && grid[y][x] == 'S') {
        startFound = true;
        start = {x, y};
      }
      if (!endFound && grid[y][x] == 'E') {
        endFound = true;
        end = {x, y};
      }
      if (startFound && endFound) {
        break;
      }
    }
  }
  recursiveFillMaze(&grid, start, &costs, 0, &end);
  printf("final solution: %lld\n", costs[end.y][end.x]);
  return 0;
}

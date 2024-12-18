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
using namespace std;
void recursiveFillMaze(vector<vector<char>> *grid, Cord currentLocation,
                       vector<vector<long long>> *costs, vector<Cord> path,
                       long long currentCost, Cord *end) {
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
    recursiveFillMaze(grid, nextLocation, costs, path, nextCost, end);
  }
  // DOWN
  if (currentLocation.y + 1 < grid->size() &&
      grid->at(currentLocation.y + 1).at(currentLocation.x) != '#') {
    Cord nextLocation = {currentLocation.x, currentLocation.y + 1};
    recursiveFillMaze(grid, nextLocation, costs, path, nextCost, end);
  }
  // LEFT
  if (currentLocation.x - 1 >= 0 &&
      grid->at(currentLocation.y).at(currentLocation.x - 1) != '#') {
    Cord nextLocation = {currentLocation.x - 1, currentLocation.y};
    recursiveFillMaze(grid, nextLocation, costs, path, nextCost, end);
  }
  // RIGHT
  if (currentLocation.x + 1 < grid->at(0).size() &&
      grid->at(currentLocation.y).at(currentLocation.x + 1) != '#') {
    Cord nextLocation = {currentLocation.x + 1, currentLocation.y};
    recursiveFillMaze(grid, nextLocation, costs, path, nextCost, end);
  }
}
using namespace std;
int main(int argc, char const *argv[]) {
  // ifstream file("example.txt");
  ifstream file("question.txt");
  int gridX = 71;
  int gridY = 71;
  // example
  // int gridX = 7;
  // int gridY = 7;
  vector<std::vector<char>> grid(gridY, std::vector<char>(gridX, '.'));
  vector<Cord> bytePositions;
  string curLine;
  // part 1
  // int index = 0;
  int part1Target = 1024;
  // example
  // int part1Target = 0;
  //  loading in the state of the machine
  int index = 0;
  while (getline(file, curLine)) {
    int insertX = stoi(curLine.substr(0, curLine.find(",")));
    int insertY = stoi(curLine.substr(curLine.find(",") + 1));
    printf("imputing at (%d,%d)\n", insertX, insertY);
    if (index < part1Target) {
      grid[insertY][insertX] = '#';
    }
    bytePositions.push_back({insertX, insertY});
    index++;
  }
  vector<vector<long long>> costs(
      grid.size(), std::vector<long long>(grid[0].size(), INT64_MAX));
  Cord end = Cord(gridX - 1, gridY - 1);
  do {
    part1Target++;
    for (int y = 0; y < costs.size(); y++) {
      for (int x = 0; x < costs[0].size(); x++) {
        costs[y][x] = INT64_MAX;
      }
    }
    grid[bytePositions[part1Target].y][bytePositions[part1Target].x] = '#';
    recursiveFillMaze(&grid, {0, 0}, &costs, {}, 0, &end);
    cout << "finished checking " << part1Target << endl;
  } while (costs[end.y][end.x] != INT64_MAX);
  for (vector<char> charList : grid) {
    for (char curChar : charList) {
      printf("%c", curChar);
    }
    printf("\n");
  }
  printf("\n");
  // printf("final solution: %lld\n", costs[end.y][end.x]);
  printf("failed at (%d,%d), index:%d\n", bytePositions[part1Target].x,
         bytePositions[part1Target].y, part1Target);
  return 0;
}

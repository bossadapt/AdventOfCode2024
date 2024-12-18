#include "cord.hpp"
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <tuple>
#include <unordered_set>
#include <vector>
enum Movement { UP, DOWN, LEFT, RIGHT };
using namespace std;
// covered by path since we want a less efficient solution for part 2
//  bool isGoingBackwards(Movement lastMovement, Movement next) {
//    switch (next) {
//    case UP:
//      if (lastMovement == DOWN) {
//        return true;
//      }
//      break;
//    case DOWN:
//      if (lastMovement == UP) {
//        return true;
//      }
//      break;
//    case LEFT:
//      if (lastMovement == RIGHT) {
//        return true;
//      }
//      break;
//    case RIGHT:
//      if (lastMovement == LEFT) {
//        return true;
//      }
//      break;
//    }
//    return false;
//  }

void recursiveFillMaze(vector<vector<char>> *grid, Cord currentLocation,
                       vector<vector<long long>> *costs, vector<Cord> path,
                       unordered_set<Cord, Cord::HashFunction> *bestUniqueTiles,
                       long long currentCost, Movement lastMovement,
                       Cord *end) {
  path.push_back(currentLocation);
  if (currentCost > costs->at(end->y).at(end->x)) {
    return;
  } else if (currentLocation.y == end->y && currentLocation.x == end->x) {
    // at the end, just ploppign all this end stuff in for part 2
    // printf("reached end with score\n");
    if (costs->at(currentLocation.y).at(currentLocation.x) > currentCost) {
      costs->at(currentLocation.y).at(currentLocation.x) = currentCost;
      bestUniqueTiles->clear();
      for (Cord tile : path) {
        bestUniqueTiles->insert(tile);
      }
    } else if (costs->at(currentLocation.y).at(currentLocation.x) ==
               currentCost) {
      for (Cord tile : path) {
        bestUniqueTiles->insert(tile);
      }
    }
  } else if (costs->at(currentLocation.y).at(currentLocation.x) < currentCost) {
    // check if its been here before;
    return;
  } else if (costs->at(currentLocation.y).at(currentLocation.x) > currentCost) {
    costs->at(currentLocation.y).at(currentLocation.x) = currentCost;
  }
  // UP
  if (grid->at(currentLocation.y - 1).at(currentLocation.x) != '#') {
    long long nextCost = currentCost + 1;
    Cord nextLocation = {currentLocation.x, currentLocation.y - 1};
    if (lastMovement != Movement::UP) {
      nextCost += 1000;
    }
    recursiveFillMaze(grid, nextLocation, costs, path, bestUniqueTiles,
                      nextCost, Movement::UP, end);
  }
  // DOWN
  if (grid->at(currentLocation.y + 1).at(currentLocation.x) != '#') {
    long long nextCost = currentCost + 1;
    Cord nextLocation = {currentLocation.x, currentLocation.y + 1};
    if (lastMovement != Movement::DOWN) {
      nextCost += 1000;
    }
    recursiveFillMaze(grid, nextLocation, costs, path, bestUniqueTiles,
                      nextCost, Movement::DOWN, end);
  }
  // LEFT
  if (grid->at(currentLocation.y).at(currentLocation.x - 1) != '#') {
    long long nextCost = currentCost + 1;
    Cord nextLocation = {currentLocation.x - 1, currentLocation.y};
    if (lastMovement != Movement::LEFT) {
      nextCost += 1000;
    }
    recursiveFillMaze(grid, nextLocation, costs, path, bestUniqueTiles,
                      nextCost, Movement::LEFT, end);
  }
  // RIGHT
  if (grid->at(currentLocation.y).at(currentLocation.x + 1) != '#') {
    long long nextCost = currentCost + 1;
    Cord nextLocation = {currentLocation.x + 1, currentLocation.y};
    if (lastMovement != Movement::RIGHT) {
      nextCost += 1000;
    }
    recursiveFillMaze(grid, nextLocation, costs, path, bestUniqueTiles,
                      nextCost, Movement::RIGHT, end);
  }
}
// brute force
//   fills the maze and only stores the most cost effective reaches at each node
//  void recursiveFillMaze(vector<vector<char>> *grid, Cord currentLocation,
//                         vector<vector<long long>> *costs, vector<Cord> path,
//                         unordered_set<Cord, Cord::HashFunction>
//                         *bestUniqueTiles, long long currentCost, Movement
//                         lastMovement, Cord *end) {
//    if (currentCost > 102488) {
//      return;
//    }
//    if (currentLocation.y == end->y && currentLocation.x == end->x) {
//      // at the end, just ploppign all this end stuff in for part 2
//      printf("reached end?(%d,%d)==(%d,%d)\n", end->x, end->y,
//      currentLocation.x,
//             currentLocation.y);

//     if (currentCost != 102488) {
//       return;
//     } else {
//       for (Cord currentCord : path) {
//         bestUniqueTiles->insert(currentCord);
//       }
//       return;
//     }
//   } else {
//     // not the end part
//     if (costs->at(currentLocation.y).at(currentLocation.x) < currentCost) {
//       // check if its been here before;
//       for (int i = path.size() - 1; i > -1; i--) {
//         if (path[i] == currentLocation) {
//           return;
//         }
//       }
//     } else if (costs->at(currentLocation.y).at(currentLocation.x) >
//                currentCost) {
//       costs->at(currentLocation.y).at(currentLocation.x) = currentCost;
//     }
//   }
//   path.push_back(currentLocation);
//   // UP
//   if (grid->at(currentLocation.y - 1).at(currentLocation.x) != '#') {
//     long long nextCost = currentCost + 1;
//     Cord nextLocation = {currentLocation.x, currentLocation.y - 1};
//     if (lastMovement != Movement::UP) {
//       nextCost += 1000;
//     }
//     recursiveFillMaze(grid, nextLocation, costs, path, bestUniqueTiles,
//                       nextCost, Movement::UP, end);
//   }
//   // DOWN
//   if (grid->at(currentLocation.y + 1).at(currentLocation.x) != '#') {
//     long long nextCost = currentCost + 1;
//     Cord nextLocation = {currentLocation.x, currentLocation.y + 1};
//     if (lastMovement != Movement::DOWN) {
//       nextCost += 1000;
//     }
//     recursiveFillMaze(grid, nextLocation, costs, path, bestUniqueTiles,
//                       nextCost, Movement::DOWN, end);
//   }
//   // LEFT
//   if (grid->at(currentLocation.y).at(currentLocation.x - 1) != '#') {
//     long long nextCost = currentCost + 1;
//     Cord nextLocation = {currentLocation.x - 1, currentLocation.y};
//     if (lastMovement != Movement::LEFT) {
//       nextCost += 1000;
//     }
//     recursiveFillMaze(grid, nextLocation, costs, path, bestUniqueTiles,
//                       nextCost, Movement::LEFT, end);
//   }
//   // RIGHT
//   if (grid->at(currentLocation.y).at(currentLocation.x + 1) != '#') {
//     long long nextCost = currentCost + 1;
//     Cord nextLocation = {currentLocation.x + 1, currentLocation.y};
//     if (lastMovement != Movement::RIGHT) {
//       nextCost += 1000;
//     }
//     recursiveFillMaze(grid, nextLocation, costs, path, bestUniqueTiles,
//                       nextCost, Movement::RIGHT, end);
//   }
// }
int main(int argc, char const *argv[]) {
  // ifstream file("example.txt");
  ifstream file("question.txt");
  string curLine;

  long long output = 0;
  vector<vector<char>> grid;
  // get the grid
  int index = 0;
  Cord startLocation = {};
  Cord endLocation = {};
  while (getline(file, curLine)) {
    grid.push_back({});
    int xIndex = 0;
    for (char currentChar : curLine) {
      if (currentChar == 'S') {
        startLocation = {xIndex, index};
      } else if (currentChar == 'E') {
        endLocation = {xIndex, index};
      }
      grid[index].push_back(currentChar);
      xIndex++;
    }
    index++;
  }
  vector<std::vector<long long>> costs(
      grid.size(), std::vector<long long>(grid[0].size(), INT64_MAX));
  unordered_set<Cord, Cord::HashFunction> uniqueTiles;
  recursiveFillMaze(&grid, startLocation, &costs, {}, &uniqueTiles, 0,
                    Movement::RIGHT, &endLocation);
  output = costs[endLocation.y][endLocation.x];
  printf("final solution: %lld\n", output);
  printf("total paths: %zu\n", uniqueTiles.size());
  return 0;
}

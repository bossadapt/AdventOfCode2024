
#include <chrono>
#include <fstream>
#include <iostream>
#include <stdio.h>
// #include <stack>
#include <stdlib.h>
#include <string>
#include <thread>
#include <vector>
using namespace std;
struct Cord {
  int x;
  int y;
};
// checking for ']' to spread to
// possible spreads
//[] | []   |   [][]    |   []
//[] |  []  |    []     |  []
bool pushable_y_rec(vector<vector<char>> grid,
                    vector<vector<int>> *locationsFound, Cord cordBeingMoved,
                    int depth, Cord movement) {
  // push the currentLocation to locations if not already on there
  if (locationsFound->size() <= depth) {
    printf("\nadding1 (%d,%d)\n", cordBeingMoved.x, depth);
    locationsFound->push_back({cordBeingMoved.x});
  } else {
    // check if it already exists
    // would use hashset if i didnt need to iterate over each bucket
    bool exists;
    vector<int> currentDepthBucket = locationsFound->at(depth);
    for (int i = 0; i < currentDepthBucket.size(); i++) {
      if (currentDepthBucket[i] == cordBeingMoved.x) {
        // theoretically even if this branch is false, then the other one should
        // have ended this run
        return true;
      }
    }

    printf("adding2 (%d,%d)\n", cordBeingMoved.x, depth);
    locationsFound->at(depth).push_back(cordBeingMoved.x);
  }
  // try to spread to new areas, and if nowhere to spread
  //[]
  //[]
  if (grid[cordBeingMoved.y + movement.y][cordBeingMoved.x] == ']') {
    // pushing straight through another box
    Cord newCordBeingMoved = {cordBeingMoved.x, cordBeingMoved.y + movement.y};
    return pushable_y_rec(grid, locationsFound, newCordBeingMoved, depth + 1,
                          movement);
  } else if (grid[cordBeingMoved.y + movement.y][cordBeingMoved.x] == '#' ||
             grid[cordBeingMoved.y + movement.y][cordBeingMoved.x - 1] == '#') {
    // pushing into a wall
    return false;
  } else {
    // either pushing into empty space or a akward box
    bool anotherPushHappening = false;
    Cord left = Cord{cordBeingMoved.x + -1, cordBeingMoved.y + movement.y};
    Cord right = Cord{cordBeingMoved.x + 1, cordBeingMoved.y + movement.y};
    if (grid[left.y][left.x] == ']' && grid[right.y][right.x] == ']') {
      printf("both found");
      return pushable_y_rec(grid, locationsFound, left, depth + 1, movement) &&
             pushable_y_rec(grid, locationsFound, right, depth + 1, movement);
    } else if (grid[left.y][left.x] == ']') {
      printf("left found");
      return pushable_y_rec(grid, locationsFound, left, depth + 1, movement);
    } else if (grid[right.y][right.x] == ']') {
      printf("right found");
      return pushable_y_rec(grid, locationsFound, right, depth + 1, movement);
    } else {
      printf("none");
      return true;
    }
  }
}

int main(int argc, char const *argv[]) {
  // ifstream file("example.txt");
  ifstream file("question.txt");
  vector<string> inputs;
  vector<Cord> movements;
  int index = 0;
  long long output = 0;
  string curLine;
  // build the grid and movements off of the inputs
  while (getline(file, curLine)) {
    if (curLine.length() == 0) {
      continue;
    } else if (curLine[0] == '#') {
      printf("%s\n", curLine.c_str());
      inputs.push_back(curLine);
    } else {
      for (char dir : curLine) {
        switch (dir) {
        case '<':
          movements.push_back({-1, 0});
          break;
        case '^':
          movements.push_back({0, -1});
          break;
        case '>':
          movements.push_back({1, 0});
          break;
        case 'v':
          movements.push_back({0, 1});
          break;
        }
      }
      printf("char finish");
    }
  }
  printf("finished 1");
  // find the robots location
  Cord robotCord = {0, 0};
  vector<vector<char>> grid;
  for (int y = 0; y < inputs.size(); y++) {
    vector<char> temp;
    for (int x = 0; x < inputs[y].size(); x++) {
      if (inputs[y][x] == '@') {
        temp.push_back('.');
        temp.push_back('.');
        robotCord = {x * 2, y};
      } else if (inputs[y][x] == 'O') {
        temp.push_back('[');
        temp.push_back(']');
      } else if (inputs[y][x] == '#') {
        temp.push_back('#');
        temp.push_back('#');
      } else if (inputs[y][x] == '.') {
        temp.push_back('.');
        temp.push_back('.');
      }
    }
    grid.push_back(temp);
  }
  printf("finished 2\n");
  for (int y = 0; y < grid.size(); y++) {
    for (int x = 0; x < grid[y].size(); x++) {
      printf("%c", grid[y][x]);
    }
    printf("\n");
  }
  printf("\n lens check 1:%zu,2:%d,3:%d,4:%zu\n", grid.size(), robotCord.x,
         robotCord.y, grid[0].size());
  printf("reached");
  // change the grid based on the movements
  for (Cord currentMove : movements) {
    Cord nextCord = {robotCord.x + currentMove.x, robotCord.y + currentMove.y};
    // printf("nextCord.x:%d , nextCord.y:%d\n", nextCord.x, nextCord.y);
    if (grid[nextCord.y][nextCord.x] == '.') {
      // printf("robot moved to (%d,%d)\n", nextCord.x, nextCord.y);
      robotCord = nextCord;
    } else if (grid[nextCord.y][nextCord.x] == '[' ||
               grid[nextCord.y][nextCord.x] == ']') {
      // check the back until wall found or space
      vector<vector<int>> Locations;
      if (currentMove.y != 0) {
        Cord pushedLocation = Cord{nextCord.x, nextCord.y};
        if (grid[nextCord.y][nextCord.x] == '[') {
          // it should always start on the ] side
          printf("correcting start from %d to %d", nextCord.x, nextCord.x + 1);
          pushedLocation.x += 1;
        }
        if (pushable_y_rec(grid, &Locations, pushedLocation, 0, currentMove)) {
          printf("push y ran");
          for (int depth = Locations.size() - 1; depth > -1; depth--) {
            for (int bucketIndex = 0; bucketIndex < Locations[depth].size();
                 bucketIndex++) {
              // offset each one by one outward and make the old space empty
              printf("\nLocation being moved from (%d,%d) to (%d,%d) and "
                     "(%d,%d) to (%d,%d)\n",
                     pushedLocation.y + depth, Locations[depth][bucketIndex],
                     pushedLocation.y + depth + currentMove.y,
                     Locations[depth][bucketIndex], pushedLocation.y + depth,
                     Locations[depth][bucketIndex],
                     pushedLocation.y + depth + currentMove.y,
                     Locations[depth][bucketIndex] - 1);
              int normalizedDepth = depth * currentMove.y;
              grid[pushedLocation.y + normalizedDepth]
                  [Locations[depth][bucketIndex]] = '.';
              grid[pushedLocation.y + normalizedDepth]
                  [Locations[depth][bucketIndex] - 1] = '.';
              grid[pushedLocation.y + normalizedDepth + currentMove.y]
                  [Locations[depth][bucketIndex]] = ']';
              grid[pushedLocation.y + normalizedDepth + currentMove.y]
                  [Locations[depth][bucketIndex] - 1] = '[';
            }
          }
          robotCord = nextCord;
        } else {
          printf("failed to push");
        }
      } else {
        int xIndex = nextCord.x;
        while (grid[nextCord.y][xIndex] == '[' ||
               grid[nextCord.y][xIndex] == ']') {
          xIndex += currentMove.x;
        }
        if (grid[nextCord.y][xIndex] == '.') {
          // move everything back one space
          while (xIndex != nextCord.x) {
            grid[nextCord.y][xIndex] = grid[nextCord.y][xIndex - currentMove.x];
            xIndex -= currentMove.x;
          }
          grid[nextCord.y][nextCord.x] = '.';
          robotCord = nextCord;
        } else {
          printf("failed to push");
        }
      }
    }

    // Uncomment to witness the robot wandering around
    //  printf("\nlocation(%d,%d) | move:(%d,%d)\n", robotCord.x, robotCord.y,
    //         currentMove.x, currentMove.y);
    //  for (int y = 0; y < grid.size(); y++) {
    //    for (int x = 0; x < grid[y].size(); x++) {
    //      if (y != robotCord.y || x != robotCord.x) {
    //        printf("%c", grid[y][x]);
    //      } else {
    //        printf("%c", '@');
    //      }
    //    }
    //    printf("\n");
    //  }
    //  this_thread::sleep_for(chrono::seconds(1));
  }
  for (int y = 0; y < grid.size(); y++) {
    for (int x = 0; x < grid[y].size(); x++) {
      if (y != robotCord.y || x != robotCord.x) {
        printf("%c", grid[y][x]);
      } else {
        printf("%c", '@');
      }
    }
    printf("\n");
  }
  for (int y = 0; y < grid.size(); y++) {
    for (int x = 0; x < grid[y].size(); x++) {
      if (grid[y][x] == '[') {
        output += 100 * y + x;
      }
    }
  }
  printf("final solution: %lld\n", output);
  return 0;
}
// // part 1
// int main(int argc, char const *argv[]) {
//   // ifstream file("example.txt");
//   ifstream file("question.txt");
//   vector<string> grid;
//   vector<Cord> movements;
//   int index = 0;
//   int output = 0;
//   string curLine;
//   // build the grid and movements off of the inputs
//   while (getline(file, curLine)) {
//     if (curLine.length() == 0) {
//       continue;
//     } else if (curLine[0] == '#') {
//       grid.push_back(curLine);
//     } else {
//       for (char dir : curLine) {
//         switch (dir) {
//         case '<':
//           movements.push_back({-1, 0});
//           break;
//         case '^':
//           movements.push_back({0, -1});
//           break;
//         case '>':
//           movements.push_back({1, 0});
//           break;
//         case 'v':
//           movements.push_back({0, 1});
//           break;
//         }
//       }
//     }
//   }
//   // find the robots location
//   Cord robotCord;
//   bool foundRobot;
//   for (int y = 0; y < grid.size() && !foundRobot; y++) {
//     for (int x = 0; x < grid[0].size(); x++) {
//       if (grid[y][x] == '@') {
//         grid[y][x] = '.';
//         robotCord = {x, y};
//         foundRobot = true;
//         break;
//       }
//     }
//   }
//   // change the grid based on the movements
//   for (Cord currentMove : movements) {
//     Cord nextCord = {robotCord.x + currentMove.x, robotCord.y +
//     currentMove.y}; if (grid[nextCord.y][nextCord.x] == '.') {
//       printf("robot moved to (%d,%d)\n", nextCord.x, nextCord.y);
//       robotCord = nextCord;
//     } else if (grid[nextCord.y][nextCord.x] == 'O') {
//       // check the back until wall found or space
//       bool canPush = false;
//       Cord currentCordCheck = {nextCord.x, nextCord.y};
//       while (grid[currentCordCheck.y][currentCordCheck.x] == 'O') {
//         currentCordCheck.y += currentMove.y;
//         currentCordCheck.x += currentMove.x;
//       }
//       if (grid[currentCordCheck.y][currentCordCheck.x] == '.') {
//         // move the group back one
//         grid[currentCordCheck.y][currentCordCheck.x] = 'O';
//         grid[nextCord.y][nextCord.x] = '.';
//         // move robot
//         printf("push box to get to (%d,%d)\n", nextCord.x, nextCord.y);
//         robotCord = nextCord;
//       } else {
//         printf("failed to push box at (%d,%d)\n", nextCord.x, nextCord.y);
//       }
//     }
//   }
//   for (int y = 0; y < grid.size(); y++) {
//     for (int x = 0; x < grid[0].size(); x++) {
//       if (grid[y][x] == 'O') {
//         output += 100 * y + x;
//       }
//     }
//   }
//   printf("final solution: %d\n", output);
//   return 0;
// }

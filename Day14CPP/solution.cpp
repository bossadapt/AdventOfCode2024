#include <chrono>
#include <cstdio>
#include <fstream>
#include <iterator>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <thread>
#include <vector>
struct BathroomRobot {
  int x;
  int y;
  int MoveX;
  int MoveY;
};
// example
// const int width = 11;
// const int height = 7;

const int width = 101;
const int height = 103;
using namespace std;
int guessFutureLocation(BathroomRobot br) {
  int locationX = br.x + (br.MoveX * 100) % width;
  int locationY = br.y + (br.MoveY * 100) % height;
  if (locationX != width / 2 && locationY != width / 2) {
    return 1;
  }
  return 0;
}
int main(int argc, char const *argv[]) {
  // ifstream file("example.txt");
  ifstream file("question.txt");
  vector<BathroomRobot> machines;
  string curLine;
  BathroomRobot curMachine = BathroomRobot();
  int index = 0;
  int output = 0;
  while (getline(file, curLine)) {
    istringstream ss(curLine);
    string curWord;
    while (ss >> curWord) {
      int x = stoi(curWord.substr(2, curWord.find(',')));
      int y = stoi(curWord.substr(curWord.find(',') + 1));
      if (index == 0) {
        curMachine.x = x;
        curMachine.y = y;
      } else {
        curMachine.MoveX = x;
        curMachine.MoveY = y;
      }
      index += 1;
    }
    machines.push_back(curMachine);
    curMachine = BathroomRobot();
    index = 0;
  }
  int topLeftQuad = 0;
  int topRightQuad = 0;
  int bottomLeftQuad = 0;
  int bottomRightQuad = 0;
  int midHeight = height / 2;
  int midWidth = width / 2;
  int seconds = 7500;
  bool fullLine = false;
  bool grid[height][width];
  while (!fullLine) {
    for (int i = 0; i < machines.size(); i++) {
      BathroomRobot current = machines[i];
      int locationX = (current.x + (current.MoveX * seconds)) % width;
      int locationY = (current.y + (current.MoveY * seconds)) % height;
      if (locationX < 0) {
        locationX += width;
      }
      if (locationY < 0) {
        locationY += height;
      }
      grid[locationY][locationX] = true;
      // printf("x:%d\n", locationX);
      // printf("y:%d\n", locationY);
      if (locationX > midWidth) {
        // right
        if (locationY > midHeight) {
          // bottom
          bottomRightQuad += 1;
        } else if (locationY != midHeight) {
          // top
          topRightQuad += 1;
        }
      } else if (locationX != midWidth) {
        if (locationY > midHeight) {
          // bottom
          bottomLeftQuad += 1;
        } else if (locationY != midHeight) {
          // top
          topLeftQuad += 1;
        }
      }
    }
    printf("second#:%d", seconds);
    for (int y = 0; y < size(grid); y++) {
      for (int x = 0; x < size(grid[0]); x++) {
        if (grid[y][x]) {
          printf("1");
        } else {
          printf(".");
        }
      }
      printf("\n");
    }
    printf("second:%d", seconds);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    for (int y = 0; y < size(grid); y++) {
      for (int x = 0; x < size(grid[0]); x++) {
        grid[y][x] = false;
      }
    }
    seconds += 1;
  }

  output = topLeftQuad * topRightQuad * bottomLeftQuad * bottomRightQuad;
  printf("TL:%d,TR:%d,BL:%d,BR:%d,output: %d\n", topLeftQuad, topRightQuad,
         bottomLeftQuad, bottomRightQuad, output);
  return 0;
}

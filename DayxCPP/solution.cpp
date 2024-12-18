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
int main(int argc, char const *argv[]) {
  ifstream file("example.txt");
  long long operands[7]{0, 1, 2, 3, 0, 0, 0};
  vector<int> instructions;
  string curLine;
  int index = 0;
  int output = 0;
  // loading in the state of the machine
  while (getline(file, curLine)) {
    switch (index) {
    case 0:
      operands[4] = stoi(curLine.substr(curLine.find(":") + 2));
      break;
    case 1:
      operands[5] = stoi(curLine.substr(curLine.find(":") + 2));
      break;
    case 2:
      operands[6] = stoi(curLine.substr(curLine.find(":") + 2));
      break;
    case 3:
      for (int i = 9; i < curLine.length(); i++) {
        if (i % 2 == 1) {
          long long current = curLine[i] - '0';
          instructions.push_back(current);
        }
      }
      break;
    case 4:

      break;
    }
    index++;
  }

  printf("\n");
  printf("final solution: %d\n", output);
  return 0;
}

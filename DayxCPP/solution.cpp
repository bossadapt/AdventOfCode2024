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
  // ifstream file("example.txt");
  ifstream file("question.txt");
  vector<ClawMachine> machines;
  string curLine;
  ClawMachine curMachine = ClawMachine();
  int index = 0;
  int output = 0;
  while (getline(file, curLine)) {
    if (curLine.length() == 0) {
      machines.push_back(curMachine);
      curMachine = ClawMachine();
      index = 0;
    }
    istringstream ss(curLine);
    string curWord;
    while (ss >> curWord) {
      //
    }
  }

  printf("final solution: %d\n", output);
  return 0;
}

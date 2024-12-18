#include <chrono>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <thread>
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
enum Registers {
  A = 4,
  B = 5,
  C = 6,
};
using namespace std;
vector<long long> santaHelper(vector<long long> program,
                              vector<long long> comboOperands) {
  vector<long long> output;
  for (int instructionPointer = 0; instructionPointer < program.size();
       instructionPointer++) {
    bool jumpHappened = false;
    switch (program[instructionPointer]) {
    case 0: {
      comboOperands[Registers::A] =
          comboOperands[Registers::A] /
          pow(2, comboOperands[program[instructionPointer + 1]]);
      break;
    }
    case 1: {
      comboOperands[Registers::B] =
          comboOperands[Registers::B] ^ program[instructionPointer + 1];
      break;
    }
    case 2: {
      comboOperands[Registers::B] =
          comboOperands[program[instructionPointer + 1]] % 8;
      break;
    }
    case 3: {
      if (comboOperands[Registers::A] == 0) {
        break;
      }
      instructionPointer = program[instructionPointer + 1];
      jumpHappened = true;
      break;
    }
    case 4: {
      comboOperands[Registers::B] =
          comboOperands[Registers::B] ^ comboOperands[Registers::C];
      break;
    }
    case 5: {
      int out = comboOperands[program[instructionPointer + 1]] % 8;
      output.push_back(out);
      break;
    }
    case 6: {
      comboOperands[Registers::B] =
          comboOperands[Registers::A] /
          pow(2, comboOperands[program[instructionPointer + 1]]);
      break;
    }
    case 7: {
      comboOperands[Registers::C] =
          comboOperands[Registers::A] /
          pow(2, comboOperands[program[instructionPointer + 1]]);
      break;
    }
    }
    if (!jumpHappened) {
      instructionPointer++;
    } else {
      // negating next increase
      instructionPointer--;
    }
  }
  return output;
}
int main(int argc, char const *argv[]) {
  // ifstream file("example.txt");
  ifstream file("question.txt");
  vector<long long> comboOperands = {
      0, 1, 2, 3, /*RegisterA*/ 0, /*RegisterB*/ 0, /*RegisterC*/ 0};
  comboOperands[0] = 0;
  vector<long long> program;
  string curLine;
  int index = 0;
  // loading in the state of the machine
  while (getline(file, curLine)) {
    switch (index) {
    case 0:
      comboOperands[4] = stoi(curLine.substr(curLine.find(":") + 2));
      break;
    case 1:
      comboOperands[5] = stoi(curLine.substr(curLine.find(":") + 2));
      break;
    case 2:
      comboOperands[6] = stoi(curLine.substr(curLine.find(":") + 2));
      break;
    case 4:
      for (int i = 9; i < curLine.length(); i++) {
        if (i % 2 == 1) {
          int current = curLine[i] - '0';
          program.push_back(current);
        }
      }
      break;
    }
    index++;
  }

  // Machine state printout
  printf("\n==========MACHINE STATE START===========\n");
  printf("operand:\n");
  for (long long operand : comboOperands) {
    printf("%lld,", operand);
  }
  printf("\nprogram:\n");
  for (long long curr : program) {
    printf("%lld,", curr);
  }
  printf("\n==========MACHINE STATE END===========\n");
  //
  // machine actually running
  // vector<int> idealOutput;
  // idealOutput = santaHelper(program, comboOperands);
  long long newA = -1;
  long long ogA = comboOperands[Registers::A];
  do {
    newA++;
    if (newA == ogA) {
      continue;
    } else {
      comboOperands[Registers::A] = newA;
      if (program == santaHelper(program, comboOperands)) {
        break;
      }
    }
  } while (true);
  printf("clone found at:%lld", newA);
}
// part 1
// int main(int argc, char const *argv[]) {
//   // ifstream file("example.txt");
//   ifstream file("question.txt");
//   long long comboOperands[7]{
//       0, 1, 2, 3, /*RegisterA*/ 0, /*RegisterB*/ 0, /*RegisterC*/ 0};
//   vector<int> program;
//   vector<int> output;
//   vector<int> output2;
//   string curLine;
//   int index = 0;
//   // loading in the state of the machine
//   while (getline(file, curLine)) {
//     switch (index) {
//     case 0:
//       comboOperands[4] = stoi(curLine.substr(curLine.find(":") + 2));
//       break;
//     case 1:
//       comboOperands[5] = stoi(curLine.substr(curLine.find(":") + 2));
//       break;
//     case 2:
//       comboOperands[6] = stoi(curLine.substr(curLine.find(":") + 2));
//       break;
//     case 4:
//       for (int i = 9; i < curLine.length(); i++) {
//         if (i % 2 == 1) {
//           int current = curLine[i] - '0';
//           program.push_back(current);
//         }
//       }
//       break;
//     }
//     index++;
//   }

//   // Machine state printout
//   printf("\n==========MACHINE STATE START===========\n");
//   printf("operand:\n");
//   for (long long operand : comboOperands) {
//     printf("%lld,", operand);
//   }
//   printf("\nprogram:\n");
//   for (long long curr : program) {
//     printf("%lld,", curr);
//   }
//   printf("\n==========MACHINE STATE END===========\n");
//   //
//   // machine actually running

//   for (int instructionPointer = 0; instructionPointer < program.size();
//        instructionPointer++) {
//     bool jumpHappened = false;
//     switch (program[instructionPointer]) {
//     case 0: {
//       // printf("ran case 0\n");
//       comboOperands[Registers::A] =
//           comboOperands[Registers::A] /
//           pow(2, comboOperands[program[instructionPointer + 1]]);
//       break;
//     }
//     case 1: {
//       // printf("ran case 1\n");
//       comboOperands[Registers::B] =
//           comboOperands[Registers::B] ^ program[instructionPointer + 1];
//       break;
//     }
//     case 2: {
//       // printf("ran case 2\n");
//       comboOperands[Registers::B] =
//           comboOperands[program[instructionPointer + 1]] % 8;
//       break;
//     }
//     case 3: {
//       // printf("ran case 3\n");
//       if (comboOperands[Registers::A] == 0) {
//         break;
//       }
//       instructionPointer = program[instructionPointer + 1];
//       jumpHappened = true;
//       break;
//     }
//     case 4: {
//       // printf("ran case 4\n");
//       comboOperands[Registers::B] =
//           comboOperands[Registers::B] ^ comboOperands[Registers::C];
//       break;
//     }
//     case 5: {
//       printf("ran case 5\n");
//       int out = comboOperands[program[instructionPointer + 1]] % 8;
//       // if (!secondRun) {
//       //   output.push_back(out);
//       // } else {
//       //   output2.push_back(out);
//       // }
//       output.push_back(out);
//       break;
//     }
//     case 6: {
//       // printf("ran case 6\n");
//       comboOperands[Registers::B] =
//           comboOperands[Registers::A] /
//           pow(2, comboOperands[program[instructionPointer + 1]]);
//       break;
//     }
//     case 7: {
//       // printf("ran case 7\n");
//       comboOperands[Registers::C] =
//           comboOperands[Registers::A] /
//           pow(2, comboOperands[program[instructionPointer + 1]]);
//       break;
//     }
//     }
//     // printf("instruction counter:%d\n", instructionPointer);
//     //  printf("reached");
//     if (!jumpHappened) {
//       instructionPointer++;
//     } else {
//       // negating next increase
//       instructionPointer--;
//     }
//   }
//   printf("\n==========MACHINE STATE START===========\n");
//   printf("operand:\n");
//   for (long long operand : comboOperands) {
//     printf("%lld,", operand);
//   }
//   printf("\nprogram:\n");
//   for (long long curr : program) {
//     printf("%lld,", curr);
//   }
//   printf("\n==========MACHINE STATE END===========\n");
//   printf("\nsystem output:\n");
//   for (int out : output) {
//     printf("%d,", out);
//   }
//   printf("\n");
// }

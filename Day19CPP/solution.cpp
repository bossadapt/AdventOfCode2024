#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <tuple>
#include <unordered_set>
#include <vector>

using namespace std;
// working backwards to build the pattern while taking multiple routes incase a
// shorter  pattern might cause me to trip up
// say the pattern is rggrb
// if rb is solved there will be a new instance of the method that pretends that
// solution does not exist and look for a pattern to fit grb
bool isTowelPatternPossible(unordered_set<string> *existingTowels,
                            string *goalTowelPattern, int currentSpot,
                            int numberOfCharToCheck, int longestTowelLength) {

  if (currentSpot == -1 || numberOfCharToCheck > longestTowelLength) {
    // printf("failedSMH\n");
    return false;
  }
  string curSubstring =
      goalTowelPattern->substr(currentSpot, numberOfCharToCheck);
  // printf("testing for %s\n", curSubstring.c_str());
  //  if it exists in existingTowels but is not found in existing towels used
  if (existingTowels->find(curSubstring) != existingTowels->end()) {
    // found all spots needed
    // printf("found %s\n", curSubstring.c_str());
    if (currentSpot == 0) {
      // printf("passed\n");
      return true;
    }
    // send it two diffrent realities where it existed and one where it didnt
    // didnt
    bool didntExist = isTowelPatternPossible(
        existingTowels, goalTowelPattern, currentSpot - 1,
        numberOfCharToCheck + 1, longestTowelLength);
    // did
    bool didExist =
        isTowelPatternPossible(existingTowels, goalTowelPattern,
                               currentSpot - 1, 1, longestTowelLength);
    return didExist || didntExist;
  } else {
    // just didnt exist or already existed
    return isTowelPatternPossible(existingTowels, goalTowelPattern,
                                  currentSpot - 1, numberOfCharToCheck + 1,
                                  longestTowelLength);
  }
}
int main(int argc, char const *argv[]) {
  // ifstream file("example.txt");
  ifstream file("question.txt");
  vector<string> goalTowelPatterns;
  unordered_set<string> existingTowels;
  string curLine;
  string curExistingTowel = "";
  long long output = 0;
  int longestExistingTowel;
  bool allExistingTowelsAdded = false;
  // loading in the state of the machine
  while (getline(file, curLine)) {
    if (curLine.empty()) {
      allExistingTowelsAdded = true;
      if (!curExistingTowel.empty()) {
        existingTowels.insert(curExistingTowel);
        curExistingTowel = "";
      }
      continue;
    }
    // importing
    if (allExistingTowelsAdded) {
      goalTowelPatterns.push_back(curLine);
    } else {
      curExistingTowel.clear();
      for (char curChar : curLine) {
        if (curChar == ' ') {
          continue;
        } else if (curChar == ',' && !curExistingTowel.empty()) {
          existingTowels.insert(curExistingTowel);
          // printf("added existing towel: '%s'\n", curExistingTowel.c_str());
          curExistingTowel.clear();
        } else {
          curExistingTowel = curExistingTowel + curChar;
        }
      }
    }
  }
  // find longest towel to cut back on uneeded recursion
  for (string towel : existingTowels) {
    if (towel.length() > longestExistingTowel) {
      longestExistingTowel = towel.length();
    }
  }
  for (string goal : goalTowelPatterns) {
    // unordered_set<string> newSet;
    printf("testing for goal: '%s'\n", goal.c_str());
    if (isTowelPatternPossible(&existingTowels, &goal, goal.length() - 1,
                               goal.length(), longestExistingTowel)) {
      output++;
    }
  }

  printf("\n");
  printf("final solution: %lld\n", output);
  return 0;
}

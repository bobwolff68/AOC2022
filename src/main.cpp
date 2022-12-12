#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include "stdio.h"
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <assert.h>

using namespace std;

bool ingestStrings(const char* fname, std::vector<std::string>& inputList) {
  char str[20];
  FILE* fp = fopen(fname, "r");

  if (!fp)
    return false;

  inputList.clear();

  while(1) {
    if (EOF==fscanf(fp, "%s\n", str)) {
      printf("Read a total of %lu entries.\n", inputList.size());
      fclose(fp);
      return true;
    }
      
    inputList.push_back(str);
    if (inputList.size() % 100 == 0)
      printf("Another 100 entries read...size is: %lu\n", inputList.size());
  }

}

bool ingestInts(const char* fname, std::vector<uint32_t>& inputList) {
  uint32_t tmp;
  FILE* fp = fopen(fname, "r");

  if (!fp)
    return false;

  inputList.clear();

  while(1) {
    if (EOF==fscanf(fp, "%u\n", &tmp)) {
      printf("Read a total of %lu entries.\n", inputList.size());
      fclose(fp);
      return true;
    }
      
    inputList.push_back(tmp);
    if (inputList.size() % 100 == 0)
      printf("Another 100 entries read...size is: %lu\n", inputList.size());
  }

}

bool ingestLines(const char* fname, std::vector<string>& inputList) {
  std::string line;
  std::ifstream input(fname);

  if (!input.is_open())
    return false;

  inputList.clear();

  while(std::getline( input, line )) {
    // if (line.length()==0) {
    //   printf("Finished reading for group %d. Total:%d\n", groupNum, groupTotal+tmp);
    //   inputList.push_back(groupTotal+tmp);
    // }
    // else
      inputList.push_back(line);

    if (inputList.size() % 250 == 0)
      printf("Another 100 entries read...size is: %lu\n", inputList.size());
  }

  printf("Read a total of %lu lines.\n", inputList.size());
  return true;
}

bool ingestIntGroups(const char* fname, std::vector<uint32_t>& inputList) {
  uint32_t tmp;
  std::string line;
  std::ifstream input(fname);

  if (!input.is_open())
    return false;

  inputList.clear();

  int groupNum=0;
  int groupTotal;
  int maxGroup=0;
  while(std::getline( input, line )) {
    if (line.length()==0) {
      tmp = strtoul(line.c_str(), NULL, 10);
      groupNum++;
      printf("Finished reading for group %d. Total:%d\n", groupNum, groupTotal+tmp);
      inputList.push_back(groupTotal+tmp);
      if (groupTotal+tmp > maxGroup)
        maxGroup = groupTotal + tmp;
      groupTotal=0;
    }
    else
      groupTotal += strtoul(line.c_str(), NULL, 10);
      
    // if (inputList.size() % 100 == 0)
    //   printf("Another 100 entries read...size is: %lu\n", inputList.size());
  }

  printf("Read a total of %lu entries. Max group entry was: %d\n", inputList.size(), maxGroup);
  return true;
}

bool ingestStringInt(const char* fname, std::vector<std::string>& inputCmds, std::vector<uint32_t>& inputInts) {
  uint32_t tmp;
  char cmd[10];
  FILE* fp = fopen(fname, "r");

  if (!fp)
    return false;

  inputInts.clear();
  inputCmds.clear();

  while(1) {
    if (EOF==fscanf(fp, "%s %u\n", cmd, &tmp)) {
      printf("Read a total of %lu entries.\n", inputInts.size());
      fclose(fp);
      return true;
    }
      
    inputCmds.push_back(cmd);
    inputInts.push_back(tmp);
    if (inputInts.size() % 100 == 0)
      printf("Another 100 entries read...size is: %lu\n", inputInts.size());
  }

}

void initCharStackWithString(stack<char>& theStack, string theString) {
  for (auto i=0; i<theString.length(); i++)
    theStack.push(theString[i]);
}

void initStackWithChar(stack<char>& theStack, vector<char>& theChars) {
  for (auto i=0; i<theChars.size(); i++)
    theStack.push(theChars[i]);
}

void initStackWithStrings(stack<string>& theStack, vector<string>& theStrings) {
  for (auto i=0; i<theStrings.size(); i++)
    theStack.push(theStrings[i]);
}

bool uniqueVector(vector<char> inVec) {
  sort(inVec.begin(), inVec.end());
  auto it = std::unique(inVec.begin(), inVec.end());
  return (it==inVec.end());
}

bool uniqueVectorUsingSet(vector<char> inVec) {
  std::set<char> st(inVec.begin(), inVec.end());
  return (inVec.size() == st.size());
}

void trimDir(std::string& dirInOut) {
  if (dirInOut.length() <= 1)
    return;
  else {
    auto i = dirInOut.rfind('/');
    if (i==0)
      dirInOut = "/";
    else
      dirInOut = dirInOut.substr(0, i);
  }
}

int main(int argc, char** argv) {
  printf("Hello world.\n");

  vector<string> rawInput;
  ingestLines("input/day12-sample.input", rawInput);
//  ingestLines("input/day12-sample2.input", rawInput);
//  ingestLines("input/day12.input", rawInput);

  int width=rawInput[0].length();
  int height=rawInput.size();

  int tally=0;

  int quantity, from, to;

//  for (auto i=0; i<rawInput.size(); i++) {
  for (auto i=0; i<5; i++) {
      // Read next instruction.
//        sscanf(rawInput[line].c_str(), "%s %d", charCmd, &operand);
  }

  printf("Final Part 1 Tally: %d\n", tally);
}

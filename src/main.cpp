#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include "stdio.h"
#include <string>
#include <vector>
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

void day1() {
  vector<uint32_t> theList;

  if (!ingestIntGroups("day1.input", theList)) {
    printf("Error ingesting data.\n");
    exit(1);
  }

  std::sort(theList.begin(), theList.end());
//std::sort(calories.begin(), calories.end(), std::greater<>());
  printf("First 3: %d, %d, %d\n", theList[0], theList[1], theList[2]);
  int sz = theList.size();
  printf("Last 3: %d, %d, %d\n", theList[sz-1], theList[sz-2], theList[sz-3]);
  printf("last sum: %d\n", theList[sz-1]+theList[sz-2]+theList[sz-3]);
}

int calcScore(unsigned char them, unsigned char us) {
  int draw=3;
  int win=6;
  if (them=='A' && us=='X') return draw;
  if (them=='B' && us=='Y') return draw;
  if (them=='C' && us=='Z') return draw;

  if (them=='A' && us=='Y') return win;
  if (them=='B' && us=='Z') return win;
  if (them=='C' && us=='X') return win;

  return 0; // loss
}

void day2() {
vector<string> inbound;

  ingestLines("day2.input", inbound);

  unsigned char they;
  unsigned char me;
  unsigned char theyRock='A';
  unsigned char theyPaper='B';
  unsigned char theyScissors='C';
  unsigned char meRock='X';
  unsigned char mePaper='Y';
  unsigned char meScissors='Z';
  int rockScore=1;
  int paperScore=2;
  int scissorsScore=3;
  int loss=0;
  int draw=3;
  int win=6;

  int tempScore=0;
  vector<int> scores;

  int otherTotal=0;

  for(int i=0; i<inbound.size(); i++) {
    they = inbound[i][0];
    me = inbound[i][2];
    tempScore = 0;


#if 0
    switch(me) {
      case 'X':
        tempScore = rockScore;
        break;
      case 'Y':
        tempScore = paperScore;
        break;
      case 'Z':
        tempScore = scissorsScore;
        break;
      default:
        printf("'me' played is invalid at index: %d, value:%c\n", i, me);
        break;
    }

    if (they==theyRock) {
      switch(me) {
        case 'X':
          tempScore += draw;
          break;
        case 'Y':
          tempScore += win;
          break;
        case 'Z':
          tempScore += loss;
          break;
        default:
          printf("invalid theyRock at index:%d\n", i);
          break;
      }
    }
    else if (they==theyPaper) {
      switch(me) {
        case 'X':
          tempScore += loss;
          break;
        case 'Y':
          tempScore += draw;
          break;
        case 'Z':
          tempScore += win;
          break;
        default:
          printf("invalid theyPaper at index:%d\n", i);
          break;
      }
    }
    else if (they==theyScissors) {
      switch(me) {
        case 'X':
          tempScore += win;
          break;
        case 'Y':
          tempScore += loss;
          break;
        case 'Z':
          tempScore += draw;
          break;
        default:
          printf("invalid theyScissors at index:%d\n", i);
          break;
      }
    }
    else {
      printf("Invalid 'they' at index: %d value: %c\n", i, they);
    }
#else
// X is need to LOSE
// Y is need to DRAW
// Z is need to WIN
    if (they==theyRock) {
      switch(me) {
        case 'X': // scissors loses
          tempScore = 3 + 0;
          break;
        case 'Y': // rock draws
          tempScore = 1 + 3;
          break;
        case 'Z': // paper wins
          tempScore = 2 + 6;
          break;
        default:
          printf("invalid theyRock at index:%d\n", i);
          break;
      }
    }
    else if (they==theyPaper) {
      switch(me) {
        case 'X': // rock loses
          tempScore = 1 + 0;
          break;
        case 'Y': // paper draws
          tempScore = 2 + 3;
          break;
        case 'Z': // scissors win
          tempScore = 3 + 6;
          break;
        default:
          printf("invalid theyPaper at index:%d\n", i);
          break;
      }
    }
    else if (they==theyScissors) {
      switch(me) {
        case 'X': // paper loses
          tempScore = 2 + 0;
          break;
        case 'Y': // scissors draw
          tempScore = 3 + 3;
          break;
        case 'Z': // rock wins
          tempScore += 1 + 6;
          break;
        default:
          printf("invalid theyScissors at index:%d\n", i);
          break;
      }
    }
    else {
      printf("Invalid 'they' at index: %d value: %c\n", i, they);
    }
#endif

    scores.push_back(tempScore);
    otherTotal += tempScore;
  }

  int total=0;
  for(int i=0; i<scores.size(); i++)
    total += scores[i];

  printf("Final total: %d while otherTotal=%d\n", total, otherTotal);

}

int main(int argc, char** argv) {
  printf("Hello world.\n");


exit(0);
}


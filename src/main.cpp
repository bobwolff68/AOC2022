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

#define SleepMS(x)  (std::this_thread::sleep_for(std::chrono::milliseconds((x))))

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

void day12printPath(vector<int>& pX, vector<int>& pY) {
  assert(pX.size() == pY.size());

  printf("Solution Path: %lu long.\n", pX.size());
  for (auto i=0; i<pX.size(); i++) {
//    printf(" grid[%d][%d] ", pY[i], pX[i]);
  }
  printf("\n");
}

void day12printVisited(vector<string>& m) {
  bool bSkippedRows=false;
  string empty="";

  for (auto k=0; k<m[0].length(); k++)
    empty.push_back('.');

  printf("MAP VISITED:\n");
  for (auto i=0; i<m.size(); i++) {
      if (m[i] == empty && !bSkippedRows) {
        printf("  Empties...\n");
        bSkippedRows=true;
      }
      if (m[i] != empty)
        printf("%s\n", m[i].c_str());
  }
  if (bSkippedRows)
    printf("  ...Empties\n");
}

vector<int> solLengths;

void day12popEm(vector<int>& pX, vector<int>& pY) {
  assert(pX.size() == pY.size());
  if (pX.size() < 1) {
    printf("popEm: ERROR - Cannot POP - pX.size()==%lu\n", pX.size());
  }
  else {
    pX.pop_back();
    pY.pop_back();
  }
}

void day12search(vector<string>& grid, vector<string>& v, int cX, int cY, vector<int>& pX, vector<int>& pY) {
  int curHeight;
  int width=grid[0].length();
  int height=grid.size();
  bool dbg=false;
  static int totalCalls=0;

  pX.push_back(cX);
  pY.push_back(cY);

  if (v[cY][cX] != '.')
    return;

  day12printVisited(v);
//  SleepMS(500);

  // if (pX.size() > 100) {
  //   day11printVisited(v);
  //   printf("EJECTING for PX SIZE of:%lu\n", pX.size());
  //   return;
  // }

  // if (totalCalls++ > 500) {
  //   printf("BALING OUT - TOTALCALLS.\n");
  //   return;
  // }

  if (cX<0 || cX>=width)
    return;
    
  if (cY<0 || cY>=height)
    return;
    
  if (grid[cY][cX]=='S')
    curHeight=1;  // lowest height (=='a')
  else
    curHeight=grid[cY][cX]-'a'+1;

  if (grid[cY][cX]=='E') {
    // Solution.
    day12printPath(pX, pY);
    solLengths.push_back(pX.size());
    return;
  }

  int nX, nY;
  int nH;

  if (dbg) 
  printf("@[%d][%d]=%d\n", cY, cX, curHeight);

  // Right
  nX=cX+1;
  nY=cY;
  if (dbg) printf("  RIGHT NextCalc[%d][%d]\n", nY, nX);

  if (nX>=0 && nY>=0 && nX<width && nY<height && v[nY][nX]=='.') {
    if (grid[nY][nX]=='S')
      nH=1;
    else if (grid[nY][nX]=='E')
      nH='z'-'a'+1;
    else
    nH = grid[nY][nX] - 'a' + 1;
    if (dbg) printf("  Candidate[%d][%d]=%d\n", nY, nX, nH);
    if (curHeight+1 >= nH) {
      v[cY][cX] = '>';
      day12search(grid, v, nX, nY, pX, pY);
      day12popEm(pX, pY);
      // process 'popping' the visitation.
//      v[nY][nX] = '.';
    }
  }

  // Down
  nX=cX;
  nY=cY+1;
  if (dbg) printf("  DOWN  NextCalc[%d][%d]\n", nY, nX);
  if (nX>=0 && nY>=0 && nX<width && nY<height && v[nY][nX]=='.') {
    if (grid[nY][nX]=='S')
      nH=1;
    else if (grid[nY][nX]=='E')
      nH='z'-'a'+1;
    else
    nH = grid[nY][nX] - 'a' + 1;
    if (dbg) printf("  Candidate[%d][%d]=%d\n", nY, nX, nH);
    if (curHeight+1 >= nH) {
      v[cY][cX] = 'V';
      day12search(grid, v, nX, nY, pX, pY);
      day12popEm(pX, pY);
      // process 'popping' the visitation.
//      v[nY][nX] = '.';
    }
  }

  // Up
  nX=cX;
  nY=cY-1;
  if (dbg) printf("  UP    NextCalc[%d][%d]\n", nY, nX);

  if (nX>=0 && nY>=0 && nX<width && nY<height && v[nY][nX]=='.') {
    if (grid[nY][nX]=='S')
      nH=1;
    else if (grid[nY][nX]=='E')
      nH='z'-'a'+1;
    else
    nH = grid[nY][nX] - 'a' + 1;
    if (dbg) printf("  Candidate[%d][%d]=%d\n", nY, nX, nH);
    if (curHeight+1 >= nH) {
      v[cY][cX] = '^';
      day12search(grid, v, nX, nY, pX, pY);
      day12popEm(pX, pY);
      // process 'popping' the visitation.
//      v[nY][nX] = '.';
    }
  }

  // Left
  nX=cX-1;
  nY=cY;
  if (nX>=0 && nY>=0 && nX<width && nY<height && v[nY][nX]=='.') {
    if (grid[nY][nX]=='S')
      nH=1;
    else if (grid[nY][nX]=='E')
      nH='z'-'a'+1;
    else
    nH = grid[nY][nX] - 'a' + 1;
    if (curHeight+1 >= nH) {
      v[cY][cX] = '<';
      day12search(grid, v, nX, nY, pX, pY);
      day12popEm(pX, pY);
      // process 'popping' the visitation.
//      v[nY][nX] = '.';
    }
  }

}

void day12Go(vector<string>& grid) {
// a is lowest elevation z is highest
// S - current position
// E - best signal
// S=a and E=z
// moves up/down/left/right only - and must be no more than 1 higher than current height (or = or lower)

  int width=grid[0].length();
  int height=grid.size();

  int destX=-1, destY=-1;
  int curX=-1, curY=-1;

  for (auto row=0; row<height; row++)
    for (auto col=0; col<width; col++) {
      if (grid[row][col]=='E') {
        destX=col;
        destY=row;
      }
      if (grid[row][col]=='S') {
        curX=col;
        curY=row;
      }
    }
  
  printf("Start[%d][%d] and destination[%d][%d]\n", curY, curX, destY, destX);
  assert(curX!=-1 && curY!=-1 && destX!=-1 && destY!=-1);

  vector<int> pathX;
  vector<int> pathY;

  vector<string> visited;
  for (auto row=0; row<grid.size(); row++) {
    visited.push_back("");
    for (auto col=0; col<grid[0].length(); col++)
      visited[row].push_back('.');
    visited[row][grid[0].length()]=0; // null terminator
  }

  day12search(grid, visited, curX, curY, pathX, pathY);
//  day11printVisited(visited);
  std::sort(solLengths.begin(), solLengths.end());
  for (auto i=0; i<solLengths.size(); i++)
    printf("%d ", solLengths[i]);
  printf("\n");
  printf("PART 1 solution min length: %d\n", solLengths[0]);
}

void day12() {
  printf("Hello day 12.\n");

  vector<string> rawInput;
//  ingestLines("input/day12-sample.input", rawInput);
//  ingestLines("input/day12-sample2.input", rawInput);
  ingestLines("input/day12.input", rawInput);

  day12Go(rawInput);
}

typedef struct stItem {
  struct stItem* pNext;
  vector<int> values;
} stItem_t;

void day13nodeInit(stItem_t* pI) {
  pI->pNext=NULL;
  pI->values.clear();
}

void day13printItem(stItem_t* pItems) {
  assert(pItems);
  stItem_t* pI = pItems;
  int iter=0;
  bool dbg=true;

  while(1) {
    if (dbg) printf("Iter: %d\n", iter);
    if (pI)
      printf("[");
    else
      break;
    
    if (pI->values.size()) {
      int sz=pI->values.size();
      for(auto x=0; x<sz; x++) {
        printf("%d", pI->values[x]);
        if (x!=sz-1)
          printf(",");
      }
      printf("]");
    }

    if (pI->pNext) {
      if (pI->values.size())
        printf(",");
      pI=pI->pNext;
    }
    else {
      printf("]\n");
      break;
    }

    iter++;
  }
  printf("\n");
}

void day13deleteNode(stItem_t* pI) {
  assert(pI);
  if (pI->pNext)
    day13deleteNode(pI->pNext);
  else
    delete pI;
}

// Frees everything except the item passed in.
void day13freeItem(stItem_t* pItems) {
  assert(pItems);

  if (pItems->pNext)
    day13deleteNode(pItems->pNext);

  day13nodeInit(pItems);
}

void day13parseLine(stItem_t* pItems, const char* ch) {
  assert(pItems);
  assert(ch);

  int tmpValue;
  int ret;

  // Skip the first character which is always [
  for (auto x=1; x<strlen(ch); x++) {
    if (ch[x]=='[') {
      pItems->pNext = new stItem_t;
      assert(pItems->pNext);
      day13nodeInit(pItems->pNext);
      pItems = pItems->pNext;
    }
    else if (ch[x]==']') {
      // End of a list. Nothing to do here?
    }
    else if (ch[x]==',') {
      // Comma separator ... skip it...
    }
    else if (ch[x]==0)
      break;
    else {
      // Bring in a number and advance to either a ',' or a ']'
      ret = sscanf(ch+x, "%d", &tmpValue);
      if (ret==0) {
        printf("  PROBLEM reading number at loc:%d - string:%s\n", x, ch);
        break;
      }
      else if (ret==EOF) {
        printf("  FOUND EOF reading number. Hmm - at val:%d, loc:%x, str:%s\n", tmpValue, x, ch);
        break;
      }
      else {
        pItems->values.push_back(tmpValue);
        while (ch[x]>='0' && ch[x]<='9')
          x++;
      }
    }
  }
}

int day13newNode(stItem_t* pI, const char* ch) {
  assert(pI);
  assert(ch);
  assert(ch[0]!=0);
  int ret;
  int tmpValue;
  bool dbg=true;
  stItem_t* pInew = new stItem_t;

  assert(pInew);
  day13nodeInit(pInew);

  pI->pNext = pInew;

  if (dbg) printf("newNode: input=%s\n", ch);

  int x=0;  // Start at the beginning
  while (1) {
    if (ch[x]=='[') {
      if (dbg) printf("Going for new node @ [%d]\n", x+1);
      x += day13newNode(pInew, ch+x+1);
      if (dbg) printf("  Resuming parsing after new node @[%d]: %s\n", x, ch+x);
      continue;
    }
    else if (ch[x]==']' || ch[x]==0)
      return x+1;
    else if (ch[x]==',') {
      x++;
      continue;
    }
    else {
      // Bring in a number and iterate numbers and commas
      while(1) {
        ret = sscanf(ch+x, "%d", &tmpValue);
        if (ret==0) {
          printf("  PROBLEM reading number at loc:%d - string:%s\n", x, ch);
          break;
        }
        else if (ret==EOF) {
          printf("  FOUND EOF reading number. Hmm - at val:%d, loc:%x, str:%s\n", tmpValue, x, ch);
          break;
        }
        else {
          if (dbg) printf("  Got value @ [%d]: %d\n", x, tmpValue);
          pInew->values.push_back(tmpValue);
          while ((ch[x]>='0' && ch[x]<='9') || ch[x]==',') {
//            if (dbg) printf("newNode: Skipping (%c)\n", ch[x]);
            x++;
            if (ch[x-1]==',')
              break;
          }
        }

        if (ch[x]=='[' || ch[x]==']') {
          if (dbg) printf("  Skipping out of number list @[%d] due to: (%c)\n", x, ch[x]);
          break;
        }
      }
    }

    x++;
  }

  assert(false);
  return x;
}

void day13() {
  printf("Hello Day 13.\n");

  vector<string> rawInput;
  ingestLines("input/day13-sample.input", rawInput);
//  ingestLines("input/day12-sample2.input", rawInput);
//  ingestLines("input/day13.input", rawInput);
  int tally=0;

  stItem_t rootFirst;
  stItem_t rootSecond;
  stItem_t* pI;

  day13nodeInit(&rootFirst);
  day13nodeInit(&rootSecond);

//  for (auto i=0; i<rawInput.size(); i++) {
  for (auto i=0; i<6; i++) {
    printf("PROCESSING line:%d: %s\n", i, rawInput[i].c_str());
    if (i % 3 == 0) {
      pI = &rootFirst;
      day13freeItem(pI);
      day13newNode(pI, rawInput[i].c_str()+1);
//      day13parseLine(pI, rawInput[i].c_str());
      day13printItem(pI);
    }
    else if (i % 3 == 1) {
      pI = &rootSecond;
      day13freeItem(pI);
      day13newNode(pI, rawInput[i].c_str()+1);
//      day13parseLine(pI, rawInput[i].c_str());
      day13printItem(pI);
    }
    else
      printf("Time to compare stuff.\n");

  }

//  printf("Final Part 1 Tally: %d\n", tally);
}

void dayXX() {
  printf("Hello world.\n");

  vector<string> rawInput;
//  ingestLines("input/day12-sample.input", rawInput);
//  ingestLines("input/day12-sample2.input", rawInput);
  ingestLines("input/day12.input", rawInput);


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

int main(int argc, char** argv) {
  printf("Hello world.\n");

  day13();
}

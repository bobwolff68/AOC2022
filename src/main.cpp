#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include "stdio.h"
#include <string>
#include <vector>
#include <tuple>
#include <map>
#include <set>
#include <queue>
#include <cmath>
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

  if (dbg) printf("Node has %lu values and has %s list entry.\n", pItems->values.size(), pItems->pNext ? "a" : "no");
  printf("[");
  
  if (pI->values.size()) {
    int sz=pI->values.size();
    for(auto x=0; x<sz; x++) {
      printf("%d", pI->values[x]);
      if (x!=sz-1)
        printf(",");
    }
  }

  if (pI->pNext) {
    printf("]");
    day13printItem(pI->pNext);
  }

  printf("]\n");
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
      x = x+1+ day13newNode(pInew, ch+x+1);
      if (dbg) printf("  Resuming parsing after new node @[%d]: %s\n", x, ch+x);
      continue;
    }
    else if (ch[x]==']' || ch[x]==0) {
      printf("  Exiting node - number of values in node are:%lu @[%d]: %s\n", pInew->values.size(), x, ch);
      return x+1;
    }
    else if (ch[x]==',') {
      x++;
      continue;
    }
    else {
      // Bring in a number and advance past the number - then go for next round.
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
        pInew->values.push_back(tmpValue);
        if (dbg) printf("  Got value @ [%d]: %d - number of values in list is:%lu\n", x, tmpValue, pInew->values.size());
        while (ch[x+1]>='0' && ch[x+1]<='9') {
          if (dbg) printf("newNode: Skipping @[%d] (%c)\n", x, ch[x]);
          x++;
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
      assert(pI->pNext);
      day13printItem(pI->pNext);
    }
    else if (i % 3 == 1) {
      pI = &rootSecond;
      day13freeItem(pI);
      day13newNode(pI, rawInput[i].c_str()+1);
//      day13parseLine(pI, rawInput[i].c_str());
      assert(pI->pNext);
      day13printItem(pI->pNext);
    }
    else
      printf("Time to compare stuff.\n");

  }

//  printf("Final Part 1 Tally: %d\n", tally);
}

class cube {
public:
  cube(int x, int y, int z) { ox=x; oy=y; oz=z;
    for (auto x=0; x<6; x++) showing[x]=true;
    bIsOutside=false;};
  enum Sides {Front, Back, Left, Right, Bottom, Top};
  // Can't have MORE than a single common side.
  // ONLY one axis can be different and only by 1.
  void CalcCommon(int x, int y, int z) {
    if (x==ox && y==oy && z==oz) {
      printf("SAME Origin: (%d,%d,%d)\n", x, y, z);
    }
    else if (x==ox && y==oy && abs(z-oz)==1) {
      // Top or bottom are common.
      if (z > oz) showing[Top]=false;
      else showing[Bottom]=false;
    }
    else if (x==ox && abs(y-oy)==1 && z==oz) {
      // Front or Back are common.
      if (y > oy) showing[Back]=false;
      else showing[Front]=false;
    }
    else if (abs(x-ox)==1 && y==oy && z==oz) {
      // Left or Right are common.
      if (x > ox) showing[Right]=false;
      else showing[Left]=false;
    }
  };
  int SidesShowing() { int numShowing=0;
    for (auto x=0; x<6; x++)
      if (showing[x]) numShowing++;
    return numShowing;
  };

  int ox, oy, oz;
  bool showing[6];
  bool bIsOutside;
};

vector<cube> theCubes;

cube* isFound(int x, int y, int z) {
  for (std::vector<cube>::iterator it=theCubes.begin(); it<theCubes.end(); it++)
    if (it->ox==x && it->oy==y && it->oz==z) {
      return &theCubes[it-theCubes.begin()];
    }
  
  return nullptr;
}

void markLocationOutsideIfFound(int x, int y, int z) {
  cube* pc=isFound(x,y,z);
  if (pc) {
    pc->bIsOutside=true;
  }
}

int tallyExternal() {
  int tally=0;
  for (auto it: theCubes)
    if (it.bIsOutside) tally++;

  return tally;
}

int getNumSidesOnExternals() {
  int tally=0;
  for (auto it: theCubes)
    if (it.bIsOutside) {
      tally += it.SidesShowing();
    }

  return tally;
}

int getNumSidesOnInternals() {
  int tally=0;
  for (auto it: theCubes)
    if (it.bIsOutside==false) {
      tally += it.SidesShowing();
    }

  return tally;
}

void day18() {
  printf("Hello world.\n");

  vector<string> rawInput;
//  ingestLines("input/day18-sample.input", rawInput);
//  ingestLines("input/day18-sample2.input", rawInput);
  ingestLines("input/day18.input", rawInput);

  int height=rawInput.size();

  int tally=0;

  for (auto i=0; i<rawInput.size(); i++) {
//  for (auto i=0; i<5; i++) {
      // Read next instruction.
      int x,y,z;
      sscanf(rawInput[i].c_str(), "%d,%d,%d", &x, &y, &z);
      theCubes.push_back(cube(x,y,z));
  }

  printf("Number of cubes=%lu\n", theCubes.size());
  cube* pMyCube;
  cube* pTheirCube;
  for (auto me=0; me<theCubes.size(); me++) {
    pMyCube=&theCubes[me];
    for (auto them=0; them<theCubes.size(); them++) {
      pTheirCube=&theCubes[them];
      if (me==them)
        continue;
      pMyCube->CalcCommon(pTheirCube->ox,pTheirCube->oy,pTheirCube->oz);
    }
  }

  for (auto it: theCubes)
    tally += it.SidesShowing();

// Part 1 - answer is 3636
  printf("Final Part 1 Tally: %d\n", tally);

  int minx, maxx, miny, maxy, minz, maxz;
  int t;
  t=theCubes[0].ox;
  minx=maxx=t;
  t=theCubes[0].oy;
  miny=maxy=t;
  t=theCubes[0].oz;
  minz=maxz=t;
  for (auto it: theCubes) {
    if (it.ox<minx) minx=it.ox;
    if (it.ox>maxx) maxx=it.ox;
    if (it.oy<miny) miny=it.oy;
    if (it.oy>maxy) maxy=it.oy;
    if (it.oz<minz) minz=it.oz;
    if (it.oz>maxz) maxz=it.oz;
  }
  // Now we know the overall min and max 'scan area'
  // expand the bounds of x/y/z box by one in all directions.
  //   This makes it easier later for our external scan.
    minx--; maxx++;
    miny--; maxy++;
    minz--; maxz++;

  cube* pc;


// Create a 2-d map of the front-shell and the back-shell
// Then iterate "Y" through each 2-d item to count ANY missing items.
// 
// Might I need an outer shell for the other directions too??

//
// Push front to back - note when we get to the first cube and begin counting ABSENT cubes
//   until we run into another cube. Then quit the push.
//
    bool foundOutside=false;
    int missingInternal=0;
    int candidates=0;
    for (auto x=minx; x<maxx; x++) {
      for (auto z=minz; z<maxz; z++) {
        foundOutside=false;
        candidates=0;
        for (auto y=miny; y<maxy; y++) {
          pc = isFound(x,y,z);
          if (pc && !foundOutside) {
            foundOutside=true;
          }
          else if (foundOutside && !pc) {
            // Found an internal missing cube.
            candidates++;
          }
          else if (foundOutside && pc) {
            // We've reached the other side of the shell
            missingInternal += candidates;
            if (candidates) 
              printf("Adding %d candidates now that we found the back side of the shell\n", candidates);
            break;
          }
        }
      }
    }
  printf("INTERNAL_HOLES: %d\n", missingInternal);



  // Now we approach the droplet from each of 6 directions and identify the first
    for (auto x=minx; x<maxx; x++) {
      for (auto z=minz; z<maxz; z++) {
        for (auto y=miny; y<maxy; y++) {
          markLocationOutsideIfFound(x,y,z);
          pc = isFound(x,y,z);
          if (pc) {
            pc->showing[cube::Back]=false;
            break;
          }

          markLocationOutsideIfFound(x-1,y,z);
          markLocationOutsideIfFound(x+1,y,z);
          markLocationOutsideIfFound(x,y,z-1);
          markLocationOutsideIfFound(x,y,z+1);
        }
      }
    }

    printf("FRONT_CHECK: Out of %lu total cubes, %d are external\n", theCubes.size(), tallyExternal());

    for (auto y=miny; y<maxy; y++) {
      for (auto z=minz; z<maxz; z++) {
        for (auto x=minx; x<maxx; x++) {
          markLocationOutsideIfFound(x,y,z);
          pc = isFound(x,y,z);
          if (pc) {
            pc->showing[cube::Right]=false;
            break;
          }

          markLocationOutsideIfFound(x,y-1,z);
          markLocationOutsideIfFound(x,y+1,z);
          markLocationOutsideIfFound(x,y,z-1);
          markLocationOutsideIfFound(x,y,z+1);
        }
      }
    }

    printf("LEFT_CHECK: Out of %lu total cubes, %d are external\n", theCubes.size(), tallyExternal());

    for (auto y=miny; y<maxy; y++) {
      for (auto x=minx; x<maxx; x++) {
        for (auto z=minz; z<maxz; z++) {
          markLocationOutsideIfFound(x,y,z);
          pc = isFound(x,y,z);
          if (pc) {
            pc->showing[cube::Top]=false;
            break;
          }

          markLocationOutsideIfFound(x,y-1,z);
          markLocationOutsideIfFound(x,y+1,z);
          markLocationOutsideIfFound(x-1,y,z);
          markLocationOutsideIfFound(x+1,y,z);
        }
      }
    }

    printf("BOTTOM_CHECK: Out of %lu total cubes, %d are external\n", theCubes.size(), tallyExternal());

//
// Now the NEGATIVE moving sides
//
    for (auto y=maxy; y>=miny; y--) {
      for (auto z=maxz; z>=minz; z--) {
        for (auto x=maxx; x>=minx; x--) {
          markLocationOutsideIfFound(x,y,z);
          pc = isFound(x,y,z);
          if (pc) {
            pc->showing[cube::Left]=false;
            break;
          }

          markLocationOutsideIfFound(x,y-1,z);
          markLocationOutsideIfFound(x,y+1,z);
          markLocationOutsideIfFound(x,y,z-1);
          markLocationOutsideIfFound(x,y,z+1);
        }
      }
    }

    printf("RIGHT_CHECK: Out of %lu total cubes, %d are external\n", theCubes.size(), tallyExternal());

    for (auto z=maxz; z>=minz; z--) {
      for (auto x=maxx; x>=minx; x--) {
        for (auto y=maxy; y>=miny; y--) {
          markLocationOutsideIfFound(x,y,z);
          pc = isFound(x,y,z);
          if (pc) {
            pc->showing[cube::Front]=false;
            break;
          }

          markLocationOutsideIfFound(x-1,y,z);
          markLocationOutsideIfFound(x+1,y,z);
          markLocationOutsideIfFound(x,y,z-1);
          markLocationOutsideIfFound(x,y,z+1);
        }
      }
    }

    printf("BACK_CHECK: Out of %lu total cubes, %d are external\n", theCubes.size(), tallyExternal());

    for (auto x=maxx; x>=minx; x--) {
      for (auto y=maxy; y>=miny; y--) {
        for (auto z=maxz; z>=minz; z--) {
          markLocationOutsideIfFound(x,y,z);
          pc = isFound(x,y,z);
          if (pc) {
            pc->showing[cube::Bottom]=false;
            break;
          }

          markLocationOutsideIfFound(x-1,y,z);
          markLocationOutsideIfFound(x+1,y,z);
          markLocationOutsideIfFound(x,y-1,z);
          markLocationOutsideIfFound(x,y+1,z);
        }
      }
    }

    printf("TOP_CHECK: Out of %lu total cubes, %d are external\n", theCubes.size(), tallyExternal());

// part 2 showed 3636 which is too high
//     3258 is also too high which was 3636 - 63*6 for the 63 internal open spots
//     but 
  printf("BOGUS - Counting only external cubes for sides-showing results in: %d\n", getNumSidesOnExternals());

  printf("How many exposed sides are INTERNAL: %d\n", getNumSidesOnInternals());
  // for (auto it: theCubes) {
  //   if (it.bIsOutside==false) {
  //     printf("Internal at (%d,%d,%d)\n", it.ox, it.oy, it.oz);
  //   }
  // }
}

void day20printVec(const char* msg, int iter, const vector<tuple<int,bool>> in) {
  assert(msg);
  printf("@Iteration=%d - %s: <", iter, msg);
  for (auto it: in) {
    printf("%d:%c ", get<0>(it), get<1>(it) ? 't' : 'f');
  }
  printf(">\n");
}

void day20printPart1AfterZero(vector<int> after) {
  printf("AFTER Zero Vector (Size of vector is: %lu):\n", after.size());

  for (auto i=0;i<3;i++)
    printf("[%d] = %d\n", i, after[i]);
  for (auto i=995;i<1005;i++)
    printf("[%d] = %d\n", i, after[i]);
  for (auto i=1995;i<2005;i++)
    printf("[%d] = %d\n", i, after[i]);
  for (auto i=2995;i<3004;i++)
    printf("[%d] = %d\n", i, after[i]);
}

void day20() {
  printf("Hello world.\n");

  vector<string> rawInput;
  ingestLines("input/day20-sample.input", rawInput);
//  ingestLines("input/day20.input", rawInput);

  vector<tuple<int,bool>> enc;
  vector<int> afterZero;
//  afterZero.push_back(0);   // Zero is at zero.

    for(auto it: rawInput) {
      int tmp;
      sscanf(it.c_str(), "%d", &tmp);
      enc.push_back(make_tuple(tmp, false));
    }

  int tally=0;

  int iterations=0;
  bool bFoundZero=false;
  bool bFirstTimeFindingZero=true;
  bool dbg=true;
  int simplePasses=0;

  int finalValues[3] = {-999,-998,-997};

  while(1) {
    for (vector<tuple<int,bool>>::iterator it=enc.begin(); it<enc.end() ; ) {
//      if (dbg) day20printVec("Before", iterations, enc);

      if (afterZero.size()>=3004) { day20printPart1AfterZero(afterZero); exit(0); }

      // Skip all of the items that have already been moved in this round.
      // while (it!=enc.end() && get<1>(*it)==true) {
      //   it++;
      // }
      for (it=enc.begin(); it!=enc.end(); it++) {
        if (get<1>(*it)==false)
          break;
      }

      if (it==enc.end()) {
        printf("ITER_COUNT==%d - Got to the end of the list.\n", iterations);
        assert(iterations==enc.size());

        vector<tuple<int,bool>>::iterator it3=enc.begin();
        if (bFoundZero && bFirstTimeFindingZero) {
          bFirstTimeFindingZero=false;
          // Find zero and then push entries AFTER that.
          for (it3=enc.begin(); it3!=enc.end(); it3++)
            if (get<0>(*it3)==0)
              break;
        }
        // Now iterate through either 'the rest' of the vector or the whole vector
        while(it3 != enc.end()) {
          afterZero.push_back(get<0>(*it3));
          it3++;
        }

        // Reset iteration count for next go-round.
        iterations=0;
        break;
      }

//      if (dbg) printf("  Beginning: focus will be %d @ [%lu]\n", get<0>(*it), it-enc.begin());

      int actionValue=get<0>(*it);
      int remainToEnd=enc.end() - it;
      int index=it - enc.begin();
      vector<tuple<int,bool>>::iterator lastit = enc.end();

      iterations++;

      if (actionValue != 0) {
        if (lastit==it) {
          enc.erase(it);
          it = enc.begin();
        }
        else
          it=enc.erase(it);
      }
      
      // Move it.
      if (actionValue>0) {
        // Move forward
        if (remainToEnd > actionValue) {
          enc.insert(it+actionValue, make_tuple(actionValue, true));
        }
        else {
          int rem = actionValue - remainToEnd + 1;
          enc.insert(enc.begin()+rem, make_tuple(actionValue, true));
        }
      }
      else if (actionValue < 0) {
        // Move backwards
        if (index + actionValue >= 0) {
          if (dbg) printf("going backwards: %d from index %d\n", actionValue, index);
          vector<tuple<int,bool>>::iterator writ = it + actionValue;
//          printf("  New home at %d\n", get<0>(*(writ)));
          if (index + actionValue == 0)
            enc.push_back(make_tuple(actionValue, true));
          else
            enc.insert(it+actionValue, make_tuple(actionValue, true));
        }
        else {
          int rem = index + actionValue;  // value(-3) and index=1 yields -2 from end
          if (dbg) printf("going backwards with wrap(rem==%d): %d from index %d\n", rem, actionValue, index);
          vector<tuple<int,bool>>::iterator writ = enc.end() + rem;
//          printf("  New home at %d\n", get<0>(*writ));
          enc.insert(writ, make_tuple(actionValue, true));
        }
      }
      else {
        // value is zero. Start counting.
        bFoundZero = true;
        get<1>(*it) = true;
        it++;
      }

      if (dbg) day20printVec(" After", iterations, enc);

    }

    // Reset all movement flags.
    for (auto& it2: enc) {
      std::get<1>(it2) = false;
//      printf("Resetting movement for: %d is now:%c\n", get<0>(*it2), get<1>(*it2) ? 't':'f');
    }

//printf("The iteration is: %d\n", iterations);
    // simplePasses++;
    // if (simplePasses==1000) {
    //   printf("Exiting early. passes=%d\n", simplePasses);
    //   exit(0);
    // }
    //   if (dbg) day20printVec("PRE_EXIT", enc, iterations);
    // printf("EXITING.\n");
    // break;
  }

  printf("Final Part 1 Tally: %d\n", tally);
}

typedef map<string, int64_t> num_t;
typedef map<string, string> equation_t;

void day21printnumbers(const char* msg, num_t& nums) {
  printf("%s: List of NUMBERS:\n", msg);
  for (auto it: nums) {
    printf("%s: %lld\n", it.first.c_str(), it.second);
  }
}

void day21printEquations(const char* msg, equation_t& eqs) {
  printf("%s: List of EQUATIONS:\n", msg);
  for (auto it: eqs) {
    printf("%s: %s\n", it.first.c_str(), it.second.c_str());
  }
}

void day21parseEq(string& eq, string& one, char& op, string& two) {
  char _one[10];
  char _two[10];
  char _op[5];

  sscanf(eq.c_str(), "%s %s %s", _one, _op, _two);
  one = _one;
  op = _op[0];
  two = _two;
//  printf("PARSE source:%s  into %s %c %s\n", eq.c_str(), one.c_str(), op, two.c_str());
}

bool day21reduction(num_t& nums, equation_t& eqs) {
  bool reduced=false;
  string one, two;
  char op;
  bool dbg=false;

  for (auto it=eqs.begin(); it!=eqs.end(); it++) {
    day21parseEq(it->second, one, op, two);
    if (one=="humn" || two=="humn")
      continue;

    if (dbg) printf("Reducing: Looking for %s or %s in numbers list.\n", one.c_str(), two.c_str());

    if (nums.find(one)!=nums.end() && nums.find(two)!=nums.end()) {
      // We found one reducible item
      int64_t v1, v2;
      reduced=true;
      v1 = nums.find(one)->second;
      v2 = nums.find(two)->second;
      if (nums.find(it->first) != nums.end()) {
        printf("ERROR: in Reduction: DUPLICATE FOUND for Monkey with numbers: %s\n", it->first.c_str());
        exit(0);
      }

      switch (op) {
        case '+':
          nums[it->first] = v1 + v2;
          eqs.erase(it);
          break;
        case '-':
          if (v2 > v1) {
            printf("for %s, would go negative for v1(%lld) - v2(%lld)\n", it->first.c_str(), v1, v2);
            exit(0);
          }
          nums[it->first] = v1 - v2;
          eqs.erase(it);
          break;
        case '*':
          nums[it->first] = v1 * v2;
          eqs.erase(it);
          break;
        case '/':
          nums[it->first] = v1 / v2;
          eqs.erase(it);
          break;
        default:
          printf("ERROR: Reduction - bad operator of: %c\n", op);
          exit(0);
          break;
      }

      return reduced; // Skipping out early because we screwed up the list by deleting 'it'
      // printf("GOT ONE.\n");
      // exit(0);
    }
  }

  if (dbg) printf("REDUCTION_COMPLETE.\n");
  return reduced;
}

string day21subOut(num_t& nums, equation_t& eqs, string& in, string& toSub, string& eqOut) {
  assert(in.find(toSub)!=std::string::npos);
  size_t front = in.find(toSub);
  bool dbg=true;
  string tmp;

  eqOut=""; // If number sub, this will stay as null.
  if (dbg) printf("Subbing: In:%s - toSub:%s\n", in.c_str(), toSub.c_str());

  if (eqs.find(toSub)!=eqs.end()) {
    // Substitute another equation here.
    tmp = in.substr(0,front) + "(";
    tmp += eqs[toSub];
    tmp += ")";
    tmp += in.substr(front+4);
    eqOut=eqs[toSub];
  }
  else {
    // Substitute a number
    assert(nums.find(toSub)!=nums.end());
    char tmp2[20];
    snprintf(tmp2, 20, "%lld", nums[toSub]);

    tmp = in.substr(0,front) + tmp2;
    tmp += in.substr(front+4);
  }

  if (dbg) printf("Subbing: OUT:%s\n", tmp.c_str());
  return tmp;
}

void day21sub(num_t& nums, equation_t& eqs, string& subRoot) {
  string one, two;
  string eqOutOne;
  char op;
  string out="(";

  day21parseEq(eqs[subRoot], one, op, two);
  out += eqs[subRoot];
  out += ")";
  printf("SUB: Starting sub of %s - one(%s), two(%s)\n", out.c_str(), one.c_str(), two.c_str());

  assert(nums.find(subRoot)==nums.end());

  vector<string> subList;
  subList.push_back(one);
  subList.push_back(two);

  while (subList.size()) {
    out = day21subOut(nums, eqs, out, subList.back(), eqOutOne);
    subList.pop_back();

    if (eqOutOne!="") {
      day21parseEq(eqOutOne, one, op, two);
      if (one != "humn")
        subList.push_back(one);
      if (two != "humn")
        subList.push_back(two);
    }

    // if (one=="humn" || two=="humn") {
    //   printf("Found HUMN - size of remaining vector is: %lu\n", subList.size());
    //   break;
    // }
  }

}

void day21() {
  printf("Hello world.\n");

  vector<string> rawInput;
//  ingestLines("input/day21-sample.input", rawInput);
//  ingestLines("input/day21-sample2.input", rawInput);
  ingestLines("input/day21.input", rawInput);


  int width=rawInput[0].length();
  int height=rawInput.size();

  int tally=0;

  char monkey[5];
  string valueStr;
  int value;
  num_t numbers;
  equation_t equations;
  string name;

  for (auto i=0; i<rawInput.size(); i++) {
//  for (auto i=0; i<5; i++) {
      // Read next instruction.
      sscanf(rawInput[i].c_str(), "%s", monkey);
      monkey[4] = 0; // trim off ":"
      name = monkey;
      valueStr = &rawInput[i][6];

      if (sscanf(valueStr.c_str(), "%d", &value)==1) {
        // Make sure there's NOT already one of these.
        printf("Processing Monkey:%s with a number of %d\n", name.c_str(), value);
        if (numbers.find(name) != numbers.end()) {
          printf("ERROR: DUPLICATE FOUND for Monkey with numbers: %s\n", name.c_str());
          exit(0);
        }
        numbers[name] = value;
      }
      else {
        // Make sure there's NOT already one of these.
        printf("Processing Monkey:%s with an equation of %s\n", name.c_str(), valueStr.c_str());
        if (equations.find(name) != equations.end()) {
          printf("ERROR: DUPLICATE FOUND for Monkey with an equation: %s\n", name.c_str());
          exit(0);
        }
        equations[name] = valueStr;
      }
  }

  day21printnumbers("START", numbers);
  day21printEquations("START", equations);

  // Collapse any equations to a value and then do it again until we're down to name-recursion-items
  while (day21reduction(numbers, equations))
    ;

  // day21printnumbers("REDUCED", numbers);
  // day21printEquations("REDUCED", equations);

  // printf("ddzt: ssgd(%lld) * ntvz(%lld)\n", numbers["ssgd"], numbers["ntvz"]);
  // printf("rmtp: sczz(%lld) * nsgb(%lld)\n", numbers["sczz"], numbers["nsgb"]);
  // printf("root: ddzt(%lld) + rmtp(%lld)\n", numbers["ddzt"], numbers["rmtp"]);
  // printf("Final Part 1 Tally: %lld\n", numbers["root"]);
  // -98997638 was wrong
  // Part 1 - answer: 256997859093114  (using int64_t)

  // Part 2 - solve (6 * (29958372186126 - (((3 * (((783 + ((((210 + (3 * ((((((((((((2 * (((((((892 + ((((((((208 + (((26 * ((((2 * (((((((638 + ((((((((((693 + ((humn - 898) * 24)) / 9) - 914) * 9) + 765) / 2) - 172) / 5) + 557) * 7)) * 2) - 916) / 6) - 350) / 3) + 585)) + 540) / 8) - 121)) - 668) * 2)) / 6) + 598) / 8) - 730) * 57) - 327) / 6)) * 6) - 537) / 3) + 116) * 3) - 717)) + 481) + 676) / 5) + 53) / 6) - 506) * 7) - 600) + 255) / 2) + 585))) * 2) - 384) / 2)) / 2) - 570)) + 397) / 7)))=77247625979730
  // 3952288690726
  string one, two;
  char op1;
  day21parseEq(equations["root"], one, op1, two);

  string subRoot;
  int64_t valueRoot;
  if (numbers.find(one)!=numbers.end()) {
    valueRoot = numbers[one];
    assert(valueRoot!=0);
    subRoot = two;
    printf("ROOT = %lld %c %s\n", valueRoot, op1, subRoot.c_str());
  }
  else {
    assert(numbers.find(two)!=numbers.end());
    valueRoot = numbers[two];
    subRoot = one;
    printf("ROOT = %s %c %lld\n", subRoot.c_str(), op1, valueRoot);
  }
  day21sub(numbers, equations, subRoot);
  printf("SUB-OUTPUT: %s\n", subRoot.c_str());
}

typedef vector<pair<int, int>> d23_t;
d23_t elvesCurrent;
d23_t elvesProposed;
int d23minx, d23maxx, d23miny, d23maxy;
enum d23_dir {North, South, West, East};
d23_dir curDir=North;

void day23calcBounding() {
  bool dbg=true;
  assert(elvesCurrent.size() != 0);
  d23minx=elvesCurrent[0].first;
  d23maxx=elvesCurrent[0].first;
  d23miny=elvesCurrent[0].second;
  d23maxy=elvesCurrent[0].second;

  for (auto it: elvesCurrent) {
    if (it.first<d23minx) d23minx=it.first;
    if (it.first>d23maxx) d23maxx=it.first;
    if (it.second<d23miny) d23miny=it.second;
    if (it.second>d23maxy) d23maxy=it.second;
  }
  if (dbg) printf("Bounding: #Elves:%lu - MinX=%d, MaxX=%d, MinY=%d, MaxY=%d\n", elvesCurrent.size(), d23minx, d23maxx, d23miny, d23maxy);
}

bool day23isPresentAt(int x, int y) {
  for (auto it: elvesCurrent) {
    if (it.first==x && it.second==y)
      return true;
  }
  return false;
}

bool day23isAllAloneAt(int x, int y) {
  assert(day23isPresentAt(x,y));

  if (day23isPresentAt(x-1,y-1) || day23isPresentAt(x,y-1) || day23isPresentAt(x+1,y-1) ||
      day23isPresentAt(x-1,y) || day23isPresentAt(x+1,y) ||
      day23isPresentAt(x-1,y+1) || day23isPresentAt(x,y+1) || day23isPresentAt(x+1,y+1))
        return false;

  return true;
}

int day23getEmptySpaces() {
  day23calcBounding();
  return (d23maxx-d23minx+1)*(d23maxy-d23miny+1) - elvesCurrent.size();
  // int emptySpaces=(d23maxx-d23minx+1)*(d23maxy-d23miny+1);  // Start with no one anywhere.
  // for (auto y=d23miny; y<=d23maxy; y++) {
  //   for (auto x=d23minx; x<=d23maxx; x++) {
  //     if (day23isPresentAt(x,y))
  //       emptySpaces--;
  //   }
  // }  
  // return emptySpaces;
}

void day23printCurrent(const char* msg) {
  printf("[%s] The Grove currently looks like this:\n", msg);
  day23calcBounding();
  for (auto y=d23miny-1; y<=d23maxy+1; y++) {
    for (auto x=d23minx-1; x<=d23maxx+1; x++) {
      if (day23isPresentAt(x,y))
        printf("#");
      else
        printf(".");
    }
    printf("\n");
  }  
}

int day23getIndexFor(d23_t& theList, int x, int y) {
  for (d23_t::iterator it=theList.begin(); it!=theList.end(); it++) {
    if (it->first==x && it->second==y)
      return it-theList.begin();
  }
  return -1;
}

void day23backOutProposalAt(int x, int y) {
  // Find x,y in the proposed list.
  //   Then figure the index and use that index in the current list to get the prior value.
  //   Use the prior value to change the current proposal.
  d23_t::iterator itProp = elvesProposed.begin();
  while (itProp != elvesProposed.end()) {
    if (itProp->first==x && itProp->second==y) {
      itProp->first  = elvesCurrent[itProp-elvesProposed.begin()].first;
      itProp->second = elvesCurrent[itProp-elvesProposed.begin()].second;
      return;
    }

    itProp++;
  }

  printf("ERROR: Backing out proposal at (%d, %d) failed. Not found.\n", x, y);
  exit(0);
}

//
// 
// The proposed list MIRRORS the current list. 
//   Each elf either moves or stays put - so if we do need to back out, we can.
//
//
void day23makeProposalAt(int x, int y) {
  bool dbg=false;
  d23_dir dirTry = curDir;
  int triesRemaining=4;
  static vector<string> directions { "North", "South", "West", "East"};
  int pX, pY;
  bool bProposed=false;

  if (day23isAllAloneAt(x, y)) {
    if (dbg) printf("   Proposal: All alone - no movement for (%d, %d)\n", x, y);
    elvesProposed.push_back(make_pair(x, y));
    return;
  }

  while (triesRemaining--) {
//    if (dbg) printf("   Proposal: For (%d, %d) - trying direction: %s\n", x, y, directions[int(dirTry)].c_str());
    switch(dirTry) {
      case North:
        if (!day23isPresentAt(x-1, y-1) && !day23isPresentAt(x, y-1) && !day23isPresentAt(x+1, y-1)) {
          bProposed=true;
          pX = x;
          pY = y-1;
        }
        else
          dirTry = South;
        break;
      case South:
        if (!day23isPresentAt(x-1, y+1) && !day23isPresentAt(x, y+1) && !day23isPresentAt(x+1, y+1)) {
          bProposed=true;
          pX = x;
          pY = y+1;
        }
        else
          dirTry = West;
        break;
      case West:
        if (!day23isPresentAt(x-1, y-1) && !day23isPresentAt(x-1, y) && !day23isPresentAt(x-1, y+1)) {
          bProposed=true;
          pX = x-1;
          pY = y;
        }
        else
          dirTry = East;
        break;
      case East:
        if (!day23isPresentAt(x+1, y-1) && !day23isPresentAt(x+1, y) && !day23isPresentAt(x+1, y+1)) {
          bProposed=true;
          pX = x+1;
          pY = y;
        }
        else
          dirTry = North;
        break;
    }

    if (bProposed) {
      // Need to figure if there's a collision or not
      if (day23getIndexFor(elvesProposed, pX, pY)!=-1) {
        // Need to back out.
        if (dbg) printf(" ALERT: Backing out proposal for collision at (%d, %d)\n", pX, pY);
        day23backOutProposalAt(pX, pY);
        // Now don't move the current one.
        elvesProposed.push_back(make_pair(x, y));
        return;
      }
      else {
        elvesProposed.push_back(make_pair(pX,pY));
        if (dbg) printf("   Proposal-%s: Elf @ (%d, %d) moving to (%d, %d)\n", directions[int(dirTry)].c_str(), x, y, pX, pY);
        return;
      }
    }
  }

// If we drop out the bottom, then by definition our proposed location is not moving.
  if (dbg) printf("   Proposal: Unable to move - no movement for (%d, %d)\n", x, y);
  elvesProposed.push_back(make_pair(x, y));

}

void day23doProposals() {
  bool dbg=false;
  int dbgCount=0;
  elvesProposed.clear();

  for (auto it: elvesCurrent) {
    if (dbg) printf("Proposal being prepped at (%d, %d)\n", it.first, it.second);
    day23makeProposalAt(it.first, it.second);
//    if (dbgCount++ == 2) exit(0);
  }
}

void day23() {
  printf("Hello world.\n");

  vector<string> rawInput;
//  ingestLines("input/day23-sample0.input", rawInput);
//  ingestLines("input/day23-sample.input", rawInput);
//  ingestLines("input/day23-sample2.input", rawInput);
  ingestLines("input/day23.input", rawInput);

  int width=rawInput[0].length();
  int height=rawInput.size();

  int tally=0;

  int quantity, from, to;

  for (auto i=0; i<rawInput.size(); i++) {
//  for (auto i=0; i<5; i++) {
    for (auto col=0; col<width; col++) {
      if (rawInput[i][col]=='#')
        elvesCurrent.push_back(make_pair(col, i));
    }
//        sscanf(rawInput[i].c_str(), "%s %d", charCmd, &operand);
  }

  day23printCurrent("START");
  for (auto i=0; i<10000; i++) {
    printf("ROUND #%d starting. #Elves:%lu Default direction is:%d\n", i+1, elvesCurrent.size(), int(curDir));
//  if (i==2) propExit=true;
    day23doProposals();
    if (elvesCurrent == elvesProposed) {
      printf("***NO CHANGES*** - Round#%d\n", i+1);
      exit(0);
    }
    elvesCurrent = elvesProposed;
//    day23printCurrent("POST-PROPOSALs");
    day23calcBounding();
    printf("ROUND #%d END - #Elves:%lu Number of empty spaces: %d\n", i+1, elvesCurrent.size(), day23getEmptySpaces());
    curDir = d23_dir((int(curDir) + 1) % 4);
//  if (i==4) exit(0);
  }

  printf("Final Part 1 # of empty spaces: %d\n", day23getEmptySpaces());
  // Part 1 answer - 4208
}

typedef vector<tuple<int, int, char>> d24_t;
d24_t blizzards;
typedef vector<vector<char>> d24map_t;
d24map_t expeditionMap;
static int entranceCol=-1;
static int exitCol=-1;
static int EmapWidth=-1;
static int EmapHeight=-1;
pair<int, int> E {-1, -1};

int day24getEntryAt(int x, int y, char& v) {
  int qty=0;

  if (x < 0 || x >= EmapWidth || y < 0 || y >= EmapHeight)
    return -1;

  for (auto it: blizzards) {
    if (get<0>(it)==x && get<1>(it)==y) {
      qty++;
      v = get<2>(it);
    }
  }

  if (qty>1)
    v = '0' + qty;
  return qty;
}

void day24makeMap() {
  vector<char> row;
  expeditionMap.clear();
  
  for (auto y=0; y<EmapHeight; y++) {
    row.clear();
    for (auto x=0; x<EmapWidth; x++) {
      char entry;
      int qty = day24getEntryAt(x,y,entry);

      if (E.first==x && E.second==y)
        row.push_back('E');
      else if (qty > 0)
        row.push_back(entry);
      else
        row.push_back('.');
    }
    expeditionMap.push_back(row);
  }  
}

void day24printmap(const char* msg) {
  printf("[%s] The Expedition Map currently looks like this:\n", msg);
  day24makeMap();

  if (E.first==-1) {
    for (auto c=0; c<entranceCol; c++)
      printf(" ");
    printf("E\n");
  }

  for (auto y=0; y<EmapHeight; y++) {
    for (auto x=0; x<EmapWidth; x++) {
      printf("%c", expeditionMap[y][x]);
    }
    printf("\n");
  }  

  for (auto c=0; c<exitCol; c++)
    printf(" ");
  printf("X\n");

}

void day24moveBlizzards() {
  for (auto& it: blizzards) {
    char direction = get<2>(it);
    int x = get<0>(it);
    int y = get<1>(it);
    switch(direction) {
      case '^':
        y--;
        if (y==-1) y=EmapHeight-1;
        break;
      case 'v':
        y++;
        if (y==EmapHeight) y=0;
        break;
      case '<':
        x--;
        if (x==-1) x=EmapWidth-1;
        break;
      case '>':
        x++;
        if (x==EmapWidth) x=0;
        break;
      default:
        printf("ERROR: Bad blizzard type of:%c\n", direction);
        exit(0);
        break;
    }
    get<0>(it) = x;
    get<1>(it) = y;
  }
}

void day24getMoveCandidates(vector<pair<int,int>>& cand) {
  char c;
  cand.clear();
  if (E.first==-1) {
    // Only 'wait' and down are even possible.
    cand.push_back(make_pair(-1,-1));   // Special response for 'wait'
    if (day24getEntryAt(entranceCol, 0, c)==0)
      cand.push_back(make_pair(entranceCol, 0));
  }
  else if (E.second==EmapHeight-1 && E.first==exitCol) {
    // This is the *END* - one move gets us out.
    cand.push_back(make_pair(-2, -2));
    return;
  }
  else {
    // U/D/L/R or wait
    // Up
    if (day24getEntryAt(E.first, E.second-1, c)==0)
      cand.push_back(make_pair(E.first, E.second-1));
    // Down
    if (day24getEntryAt(E.first, E.second+1, c)==0)
      cand.push_back(make_pair(E.first, E.second+1));
    // Left
    if (day24getEntryAt(E.first-1, E.second, c)==0)
      cand.push_back(make_pair(E.first-1, E.second));
    // Right
    if (day24getEntryAt(E.first+1, E.second, c)==0)
      cand.push_back(make_pair(E.first+1, E.second));
    // Wait
    if (day24getEntryAt(E.first, E.second, c)==0)
      cand.push_back(make_pair(E.first, E.second));
  }
}

void day24() {
  printf("Hello world.\n");

  vector<string> rawInput;
//  ingestLines("input/day24-sample.input", rawInput);
  ingestLines("input/day24-sample2.input", rawInput);
//  ingestLines("input/day24.input", rawInput);

  int width=rawInput[0].length();
  int height=rawInput.size();

  int tally=0;

  int quantity, from, to;

  for (auto i=0; i<rawInput.size(); i++) {
//  for (auto i=0; i<5; i++) {
    for (auto col=0; col<width; col++) {
      if (i==0) {
        // Looking for the entrance.
        if (rawInput[i][col]=='.')
          entranceCol = col-1;
      }
      else if (i==height-1) {
        // Looking for the entrance.
        if (rawInput[i][col]=='.')
          exitCol = col-1;
      }
      else if (rawInput[i][col]!='#' && rawInput[i][col]!='.')
        blizzards.push_back(make_tuple(col-1, i-1, rawInput[i][col]));
    }
  }

  assert(entranceCol != -1);
  assert(exitCol != -1);
  EmapWidth = width-2;
  EmapHeight = height-2;

  printf("Map width:%d, height:%d and # of blizzards at start: %lu\n", EmapWidth, EmapHeight, blizzards.size());

  day24printmap("START");

  vector<pair<int,int>> cand;

  for (auto iter=0; iter<7; iter++) {
    day24moveBlizzards();
    day24getMoveCandidates(cand);
    printf("From E(%d,%d) Received %lu candidate pairs\n", E.first, E.second, cand.size());
    if (cand.size() && cand[0].first==-2) {
      printf("PART 2 ENDING - Total rounds: %d\n", iter+2);
      exit(0);
    }
//    exit(0);
    day24printmap("IN_PROC");
//    SleepMS(1000);
  }

  printf("Final Part 1 Tally: %d\n", tally);
}

#define MAXDIGITS 22

map<char, int> snToReg { {'2',2}, {'1',1}, {'0', 0}, {'-',-1}, {'=',-2}};
map<int, char> regToSN { {2, '2'}, {1, '1'}, {0, '0'}, {-1, '-'}, {-2, '='}};

int64_t placeValue(int place) {
  int64_t v = pow(5, place);
  return v;
}

int64_t maxValue(int place, int digit=2) {
  return placeValue(place) * digit;  // We don't have higher digits than 2.
}

// This is kinda fuzzy at the moment
// The max value at place 5 is 2*3125=6250
// But if place 5 is '2' and place 4 is NEGATIVE ... -2, does this inform us?
// Or really a minimum might be '1' in place 5 and -2 in place 4
int64_t minValue(int place, int digit=-2) {
  return placeValue(place) * digit;  // We don't have higher digits than 2.
}

void bumpUpAndCascade(string& curOut, int place) {
  bool dbg=true;

  for (int ch=curOut.length()-1-place; ch<MAXDIGITS; ch--) {
    if (dbg) printf("BUMPing place:%d for input:%s\n", ch, curOut.c_str());
    if (curOut[ch] == '=')
      curOut[ch] = '-';
    else if (curOut[ch] == '-')
      curOut[ch] = '0';
    else if (curOut[ch] == '0' || curOut[ch] == '1')
      curOut[ch]++;
    else {
      // place is already '2' and cannot become '3' so it becomes -2
      // and forces the next entry to bump up.
      assert(curOut[ch] == '2');
      curOut[ch] = '=';
      if (dbg) printf("  BUMPing cascading...\n");
      continue; // Go again. Bump up the next one due to this one going negative.
    }

    break; // All done
  }

  if (dbg) printf("  BUMPing complete. Result: %s\n", curOut.c_str());
}

int64_t toDec(string& in) {
  int place=0;
  int64_t pvals[MAXDIGITS];
  int64_t sum=0;
  bool dbg=false;

  for (auto x=0;x<MAXDIGITS;x++) pvals[x]=0;

  for (int i=in.length()-1; i>=0; i--) {
    // Process this place.
    if (dbg) printf("toDec: i=%d, place=%d, in[i]=%c, sntoReg=%d\n", i, place, in[i], snToReg[in[i]]);
    pvals[place] = placeValue(place) * snToReg[in[i]];
    place++;
  }

//exit(0);
  for (auto x=0; x<MAXDIGITS; x++) sum += pvals[x];

  if (dbg) {
    printf("Digit translations:\n");
    for (auto x=0; x<in.length(); x++) {
      char c = in[in.length()-1-x];
      printf("%c @ place:%d becomes %d*%lld = %lld\n", c, x, snToReg[c], placeValue(x), pvals[x]);
    }
  }

  return sum;
}

string toSNAFU(int64_t indec) {
  int place;
  int64_t curval = indec;
  string out="";
  bool dbg=true;

  for (auto i=0; i<MAXDIGITS; i++)
    out += "0";

  for (place=MAXDIGITS-1; place>0; place--) {
    int digit;
    int index=out.length()-1-place;
    if (dbg) printf("Looking at place: %d, curval=%lld, placeValue=%lld\n", place, curval, placeValue(place));
    if (curval >= placeValue(place)) {
      // Time to do something in this place.
      digit = curval / placeValue(place);
      if (digit == 3) {
        out[index] = '='; // Converting to -2
        bumpUpAndCascade(out, place+1);
      }
      else if (digit == 4) {
        out[index] = '-'; // Converting to -1
        bumpUpAndCascade(out, place+1);
      }
      else {
        out[index] = char('0'+digit);
      }

      curval = curval - digit * placeValue(place);
      if (dbg) printf("  curval=%lld current output:%s\n", curval, out.c_str());
//if (place==2) exit(0);
    }
  }

  // Trim off the leading zeros.
  auto loc = out.find_first_not_of('0');
  if (loc != std::string::npos)
    out.substr(loc);
  
  if (dbg) printf("  FINAL out string is:%s\n", out.c_str());
  return out;
}

void day25() {
  printf("Hello world.\n");

  vector<string> rawInput;
//  ingestLines("input/day25-sample.input", rawInput);
  ingestLines("input/day25.input", rawInput);


  int width=rawInput[0].length();
  int height=rawInput.size();

  int64_t tally=0;
  string trySnafu;

  printf("base-5 place values:\n");
  for (auto i=0;i<MAXDIGITS;i++)
    printf("%d : %lld\n", i, placeValue(i));

assert(width <= MAXDIGITS);

  // for (char c='2'; c>= '0'; c--)
  //   printf("Translate: %c = %d\n", c, snToReg[c]);
  // printf("Translate: %c = %d\n", '-', snToReg['-']);
  // printf("Translate: %c = %d\n", '=', snToReg['=']);

  for (auto i=0; i<rawInput.size(); i++) {
//  for (auto i=0; i<1; i++) {
    int64_t dec = toDec(rawInput[i]);
    printf("Converting: %s becomes %lld\n", rawInput[i].c_str(), dec);
    tally += dec;
  }

  printf("Final Part 1 SNAFU to decimal Tally: %lld\n", tally);

  // Part 1 re-conversion answer is 2-20=01--0=0=0=2-120
  string snafu = toSNAFU(tally);

}

using grid_t = vector<string>;
grid_t grid;
string instructions;
static int direction=0;  // 0=Right, 1=Down, 2=Left, 3=Right
pair<int, int> location;
int gridWidth;
int gridHeight;

void setInitLocation() {
  location.second = 0;  // Y = 0;
  location.first=grid[0].find_first_not_of(' ');
}

pair<int,int> mods[4] = {{1,0}, {0, 1}, {-1, 0}, {0, -1}};
char dirs[4] = {'>', 'v', '<', '^'};

void MoveIt(int dist) {
  bool dbg=false;
  int x, y;
  if (dbg) printf("MoveIt: From location (%d, %d) go %c by %d spots.\n", location.first, location.second, dirs[direction], dist);
  for (auto i=0; i<dist; i++) {
    x = location.first  + mods[direction].first;
    y = location.second + mods[direction].second;

    // Clear x,y as in bounds and wrapping.
    switch (direction) {
      case 0: // Right
        if (x >= gridWidth || grid[y][x] == ' ') {
          // Need to wrap and cope with leading spaces to get back on the map.
          x = grid[y].find_first_not_of(' ');
        }
        break;
      case 1: // Down
        if (y >= gridHeight || grid[y][x]==' ') {
          // Need to wrap ROWS which can't be done without iterating through each row looking for non-space entries
          for (y = 0; y<location.second; y++)
            if (grid[y][x] != ' ')
              break;
        }
        break;
      case 2: // Left
        if (x==-1 || grid[y][x]==' ')
          x = grid[y].find_last_not_of(' ');
        if (dbg) printf("  WRAP_LEFT: New X position will be:%d with '%c' in that location.\n", x, grid[y][x]);
        break;
      case 3: // Up
        if (y==-1 || grid[y][x]==' ') {
          // Need to wrap 
          for (y = gridHeight-1; y>location.second; y--)
            if (grid[y][x] != ' ')
              break;
        }
        break;
    }

    // Decide if we advance to this new x,y based on what is in that location
    if (grid[y][x] != '#') {
      grid[y][x] = dirs[direction]; // Put a <>^v in the spot
      location.first = x;
      location.second = y;
      if (dbg) printf("  MoveIt: @ dist=%d we did move to a new location (%d, %d).\n", i, x, y);
    }
    else
      if (dbg) printf("  MoveIt: @ dist=%d, didn't move since new location (%d, %d) would be '%c'\n", i, x, y, grid[y][x]);
  }
}

void day22() {
  printf("Hello world.\n");

  vector<string> rawInput;
//  ingestLines("input/day22-sample.input", rawInput);
  ingestLines("input/day22.input", rawInput);

  int width=rawInput[0].length();
  int height=rawInput.size();

  int tally=0;

  for (auto i=0; i<rawInput.size(); i++) {
//  for (auto i=0; i<1; i++) {
    if (rawInput[i].length()==0)
      break;
    grid.push_back(rawInput[i]);
    if (rawInput[i].length() > width)
      width = rawInput[i].length();
  }

  // Pad every grid line out to width.
  for (auto row=0; row<grid.size(); row++)
    while(grid[row].length() < width)
      grid[row] += " ";

  gridWidth = width;
  gridHeight = height - 2;
  printf("Grid ingested. Width=%d, Height=%d\n", gridWidth, gridHeight);

  instructions = rawInput[height-1];
  assert(instructions.length() != 0);
  printf("Instructions are: %s\n", instructions.c_str());

  setInitLocation();
  printf("Initial location is: (%d, %d)\n", location.first, location.second);

  int pos=0;
  while (pos < instructions.length()) {
    int dist;
    sscanf(instructions.c_str()+pos, "%d", &dist);
    while (instructions[pos]>='0' && instructions[pos]<='9') {
      pos++;
    }

    char relDir=instructions[pos++];
    printf("Dir=%d: Go %d spaces and then turn '%c'\n", direction, dist, relDir);

    MoveIt(dist);

    if (pos==instructions.length())
      break;

    if (relDir=='R') {
      direction = (direction + 1) % 4;
    }
    else if (relDir=='L') {
      if (direction==0)
        direction=3;
      else
        direction--;
    }
    else
      printf("ERROR: BAD direction of: %c\n", relDir);
//if (pos > 12) exit(0);
  }

  // NOTE: Final location is (location.first+1, location.second+1)
  printf("Final location is at (%d, %d)\n", location.first, location.second);
  tally = 1000 * (location.second+1) + 4 * (location.first+1) + direction;

  // Part 1 answer: 56372
  printf("Final Part 1 Tally: %d\n", tally);

}

string gasses;
vector<string> chamber;
const int MAXROCKS=5;
typedef struct aRock { 
  vector<string> rockData; 
  int width; 
  int height;
} aRock_t;

aRock_t rocks[MAXROCKS] = {{{"@@@@"}, 4, 1}, {{".@.","@@@",".@."}, 3, 3}, {{"..@","..@","@@@"}, 3, 3},
                        {{"@", "@", "@", "@"}, 1, 4}, {{"@@", "@@"}, 2, 2}};
static int currentRock=0;
static int currentGasEntry=0;
int rockX, rockY;

void day17printChamber(const char* msg, int nrx, int nry, int round, bool bPrintRock=true) {
  bool dbg=false;
  printf("%s: Chamber View @ Round:%d\n", msg, round);
  if (dbg) printf(" RockX=%d, RockY=%d, thisRockWidth=%d, thisRockHeight=%d\n", nrx, nry, rocks[currentRock].width, rocks[currentRock].height);
  for (auto i=0; i<chamber.size(); i++) {
    if (dbg) printf(" For i=%d, init value is:%s\n", i, chamber[i].c_str());
    if (bPrintRock && i>=nry && i<nry+rocks[currentRock].height) {
      if (dbg) printf(" ROCK[%d] in the zone is: %s\n", i-nrx, rocks[currentRock].rockData[i-nry].c_str());
      // We're in the zone for where the new rock needs drawn in.
      // Need to take into account BOTH the rock and what's already in the chamber.
      string line=chamber[i]; // Start with what's in the chamber.
      for (auto col=0;col<rocks[currentRock].width;col++) {
        // lay in each non-DOT into the 'line'
        assert(i-nry >= 0);
        if (rocks[currentRock].rockData[i-nry][col] != '.')
          line[nrx+col] = rocks[currentRock].rockData[i-nry][col];
      }

      printf("|%s|\n", line.c_str());
    }
    else
      printf("|%s|\n", chamber[i].c_str());
  }

  printf("+-------+\n");
}

bool day17wouldCollide(int rx, int ry) {
  bool dbg=false;
  // Checking to see if this proposed location would hit existing '#' or walls.
  // first let's check the easy stuff - left/right OOB or bottom of chamber
  if (!chamber.size() || ry+rocks[currentRock].height>chamber.size())
    return true;

  if (rx<0 || rx+rocks[currentRock].width>chamber[ry].length())
    return true;
  
  // Now let's step through thr rock data rows
  for (auto rrow=0; rrow<rocks[currentRock].height; rrow++) {
    if (dbg) printf("Collision-check: rx:%d, ry:%d, rockrow:%d(%s), chamberrow:%d(%s)\n", rx, ry, rrow, rocks[currentRock].rockData[rrow].c_str(), ry+rrow, chamber[ry+rrow].c_str());
    for (auto i=0; i<rocks[currentRock].width; i++) {
      if (rocks[currentRock].rockData[rrow][i] != '.') {
        // The rock is at this location. What's underneath it in the proposed location?
        if (chamber[ry+rrow][rx+i] != '.')
          return true;
      }
    }
  }
  return false;
}

void day17gasShift(const char dir) {
  int nx;
  assert(dir=='<' || dir=='>');
  if (dir=='<')
    nx = rockX-1;
  else
    nx = rockX+1;

//  printf("GAS blast pushes:%s\n", dir=='>' ? "RIGHT" : "LEFT");
  if (day17wouldCollide(nx, rockY))
    return;
  
  // No collision - make the move.
  rockX = nx;
}

void day17mergeRock() {
  bool dbg=true;
  // Checking to see if this proposed location would hit existing '#' or walls.
  // first let's check the easy stuff - left/right OOB or bottom of chamber
  assert (chamber.size() && rockY+rocks[currentRock].height<=chamber.size());
  assert (rockX>=0 && rockX+rocks[currentRock].width<=chamber[rockY].length());
  
  // Now let's step through thr rock data rows
  for (auto rrow=0; rrow<rocks[currentRock].height; rrow++) {
//    if (dbg) printf("Collision-check: rx:%d, ry:%d, rockrow:%d(%s), chamberrow:%d(%s)\n", rx, ry, rrow, rocks[currentRock].rockData[rrow].c_str(), ry+rrow, chamber[ry+rrow].c_str());
    for (auto i=0; i<rocks[currentRock].width; i++) {
      if (rocks[currentRock].rockData[rrow][i] != '.') {
        // The rock is at this location. Lay it down as '#'
        chamber[rockY+rrow][rockX+i] = '#';
      }
    }
  }
}

static bool forceExit=false;
void day17prepChamber() {
  int required=3 + rocks[currentRock].height;
  int additional=-1;

  if (chamber.size() == 0)
    additional = required;

  for (auto i=0; i<chamber.size(); i++) {
    if (chamber[i].find('#') != std::string::npos) {
      additional = required-i;
      break;
    }
  }

  if (additional < 0) {
    // We have more than we need already.
    rockY = abs(additional);
    return;
  }
  else
    rockY=0;


//  printf("PREP_CHAMBER: Required:%d, Additional Needed:%d\n", required, additional);
  while (additional--)
    chamber.insert(chamber.begin(), ".......");
}

void day17() {
  printf("Hello world.\n");

  vector<string> rawInput;
//  ingestLines("input/day17-sample.input", rawInput);
  ingestLines("input/day17.input", rawInput);

  int width=rawInput[0].length();
  int height=rawInput.size();

  int tally=0;

  gasses = rawInput[0];

  // for (int i=0; i<MAXROCKS; i++) {
  //   printf("Rock %d - width:%d, height:%d\n", i, rocks[i].width, rocks[i].height);
  //   for (int row=0; row<rocks[i].rockData.size(); row++) {
  //     vector<string> myRock=rocks[i].rockData;
  //     printf("%s\n", myRock[row].c_str());
  //   }
  // }

//  day17printChamber("PRE-START", rockX, rockY, -1);

  uint64_t rounds=1;
  while (1) {
//    printf("BEGINNING new rock:%d at round:%d\n", currentRock, rounds);
    day17prepChamber();
    rockX=2;
// Do *NOT* set rockY here. Let the prep routine do it.    rockY=0;

//    day17printChamber("Pre-Gas", rockX, rockY, rounds);

    day17gasShift(gasses[currentGasEntry++]);
//    day17printChamber("Post-Gas, Pre-Drop", rockX, rockY, rounds);

    while (!day17wouldCollide(rockX, rockY+1)) {
      rockY++;
//      printf("  Pre-GAS during drop, direction=%c, rockX:%d, rockY:%d\n", gasses[currentGasEntry], rockX, rockY);
      day17gasShift(gasses[currentGasEntry++]);
      if (currentGasEntry==gasses.length())
        currentGasEntry = 0;
//      printf("  Post-GAS during drop, rockX:%d, rockY:%d\n", rockX, rockY);
//      day17printChamber("Post-Gas, During-Drop", rockX, rockY, rounds);
    }

    day17mergeRock();

//    day17printChamber("Post-Drop - end of round", rockX, rockY, rounds, false);

//if (rounds==10) exit(0);
//    if (rounds==2022)
    if (rounds==50455*2)
      break;
    rounds++;
    if (rounds % 10000 == 0) {
      printf("Progress: %llu complete.\n", rounds);
    }
    
    currentRock = (currentRock + 1) % MAXROCKS;
  }

  for (auto i=0; i<chamber.size(); i++) {
    // Find the first entry that has a '#' in it.
    if (chamber[i].find('#') != string::npos) {
      // Answer for part 1: 3048
      printf("PART 1 - height of rocks after %llu rounds is: %lu\n", rounds, chamber.size()-i);
      break;
    }
  }
  printf("Final Part 1 Tally: %d\n", tally);

}

int main(int argc, char** argv) {
  printf("Hello world.\n");

  day17();
//  day24();
  // day20();
//  day18();
//  day13();
}

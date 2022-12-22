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

void dayXX() {
  printf("Hello world.\n");

  vector<string> rawInput;
//  ingestLines("input/day12-sample.input", rawInput);
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

int main(int argc, char** argv) {
  printf("Hello world.\n");

  // day20();
//  day18();
//  day13();
}


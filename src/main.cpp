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

int makeLossFrom(unsigned char them) {
  if (them=='A') return 3;  // scissors
  if (them=='B') return 1;  // rock
  if (them=='C') return 2;  // paper

  return 0;
}

int makeDrawFrom(unsigned char them) {
  if (them=='A') return 1;
  if (them=='B') return 2;
  if (them=='C') return 3;

  return 0;
}

int makeWinFrom(unsigned char them) {
  if (them=='A') return 2;  // paper
  if (them=='B') return 3;  // scissors
  if (them=='C') return 1;  // rock

  return 0;
}

void mapExample() {
  // Create a map of three (string, int) pairs
    map<string, int> m{{"CPU", 10}, {"GPU", 15}, {"RAM", 20}};

  m["XYZ"] = 42;

  auto avail = m.find("junk");
  if (avail != m.end())
    printf("Found the item junk\n");

  avail = m.find("XYZ");
  if (avail != m.end())
    printf("Found the item XYZ\n");

  for (const auto& n : m)
     printf("%s = %d\n", n.first.c_str(), n.second);
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

void testInitStack() {
  stack<string> mystack;
  vector<string> mystr = {"hi", "there", "world."};
  initStackWithStrings(mystack, mystr);
  while(!mystack.empty()) {
    printf("Stack: %s\n", mystack.top().c_str());
    mystack.pop();
  }

  vector<char> chr = {'A', 'B', 'C', 'D'};
  stack<char> stchr;
  initStackWithChar(stchr, chr);
  while(!stchr.empty()) {
    printf("Char-Stack: %c\n", stchr.top());
    stchr.pop();
  }

  string str = "ABCDEFG";
  stack<char> stchr2;
  initCharStackWithString(stchr2, str);
  while(!stchr2.empty()) {
    printf("Char-Stack-from-string: %c\n", stchr2.top());
    stchr2.pop();
  }
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

    tempScore += calcScore(they, me);
#else
// X is need to LOSE
// Y is need to DRAW
// Z is need to WIN
    switch(me) {
      case 'X':
        tempScore = loss;
        tempScore += makeLossFrom(they);
        break;
      case 'Y':
        tempScore = draw;
        tempScore += makeDrawFrom(they);
        break;
      case 'Z':
        tempScore = win;
        tempScore += makeWinFrom(they);
        break;
      default:
        printf("'me' played is invalid at index: %d, value:%c\n", i, me);
        break;
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

void day3() {
  vector<string> raw;
  vector<string> c1;
  vector<string> c2;

  ingestLines("day3.input", raw);

  for (auto i=0; i<raw.size(); i++) {
    assert(raw[i].length() % 2 == 0);
    c1.push_back(raw[i].substr(0,raw[i].length()/2));
    c2.push_back(raw[i].substr(raw[i].length()/2));
  }

  int sum=0;
#if 0
  for (auto i=0; i<raw.size(); i++) {
//  for (auto i=0; i<2; i++) {
    // iterate through c1 entirely.
    // If we get zero or more than one match with c2, let's flag it.
    int matches=0;
    unsigned char matchValue;
    for (auto x=0; x<c1[i].length(); x++) {
//      auto it = find(c2[i].begin(), c2[i].end());
      printf("raw: %s\n", raw[i].c_str());
      printf("c1: %s\n", c1[i].c_str());
      printf("c2: %s\n", c2[i].c_str());
      if (std::find(c2[i].begin(), c2[i].end(), c1[i][x]) != c2[i].end()) {
        matches++;
        matchValue = c1[i][x];
        printf("Match: at column: %d, value: %c, sum before: %d\n", x, c1[i][x], sum);
        if (matchValue>='a' && matchValue<='z')
          sum += 1+ matchValue - 'a';
        else
          sum += 27 + matchValue - 'A';
        printf("Sum after: %d\n", sum);
        break;  // Skip the rest.
      }
    }
    if (matches==0) 
      printf("At iteration: %d, we had no matches.\n", i);
    else if (matches > 1)
      printf("At iteration: %d we had more than one match - we had %d matches\n", i, matches);
  }
#else
  assert(raw.size() % 3 == 0);
  sum=0;
  for (auto i=0; i<raw.size(); i+=3) {
//  for (auto i=0; i<2; i++) {
    // iterate through c1 entirely.
    // If we get zero or more than one match with c2, let's flag it.
    int matches=0;
    unsigned char matchValue;
    for (auto x=0; x<raw[i].length(); x++) {
      if (find(raw[i+1].begin(), raw[i+1].end(), raw[i][x])!=raw[i+1].end()) {
        // Found a match from '0' to '1' ... is there also a match to '2'
        if (find(raw[i+2].begin(), raw[i+2].end(), raw[i][x]) != raw[i+2].end()) {
          matchValue = raw[i][x];
          printf("Match: at column: %d, value: %c, sum before: %d\n", x, c1[i][x], sum);
          if (matchValue>='a' && matchValue<='z')
            sum += 1+ matchValue - 'a';
          else
            sum += 27 + matchValue - 'A';
          printf("Sum after: %d\n", sum);
          break;  // skip out.
        }
      }

    }
    if (matches==0) 
      printf("At iteration: %d, we had no matches.\n", i);
    else if (matches > 1)
      printf("At iteration: %d we had more than one match - we had %d matches\n", i, matches);
  }
#endif

  printf("sum is: %d\n", sum);

}

void day4() {

  vector<string> rawInput;
  ingestLines("day4.input", rawInput);

  vector<int> L1;
  vector<int> H1;
  vector<int> L2;
  vector<int> H2;

  int lT1, hT1, lT2, hT2;

  int tally=0;

#if 0
  // Part 1 was *433*
  for (auto i=0; i<rawInput.size(); i++) {
    sscanf(rawInput[i].c_str(), "%d-%d,%d-%d", &lT1, &hT1, &lT2, &hT2);
//    printf("Got %d-%d , %d-%d\n", lT1, hT1, lT2, hT2);
    if (lT1<=lT2 && hT1>=hT2)
      tally++;
    else if (lT2<=lT1 && hT2>=hT1)
      tally++;
  }
#else
// Part 2 was *852*
  for (auto i=0; i<rawInput.size(); i++) {
    sscanf(rawInput[i].c_str(), "%d-%d,%d-%d", &lT1, &hT1, &lT2, &hT2);
//    printf("Got %d-%d , %d-%d\n", lT1, hT1, lT2, hT2);
    if ( (lT1>=lT2 && lT1<=hT2) || (lT2>=lT1 && lT2<=hT1) )
      tally++;
    else if ( (hT1>=lT2 && hT1<=lT2) || (hT2>=lT1 && hT2<=hT1) )
      tally++;
  }
#endif

  printf("Result: %d\n", tally);
}

void day5() {
  vector<string> rawInput;
  ingestLines("day5.input", rawInput);

  int tally=0;

  vector<int> allInts;

/*
[C]         [S] [H]                
[F] [B]     [C] [S]     [W]        
[B] [W]     [W] [M] [S] [B]        
[L] [H] [G] [L] [P] [F] [Q]        
[D] [P] [J] [F] [T] [G] [M] [T]    
[P] [G] [B] [N] [L] [W] [P] [W] [R]
[Z] [V] [W] [J] [J] [C] [T] [S] [C]
[S] [N] [F] [G] [W] [B] [H] [F] [N]
 1   2   3   4   5   6   7   8   9 
*/

// Only 9 stacks but they are labeled 1-9 so not using '0'
  std::stack<char> crates[10];

// Setup the crate stacks manually rather than parsing
  crates[9].push('N');
  crates[9].push('C');
  crates[9].push('R');

  crates[8].push('F');
  crates[8].push('S');
  crates[8].push('W');
  crates[8].push('T');

  crates[7].push('H');
  crates[7].push('T');
  crates[7].push('P');
  crates[7].push('M');
  crates[7].push('Q');
  crates[7].push('B');
  crates[7].push('W');

  crates[6].push('B');
  crates[6].push('C');
  crates[6].push('W');
  crates[6].push('G');
  crates[6].push('F');
  crates[6].push('S');

  crates[5].push('W');
  crates[5].push('J');
  crates[5].push('L');
  crates[5].push('T');
  crates[5].push('P');
  crates[5].push('M');
  crates[5].push('S');
  crates[5].push('H');

  crates[4].push('G');
  crates[4].push('J');
  crates[4].push('N');
  crates[4].push('F');
  crates[4].push('L');
  crates[4].push('W');
  crates[4].push('C');
  crates[4].push('S');

  crates[3].push('F');
  crates[3].push('W');
  crates[3].push('B');
  crates[3].push('J');
  crates[3].push('G');

  crates[1].push('S');
  crates[1].push('Z');
  crates[1].push('P');
  crates[1].push('C');
  crates[1].push('L');
  crates[1].push('B');
  crates[1].push('F');
  crates[1].push('C');

  crates[2].push('N');
  crates[2].push('V');
  crates[2].push('G');
  crates[2].push('P');
  crates[2].push('H');
  crates[2].push('W');
  crates[2].push('B');

  int quantity, from, to;
// move 2 from 5 to 9
// PART 1 answer: FWSHSPJWM
  std::stack<char> crane;

  for (auto i=0; i<rawInput.size(); i++) {
//  for (auto i=0; i<5; i++) {
    sscanf(rawInput[i].c_str(), "move %d from %d to %d", &quantity, &from, &to);
//    printf("move %d from %d to %d\n", quantity, from, to);

    assert(crates[from].size()>=quantity);
    // New crane feature - acts like its own stack
    for (auto j=0;j<quantity; j++) {
      crane.push(crates[from].top());
      crates[from].pop();

        // crates[to].push(crates[from].top());
        // crates[from].pop();
    }

    // After they are in the crane hands...
    while(!crane.empty()) {
      crates[to].push(crane.top());
      crane.pop();
    }
  }

    printf("TOP of each stack: ");
    for (auto i=1; i<=9; i++) {
      printf("%c", crates[i].top());
    }
    printf("\n");
}

void day6() {
  vector<string> rawInput;
  ingestLines("day6.input", rawInput);

  int tally=0;

  vector<int> allInts;

  int quantity, from, to;

// four chars all different
  vector<char> q;

//const int startSize=4;
const int startSize=14;
  for (auto i=0; i<startSize; i++)
    q.push_back(rawInput[0][i]);

// Part 1 - answer: 1531
// Part 2 - answer: 2518

  bool foundDuplicate=false;  
//  for (auto i=0; i<rawInput.size(); i++) {
  for (auto i=startSize; i<rawInput[0].length(); i++) {
    foundDuplicate=false;
    printf("queue: %c %c %c %c\n", q[0], q[1], q[2], q[3]);

    if (!uniqueVector(q))
      foundDuplicate=true;

    // for (auto first=0; first<13; first++) {
    //   for (auto second=first+1; second<14; second++) {
    //     if (q[first]==q[second]) {
    //       foundDuplicate=true;
    //       break;
    //     }
    //   }
    // }

    if (!foundDuplicate) {
        printf("Found start code at: %d\n", i);
        exit(1);
    }

    q.erase(q.begin());
    q.push_back(rawInput[0][i]);
  }

  printf("Result: %d\n", tally);
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

void day7() {
  vector<string> rawInput;
  ingestLines("input/day7.input", rawInput);

  int tally=0;

  vector<int> allInts;

  int quantity, from, to;

// dirs <= 100000 bytes
// sum of those dir sizes

  map<string, uint32_t> dirs;
  map<string, uint32_t> trees;   // Tally of the recursive count for this dir

string cmd;
char cmdChar[10];
string arg;
char argChar[30];
string curdir;

uint32_t tmpSize;

  for (auto i=0; i<rawInput.size(); i++) {
//  for (auto i=0; i<40; i++) {
    if (rawInput[i][0] == '$') {
      // Command
      assert(rawInput[i][1] == ' ');
      sscanf(rawInput[i].c_str(), "$ %s %s", cmdChar, argChar);
      cmd = cmdChar;
      arg = argChar;

      if (cmd=="cd") {
        if (arg=="/")
          curdir="/";
        else if (arg=="..") {
          // Need to prune curdir by the tail portion
//          printf("cd .. - BEFORE: %s\n", curdir.c_str());
          trimDir(curdir);
//          printf("cd .. -  AFTER: %s\n", curdir.c_str());
        }
        else if (arg[0]=='.' && arg[1]=='.') {
          // relative cd with extra stuff.
          printf("ODDBALL 'cd' argument of: %s\n", arg.c_str());
          assert(false);
        }
        else if (arg[0] == '/') {
          // absolute path cd
          printf("ODDBALL 'cd' argument of: %s\n", arg.c_str());
          assert(false);
        }
        else {
          // arg is next depth relative
          if (curdir != "/")
            curdir += "/";
          curdir += arg;

          assert(dirs.count(curdir)==0 || dirs[curdir]==0);
          if (dirs.count(curdir)) {
            // We've already been here.
//            printf("DUPLICATE DIRECTORY LS at line [%u]: %s - dir-tally is already:%u\n", i, curdir.c_str(), dirs[curdir]);
            continue;
          }
        }
      }
      else if (cmd=="ls") {
        // Do nothing...what follows is 'dir' or 'size' info until next '$'
//        printf("ls found for dir=%s\n", curdir.c_str());
      }
    }
    else {
      // Not a command - this is a listing
      sscanf(rawInput[i].c_str(), "%s %s", cmdChar, argChar);
      cmd = cmdChar;
      arg = argChar;
      if (cmd=="dir") {
        string nDir;
        // Must add entries for all dirs.
        if (curdir=="/")
          nDir = curdir + arg;
        else
          nDir = curdir + "/" + arg;
        dirs[nDir] = 0;
      }
      else {
        sscanf(cmd.c_str(), "%d", &tmpSize);
        dirs[curdir] += tmpSize;
//        printf("File found size: %u, tally for %s is %u\n", tmpSize, curdir.c_str(), dirs[curdir]);
      }
    }

  }

#if 0
// rip through the list of dirs and ERASE (set to zero) any dirs that are >100000
  for (const auto& n : dirs) {
      if (n.second > 100000)
        dirs[n.first] = 0;
  }
#endif

#if 0
  for (const auto& n : dirs) {
      if (n.second > 100000)
        printf("Skipping dir %s\n", n.first.c_str());
      else {
        printf("Tally of dir %s is %u\n", n.first.c_str(), n.second);
        tally += n.second;
      }
  }
#endif

// Build the recursive tree - walk the list and at each iteration, 
// find any other entries aside from itself that have the same starting-dir-name
// And if they match, add their value to this one.
  for (const auto& n : dirs) {
    trees[n.first] = n.second;
    for (const auto& y: dirs) {
      if (y.first==n.first)
        continue; // skip ourselves
      else {
//        if (y.first.find(n.first,0)!=std::string::npos) {
        if (y.first.find(n.first,0)==0) {
          // now we have a subdirectory of n.first
          trees[n.first] += y.second;
//          printf("Subdir %s of %s adds %u TotTree: %u\n", y.first.c_str(), n.first.c_str(), y.second, trees[n.first]);
        }
      }
    }
  }

  // Tally the results
  tally=0;
  printf("Tally Up trees...\n");
  for (const auto& n : trees) {
    if (n.second<=100000) {
      tally += n.second;
      printf("  Adding %u found in %s\n", n.second, n.first.c_str());
    }
  }

// 2031851 part 1 answer
  printf("Result: %d\n", tally);
  // 132067 in root
  printf("value of / alone is: %u\n", dirs["/"]);
  printf("value of / for whole tree is: %u\n", trees["/"]);


  const uint32_t toDelete=trees["/"] - 40000000;
  string candidate;
  uint32_t bytesWillFree=0;

  for (const auto& n : trees) {
    if (n.second > toDelete) {
      // candidate?
      if (bytesWillFree==0 || n.second < bytesWillFree) {
        // Better candidate
        candidate = n.first;
        bytesWillFree = n.second;
      }
    }
  }
  printf("Free target: %u ... dir that will free %u bytes is %s\n", toDelete, bytesWillFree, candidate.c_str());
// Listing for comparisons
#if 0
  vector<string> theDirs;
  for (const auto& n : dirs) {
    theDirs.push_back(n.first);
  }
  printf("DIRS sorted with file-sums\n");
  std::sort(theDirs.begin(), theDirs.end());
  for (const auto& n : theDirs) {
    printf("%s %u\n", n.c_str(), dirs[n]);
  }
#endif
// Listing for comparisons
#if 0
  vector<string> theDirs;
  for (const auto& n : trees) {
    theDirs.push_back(n.first);
  }
  printf("TREES (recursively summed tallies) sorted with file-sums\n");
  std::sort(theDirs.begin(), theDirs.end());
  for (const auto& n : theDirs) {
    printf("%s %u\n", n.c_str(), trees[n]);
  }
#endif
}

bool isVisible(int x, int y, vector<string> grid) {
  // target of interest is x,y
  // Attack 4 tiems for each direction
  unsigned char targHeight=grid[y][x];
  int width=grid[0].length();
  int height=grid.size();
  bool isVisible=true;
  bool dbg=false;

  printf("isVisible: Target tree at y=%d,x=%d is %c\n", y, x, targHeight);
  // From the left
  for (auto col=0;col<x;col++) {
    if (dbg)
    printf("LEFT: targ:%c value:%c at y=%d,x=%d\n",targHeight,grid[y][col],y,col);
    if (grid[y][col] >= targHeight) {
//      printf("LEFT: Not visible due to %c at y=%d,x=%d\n", grid[y][col], y,col);
      isVisible=false;
      break;  // move on
    }
  }
  if (isVisible)
    return true;
  else
    isVisible=true;

  // To the right starting at the target going right
  for (auto col=x+1;col<width;col++) {
    if (dbg)
    printf("RIGHT: targ:%c value:%c at y=%d,x=%d\n",targHeight,grid[y][col],y,col);
    if (grid[y][col] >= targHeight) {
      isVisible=false;
      break;
    }
  }
  if (isVisible)
    return true;
  else
    isVisible=true;

  // From above down to the target
  for (auto row=0;row<y;row++) {
    if (dbg)
    printf("TOP: targ:%c value:%c at y=%d,x=%d\n",targHeight,grid[row][x],row,x);
    if (grid[row][x] >= targHeight) {
      isVisible=false;
      break;
    }
  }
  if (isVisible)
    return true;
  else
    isVisible=true;

  // From target row+1 down to bottom
  for (auto row=y+1;row<height;row++) {
    if (dbg)
    printf("BOTTOM: targ:%c value:%c at y=%d,x=%d\n",targHeight,grid[row][x],row,x);
    if (grid[row][x] >= targHeight) {
      isVisible=false;
      break;
    }
  }

  return isVisible;
}

int viewingScore(int x, int y, vector<string> grid) {
  // target of interest is x,y
  // Attack 4 times for each direction
  unsigned char targHeight=grid[y][x];
  int width=grid[0].length();
  int height=grid.size();
  int leftScore, rightScore, topScore, bottomScore;
  bool dbg=false;

  if (dbg)
    printf("viewingScore: Target tree at y=%d,x=%d is %c\n", y, x, targHeight);
  // From the left
  for (auto col=x-1;col>=0;col--) {
    // if (dbg)
    // printf("LEFT: targ:%c value:%c at y=%d,x=%d\n",targHeight,grid[y][col],y,col);
    if (grid[y][col] >= targHeight || col==0) {
//      printf("LEFT: Not visible due to %c at y=%d,x=%d\n", grid[y][col], y,col);
      leftScore = x-col;
      if (dbg)
        printf("  LEFT: score: %d\n",leftScore);
      break;  // move on
    }
  }

  // To the right starting at the target going right
  for (auto col=x+1;col<width;col++) {
    // if (dbg)
    // printf("RIGHT: targ:%c value:%c at y=%d,x=%d\n",targHeight,grid[y][col],y,col);
    if (grid[y][col] >= targHeight || col==width-1) {
      rightScore = col-x;
      if (dbg)
        printf("  RIGHT: score: %d\n",rightScore);
      break;
    }
  }

  // From above down to the target
  for (auto row=y-1;row>=0;row--) {
    // if (dbg)
    // printf("TOP: targ:%c value:%c at y=%d,x=%d\n",targHeight,grid[row][x],row,x);
    if (grid[row][x] >= targHeight || row==0) {
      topScore = y-row;
      if (dbg)
        printf("  TOP: score: %d\n",topScore);
      break;
    }
  }

  // From target row+1 down to bottom
  for (auto row=y+1;row<height;row++) {
    // if (dbg)
    // printf("BOTTOM: targ:%c value:%c at y=%d,x=%d\n",targHeight,grid[row][x],row,x);
    if (grid[row][x] >= targHeight || row==height-1) {
      bottomScore = row - y;
      if (dbg)
        printf("  BOTTOM: score: %d\n",bottomScore);
      break;
    }
  }

  return leftScore * rightScore * topScore * bottomScore;
}

void day8() {
  vector<string> rawInput;
  ingestLines("input/day8.input", rawInput);

  int width=rawInput[0].length();
  int height=rawInput.size();

  int tally=width*2 + (height-2)*2; // All trees on the border are visible by definition.

  vector<int> allInts;

  int quantity, from, to;

#ifdef PART1
  printf("Grid size is: %d rows and %d columns.\n", height, width);

  for (auto y=1;y<height-1;y++) {
//  for (auto y=1;y<2;y++) {
    printf("Grid line raw is: %s\n",rawInput[y].c_str());
    for (auto x=1;x<width-1;x++) {
//  for (auto x=1;x<10;x++) {
      if (isVisible(x,y,rawInput)) {
        tally++;
      }
    }
  }

//  for (auto i=1; i<rawInput.size(); i++) {
  for (auto i=0; i<5; i++) {

//      sscanf(rawInput[i].c_str(), "$ %s %s", cmdChar, argChar);
  }

// 392 is too low
// 839 is too low
// Part 1 - answer 1719
  printf("Final Part 1 Tally: %d\n", tally);
#endif

  // Part 2
  int bestScore=0;
  int bestX=0;
  int bestY=0;
  for (auto y=1;y<height-1;y++) {
//  for (auto y=1;y<2;y++) {
//    printf("Grid line raw is: %s\n",rawInput[y].c_str());
    for (auto x=1;x<width-1;x++) {
//  for (auto x=1;x<10;x++) {
      tally = viewingScore(x,y,rawInput);
      if (tally>bestScore) {
        bestScore=tally;
        bestX=x;
        bestY=y;
      }
    }
  }

// part 2 answer: 590824
  printf("Final Part 2 best view is from y=%d,x=%d with value of: %d\n", bestY,bestX,bestScore);
}

// Day 9 item global
set<string> tailLocs; // format: X,Y

void setTail(int tX, int tY) {
  string tLocNow;
  char chr[10];

  snprintf(chr, 10, "%d,%d", tX, tY);
  tLocNow = chr;
//  printf("New tail=(%s)\n", tLocNow.c_str());

  tailLocs.insert(tLocNow);
}

void day9printGrid(const char* msg, int* X, int* Y, int leftX, int rightX, int bottomY, int topY) {
  char line[rightX-leftX + 1];
  int width=rightX-leftX + 1;
  int height=topY-bottomY + 1;
  int offsetX;
  int offsetY;

  offsetX = -leftX;
  offsetY = -bottomY;

  if (msg)
    printf("GRID-PRINT: %s\n", msg);

  for (int row=topY; row>=bottomY; row--) {
    for (int q=0; q<width; q++) 
      line[q]='.';
    line[width]=0;

    if (row==0) {
      // We have the origin in here. Put a 's' there if offsetX is positive (it's on screen)
      if (offsetX>=0)
        line[offsetX]='s';
    }

    for (int col=leftX; col<rightX; col++) {
      for (int knot=0; knot<10; knot++) {
        // Now let's place numbers
        if (line[col+offsetX]=='.' || line[col+offsetX]=='s') {
          // We can place a number here if one belongs here.
          if (X[knot]==col && Y[knot]==row) {
            if (knot==0)
              line[col+offsetX] = 'H';
            else
              line[col+offsetX] = '0'+knot;
            break;  // don't allow anyone 'higher' in the chain print here.
          }
        }
      }
    }

    printf("%s\n", line);
  }

}

void day9printLocs(const char* msg, int* X, int* Y, int depth=4) {
  bool dbg=false;
  if (!dbg)
    return;

  printf("XY-Placement (%s):", msg);
  for (auto i=0; i<depth; i++) {
    printf(" [%d]=(%d,%d) :", i, X[i], Y[i]);
  }
  printf("\n");
}

void day9move(char dir, int dist, int* kX, int* kY) {
  bool detaildbg=false;
  printf("DIRECTION/DISTANCE: %c %d\n", dir, dist);
  day9printLocs("BEFORE", kX, kY, 10);
  if (detaildbg) day9printGrid("BEFORE STARTING MOVE", kX, kY, -11, 14, -5, 15);

  for (auto i=0; i<dist; i++) {
    // Do the movement for head first. All else follows
    switch(dir) {
      case 'U':
        kY[0]++;
        break;
      case 'D':
        kY[0]--;
        break;
      case 'R':
        kX[0]++;
        break;
      case 'L':
        kX[0]--;
        break;
      default:
        assert("bad direction."==NULL);
        break;
    }

    for (auto iter=0; iter<9; iter++) {
      if (detaildbg) printf("  Repeat:%d Iter:%d: Before: [%d]=(%d,%d) and [%d]=(%d,%d)\n", i, iter, iter, kX[iter],kY[iter], iter+1, kX[iter+1],kY[iter+1]);

      if (abs(kX[iter]-kX[iter+1]) > 2) {
        printf("kX[%d]=%d and kX[%d]=%d. Shouldn't be more than 2 from each other.\n", iter, kX[iter], iter+1, kX[iter+1]);
        assert("bad kX distance."==NULL);
      }

      if (abs(kY[iter]-kY[iter+1]) > 2) {
        printf("kY[%d]=%d and kY[%d]=%d. Shouldn't be more than 2 from each other.\n", iter, kY[iter], iter+1, kY[iter+1]);
        assert("bad kY distance."==NULL);
      }

      if (abs(kY[iter]-kY[iter+1])>1 || abs(kX[iter]-kX[iter+1])>1) {

        if (dir=='U' || dir=='D') {
          if (abs(kX[iter] - kX[iter+1])==1) {
            // This is the case where the tail needs to get 'in line' with head
            kX[iter+1] = kX[iter];
          }
        }
        else if (dir=='L' || dir=='R') {
          if (abs(kY[iter] - kY[iter+1])==1) {
            // This is the case where the tail needs to get 'in line' with head
            kY[iter+1] = kY[iter];
          }
        }

        if ((abs(kX[iter] - kX[iter+1])==2)) {
            // new movement item. Direction is up, but we got a 2-gap on the x. Gap-up by one.
            if (kX[iter] > kX[iter+1])
              kX[iter+1]++;
            else
              kX[iter+1]--;
            
            // Always gap-up the Y in this case so long as there *IS* a gap.
            if ((abs(kY[iter] - kY[iter+1])!=0)) {
              if (kY[iter] > kY[iter+1])
                kY[iter+1]++;
              else
                kY[iter+1]--;
            }
        }

        if ((abs(kY[iter] - kY[iter+1])==2)) {
            // New movement - Y must need to gap up by one.
            if (kY[iter] > kY[iter+1])
                kY[iter+1]++;
              else
                kY[iter+1]--;

            // Always gap-up the X in this case so long as there *IS* a gap.
            if ((abs(kX[iter] - kX[iter+1])!=0)) {
              if (kX[iter] > kX[iter+1])
                kX[iter+1]++;
              else
                kX[iter+1]--;
            }
        }
      }

      if (iter==8)
        setTail(kX[9], kY[9]);

//      if (detaildbg && dir=='L') day9printGrid("AFTER KNOT Processed", kX, kY, -11, 14, -5, 15);
      if (detaildbg) printf("  Repeat:%d Iter:%d:  After: [%d]=(%d,%d) and [%d]=(%d,%d)\n", i, iter, iter, kX[iter],kY[iter], iter+1, kX[iter+1],kY[iter+1]);
    }

      if (detaildbg) day9printGrid("AFTER ONE FULL ROPE MOVEMENT", kX, kY, -11, 14, -5, 15);
    day9printLocs("INTERIM", kX, kY);
  }
  day9printLocs("AFTER", kX, kY, 10);
}

void day9() {

  vector<string> rawInput;
//  ingestLines("input/day9-sample.input", rawInput);
//  ingestLines("input/day9-sample2.input", rawInput);
  ingestLines("input/day9.input", rawInput);

  int width=rawInput[0].length();
  int height=rawInput.size();

  int tally=0;

  int quantity, from, to;
  char dir;
  int dist;

  int headX, headY;
  int tailX, tailY;

  int knotX[10];
  int knotY[10];

  for (auto i=0; i<10; i++) {
    knotX[i] = 0;
    knotY[i] = 0;
  }

  tailLocs.insert("0,0");

  for (auto i=0; i<rawInput.size(); i++) {
//  for (auto i=0; i<3; i++) {
    sscanf(rawInput[i].c_str(), "%c %d", &dir, &dist);
//    printf("Got: %c %d\n", dir, dist);

    day9move(dir, dist, knotX, knotY);
#if 0
    if (dir=='U') {
      day9moveUp(dist, knotX, knotY);
    }
    else if (dir=='D') {
      day9moveDown(dist, knotX, knotY);
    }
    else if (dir=='R') {
      day9moveRight(dist, knotX, knotY);
    }
    else if (dir=='L') {
      day9moveLeft(dist, knotX, knotY);
    }
    else {
      assert(false);
    }
#endif

  }

  printf("printing list of tail locations:\n");
  for (const auto& elem : tailLocs)
    printf(" (%s) :", elem.c_str());
  printf("\n");

// Part 1 answer: 6357
// Part 2 - 2598 is too low
// Part 2 - 2636 is too high
// Part 2 - 2627 is the answer
  printf("Part 1 - total tail locations: %lu\n", tailLocs.size());
}

int main(int argc, char** argv) {
  printf("Hello world.\n");

  vector<string> rawInput;
//  ingestLines("input/day10-sample.input", rawInput);
//  ingestLines("input/day10-sample2.input", rawInput);
  ingestLines("input/day10.input", rawInput);

  int width=rawInput[0].length();
  int height=rawInput.size();

  int tally=0;

  int quantity, from, to;

  for (auto i=0; i<rawInput.size(); i++) {
//  for (auto i=0; i<3; i++) {
//    sscanf(rawInput[i].c_str(), "%c %d", &dir, &dist);
//    printf("Got: %c %d\n", dir, dist);


  }

//  printf("Final Part 1 Tally: %d\n", tally);

}

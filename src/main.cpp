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

int main(int argc, char** argv) {
  printf("Hello world.\n");
day7();
exit(1);
  vector<string> rawInput;
  ingestLines("input/day8.input", rawInput);

  int tally=0;

  vector<int> allInts;

  int quantity, from, to;

//  for (auto i=0; i<rawInput.size(); i++) {
  for (auto i=0; i<10; i++) {

//      sscanf(rawInput[i].c_str(), "$ %s %s", cmdChar, argChar);
  }

  printf("Final Tally: %d\n", tally);
}


#pragma once

#include <string>
#include <map>

struct Value
{
  Value(std::string id) : id(id), isNum(false) {}
  Value(long long num) : num(num), isNum(true) {}
  std::string id;
  long long num;
  bool isNum;
};
// soon better optimalization
// using normal variable
// MEMORY ADR = VAL:
// 1 = 15
// ...

// A has address [1]

// A = 15 (MEM[1] <- 15)

// using pointer variable
// MEMORY ADR = VAL:
// 1 = 2
// 2 = 15
// ...

// Ptr has address [1]
// A has address [2]

// Ptr = &A (MEM[1] <- 2)
// *Ptr = 15 (MEM[MEM[1]] <- 15) in other words ( MEM[2] <- 15)

#define ACU_ADR 0
#define TMP_ADR 1
#define TMP_ADR_2 2
#define TMP_ADR_3 3
#define TMP_ADR_4 4
#define TMP_ADR_5 5
#define TMP_ADR_6 6
#define TMP_ADR_7 7
#define TMP_ADR_8 8
#define TMP_ADR_9 9 // XD

class VaribleStorage
{
public:
  VaribleStorage();
  bool exists(std::string id);
  long long getAddress(std::string id);
  void initialize(std::string id);
  bool isInitialized(std::string id);
  bool createVariable(std::string id);

#ifdef DEBUG
  void printVariables();
#endif

private:
  std::map<std::string, std::pair<long long, bool>> variables;
};

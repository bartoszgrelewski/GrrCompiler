#pragma once

#include <vector>
#include <cmath>
#include <string>
#include <iostream>
#include <map>
#include <stack>
#include <utility>
#include "data.hpp"

class Code
{
public:
    Code();

    std::string getCode();
    void warning(std::string);

    // atomic method adds to the list of assembler commands, for example HALT
    void atomic(std::string);
    // ex. LOADI GETI
    void atomic(std::string, long long);

    void get(long long);
    void put(long long);
    void load(long long);
    void store(long long);
    void loadi(long long);
    void storei(long long);
    void add(long long);
    void addi(long long);
    void sub(long long);
    void subi(long long);
    void set(long long);
    void half();
    void jump(long long);
    void jpos(long long);
    void jzero(long long);
    void jumpi(long long);
    void jump();
    void jpos();
    void jzero();
    void jumpi();
    void halt();

    void read(std::string id);
    void write(Value *);

    void assign(std::string, Value *);

    void ifElseBlock();
    void elseBlock();
    void ifBlock();
    void beginWhile();
    void whileBlock();
    void repeatBlock();
    void repeatEndBlock();

    void call(std::string, std::vector<std::string>);
    void createProcedure(std::string, std::vector<std::string>);
    void beginMain();
    void procedureEnd(std::string);

    Value *plus(Value *, Value *);
    Value *minus(Value *, Value *);
    Value *times(Value *, Value *);
    Value *div(Value *, Value *);
    Value *mod(Value *, Value *);
    void eq(Value *, Value *);
    void neq(Value *, Value *);
    void le(Value *, Value *);
    void ge(Value *, Value *);
    void leq(Value *, Value *);
    void geq(Value *, Value *);

    void declareVariable(std::string);

private:
    // vector size moze wypisac wielkosc
    // vector size might print size
    std::vector<std::string> assemblyCode; // list of assembler commands
    VaribleStorage variables;
    std::map<std::string, std::pair<int, std::vector<std::string>>> procedures;

    long long div_adr;
    long long mul_adr;
    long long mod_adr;

    /** Stack of branches (jumps) to resolve. Zero vector element is address where condition check
     *  starts remaining ones are assembly program line numbers with empty jump instructions (without number)
     */
    std::stack<std::vector<int>> branchStack;

    std::vector<std::string> initializeErrors;
    bool insideLoop = false;

#ifdef DEBUG
    std::vector<std::pair<int, std::string>> asmComments;
#endif
};

int yyerror(std::string);

#define CURR_PROGC assemblyCode.size()
#define ADR(x) variables.getAddress(x)

#define INIT_CHECK(x, y)                                                      \
    if (!variables.isInitialized(x))                                          \
    {                                                                         \
        if (insideLoop)                                                       \
        {                                                                     \
            std::cout << "WARNING potential use of non initialized variable " \
                      << x << '\n';                                           \
            initializeErrors.push_back(x);                                    \
        }                                                                     \
        else                                                                  \
            yyerror("Use of non initialized variable \"" + x + "\"" + y);     \
    }

#define EXISTS_CHECK(x, y)                                      \
    if (!variables.exists(x))                                   \
    {                                                           \
        yyerror("Use of undefined variable \"" + x + "\"" + y); \
    }

#ifdef DEBUG
#define debug(msg) std::cout << "DEBUG " << msg << std::endl;
#define debug_asm_blk(msg) asmComments.push_back(std::make_pair(CURR_PROGC, msg));
#define debug_asm(msg) asmComments.push_back(std::make_pair(-CURR_PROGC, msg));
#else
#define debug(msg)
#define debug_asm_blk(msg)
#define debug_asm(msg)
#endif

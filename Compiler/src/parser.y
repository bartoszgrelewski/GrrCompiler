%{
  #include <iostream>
  #include <vector>
  #include "code.hpp"

  int yylex();
  int yyerror(std::string);
  void yyset_in(FILE*);

  extern int yylineno;

  Code* _code = new Code();
  std::vector<std::string> temp_variables;
  std::string context = "";
%}

%code requires {
  #include "data.hpp"
}

%union {
  std::string* id;
  long long num;
  Value* val;
}

%start program_all

%token PROCEDURE IS
%token PROGRAM
%token VAR TBEGIN END
%token ASSIGN
%token IF THEN ELSE ENDIF
%token WHILE DO ENDWHILE
%token REPEAT UNTIL
%token READ WRITE
%token ERROR
%token LE GE LEQ GEQ EQ NEQ
%token <id> identifier
%token <num> number

%left PLUS MINUS
%left TIMES DIV MOD
 
%type <val> value
%type <val> expression

%%
program_all:     procedures main                                                          { _code->halt(); }
;

procedures:     procedures PROCEDURE proc_head IS VAR declarations TBEGIN commands END    { _code->procedureEnd(context); context = ""; } 
                | procedures PROCEDURE proc_head IS TBEGIN commands END                   { _code->procedureEnd(context); context = ""; } 
                |
;

main:           PROGRAM                                                           { _code->beginMain(); }
                main_head                                                         { }
;     

main_head:      IS VAR declarations TBEGIN commands END                           { }
                | IS TBEGIN commands END                                          { }
;

commands:       commands command
                | command
;

command:        identifier ASSIGN expression ';'                                  {  _code->assign(context + *$1, $3); }
                | IF condition THEN commands                                      { _code->ifElseBlock(); }
                  ELSE commands ENDIF                                             { _code->elseBlock(); }
                | IF condition THEN commands ENDIF                                { _code->ifBlock(); }
                | WHILE                                                           { _code->beginWhile(); }
                  condition DO commands ENDWHILE                                  { _code->whileBlock(); }
                | REPEAT                                                          { _code->repeatBlock(); }
                  commands UNTIL condition ';'                                    { _code->repeatEndBlock(); }
                | identifier '(' head_declarations ')' ';'                        { 
                                                                                    std::string last_context = context;
                                                                                    context = *$1 + '-';
                                                                                    _code->call(context, temp_variables);
                                                                                    temp_variables.clear();
                                                                                    context = last_context;
                                                                                  }
                | READ identifier ';'                                             { _code->read(context + *$2);}
                | WRITE value ';'                                                 { _code->write($2); }
;


proc_head:       identifier '(' head_declarations ')'                             { context = *$1 + '-'; _code->createProcedure(context, temp_variables); temp_variables.clear();}                                                    
;        
 

declarations:    declarations',' identifier                                       { _code->declareVariable(context + *$3); }
                | identifier                                                      { _code->declareVariable(context + *$1); }
;

head_declarations:   head_declarations ',' identifier                             { temp_variables.push_back(context + *$3); }
                      | identifier                                                { temp_variables.push_back(context + *$1); }
;

expression:     value                                                             { $$ = $1; }
                | value PLUS value                                                { $$ = _code->plus($1, $3); }
                | value MINUS value                                               { $$ = _code->minus($1, $3); }
                | value TIMES value                                               { $$ = _code->times($1, $3); }
                | value DIV value                                                 { $$ = _code->div($1, $3); }
                | value MOD value                                                 { $$ = _code->mod($1, $3); }
;

condition:      value EQ value                                                    { _code->eq($1, $3); }
                | value NEQ value                                                 { _code->neq($1, $3); }
                | value LE value                                                  { _code->le($1, $3); }
                | value GE value                                                  { _code->ge($1, $3); }
                | value LEQ value                                                 { _code->leq($1, $3); }
                | value GEQ value                                                 { _code->geq($1, $3); }
;

value:          number                                                            { $$ = new Value($1); }
                | identifier                                                      { $$ = new Value(context + *$1); }
;

%%

int yyerror(std::string err) {
    std::cout << "error in line " << yylineno << std::endl;
    std::cout << "error message: " << err << std::endl;
    exit(-3);
}

std::string parse(FILE* in){
    yyset_in(in);
    yyparse();
    return _code->getCode();
}
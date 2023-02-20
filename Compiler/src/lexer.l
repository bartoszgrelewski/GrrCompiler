%option noyywrap
%option yylineno
%option nounput

%{
  #include "parser.h"
  #include <string>
%}

%x comment

%%

"PROCEDURE"     { return PROCEDURE; }
"IS"            { return IS; }
"PROGRAM"       { return PROGRAM; }

"VAR"           { return VAR; }
"BEGIN"         { return TBEGIN; }
"END"           { return END; }

":="            { return ASSIGN; }

"IF"            { return IF; }
"THEN"          { return THEN; }
"ELSE"          { return ELSE; }
"ENDIF"         { return ENDIF; }

"WHILE"         { return WHILE; }
"DO"            { return DO; }
"ENDWHILE"      { return ENDWHILE; }

"REPEAT"        { return REPEAT; }
"UNTIL"         { return UNTIL; }

"READ"          { return READ; }
"WRITE"         { return WRITE; }

"+"             { return PLUS; }
"-"             { return MINUS; }
"*"             { return TIMES; }
"/"             { return DIV; }
"%"             { return MOD; }

"="             { return EQ; } 
"!="            { return NEQ; }
"<"             { return LE; } 
">"             { return GE; } 
"<="            { return LEQ; } 
">="            { return GEQ; } 

[_a-z]+         { yylval.id = new std::string(yytext); return identifier; } 
[0-9]+          { yylval.num = stoll(std::string(yytext)); return number; } //{ yylval.num = stoll(std::string(yytext)); return number; }
[\;\(\)\:\,]    { return yytext[0]; } 

"["             BEGIN(comment);
<comment>"]"    BEGIN(INITIAL);
<comment>.|\n   ;

[ \t\n\r]+      ;
.               { return ERROR; }
%%

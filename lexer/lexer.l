%{
#include "token.hpp"
#include <vector>

extern std::vector<Token> tokens;
%}

%%
[0-9]+      { tokens.emplace_back(TokenType::NUMBER, yytext); }
[a-zA-Z]+   { tokens.emplace_back(TokenType::ID, yytext); }
"+"         { tokens.emplace_back(TokenType::PLUS, yytext); }
"-"         { tokens.emplace_back(TokenType::MINUS, yytext); }
"*"         { tokens.emplace_back(TokenType::MUL, yytext); }
"/"         { tokens.emplace_back(TokenType::DIV, yytext); }
"("         { tokens.emplace_back(TokenType::LPAREN, yytext); }
")"         { tokens.emplace_back(TokenType::RPAREN, yytext); }
[ \t\n]+    ;
.           { return 1; }
%%

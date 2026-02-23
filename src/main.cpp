#include "parser.hpp"
#include "token.hpp"
#include <vector>

extern int yylex();
extern std::vector<Token> tokens;

int main() {
    yylex();  // запускаем flex

    tokens.emplace_back(TokenType::END, "$");

    SLRParser parser;
    parser.parse(tokens);

    return 0;
}
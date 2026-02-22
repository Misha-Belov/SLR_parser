#include "parser.hpp"

int main() {
    std::vector<Token> tokens = {
        {TokenType::ID, "x"},
        {TokenType::MUL, "*"},
        {TokenType::ID, "y"},
        {TokenType::END, "$"}
    };

    SLRParser parser;
    parser.parse(tokens);

    return 0;
}

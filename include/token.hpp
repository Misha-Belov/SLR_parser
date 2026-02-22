#pragma once
#include <string>

enum class TokenType {
    ID,
    NUMBER,
    PLUS,
    MINUS,
    MUL,
    DIV,
    LPAREN,
    RPAREN,
    END,     // $
    INVALID
};

struct Token {
    TokenType type;
    std::string lexeme;

    Token(TokenType t, std::string l)
        : type(t), lexeme(std::move(l)) {}
};

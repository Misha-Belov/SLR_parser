#pragma once
#include "token.hpp"
#include "grammar.hpp"
#include "slr_table.hpp"

#include <stack>
#include <vector>
#include <iostream>

class SLRParser {
public:
    explicit SLRParser();

    void parse(const std::vector<Token>& tokens);

private:
    std::vector<Production> productions;
    SLRTable table;

    void printState(const std::stack<std::string>& stack,
                    const std::vector<Token>& input,
                    size_t position,
                    const std::string& action) const;

    std::string tokenToSymbol(const Token& token) const;
};

#include "parser.hpp"

SLRParser::SLRParser() {
    productions = {
        {"E", {"E", "+", "T"}}, // 0
        {"E", {"E", "-", "T"}}, // 1
        {"E", {"T"}},           // 2
        {"T", {"T", "*", "F"}}, // 3
        {"T", {"T", "/", "F"}}, // 4
        {"T", {"F"}},           // 5
        {"F", {"(", "E", ")"}}, // 6
        {"F", {"id"}},          // 7
        {"F", {"number"}}       // 8
    };
}

std::string SLRParser::tokenToSymbol(const Token& token) const {
    switch(token.type) {
        case TokenType::ID: return "id";
        case TokenType::NUMBER: return "number";
        case TokenType::PLUS: return "+";
        case TokenType::MINUS: return "-";
        case TokenType::MUL: return "*";
        case TokenType::DIV: return "/";
        case TokenType::LPAREN: return "(";
        case TokenType::RPAREN: return ")";
        case TokenType::END: return "$";
        default: return "invalid";
    }
}

void SLRParser::parse(const std::vector<Token>& tokens) {
    std::stack<int> stateStack;
    std::stack<std::string> symbolStack;

    stateStack.push(0);

    size_t pos = 0;

    while (true) {
        int currentState = stateStack.top();
        std::string symbol = tokenToSymbol(tokens[pos]);

        Action action = table.getAction(currentState, symbol);

        if (action.type == ActionType::SHIFT) {
            symbolStack.push(symbol);
            stateStack.push(action.value);
            printState(symbolStack, tokens, pos, "Shift");
            pos++;
        }
        else if (action.type == ActionType::REDUCE) {
            const Production& prod = productions[action.value];

            for (size_t i = 0; i < prod.rhs.size(); ++i) {
                symbolStack.pop();
                stateStack.pop();
            }

            symbolStack.push(prod.lhs);

            int gotoState = table.getGoto(stateStack.top(), prod.lhs);
            stateStack.push(gotoState);

            printState(symbolStack, tokens, pos,
                       "Reduce " + prod.lhs + " -> " + prod.rhs[0] + "..."); // упрощённо
        }
        else if (action.type == ActionType::ACCEPT) {
            std::cout << "ACCEPT\n";
            break;
        }
        else {
            std::cerr << "Syntax error at token '" << symbol << "'\n";
            break;
        }
    }
}

void SLRParser::printState(
    const std::stack<std::string>& stack,
    const std::vector<Token>& input,
    size_t position,
    const std::string& action) const
{
    std::cout << "STACK: ";
    // Выводим стек от дна к вершине
    std::vector<std::string> elements;
    std::stack<std::string> temp = stack;
    while (!temp.empty()) {
        elements.push_back(temp.top());
        temp.pop();
    }
    for (auto it = elements.rbegin(); it != elements.rend(); ++it)
        std::cout << *it << " ";

    std::cout << "| INPUT: ";
    for (size_t i = position; i < input.size(); ++i)
        std::cout << input[i].lexeme;
    std::cout << " | ACTION: " << action << "\n";
}
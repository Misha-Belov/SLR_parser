#pragma once
#include <string>
#include <vector>

struct Production {
    std::string lhs;
    std::vector<std::string> rhs;

    Production(const std::string& left,
               const std::vector<std::string>& right)
        : lhs(left), rhs(right) {}
};

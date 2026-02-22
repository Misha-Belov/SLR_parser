#pragma once
#include <map>
#include <utility>
#include <string>

enum class ActionType {
    SHIFT,
    REDUCE,
    ACCEPT,
    ERROR
};

struct Action {
    ActionType type;
    int value;  // state for SHIFT, production index for REDUCE

    Action(ActionType t = ActionType::ERROR, int v = -1)
        : type(t), value(v) {}
};

class SLRTable {
public:
    Action getAction(int state, const std::string& terminal) const;
    int getGoto(int state, const std::string& nonTerminal) const;

private:
    std::map<std::pair<int, std::string>, Action> actionTable;
    std::map<std::pair<int, std::string>, int> gotoTable;

public:
    SLRTable(); // заполнение таблиц
};

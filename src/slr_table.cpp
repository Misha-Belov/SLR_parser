#include "slr_table.hpp"

SLRTable::SLRTable() {
    // Пример заполнения (частично)
    actionTable[{0, "id"}] = Action(ActionType::SHIFT, 5);
    actionTable[{0, "("}]  = Action(ActionType::SHIFT, 4);

    actionTable[{1, "$"}]  = Action(ActionType::ACCEPT, 0);

    // Пример reduce
    actionTable[{2, "+"}] = Action(ActionType::REDUCE, 2);
    actionTable[{2, "$"}] = Action(ActionType::REDUCE, 2);

    // goto
    gotoTable[{0, "E"}] = 1;
    gotoTable[{0, "T"}] = 2;
    gotoTable[{0, "F"}] = 3;
}

Action SLRTable::getAction(int state, const std::string& terminal) const {
    auto it = actionTable.find({state, terminal});
    if (it != actionTable.end())
        return it->second;
    return Action();
}

int SLRTable::getGoto(int state, const std::string& nonTerminal) const {
    auto it = gotoTable.find({state, nonTerminal});
    if (it != gotoTable.end())
        return it->second;
    return -1;
}

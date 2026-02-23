#include "slr_table.hpp"

SLRTable::SLRTable() {
    // State 0
    actionTable[{0, "id"}] = Action(ActionType::SHIFT, 5);
    actionTable[{0, "number"}] = Action(ActionType::SHIFT, 4);
    actionTable[{0, "("}] = Action(ActionType::SHIFT, 7);
    gotoTable[{0, "E"}] = 1;
    gotoTable[{0, "T"}] = 2;
    gotoTable[{0, "F"}] = 3;

    // State 1
    actionTable[{1, "+"}] = Action(ActionType::SHIFT, 8);
    actionTable[{1, "-"}] = Action(ActionType::SHIFT, 9);
    actionTable[{1, "$"}] = Action(ActionType::ACCEPT, 0);

    // State 2 (E -> T ·)
    actionTable[{2, "*"}] = Action(ActionType::SHIFT, 6);
    actionTable[{2, "/"}] = Action(ActionType::SHIFT, 11);
    actionTable[{2, "+"}] = Action(ActionType::REDUCE, 2); // E -> T
    actionTable[{2, "-"}] = Action(ActionType::REDUCE, 2);
    actionTable[{2, ")"}] = Action(ActionType::REDUCE, 2);
    actionTable[{2, "$"}] = Action(ActionType::REDUCE, 2);

    // State 3 (T -> F ·)
    actionTable[{3, "+"}] = Action(ActionType::REDUCE, 5); // T -> F
    actionTable[{3, "-"}] = Action(ActionType::REDUCE, 5);
    actionTable[{3, "*"}] = Action(ActionType::REDUCE, 5);
    actionTable[{3, "/"}] = Action(ActionType::REDUCE, 5);
    actionTable[{3, ")"}] = Action(ActionType::REDUCE, 5);
    actionTable[{3, "$"}] = Action(ActionType::REDUCE, 5);

    // State 4 (F -> number ·)
    actionTable[{4, "+"}] = Action(ActionType::REDUCE, 8); // F -> number
    actionTable[{4, "-"}] = Action(ActionType::REDUCE, 8);
    actionTable[{4, "*"}] = Action(ActionType::REDUCE, 8);
    actionTable[{4, "/"}] = Action(ActionType::REDUCE, 8);
    actionTable[{4, ")"}] = Action(ActionType::REDUCE, 8);
    actionTable[{4, "$"}] = Action(ActionType::REDUCE, 8);

    // State 5 (F -> id ·)
    actionTable[{5, "+"}] = Action(ActionType::REDUCE, 7); // F -> id
    actionTable[{5, "-"}] = Action(ActionType::REDUCE, 7);
    actionTable[{5, "*"}] = Action(ActionType::REDUCE, 7);
    actionTable[{5, "/"}] = Action(ActionType::REDUCE, 7);
    actionTable[{5, ")"}] = Action(ActionType::REDUCE, 7);
    actionTable[{5, "$"}] = Action(ActionType::REDUCE, 7);

    // State 6 (T -> T * · F)
    actionTable[{6, "id"}] = Action(ActionType::SHIFT, 5);
    actionTable[{6, "number"}] = Action(ActionType::SHIFT, 4);
    actionTable[{6, "("}] = Action(ActionType::SHIFT, 7);
    gotoTable[{6, "F"}] = 12;

    // State 7 (F -> ( · E )
    actionTable[{7, "id"}] = Action(ActionType::SHIFT, 5);
    actionTable[{7, "number"}] = Action(ActionType::SHIFT, 4);
    actionTable[{7, "("}] = Action(ActionType::SHIFT, 7);
    gotoTable[{7, "E"}] = 13;
    gotoTable[{7, "T"}] = 2;
    gotoTable[{7, "F"}] = 3;

    // State 8 (E -> E + · T)
    actionTable[{8, "id"}] = Action(ActionType::SHIFT, 5);
    actionTable[{8, "number"}] = Action(ActionType::SHIFT, 4);
    actionTable[{8, "("}] = Action(ActionType::SHIFT, 7);
    gotoTable[{8, "T"}] = 14;
    gotoTable[{8, "F"}] = 3;

    // State 9 (E -> E - · T)
    actionTable[{9, "id"}] = Action(ActionType::SHIFT, 5);
    actionTable[{9, "number"}] = Action(ActionType::SHIFT, 4);
    actionTable[{9, "("}] = Action(ActionType::SHIFT, 7);
    gotoTable[{9, "T"}] = 15;
    gotoTable[{9, "F"}] = 3;

    // State 11 (T -> T / · F)
    actionTable[{11, "id"}] = Action(ActionType::SHIFT, 5);
    actionTable[{11, "number"}] = Action(ActionType::SHIFT, 4);
    actionTable[{11, "("}] = Action(ActionType::SHIFT, 7);
    gotoTable[{11, "F"}] = 16;

    // State 12 (T -> T * F ·)
    actionTable[{12, "+"}] = Action(ActionType::REDUCE, 3); // T -> T * F
    actionTable[{12, "-"}] = Action(ActionType::REDUCE, 3);
    actionTable[{12, "*"}] = Action(ActionType::REDUCE, 3);
    actionTable[{12, "/"}] = Action(ActionType::REDUCE, 3);
    actionTable[{12, ")"}] = Action(ActionType::REDUCE, 3);
    actionTable[{12, "$"}] = Action(ActionType::REDUCE, 3);

    // State 13 (F -> ( E · )
    actionTable[{13, "+"}] = Action(ActionType::SHIFT, 8);
    actionTable[{13, "-"}] = Action(ActionType::SHIFT, 9);
    actionTable[{13, ")"}] = Action(ActionType::SHIFT, 17);

    // State 14 (E -> E + T ·)
    actionTable[{14, "*"}] = Action(ActionType::SHIFT, 6);
    actionTable[{14, "/"}] = Action(ActionType::SHIFT, 11);
    actionTable[{14, "+"}] = Action(ActionType::REDUCE, 0); // E -> E + T
    actionTable[{14, "-"}] = Action(ActionType::REDUCE, 0);
    actionTable[{14, ")"}] = Action(ActionType::REDUCE, 0);
    actionTable[{14, "$"}] = Action(ActionType::REDUCE, 0);

    // State 15 (E -> E - T ·)
    actionTable[{15, "*"}] = Action(ActionType::SHIFT, 6);
    actionTable[{15, "/"}] = Action(ActionType::SHIFT, 11);
    actionTable[{15, "+"}] = Action(ActionType::REDUCE, 1); // E -> E - T
    actionTable[{15, "-"}] = Action(ActionType::REDUCE, 1);
    actionTable[{15, ")"}] = Action(ActionType::REDUCE, 1);
    actionTable[{15, "$"}] = Action(ActionType::REDUCE, 1);

    // State 16 (T -> T / F ·)
    actionTable[{16, "+"}] = Action(ActionType::REDUCE, 4); // T -> T / F
    actionTable[{16, "-"}] = Action(ActionType::REDUCE, 4);
    actionTable[{16, "*"}] = Action(ActionType::REDUCE, 4);
    actionTable[{16, "/"}] = Action(ActionType::REDUCE, 4);
    actionTable[{16, ")"}] = Action(ActionType::REDUCE, 4);
    actionTable[{16, "$"}] = Action(ActionType::REDUCE, 4);

    // State 17 (F -> ( E ) ·)
    actionTable[{17, "+"}] = Action(ActionType::REDUCE, 6); // F -> ( E )
    actionTable[{17, "-"}] = Action(ActionType::REDUCE, 6);
    actionTable[{17, "*"}] = Action(ActionType::REDUCE, 6);
    actionTable[{17, "/"}] = Action(ActionType::REDUCE, 6);
    actionTable[{17, ")"}] = Action(ActionType::REDUCE, 6);
    actionTable[{17, "$"}] = Action(ActionType::REDUCE, 6);
}

Action SLRTable::getAction(int state, const std::string& terminal) const {
    auto it = actionTable.find({state, terminal});
    if (it != actionTable.end())
        return it->second;
    return Action(ActionType::ERROR, -1);
}

int SLRTable::getGoto(int state, const std::string& nonTerminal) const {
    auto it = gotoTable.find({state, nonTerminal});
    if (it != gotoTable.end())
        return it->second;
    return -1;
}
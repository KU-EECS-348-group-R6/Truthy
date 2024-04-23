#include "BooleanLogic.hpp"

bool BooleanLogic::and_op(bool a, bool b) { return a && b; }
bool BooleanLogic::or_op(bool a, bool b) { return a || b; }
bool BooleanLogic::not_op(bool a) { return !a; }
bool BooleanLogic::nand_op(bool a, bool b) {return !(a && b); }
bool BooleanLogic::xor_op(bool a, bool b) { return (a && !b) || (!a && b); }

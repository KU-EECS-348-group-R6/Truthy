#ifndef BOOLEAN_LOGIC_HPP
#define BOOLEAN_LOGIC_HPP

#include <stdexcept> // For using standard exception library

class BooleanLogic {
public:
    static bool and_op(bool a, bool b);
    static bool or_op(bool a, bool b);
    static bool not_op(bool a);
    static bool nand_op(bool a, bool b);
    static bool xor_op(bool a, bool b);
};

#endif // BOOLEAN_LOGIC_HPP

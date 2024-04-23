#include "Token.hpp"

// Constructor for operands
Token::Token(bool val) : type(Type::OPERAND), value(val) {}

// Constructor for operators and parentheses
Token::Token(char sym, Type t) : type(t), symbol(sym) {}

// Method to check if the token is an operator
bool Token::isOperator() const {
    return type == Type::OPERATOR && (symbol == '&' || symbol == '|' || symbol == '!' || symbol == '@' || symbol == '$');
}

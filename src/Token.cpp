#include "Token.hpp"

Token::Token(bool value) : type(Token::Type::OPERAND), value(value) {}
Token::Token(char symbol) : type(Token::Type::OPERATOR), symbol(symbol) {}

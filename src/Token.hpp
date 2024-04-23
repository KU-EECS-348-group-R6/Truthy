// Token.hpp without inline definitions
#ifndef TOKEN_HPP
#define TOKEN_HPP

#include "Span.hpp"

class Token {
public:
    enum class Type { OPERAND, OPERATOR, LEFT_PAREN, RIGHT_PAREN, VARIABLE };

    Type type;   // The type of the token in the expression
    bool value;  // Only used if type is OPERAND
    char symbol; // Used if type is OPERATOR or PARENTHESIS
    Span span;   // The span of the token in the expression

    Token(bool val, Span span);
    Token(char sym, Span span, std::string expression);
    bool isOperator() const;
    bool isOperand() const;
};

#endif // TOKEN_HPP

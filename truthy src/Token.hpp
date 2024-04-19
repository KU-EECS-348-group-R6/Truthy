// Token.hpp without inline definitions
#ifndef TOKEN_HPP
#define TOKEN_HPP

class Token {
public:
    enum class Type { OPERAND, OPERATOR, LEFT_PAREN, RIGHT_PAREN };

    Type type;
    bool value;  // Only used if type is OPERAND
    char symbol; // Used if type is OPERATOR or PARENTHESIS

    Token(bool val);
    Token(char sym, Type t);
    bool isOperator() const;
};

#endif // TOKEN_HPP

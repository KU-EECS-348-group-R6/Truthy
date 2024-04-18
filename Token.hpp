#ifndef TOKEN_HPP
#define TOKEN_HPP

class Token {
public:
    enum class Type { OPERAND, OPERATOR, PARENTHESIS };

    Type type;
    bool value;
    char symbol;

    Token(bool value);
    Token(char symbol);

    bool isOperator() const { return type == Type::OPERATOR && symbol != '(' && symbol != ')'; }
};

#endif // TOKEN_HPP

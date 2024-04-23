#include "Token.hpp"
#include "Span.hpp"
#include "errors/TokenizationException.hpp"
#include <map>

// Checks if the character is a defined operator
bool charIsOperator(char ch)  {
    return ch == '&' || ch == '|' || ch == '!' || ch == '@' || ch == '$' || ch == '=';
}

// Checks if the character is an operand (T or F)
bool charIsOperand(char ch)  {
    return std::toupper(ch) == 'T' || std::toupper(ch) == 'F';
}

// Constructor for operands
Token::Token(bool val, Span span) : type(Type::OPERAND), value(val), span(span) {}

// Constructor for operators and parentheses
Token::Token(char sym, Span span, std::string expression): span(span), symbol(sym) {
    if (charIsOperator(sym)) {
        type = Type::OPERATOR;
    } else if (charIsOperand(sym)) {
        type = Type::OPERAND;
        value = std::toupper(sym) == 'T';
    } else if (sym == '(') {
        type = Type::LEFT_PAREN;
    } else if (sym == ')') {
        type = Type::RIGHT_PAREN;
    } else if (isalpha(sym)) {
        type = Type::VARIABLE;
    } else {
        throw TokenizationException(sym, span, expression);
    }
}

// Method to check if the token is an operator
bool Token::isOperator() const {
    return type == Type::OPERATOR;
}

// Method to check if the token is an operand
bool Token::isOperand() const {
    return type == Type::OPERAND;
}

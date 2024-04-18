#ifndef EXPRESSION_PARSER_HPP
#define EXPRESSION_PARSER_HPP

#include "Token.hpp"
#include <vector>
#include <string>
#include <stack>
#include <stdexcept>

class ExpressionParser {
public:
    // Parses the input expression string into a vector of tokens in postfix notation
    std::vector<Token> parse(const std::string& expression);

private:
    // Helper function to convert infix expression to postfix
    std::vector<Token> infixToPostfix(const std::vector<Token>& infixTokens);

    // Helper function to check the precedence of operators
    int precedence(char op) const;

    // Helper function to determine if a character is an operator
    bool isOperator(char ch) const;

    // Helper function to check if the given character is a valid part of an operand
    bool isOperand(char ch) const;
};

#endif // EXPRESSION_PARSER_HPP

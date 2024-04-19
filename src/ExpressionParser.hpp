#ifndef EXPRESSION_PARSER_HPP
#define EXPRESSION_PARSER_HPP

#include "Token.hpp"
#include <vector>
#include <string>
#include <stack>
#include <set>

class ExpressionParser {
public:
    std::vector<Token> parse(const std::string& expression);
    std::set<char> extractVariables(const std::string& expression); // New method
    // Other methods...

private:
    std::vector<Token> infixToPostfix(const std::vector<Token>& infixTokens);
    int precedence(char op) const;
    bool isOperator(char ch) const;
    bool isOperand(char ch) const;
};

#endif // EXPRESSION_PARSER_HPP

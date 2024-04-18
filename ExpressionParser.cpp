#include "ExpressionParser.hpp"
#include <cctype>
#include <map>
#include <iostream>

std::vector<Token> ExpressionParser::parse(const std::string& expression) {
    std::vector<Token> infixTokens;
    bool expectOperand = true; // Start expecting an operand initially

    for (size_t i = 0; i < expression.length(); ++i) {
        char ch = expression[i];
        if (isspace(ch)) continue; // Skip whitespace

        if (expectOperand) {
            if (isOperand(ch)) {
                infixTokens.emplace_back(ch == 'T');
                expectOperand = false; // Next should be an operator or a parenthesis
            } else if (ch == '(' || ch == '!') {
                // '(' and '!' are valid if we are expecting an operand
                infixTokens.emplace_back(ch);
            } else {
                throw std::invalid_argument("Expected operand, found: " + std::string(1, ch));
            }
        } else {
            if (isOperator(ch) || ch == ')') {
                infixTokens.emplace_back(ch);
                expectOperand = ch != ')'; // If we have a closing parenthesis, we are still expecting an operator
            } else if (isOperand(ch)) {
                throw std::invalid_argument("Expected operator, found operand: " + std::string(1, ch));
            } else {
                throw std::invalid_argument("Invalid character in expression: " + std::string(1, ch));
            }
        }
    }
    if (expectOperand) {
        throw std::invalid_argument("Expression ends unexpectedly, likely missing an operand.");
    }
    return infixToPostfix(infixTokens);
}

std::vector<Token> ExpressionParser::infixToPostfix(const std::vector<Token>& infixTokens) {
    std::vector<Token> postfix;
    std::stack<Token> stack;
    for (const Token& token : infixTokens) {
        if (token.type == Token::Type::OPERAND) {
            postfix.push_back(token);
        } else if (token.symbol == '(') {
            stack.push(token);
        } else if (token.symbol == ')') {
            while (!stack.empty() && stack.top().symbol != '(') {
                postfix.push_back(stack.top());
                stack.pop();
            }
            if (stack.empty()) {
                throw std::invalid_argument("Mismatched parentheses: no matching opening parenthesis.");
            }
            stack.pop(); // Remove '(' from stack
        } else if (isOperator(token.symbol)) {
            while (!stack.empty() && precedence(stack.top().symbol) >= precedence(token.symbol)) {
                postfix.push_back(stack.top());
                stack.pop();
            }
            stack.push(token);
        }
    }

    while (!stack.empty()) {
        if (stack.top().symbol == '(') {
            throw std::invalid_argument("Mismatched parentheses: no matching closing parenthesis.");
        }
        postfix.push_back(stack.top());
        stack.pop();
    }

    return postfix;
}

int ExpressionParser::precedence(char op) const {
    std::map<char, int> prec = {
            {'!', 4}, // Highest precedence for unary NOT operator
            {'&', 3},
            {'|', 2},
            {'@', 2},
            {'$', 1} // Lowest precedence for binary operators
    };
    return prec[op];
}

bool ExpressionParser::isOperator(char ch) const {
    return ch == '&' || ch == '|' || ch == '!' || ch == '@' || ch == '$';
}

bool ExpressionParser::isOperand(char ch) const {
    return ch == 'T' || ch == 'F';
}

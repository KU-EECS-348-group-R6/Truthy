#include "ExpressionParser.hpp"
#include <cctype>
#include <map>
#include <iostream>
#include <stdexcept>

bool ExpressionParser::isOperator(char ch) const {
    return ch == '&' || ch == '|' || ch == '!' || ch == '@' || ch == '$';
}

bool ExpressionParser::isOperand(char ch) const {
    ch = std::toupper(ch);  // Normalize to uppercase to handle 't'/'T' and 'f'/'F'
    return ch == 'T' || ch == 'F';
}

std::vector<Token> ExpressionParser::parse(const std::string& expression) {
    std::vector<Token> infixTokens;
    bool expectOperand = true; // Start expecting an operand initially

    for (size_t i = 0; i < expression.length(); ++i) {
        char ch = std::toupper(expression[i]); // Normalize to uppercase for consistent processing
        if (isspace(ch)) continue; // Skip whitespace

        if (expectOperand) {
            if (isOperand(ch)) {
                infixTokens.emplace_back(ch == 'T');
                expectOperand = false; // Next should be an operator or a parenthesis
            } else if (ch == '(') {
                infixTokens.emplace_back(ch, Token::Type::LEFT_PAREN);
            } else if (ch == '!') {  // Handling unary NOT
                infixTokens.emplace_back(ch, Token::Type::OPERATOR);
            } else {
                throw std::invalid_argument("Expected operand or left parenthesis, found: " + std::string(1, ch));
            }
        } else {
            if (isOperator(ch) && ch != '!') { // Ensure '!' is not handled here as it is unary
                infixTokens.emplace_back(ch, Token::Type::OPERATOR);
                expectOperand = true; // After an operator, an operand or left parenthesis is expected
            } else if (ch == ')') {
                infixTokens.emplace_back(ch, Token::Type::RIGHT_PAREN);
                expectOperand = false; // An operator should follow a closing parenthesis
            } else {
                throw std::invalid_argument("Expected operator or right parenthesis, found: " + std::string(1, ch));
            }
        }
    }

    if (expectOperand && !infixTokens.empty()) {
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
        } else if (token.type == Token::Type::LEFT_PAREN) {
            stack.push(token);
        } else if (token.type == Token::Type::RIGHT_PAREN) {
            while (!stack.empty() && stack.top().type != Token::Type::LEFT_PAREN) {
                postfix.push_back(stack.top());
                stack.pop();
            }
            if (stack.empty()) {
                throw std::invalid_argument("Mismatched parentheses: no matching opening parenthesis.");
            }
            stack.pop(); // Remove '(' from stack
        } else if (token.isOperator()) {
            while (!stack.empty() && precedence(stack.top().symbol) >= precedence(token.symbol)) {
                postfix.push_back(stack.top());
                stack.pop();
            }
            stack.push(token);
        }
    }

    while (!stack.empty()) {
        if (stack.top().type == Token::Type::LEFT_PAREN) {
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

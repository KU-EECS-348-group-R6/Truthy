#include "ExpressionParser.hpp"
#include <cctype>
#include <map>
#include <stdexcept>

// Checks if the character is a defined operator
bool ExpressionParser::isOperator(char ch) const {
    return ch == '&' || ch == '|' || ch == '!' || ch == '@' || ch == '$' || ch == '=';
}

// Checks if the character is an operand (T or F)
bool ExpressionParser::isOperand(char ch) const {
    return std::toupper(ch) == 'T' || std::toupper(ch) == 'F';
}

// Defines the precedence of operators for use in infixToPostfix conversion
int ExpressionParser::precedence(char op) const {
    std::map<char, int> prec = {
            {'!', 4},  // NOT has the highest precedence
            {'&', 3},  // AND
            {'|', 2},  // OR
            {'@', 2},  // NAND
            {'$', 1},  // XOR
            {'=', 1}   // EQUALITY (if implemented)
    };
    return prec[op];
}

// Parses the input string expression into a vector of tokens in infix format
std::vector<Token> ExpressionParser::parse(const std::string& expression) {
    if (expression.empty()) {
        throw std::invalid_argument("Empty expression: No operands or operators present");
    }

    std::vector<Token> infixTokens;
    bool expectOperand = true; // Expect an operand initially
    char lastChar = 0; // Track the last character processed

    for (char ch : expression) {
        if (std::isspace(ch)) continue;
        if (expectOperand) {
            if (isOperand(ch)) {
                infixTokens.emplace_back(std::toupper(ch) == 'T');
                expectOperand = false; // Next, we expect an operator or a parenthesis
                lastChar = ch;
            } else if (ch == '(') {
                infixTokens.emplace_back(ch, Token::Type::LEFT_PAREN);
            } else if (ch == '!') {
                infixTokens.emplace_back(ch, Token::Type::OPERATOR);
            } else {
                throw std::invalid_argument("Unknown operator: " + std::string(1, ch) + " [Reason: Unrecognized operator symbol]");
            }
        } else {
            if (isOperator(ch)) {
                if (lastChar == ')' || isOperand(lastChar)) {
                    infixTokens.emplace_back(ch, Token::Type::OPERATOR);
                    expectOperand = true; // After an operator, an operand is expected
                } else {
                    throw std::invalid_argument("Double operator: " + std::string(1, lastChar) + " " + std::string(1, ch) + " [Reason: Two consecutive AND operators]");
                }
            } else if (ch == ')') {
                infixTokens.emplace_back(ch, Token::Type::RIGHT_PAREN);
                expectOperand = false; // An operator or closing parenthesis should follow
            } else {
                throw std::invalid_argument("Expected operator or right parenthesis, found: " + std::string(1, ch));
            }
        }
        lastChar = ch;
    }

    if (expectOperand && !infixTokens.empty()) {
        throw std::invalid_argument("Missing operand: [Reason: Expression ends unexpectedly, likely missing an operand]");
    }

    return infixToPostfix(infixTokens);
}

std::set<char> ExpressionParser::extractVariables(const std::string& expression) {
    std::set<char> variables;
    for (char ch : expression) {
        if (std::isalpha(ch) && std::isupper(ch)) { // Assume variables are uppercase letters
            variables.insert(ch);
        }
    }
    return variables;
}

// Converts a vector of tokens from infix to postfix notation using a stack-based approach
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
            if (!stack.empty()) {
                stack.pop(); // Pop the left parenthesis off the stack
            } else {
                throw std::invalid_argument("Mismatched parentheses: No matching opening parenthesis found.");
            }
        } else if (token.isOperator()) {
            while (!stack.empty() && stack.top().isOperator() && precedence(stack.top().symbol) >= precedence(token.symbol)) {
                postfix.push_back(stack.top());
                stack.pop();
            }
            stack.push(token);
        }
    }

    // Pop all the operators left in the stack
    while (!stack.empty()) {
        if (stack.top().type == Token::Type::LEFT_PAREN) {
            throw std::invalid_argument("Mismatched parentheses: No matching closing parenthesis found.");
        }
        postfix.push_back(stack.top());
        stack.pop();
    }

    return postfix;
}

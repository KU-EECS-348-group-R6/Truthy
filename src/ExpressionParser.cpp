#include "ExpressionParser.hpp"
#include "errors/TokenizationException.hpp"
#include "errors/MissingOperandsException.hpp"
#include "errors/MissingClosingParenthesisException.hpp"
#include "errors/MissingOperatorException.hpp"
#include <cctype>
#include <map>
#include <stdexcept>

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

// Parses the input string expression into a vector of tokens
std::vector<Token> ExpressionParser::parse(const std::string& expression) {
    std::vector<Token> tokens;

    // Turn each non-whitespace character into a single token
    for (int i = 0; i < expression.length(); i++) {
        char ch = expression[i];
        if (std::isspace(ch)) continue;
        tokens.emplace_back(ch, Span(i));
    }

    return tokens;
}

// Group the input tokenized expression into a vector of tokens in postfix format
std::vector<Token> ExpressionParser::group(const std::vector<Token>& infixTokens) {
    if (infixTokens.empty()) {
        throw std::invalid_argument("Empty expression: No operands or operators present");
    }

    bool expectOperand = true; // Expect an operand initially
    Token lastToken = infixTokens[0]; // Track the last token processed
    std::stack<Token> parenthesisStack; // Keep track of the parenthesis that are open

    // Validate the tokens are in a valid order
    for (const Token& token : infixTokens) {
        if (token.type == Token::Type::LEFT_PAREN) {
            parenthesisStack.push(token);
        } else if (token.type == Token::Type::RIGHT_PAREN) {
            if (parenthesisStack.empty()) {
                throw MissingClosingParenthesisException(token.span);
            }
            parenthesisStack.pop();
        }

        if (expectOperand) {
            if (token.isOperand()) {
                expectOperand = false; // Next, we expect an operator or a parenthesis
            } else if (!(token.type == Token::Type::LEFT_PAREN || token.symbol == '!')) {
                // throw std::invalid_argument("Unknown operator: " + std::string(1, ch) + " [Reason: Unrecognized operator symbol]");
                throw MissingOperandsException(token, lastToken.span);
            }
        } else {
            if (token.isOperator()) {
                if (lastToken.type == Token::Type::LEFT_PAREN || lastToken.isOperand()) {
                    expectOperand = true; // After an operator, an operand is expected
                } else {
                    // throw std::invalid_argument("Double operator: " + std::string(1, lastChar) + " " + std::string(1, ch) + " [Reason: Two consecutive AND operators]");
                    throw MissingOperatorException(token, lastToken.span);
                }
            } else if (token.type == Token::Type::RIGHT_PAREN) {
                expectOperand = false; // An operator or closing parenthesis should follow
            } else {
                // throw std::invalid_argument("Expected operator or right parenthesis, found: " + std::string(1, ch));
                throw MissingOperatorException(token, lastToken.span);
            }
        }
        lastToken = token;
    }

    if (expectOperand && !infixTokens.empty()) {
        // throw std::invalid_argument("Missing operand: [Reason: Expression ends unexpectedly, likely missing an operand]");
        throw MissingOperatorException(lastToken.span);
    }

    // If there are unclosed parenthesis at the end of the expression, throw an exception
    if (!parenthesisStack.empty()) {
        throw MissingClosingParenthesisException(parenthesisStack.top().span);
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

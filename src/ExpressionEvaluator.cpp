#include "ExpressionEvaluator.hpp"
#include "ExpressionParser.hpp"
#include "BooleanLogic.hpp"
#include <stack>
#include <stdexcept>
#include <iostream>

bool ExpressionEvaluator::evaluate(const std::string& expression) {
    ExpressionParser parser;
    std::vector<Token> infixTokens = parser.parse(expression);
    std::vector<Token> postfixTokens = parser.group(infixTokens, expression);
    std::stack<bool> evalStack;

    for (const Token& token : postfixTokens) {
        if (token.type == Token::Type::OPERAND) {
            evalStack.push(token.value);
        } else if (token.isOperator()) {
            if (token.symbol == '!') {  // Unary operator NOT
                if (evalStack.empty()) throw std::runtime_error("Syntax error: Stack underflow.");
                bool operand = evalStack.top();
                evalStack.pop();
                evalStack.push(BooleanLogic::not_op(operand));
            } else {  // Binary operators
                if (evalStack.size() < 2) throw std::runtime_error("Syntax error: Insufficient values in the stack for operation.");
                bool right = evalStack.top(); evalStack.pop();
                bool left = evalStack.top(); evalStack.pop();

                switch (token.symbol) {
                    case '&': evalStack.push(BooleanLogic::and_op(left, right)); break;
                    case '|': evalStack.push(BooleanLogic::or_op(left, right)); break;
                    case '@': evalStack.push(BooleanLogic::nand_op(left, right)); break;
                    case '$': evalStack.push(BooleanLogic::xor_op(left, right)); break;
                    default: throw std::invalid_argument("Unsupported operator: " + std::string(1, token.symbol));
                }
            }
        } else {
            throw std::runtime_error("Unexpected token type.");
        }
    }

    if (evalStack.size() != 1) {
        throw std::runtime_error("Syntax error: The expression does not evaluate to a single result.");
    }

    return evalStack.top();
}

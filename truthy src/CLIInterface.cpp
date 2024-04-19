#include "CLIInterface.hpp"
#include "ExpressionEvaluator.hpp"
#include "ExpressionParser.hpp"
#include <iostream>
#include <cmath>
#include <bitset>
#include <algorithm>
#include <vector>

void generateTruthTable(const std::string& expression, ExpressionParser& parser, ExpressionEvaluator& evaluator) {
    auto variables = parser.extractVariables(expression);
    size_t numVars = variables.size();
    size_t numCombinations = 1 << numVars;  // Equivalent to 2^numVars, more efficiently computed

    std::vector<char> vars(variables.begin(), variables.end());
    std::sort(vars.begin(), vars.end());  // Ensure variables are in a consistent order

    // Print header
    for (char var : vars) {
        std::cout << var << "\t";
    }
    std::cout << "Result\n";
    std::cout << std::string(numVars * 4 + 7, '-') << "\n";

    // Evaluate each combination
    for (size_t i = 0; i < numCombinations; ++i) {
        std::bitset<64> bits(i);  // Use 64 bits for larger capacity
        std::string modifiedExpression = expression;

        for (size_t j = 0; j < numVars; ++j) {
            char value = bits[j] ? 'T' : 'F';
            std::replace(modifiedExpression.begin(), modifiedExpression.end(), vars[j], value);
            std::cout << (value == 'T' ? "T" : "F") << "\t";
        }

        bool result = evaluator.evaluate(modifiedExpression);
        std::cout << (result ? "True" : "False") << std::endl;
    }
}


void CLIInterface::run() {
    std::string input;
    ExpressionEvaluator evaluator;
    ExpressionParser parser;

    std::cout << "Welcome to the Boolean Logic Simulator. Type 'exit' to quit or 'help' for instructions." << std::endl;
    std::cout << "Type 'table' followed by an expression to generate a truth table." << std::endl;

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);
        std::transform(input.begin(), input.end(), input.begin(), ::toupper); // Convert to uppercase to handle case-insensitivity

        if (input == "EXIT") break;
        if (input == "HELP") {
            std::cout << "Enter Boolean expressions using variables (T, F) and operators (&, |, !, @, $).\n";
            std::cout << "For example: 'T & F', '!T', '(T | F) & F'.\n";
            std::cout << "To generate a truth table: 'table (T & F) | (T & F)'\n";
            continue;
        }

        if (input.substr(0, 5) == "TABLE") {
            try {
                std::string expression = input.substr(6);
                generateTruthTable(expression, parser, evaluator);
            } catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << std::endl;
            }
            continue;
        }

        try {
            bool result = evaluator.evaluate(input);
            std::cout << "Result: " << (result ? "True" : "False") << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
}

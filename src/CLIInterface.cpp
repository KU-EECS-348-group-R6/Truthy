#include "CLIInterface.hpp"
#include "ExpressionEvaluator.hpp"
#include "ExpressionParser.hpp"
#include <iostream>
#include <bitset>
#include <algorithm>
#include <vector>


void generateTruthTable(const std::string& expression, ExpressionParser& parser, ExpressionEvaluator& evaluator) {
    std::string normalizedExpression = expression;
    std::transform(normalizedExpression.begin(), normalizedExpression.end(), normalizedExpression.begin(), ::toupper);

    auto variables = parser.extractVariables(
            normalizedExpression);  // Assumes this function handles uppercased inputs correctly

    size_t numVars = variables.size();
    size_t numCombinations = 1 << numVars;

    std::vector<char> vars(variables.begin(), variables.end());
    std::sort(vars.begin(), vars.end(), std::greater<>());  // Ensure variables are in a consistent order

    // Print header
    for (char var: vars) {
        std::cout << var << "\t";
    }
    std::cout << "Result\n";
    std::cout << std::string(numVars * 4 + 7, '-') << "\n";

    // Evaluate each combination
    for (size_t i = 0; i < numCombinations; ++i) {
        std::bitset<64> bits(i);
        std::string modifiedExpression = normalizedExpression;
        // Replace only the variables identified by the parser
        for (size_t j = 0; j < numVars; ++j) {
            std::string oldVal(1, vars[j]); // Convert char to string, already uppercased
            std::string newVal = bits[j] ? "T" : "F";
            size_t start_pos = 0;

            // Replace occurrences of variables with their truth values (T/F)
            while ((start_pos = modifiedExpression.find(oldVal, start_pos)) != std::string::npos) {
                bool isLeftAlpha = start_pos > 0 && isalpha(modifiedExpression[start_pos - 1]);
                bool isRightAlpha = start_pos + oldVal.length() < modifiedExpression.length() &&
                                    isalpha(modifiedExpression[start_pos + oldVal.length()]);
                if (!isLeftAlpha && !isRightAlpha) {
                    modifiedExpression.replace(start_pos, oldVal.length(), newVal);
                    start_pos += newVal.length(); // Move past this match
                } else {
                    start_pos += oldVal.length(); // Skip this occurrence
                }
            }
            std::cout << newVal << "\t";
        }

        // Evaluate the modified expression
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
                expression = expression.erase(0, expression.find_first_not_of(" \t")); // Trim leading whitespace if any
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

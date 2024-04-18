#include "CLIInterface.hpp"
#include "ExpressionEvaluator.hpp"
#include <iostream>
#include <string>

void CLIInterface::run() {
    std::string input;
    ExpressionEvaluator evaluator;

    std::cout << "Welcome to the Boolean Logic Simulator. Enter 'exit' to quit." << std::endl;
    std::cout << "Please enter a Boolean expression using T (True), F (False), and the operators &, |, !, @, $." << std::endl;
    std::cout << "For example, 'T & F', '!T', '(T | F) & F', etc." << std::endl;

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);
        if (input == "exit" || input == "EXIT") break;

        try {
            bool result = evaluator.evaluate(input);
            std::cout << "Result: " << (result ? "True" : "False") << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
}

#include "ExpressionEvaluator.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <string>
#include <limits>
#include <vector>

int passORfail(bool s) {
    std::cout << std::left << std::setw(10) << (s ? "Passed" : "Failed");
    return s ? 1 : 0;
}

void runValidTestCases(ExpressionEvaluator& evaluator) {
    std::vector<std::pair<std::string, bool>> testCases = {
            {"(T | F) $ F", true},
            {"! (T & T)", false},
            {"(F @ T) | (T @ F)", true},
            {"(T $ T) & F", false},
            {"! F | ! T", true},
            {"(((((T | F) & F) | (T & (T | F))) @ (T @ T)) $ (! (T | F)))", true},
            {"((F $ ((T | F) & (F @ (T | F)))) | (T $ (T & F)))", true},
            {"(((! (T $ F)) & (T @ T)) | ((F | T) & (T $ T)))", false},
            {"(((T @ T) $ (F @ T)) | ((!T) & (T | (!T))))", true},
            {"((F @ T) $ (T | (F & F))) & (T & (T @ (!T)))", false},
            {"F @ F", true},
            {"F @ T", true},
            {"T @ T", false},
            {"T $ T", false},
            {"F $ T", true},
            {"F $ F", false},
            {"T $ F", true},
            {"!T", false},
            {"!F", true},
            {"(T & F) | !(F & T)", true},
            {"(T | F) & !(F | T)", false},
            {"!(T | F) $ !(F & T)", true},
            {"(T | F) @ !(T $ F)", true},
            {"!(T & F) $ !(T | F)", true},
            {"!(T | F) @ (T & F)", true},
            {"(T & F) | ((T | F) & !(F & T))", true},
            {"!(T $ F) @ !(T @ F)", true},
            {"!(T & F)", true},
            {"T | F", true},
            {"!(T | T)", false},
            {"F & T", false},
            {"T @ F", true},
            {"!(T $ T)", true},
            {"T | (F & T)", true},
            {"(T @ F) | (T & F)", true},
            {"(F & T) $ (T | F)", true},
            {"!(T $ F)", false},
            {"(T | F) & (T & F)", false},
            {"!(F @ T)", false},
            {"T & (F | T)", true},
            {"!(T $ T)", true},
            {"(F @ T) | (T $ F)", true},
            {"!(T | F)", false},
            {"(T & F) | (F @ T)", true},
            {"!(T & T)", false},
            {"(T $ F) & (F @ T)", true},
            {"!(F & T)", true},
            {"(T & F) & F @ T", true},
            {"T & T", true},
            {"T & F", false},
            {"F & F", false},
            {"F & T", false},
            {"T | F", true},
            {"T | T", true},
            {"F | F", false},
            {"F | T", true}
    };

    int counter = 0;
    for (const auto& test : testCases) {
        bool result = evaluator.evaluate(test.first);
        bool expected = test.second;
        std::cout << std::left << std::setw(5) << counter + 1;
        std::cout << std::left << std::setw(80) << test.first;
        std::cout << std::boolalpha << std::left << std::setw(10) << expected;
        std::cout << std::boolalpha << std::left << std::setw(10) << result;
        counter += passORfail(result == expected);
        assert(result == expected);
        std::cout << std::endl;
    }

    std::cout << std::endl << counter << " OUT OF " << testCases.size() << " PASSED" << std::endl;
}

void runInvalidTestCases(ExpressionEvaluator& evaluator) {
    std::string invalidExpressions[] = {
            "! & T", "T ? T", "(T |)", "T = !(T & T)", "",
            "T &", "T | | T", "(T & (F |)", "T F", "T |& T",
            "&T", "|T", "(T&(T|F)", "((T)", "T) & T(",
            "(T & T))", "T || T", "T && T", "(T | F)) & T", "T | !",
            "!!T", "T ! T", "T !& T", "T | (T & F))", "(T | F &)",
            "(| T & F)", "(T &)", "(T | (F & T) &)", "T $", "T @ F &",
            "T &&", "T || F", "T $ $ T", "T @ @ F", "(T | )",
            "( & T)", "T (| F)", "(T & (T | ) F)", "T | T &", "T | T F T",
    };

    int passedCount = 0;
    for (const auto& expr : invalidExpressions) {
        try {
            evaluator.evaluate(expr);
            std::cout << "Unexpected pass for: " << expr << std::endl;
            assert(false);
        } catch (const std::exception& e) {
            std::cout << "Correctly caught an error for: " << expr << " - " << e.what() << std::endl;
            passedCount++;
        }
    }
    std::cout << passedCount << " OUT OF " << (sizeof(invalidExpressions) / sizeof(invalidExpressions[0])) << " INVALID CASES PASSED" << std::endl;}

int main() {
    ExpressionEvaluator evaluator;

    std::cout << "Running valid expression tests..." << std::endl;
    runValidTestCases(evaluator);

    std::cout << "Running invalid expression tests..." << std::endl;
    runInvalidTestCases(evaluator);

    std::cout << "Press ENTER to exit.";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();

    return 0;
}

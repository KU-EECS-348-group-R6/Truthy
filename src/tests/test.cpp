#include "ExpressionEvaluator.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <string>
#include <limits>

int passORfail(bool s) {
    std::cout << std::left << std::setw(10) << (s ? "Passed" : "Failed");
    return s ? 1 : 0;
}

bool strToBool(const std::string& str) {
    return str[0] == 'T';
}

void runTestCases(ExpressionEvaluator& evaluator, const std::string& testFilePath, const std::string& resultFilePath, int& passedCount) {
    std::ifstream test_cases(testFilePath);
    std::ifstream results(resultFilePath);
    std::string expression, boolString;
    int nCases = 0;
    bool result, expected;

    if (!test_cases.is_open() || !results.is_open()) {
        std::cout << "Couldn't open test case files" << std::endl;
        return;
    }

    std::cout << "Test Case Phase 1: Testing for correctness" << std::endl << std::endl;
    std::cout << std::left << std::setw(5) << "ID" << std::setw(80) << "Expression" << std::setw(10) << "Expected" << std::setw(10) << "Result" << std::setw(20) << "Pas/Fail" << std::endl;

    while (std::getline(test_cases, expression) && std::getline(results, boolString)) {
        result = evaluator.evaluate(expression);
        expected = strToBool(boolString);
        std::cout << std::left << std::setw(5) << ++nCases;
        std::cout << std::left << std::setw(80) << expression;
        std::cout << std::boolalpha << std::left << std::setw(10) << expected;
        std::cout << std::boolalpha << std::left << std::setw(10) << result;
        passedCount += passORfail(result == expected);
        assert(result == expected); // Assertion added here
        std::cout << std::endl;
    }
    test_cases.close();
    results.close();
}

void testInvalidExpressions(ExpressionEvaluator& evaluator, int& passedCount) {
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

    for (const auto& expr : invalidExpressions) {
        try {
            evaluator.evaluate(expr);
            std::cout << "Unexpected pass for: " << expr << std::endl;
            assert(false); // Should not reach this point
        } catch (const std::exception& e) {
            std::cout << "Correctly caught an error for: " << expr << " - " << e.what() << std::endl;
            passedCount++;
        }
    }
}

int main() {
    ExpressionEvaluator evaluator;
    std::string relPath = "../tests/"; // path starts at executable
    int validPassed = 0;
    int invalidPassed = 0;

    // Running test cases for valid expressions
    runTestCases(evaluator, relPath + "test_cases.txt", relPath + "test_cases_results.txt", validPassed);

    // Running test cases for invalid expressions
    testInvalidExpressions(evaluator, invalidPassed);

    std::cout << validPassed << " valid test cases passed." << std::endl;
    std::cout << invalidPassed << " invalid test cases passed." << std::endl;

    std::cout << "Press ENTER to exit.";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();

    return 0;
}

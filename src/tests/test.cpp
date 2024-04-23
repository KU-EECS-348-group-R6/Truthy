#include "../ExpressionEvaluator.hpp"
#include "../errors/MissingOperandsException.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <string>

int passORfail(bool s) {
    if (s) {
        std::cout << std::left << std::setw(10) << "Passed";
        return 1;
    }
    else {
        std::cout << std::left << std::setw(10) << "Failed";
        return 0;
    }
}
bool strToBool(const std::string& str) {
    if (str[0] == 'T') {
        return true;
    }
    else {
        return false;
    }
}
void testValidExpressions()
{
    ExpressionEvaluator evaluator;
    int counter = 0;
    int nCases = 0; //how many cases we have in file
    bool result;
    bool expected_var;
    bool debug_mode = true; //hides all correct cases
    std::string relPath = "../tests/";//path starts at executable
    std::ifstream test_cases(relPath + "test_cases.txt");
    std::ifstream results(relPath + "test_cases_results.txt");
    std::cout << "Test Case Phase 1: Testing for correctness" << std::endl << std::endl;
    std::cout << std::left << std::setw(5) << "ID" << std::setw(80) << "Expression" << std::setw(10) << "Expected" << std::setw(10) << "Result" << std::setw(20) << "Pas/Fail" << std::endl;

    if (!test_cases.is_open() || !results.is_open()) {
        std::cout << "Couldn't open test case files" << std::endl;
    }
    else {
        std::string expression;
        std::string boolString;
        while (std::getline(test_cases, expression) && std::getline(results, boolString)) {
            result = evaluator.evaluate(expression);
            expected_var = strToBool(boolString);
            std::cout << std::left << std::setw(5) << nCases+1;
            std::cout << std::left << std::setw(80) << expression;
            std::cout << std::boolalpha << std::left << std::setw(10) << expected_var;
            std::cout << std::boolalpha << std::left << std::setw(10) << result;

            counter += passORfail(result == expected_var);
            nCases++;
            std::cout << std::endl << std::endl;

        }
    }
    std::cout << counter << " OUT OF " << nCases << " PASSED" << std::endl;
    test_cases.close();
    results.close();

    while (1) {
        std::cout << "enter to exit" << std::endl;
        char ret;
        //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get(ret);

        if (ret == '\n') {
            break;
        }
    }

    // Test valid expressions
    /*
    assert(evaluator.evaluate("(T | F) $ F") == true);
    assert(evaluator.evaluate("! (T & T)") == false);
    assert(evaluator.evaluate("(F @ T) | (T @ F)") == true);
    assert(evaluator.evaluate("(T $ T) & F") == false);
    assert(evaluator.evaluate("! F | ! T") == true);
    assert(evaluator.evaluate("(((((T | F) & F) | (T & (T | F))) @ (T @ T)) $ (! (T | F)))") == true);
    assert(evaluator.evaluate("((F $ ((T | F) & (F @ (T | F)))) | (T $ (T & F)))") == false);
    assert(evaluator.evaluate("(((! (T $ F)) & (T @ T)) | ((F | T) & (T $ T)))") == false);
    assert(evaluator.evaluate("(((T @ T) $ (F @ T)) | ((!T) & (T | (!T))))") == true);
    assert(evaluator.evaluate("((F @ T) $ (T | (F & F))) & (T & (T @ (!T)))") == false);

    std::cout << "All valid expression tests passed!" << std::endl;
    */
}

void testInvalidExpressions()
{
    ExpressionEvaluator evaluator;

    // Test invalid expressions
    try
    {
        evaluator.evaluate("! & T");
        assert(false); // Should not reach this point
    }
    catch (const std::exception &e)
    {
        assert(true); // Expected an exception
    }

    try
    {
        evaluator.evaluate("T ? T");
        assert(false); // Should not reach this point
    }
    catch (const std::exception &e)
    {
        assert(true); // Expected an exception
    }

    try
    {
        evaluator.evaluate("(T |)");
        assert(false); // Should not reach this point
    }
    catch (const std::exception &e)
    {
        assert(true); // Expected an exception
    }

    try
    {
        evaluator.evaluate("T = !(T & T)");
        assert(false); // Should not reach this point
    }
    catch (const std::exception &e)
    {
        assert(true); // Expected an exception
    }

    try
    {
        evaluator.evaluate("");
        assert(false); // Should not reach this point
    }
    catch (const std::exception &e)
    {
        assert(true); // Expected an exception
    }

    std::cout << "All invalid expression tests passed!" << std::endl;
}

int main()
{
    testValidExpressions();
    testInvalidExpressions();
    return 0;
}

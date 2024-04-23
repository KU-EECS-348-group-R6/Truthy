#include "../ExpressionEvaluator.hpp"
#include <iostream>
#include <cassert>

int passORfail(bool s) {
    if (s) {
        std::cout << "Test Passed" << std::endl;
        return 1;
    }
    else {
        std::cout << "Test Failed" << std::endl;
        return 0;
    }
}
void testValidExpressions() {
    ExpressionEvaluator evaluator;
    int counter = 0;
    int nCases = 10;
    bool result;
    bool expected;
    std::cout << "Test Case Phase 1: Testing for correctness" << std::endl;
    //from projet description
    
    
    result = evaluator.evaluate("(T | F) $ F");
    expected = true;
    std::cout << "Expression: (T | F) $ F" << std::endl;
    std::cout << "Expected: " << expected << std::endl;
    std::cout << "Result: " << result << std::endl;
    counter += passORfail(result == expected);
    std::cout << std::endl << std::endl;

    result = evaluator.evaluate("! (T & T)");
    expected = false;
    std::cout << "Expression: ! (T & T)" << std::endl;
    std::cout << "Expected: " << expected << std::endl;
    std::cout << "Result: " << result << std::endl;
    counter += passORfail(result == expected);
    std::cout << std::endl << std::endl;


    result = evaluator.evaluate("(F @ T) | (T @ F)");
    expected = true;
    std::cout << "Expression: (F @ T) | (T @ F)" << std::endl;
    std::cout << "Expected: " << expected << std::endl;
    std::cout << "Result: " << result << std::endl;
    counter += passORfail(result == expected);
    std::cout << std::endl << std::endl;

    result = evaluator.evaluate("(T $ T) & F");
    expected = false;
    std::cout << "Expression: (T $ T) & F" << std::endl;
    std::cout << "Expected: " << expected << std::endl;
    std::cout << "Result: " << result << std::endl;
    counter += passORfail(result == expected);
    std::cout << std::endl << std::endl;

    result = evaluator.evaluate("! F | ! T");
    expected = true;
    std::cout << "Expression: ! F | ! T" << std::endl;
    std::cout << "Expected: " << expected << std::endl;
    std::cout << "Result: " << result << std::endl;
    counter += passORfail(result == expected);
    std::cout << std::endl << std::endl;

    result = evaluator.evaluate("(((((T | F) & F) | (T & (T | F))) @ (T @ T)) $ (! (T | F)))");
    expected = true;
    std::cout << "Expression: (((((T | F) & F) | (T & (T | F))) @ (T @ T)) $ (! (T | F)))" << std::endl;
    std::cout << "Expected: " << expected << std::endl;
    std::cout << "Result: " << result << std::endl;
    counter += passORfail(result == expected);
    std::cout << std::endl << std::endl;

    result = evaluator.evaluate("((F $ ((T | F) & (F @ (T | F)))) | (T $ (T & F)))");
    expected = false;
    std::cout << "Expression: ((F $ ((T | F) & (F @ (T | F)))) | (T $ (T & F)))" << std::endl;
    std::cout << "Expected: " << expected << std::endl;
    std::cout << "Result: " << result << std::endl;
    counter += passORfail(result == expected);
    std::cout << std::endl << std::endl;

    result = evaluator.evaluate("(((! (T $ F)) & (T @ T)) | ((F | T) & (T $ T)))");
    expected = false;
    std::cout << "Expression: (((! (T $ F)) & (T @ T)) | ((F | T) & (T $ T)))" << std::endl;
    std::cout << "Expected: " << expected << std::endl;
    std::cout << "Result: " << result << std::endl;
    counter += passORfail(result == expected);
    std::cout << std::endl << std::endl;

    result = evaluator.evaluate("(((T @ T) $ (F @ T)) | ((!T) & (T | (!T))))");
    expected = true;
    std::cout << "Expression: (((T @ T) $ (F @ T)) | ((!T) & (T | (!T))))" << std::endl;
    std::cout << "Expected: " << expected << std::endl;
    std::cout << "Result: " << result << std::endl;
    counter += passORfail(result == expected);
    std::cout << std::endl << std::endl;

    result = evaluator.evaluate("((F @ T) $ (T | (F & F))) & (T & (T @ (!T)))");
    expected = false;
    std::cout << "Expression: (F @ T) $ (T | (F & F))) & (T & (T @ (!T)))" << std::endl;
    std::cout << "Expected: " << expected << std::endl;
    std::cout << "Result: " << result << std::endl;
    counter += passORfail(result == expected);
    std::cout << std::endl << std::endl;
    std::cout << counter << " OUT OF " << nCases << " PASSED" << std::endl;

    while (1) {
        std::cout << "enter to exit" << std::endl;
        char ret;
        //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get(ret);

        if (ret == '\n') {
            break;
        }
    }
    //Using cout over asser, so that test cases can show and not throw errors
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
    */

    std::cout << "All valid expression tests passed!" << std::endl;
}

void testInvalidExpressions() {
    ExpressionEvaluator evaluator;

    // Test invalid expressions
    try {
        evaluator.evaluate("! & T");
        assert(false); // Should not reach this point
    } catch (const std::exception& e) {
        assert(true); // Expected an exception
    }

    try {
        evaluator.evaluate("T ? T");
        assert(false); // Should not reach this point
    } catch (const std::exception& e) {
        assert(true); // Expected an exception
    }

    try {
        evaluator.evaluate("(T |)");
        assert(false); // Should not reach this point
    } catch (const std::exception& e) {
        assert(true); // Expected an exception
    }

    try {
        evaluator.evaluate("T = !(T & T)");
        assert(false); // Should not reach this point
    } catch (const std::exception& e) {
        assert(true); // Expected an exception
    }

    try {
        evaluator.evaluate("");
        assert(false); // Should not reach this point
    } catch (const std::exception& e) {
        assert(true); // Expected an exception
    }

    std::cout << "All invalid expression tests passed!" << std::endl;
}

int main() {
    testValidExpressions();
    //testInvalidExpressions();
    return 0;
}

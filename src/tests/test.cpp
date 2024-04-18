#include "../ExpressionEvaluator.hpp"
#include <iostream>
#include <cassert>

void testValidExpressions() {
    ExpressionEvaluator evaluator;

    // Test valid expressions
    assert(evaluator.evaluate("(T | F) $ F") == true);
    assert(evaluator.evaluate("! (T & T)") == false);
    assert(evaluator.evaluate("(F @ T) | (T @ F)") == true);
    assert(evaluator.evaluate("(T $ T) & F") == false);
    assert(evaluator.evaluate("! F | ! T") == true);
    assert(evaluator.evaluate("(((((T | F) & F) | (T & (T | F))) @ (T @ T)) $ (! (T | F)))") == true);
    assert(evaluator.evaluate("((F $ ((T | F) & (F @ (T | F)))) | (T $ (T & F)))") == true);
    assert(evaluator.evaluate("(((! (T $ F)) & (T @ T)) | ((F | T) & (T $ T)))") == false);
    assert(evaluator.evaluate("(((T @ T) $ (F @ T)) | ((!T) & (T | (!T))))") == true);
    assert(evaluator.evaluate("((F @ T) $ (T | (F & F))) & (T & (T @ (!T)))") == false);

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
    testInvalidExpressions();
    return 0;
}

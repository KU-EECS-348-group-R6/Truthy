#include "MissingOperatorException.hpp"
#include <string>

using namespace std;

string MissingOperatorException::display()
{
    string errorMessage = "Missing operator - Expected an operator after the operand at:\n";
    errorMessage += operand_location.underline(expression);
        errorMessage += "\nInstead found: ";
    if (endOfExpression) {
        errorMessage += "the end of the expression.";
    }
    else {
        errorMessage += foundToken.symbol;
    }

    return errorMessage;
}

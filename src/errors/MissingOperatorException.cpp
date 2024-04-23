#include "MissingOperatorException.hpp"
#include <string>

using namespace std;

MissingOperatorException::MissingOperatorException(Token foundToken, Span operand_location, Span error_location, string expression) : ParseException(error_location, expression), foundToken(foundToken), operand_location(operand_location) {}
MissingOperatorException::MissingOperatorException(Span operand_location, string expression) : ParseException(operand_location, expression), operand_location(operand_location), foundToken(Token(true, Span(0))){ 
}

string MissingOperatorException::display() const
{
    string errorMessage = "Missing operator - Expected an operator after the operand at:\n";
    errorMessage += operand_location.underline(expression);
        errorMessage += "\nInstead found: ";
    if (endOfExpression) {
        errorMessage += "the end of the expression.";
    } else {
        errorMessage += foundToken.symbol;
    }

    return errorMessage;
}

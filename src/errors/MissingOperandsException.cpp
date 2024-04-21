#include "MissingOperandsException.hpp"
#include <string>

using namespace std;

MissingOperandsException::MissingOperandsException(Token foundToken, Span operator_location, Span error_location, string expression) : ParseException(error_location, expression), foundToken(foundToken), operator_location(operator_location) {}

string MissingOperandsException::display()
{
    string errorMessage = "Missing operands - Expected the start of a new expression (T, F, '(', !, or a variable) after the operator: ";
    errorMessage += foundToken.symbol;
    errorMessage += "\nFound at: "; 
    errorMessage += operator_location.underline(expression);
    errorMessage += "\nFound token: ";
    errorMessage += foundToken.symbol;

    return errorMessage;
}

#include "MissingOpeningParenthesisException.hpp"
#include <string>

using namespace std;

MissingOpeningParenthesisException::MissingOpeningParenthesisException(Span opening_parentheses_location, string expression) : ParseException(opening_parentheses_location, expression) {}

string MissingOpeningParenthesisException::display()
{
    string errorMessage = "Missing opening parenthesis - Parenthesis closed at: ";
    errorMessage += location.underline(expression);
    errorMessage += "\nWere never opened.";

    return errorMessage;
}

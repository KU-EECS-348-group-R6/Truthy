#include "MissingClosingParenthesisException.hpp"
#include <string>

using namespace std;

MissingClosingParenthesisException::MissingClosingParenthesisException(Span opening_parentheses_location, string expression) : ParseException(opening_parentheses_location, expression), opening_parentheses_location(opening_parentheses_location) {}

string MissingClosingParenthesisException::display() const
{
    string errorMessage = "Missing closing parenthesis - Parenthesis opened at:\n";
    errorMessage += opening_parentheses_location.underline(expression);
    errorMessage += "\nAre never closed.";

    return errorMessage;
}

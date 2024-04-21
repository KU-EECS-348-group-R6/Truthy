#include "MissingClosingParenthesisException.hpp"
#include <string>

using namespace std;

string MissingClosingParenthesisException::display()
{
    string errorMessage = "Missing closing parenthesis - Parenthesis opened at: ";
    errorMessage += opening_parentheses_location.underline(expression);
    errorMessage += "\nAre never closed.";

    return errorMessage;
}

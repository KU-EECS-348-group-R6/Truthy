#include "MissingOpeningParenthesisException.hpp"
#include <string>

using namespace std;

string MissingOpeningParenthesisException::display()
{
    string errorMessage = "Missing opening parenthesis - Parenthesis closed at: ";
    errorMessage += location.underline(expression);
    errorMessage += "\nWere never opened.";

    return errorMessage;
}

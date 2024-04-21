#include "ParseException.hpp"
#include <string>

ParseException::ParseException(Span location, string expression) : location(location), expression(expression) {}

char *ParseException::what() {
    string errorMessage = "Parse error: ";
    errorMessage += display();
    errorMessage += "\nAt: ";
    errorMessage += location.underline(expression);
    errorMessage += "\n";

    return strdup(errorMessage.c_str());
}

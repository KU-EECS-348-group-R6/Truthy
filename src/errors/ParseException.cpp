#include "ParseException.hpp"
#include <string>

char *ParseException::what() {
    string errorMessage = "Parse error: ";
    errorMessage += display();
    errorMessage += "\nAt: ";
    errorMessage += location.underline(expression);
    errorMessage += "\n";

    return strdup(errorMessage.c_str());
}

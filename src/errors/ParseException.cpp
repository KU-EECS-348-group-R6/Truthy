#include "ParseException.hpp"
#include <string>

ParseException::ParseException(Span location, string expression) : location(location), expression(expression) {}

char const* ParseException::what() const throw(){
    string errorMessage = "Parse error: ";
    errorMessage += display();
    errorMessage += "\nError occurred while parsing:\n";
    errorMessage += location.underline(expression);
    errorMessage += "\n";

    return strdup(errorMessage.c_str());
}

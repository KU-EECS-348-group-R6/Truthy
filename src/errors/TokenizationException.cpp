#include "TokenizationException.hpp"
#include <string>

using namespace std;

TokenizationException::TokenizationException(char invalidByte, Span span, string expression) : ParseException(span, expression), invalidByte(invalidByte) {}

string TokenizationException::display() const 
{
    string errorMessage = "Tokenization error - Found invalid byte: '";
    errorMessage += invalidByte;
    errorMessage += "' Expected one of the following operators: !, @, $, &, |, = or an ascii variable.";

    return errorMessage;
}

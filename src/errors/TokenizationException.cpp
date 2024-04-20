#include "TokenizationException.hpp"
#include <string>

using namespace std;

string TokenizationException::display()
{
    string errorMessage = "Tokenization error - Found invalid byte: '";
    errorMessage += invalidByte;
    errorMessage += "' Expected one of the following operators: !, @, $, &, |, = or an ascii variable.";

    return errorMessage;
}

// MissingClosingParenthesisException.hpp without inline definitions
#ifndef MISSING_CLOSING_PARENTHESIS_EXCEPTION_HPP
#define MISSING_CLOSING_PARENTHESIS_EXCEPTION_HPP

#include <string>
#include "ParseException.hpp"
#include "Span.hpp"
#include "Token.hpp"
using namespace std;

class MissingClosingParenthesisException : ParseException
{
private:
    Span opening_parentheses_location;

public:
    MissingClosingParenthesisException(Span opening_parentheses_location);
    virtual string display();
};

#endif // ERROR_HPP

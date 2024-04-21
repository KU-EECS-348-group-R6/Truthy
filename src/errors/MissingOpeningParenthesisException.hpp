// MissingOpeningParenthesisException.hpp without inline definitions
#ifndef MISSING_OPENING_PARENTHESIS_EXCEPTION_HPP
#define MISSING_OPENING_PARENTHESIS_EXCEPTION_HPP

#include <string>
#include "ParseException.hpp"
#include "Span.hpp"
#include "Token.hpp"
using namespace std;

class MissingOpeningParenthesisException : ParseException
{
public:
    MissingOpeningParenthesisException(Span opening_parentheses_location);
    virtual string display();
};

#endif // ERROR_HPP

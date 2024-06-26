// MissingClosingParenthesisException.hpp without inline definitions
#ifndef MISSING_CLOSING_PARENTHESIS_EXCEPTION_HPP
#define MISSING_CLOSING_PARENTHESIS_EXCEPTION_HPP

#include <string>
#include "ParseException.hpp"
#include "Span.hpp"
#include "Token.hpp"
using namespace std;

class MissingClosingParenthesisException : public ParseException
{
private:
    Span opening_parentheses_location;

public:
    MissingClosingParenthesisException(Span opening_parentheses_location, string expression);
    string display() const;
};

#endif // ERROR_HPP

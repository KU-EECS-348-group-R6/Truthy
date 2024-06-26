// MissingOpeningParenthesisException.hpp without inline definitions
#ifndef MISSING_OPENING_PARENTHESIS_EXCEPTION_HPP
#define MISSING_OPENING_PARENTHESIS_EXCEPTION_HPP

#include <string>
#include "ParseException.hpp"
#include "Span.hpp"
#include "Token.hpp"
using namespace std;

class MissingOpeningParenthesisException : public ParseException
{
public:
    MissingOpeningParenthesisException(Span opening_parentheses_location,  string expression);
    string display() const;
};

#endif // ERROR_HPP

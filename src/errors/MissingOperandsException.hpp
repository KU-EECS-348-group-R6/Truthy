// MissingOperandsException.hpp without inline definitions
#ifndef MISSING_OPERANDS_EXCEPTION_HPP
#define MISSING_OPERANDS_EXCEPTION_HPP

#include "ParseException.hpp"
#include "Span.hpp"
#include "Token.hpp"

using namespace std;

class MissingOperandsException: public ParseException
{
private:
    Token foundToken;
    Span operator_location;

public:
    MissingOperandsException(Token foundToken, Span operator_location);
    virtual string display();
};

#endif // ERROR_HPP

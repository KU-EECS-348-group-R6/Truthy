// MissingOperatorException.hpp without inline definitions
#ifndef MISSING_OPERATOR_EXCEPTION_HPP
#define MISSING_OPERATOR_EXCEPTION_HPP

#include "ParseException.hpp"
#include "Span.hpp"
#include "Token.hpp"

using namespace std;

class MissingOperatorException: public ParseException
{
private:
    bool endOfExpression;
    Token foundToken;
    Span operand_location;

public:
    MissingOperatorException(Token foundToken, Span operand_location);
    MissingOperatorException(Span operand_location);
    virtual string display();
};

#endif // ERROR_HPP

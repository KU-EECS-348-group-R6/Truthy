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
    MissingOperatorException(Token foundToken, Span operand_location, Span error_location, string expression);
    MissingOperatorException(Span operand_location, string expression);
    string display() const;
};

#endif // ERROR_HPP

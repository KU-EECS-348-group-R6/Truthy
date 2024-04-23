// SPAN.hpp without inline definitions
#ifndef SPAN_HPP
#define SPAN_HPP

#include <string>

class Span
{
private:
    int start_byte;
    int end_byte;

public:
    Span(int start, int end);
    Span(int start);

    int start();
    int end();

    std::string underline(std::string str) const;
};

#endif // TOKEN_HPP

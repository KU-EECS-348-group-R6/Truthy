#include "Span.hpp"
#include <string>

Span::Span(int start, int end) {
    this->start_byte = start;
    this->end_byte = end;
}

Span::Span(int start) {
    this->start_byte = start;
    this->end_byte = start;
}

int Span::start() {
    return start_byte;
}

int Span::end() {
    return end_byte;
}

std::string Span::underline(std::string str) const {
    // Find the original string length
    int str_len = str.length();

    // Create a new string that starts with the original string
    std::string underline = str;

    // Add a new line to the string
    underline += "\n";
    for (int i = 0; i < str_len; i++) {
        if (i >= start_byte && i <= end_byte) {
            underline += "^";
        }
        else {
            underline += " ";
        }
    }

    return underline;
}

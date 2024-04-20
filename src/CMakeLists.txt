cmake_minimum_required(VERSION 3.28)
project(Truthy)

set(CMAKE_CXX_STANDARD 17)

# Define source files without the main.cpp
set(SOURCE_FILES
        Token.cpp
        ExpressionParser.cpp
        BooleanLogic.cpp
        ExpressionEvaluator.cpp
        CLIInterface.cpp
        Span.cpp
        errors/ParseException.cpp
        errors/TokenizationException.cpp)

# Main executable
add_executable(Truthy main.cpp ${SOURCE_FILES})

# Test executable
# Make sure to reference the correct path to test.cpp from the project root directory
add_executable(TruthyTest tests/test.cpp ${SOURCE_FILES})

# Include the header files directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

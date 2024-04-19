main:
	g++ -c src/BooleanLogic.cpp src/BooleanLogic.hpp src/CLIInterface.cpp src/CLIInterface.hpp src/ExpressionEvaluator.cpp src/ExpressionEvaluator.hpp src/ExpressionParser.cpp src/ExpressionParser.hpp src/main.cpp src/Token.cpp src/Token.hpp -std=c++17
	g++ BooleanLogic.o CLIInterface.o ExpressionEvaluator.o ExpressionParser.o main.o Token.o -o truthy
	./truthy

test:
	g++ -c src/BooleanLogic.cpp src/BooleanLogic.hpp src/CLIInterface.cpp src/CLIInterface.hpp src/ExpressionEvaluator.cpp src/ExpressionEvaluator.hpp src/ExpressionParser.cpp src/ExpressionParser.hpp src/tests/test.cpp src/Token.cpp src/Token.hpp -std=c++17
	g++ BooleanLogic.o CLIInterface.o ExpressionEvaluator.o ExpressionParser.o test.o Token.o -o truthyTest
	./truthyTest

clean:
	rm -f truthy truthyTest src/*.gch *.o

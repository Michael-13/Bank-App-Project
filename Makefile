CXX = g++
CXXFLAGS = -std=c++20 -Wall -MMD -g
EXEC = bankapp
OBJECTS = main.o account.o database.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}

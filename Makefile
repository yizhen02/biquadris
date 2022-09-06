CXX = g++
CXXFLAGS = -std=c++14 -Wall -g -MMD -Werror=vla
OBJECTS = main.o window.o block.o board.o cell.o level.o score.o view.o nextBlock.o levelZero.o levelOne.o levelTwo.o levelThree.o levelFour.o controller.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = biquadris

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11 

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}

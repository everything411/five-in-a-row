CXX = clang++
ARGS = -Wall -std=c++17 -O0
main: main.o createmoves.o makemove.o searchmove.o printchessboard.o evaluate.o gameover.o utils.o globals.o hashutils.o history.o wrapper.o
	$(CXX) $(ARGS) -o main history.o wrapper.o hashutils.o globals.o createmoves.o utils.o makemove.o main.o searchmove.o printchessboard.o evaluate.o gameover.o
hashutils.o: hashutils.cpp
	$(CXX) $(ARGS) -c -o hashutils.o hashutils.cpp
createmoves.o: createmoves.cpp
	$(CXX) $(ARGS) -c -o createmoves.o createmoves.cpp
evaluate.o: evaluate.cpp
	$(CXX) $(ARGS) -c -o evaluate.o evaluate.cpp
gameover.o: gameover.cpp
	$(CXX) $(ARGS) -c -o gameover.o gameover.cpp
makemove.o: makemove.cpp
	$(CXX) $(ARGS) -c -o makemove.o makemove.cpp
printchessboard.o: printchessboard.cpp
	$(CXX) $(ARGS) -c -o printchessboard.o printchessboard.cpp
searchmove.o: searchmove.cpp
	$(CXX) $(ARGS) -c -o searchmove.o searchmove.cpp
main.o: main.cpp
	$(CXX) $(ARGS) -c -o main.o main.cpp
utils.o: utils.cpp
	$(CXX) $(ARGS) -c -o utils.o utils.cpp
globals.o: globals.cpp
	$(CXX) $(ARGS) -c -o globals.o globals.cpp
history.o: history.cpp
	$(CXX) $(ARGS) -c -o history.o history.cpp
wrapper.o: wrapper.cpp
	$(CXX) $(ARGS) -c -o wrapper.o wrapper.cpp
clean:
	rm *.o main

C = clang
ARGS = -Wall -std=c11
main: main.o createmoves.o evaluate.o makemove.o printchessboard.o gameover.o globals.o searchmove.o utils.o wrapper.o
	$(C) $(ARGS) -o main main.o createmoves.o evaluate.o makemove.o printchessboard.o gameover.o globals.o searchmove.o utils.o wrapper.o
main.o: main.c
	$(C) $(ARGS) -c -o main.o main.c
createmoves.o: createmoves.c
	$(C) $(ARGS) -c -o createmoves.o createmoves.c
evaluate.o: evaluate.c
	$(C) $(ARGS) -c -o evaluate.o evaluate.c
gameover.o: gameover.c
	$(C) $(ARGS) -c -o gameover.o gameover.c
globals.o: globals.c
	$(C) $(ARGS) -c -o globals.o globals.c
makemove.o: makemove.c
	$(C) $(ARGS) -c -o makemove.o makemove.c
printchessboard.o: printchessboard.c
	$(C) $(ARGS) -c -o printchessboard.o printchessboard.c
searchmove.o: searchmove.c
	$(C) $(ARGS) -c -o searchmove.o searchmove.c
utils.o: utils.c
	$(C) $(ARGS) -c -o utils.o utils.c
wrapper.o: wrapper.c
	$(C) $(ARGS) -c -o wrapper.o wrapper.c
clean:
	rm *.o main

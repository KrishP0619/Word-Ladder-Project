build:
	rm -f wordLadder
	gcc -g main.c -o wordLadder
run:
	./wordLadder
valgrind:
	rm -f wordLadder
	gcc -gc main.c wordLadder
	valgrind -s --tool=memcheck --leak-check=yes -track-origins=yes ./wordLadder -f
redirection:
	./wordLadder < testProgram.txt
test:
	./wordLadder testMode



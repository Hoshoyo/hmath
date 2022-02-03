all:
	gcc -g -I.. main.c -mavx -mavx2 -o main -lm
	gcc -g -I.. -O2 speed.c -mavx -mavx2 -o speed -lm
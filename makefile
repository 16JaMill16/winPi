#makefile for winPi project
winPi : winPi.c
	gcc -Wall -o winPi winPi.c -lm 

winPi++ : winPi++.c
	gcc -Wall -o winPi++ winPi++.c -lm 
#makefile for winPi project
#winPi : winPi.c
#	gcc -Wall -o winPi winPi.c -lm 

#winPi++ : winPi++.c
#	gcc -Wall -o winPi++ winPi++.c -lm 

mathUtils : mathUtils.c mathUtils.h
	gcc -Wall mathUtils.c mathUtils.h -o mathUtils

ALL: comp lancement
comp:
	gcc -o exec main.c -Wall

lancement:
	./script.sh

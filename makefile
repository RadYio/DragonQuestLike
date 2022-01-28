# Makefile du projet.
# Définition des répertoires de travail.
SRC=./src
HEAD=./header
OBJ=./obj
BIN=./bin

#Compilateur gcc

CC=gcc

all: test

test: $(OBJ)/test.o $(OBJ)/test2.o
	$(CC) $(OBJ)/test.o $(OBJ)/test2.o -o $(BIN)/test -lm

$(OBJ)/test.o: $(SRC)/test.c $(HEAD)/test2.h
	$(CC) -c $(SRC)/test.c -o $(OBJ)/test.o -lm

$(OBJ)/test2.o: $(SRC)/test2.c
	$(CC) -c $(SRC)/test2.c $(OBJ)/test2.o -lm

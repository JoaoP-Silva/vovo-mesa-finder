# cc and flags
CC = g++
CXXFLAGS = -std=c++11 -g -Wall

# folders
INCLUDE_FOLDER = ./include/
SRC_FOLDER = ./src/

# all sources, objs, and header files
MAIN = Main
INPUT = input/input4.txt

all:
	g++ -std=c++11 -g -Wall src/main.cpp -o vovomesafinder.exe -I./include/

run:
	./vovomesafinder.exe < $(INPUT) 

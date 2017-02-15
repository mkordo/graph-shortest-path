OBJ = bin/main.o bin/queue.o﻿﻿
EXE = bin/test
DIR = bin

all: clearscreen create_dir $(EXE)

$(EXE): $(OBJ)
	g++ -Wall -o $(EXE) $(OBJ)

bin/%.o: src/%.cpp
	g++ -c -std=c++11 $< -o $@

bin/%.o: ../src/*/%.cpp
	g++ -c -std=c++11 $< -o $@

create_dir:
	@mkdir -p $(DIR)

clearscreen:
	clear

clean:
	rm -f bin/*.o $(EXE)

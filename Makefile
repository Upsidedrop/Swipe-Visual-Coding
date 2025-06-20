objects = $(wildcard *.o)

all: $(objects) link run

$(objects): %.o: src/%.cpp
	@g++ -c $^ -std=c++14 -m64 -g -Wall -I include -O0 
	@echo Updating $^
link:
	@g++ *.o -o bin/debug/main -lSDL2main -lSDL2_ttf -lSDL2 -lSDL2_image -lSDL2_mixer -O0
run:
	@./bin/debug/main
build:
	@read -p "File: " file ; \
	g++ -c src/$$file -std=c++14 -m64 -g -Wall -I include -O0 ; 
	@echo Built File $$file


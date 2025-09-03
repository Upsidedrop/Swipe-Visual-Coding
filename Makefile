objects = $(wildcard *.o)

#Run 'make' to update all prexisting object files
all: $(objects) link run

$(objects): %.o: src/%.cpp
	@g++ -c $^ -std=c++14 -m64 -g -Wall -I include
	@echo Updating $^
link:
	@g++ *.o -o bin/debug/main -Llib -lSDL2main -lSDL2_ttf -lSDL2 -lSDL2_image -lSDL2_mixer
run:
	@./bin/debug/main
#Run 'make build' for a prompt that will let you compile a specific file
build:
	@read -p "File: " file ; \
	g++ -c src/$$file -std=c++14 -m64 -g -Wall -I include ; 
	@echo Built File $$file
CC=gcc
CFLAGS=-c -Wall `sdl-config --cflags` `pkg-config --cflags SDL_ttf`
LDFLAGS=-lSDL -lSDL_net -lSDL_mixer `sdl-config --libs` `pkg-config --libs SDL_ttf`

SOURCES_MAIN=main.c src/c/affichage.c src/c/roulette.c
OBJECTS_MAIN=$(SOURCES_MAIN:.c=.o)
EXECUTABLE_MAIN=prog



all: $(EXECUTABLE_MAIN) 

$(EXECUTABLE_MAIN): $(OBJECTS_MAIN)
	$(CC) $(OBJECTS_MAIN) -o $@ $(LDFLAGS)


%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *o src/NET/*o src/c/*o $(EXECUTABLE_MAIN) 

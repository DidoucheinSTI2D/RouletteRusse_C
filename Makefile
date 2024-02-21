CC=gcc
CFLAGS=-c -Wall `sdl-config --cflags` `pkg-config --cflags SDL_ttf`
LDFLAGS=-lSDL -lSDL_net -lSDL_mixer `sdl-config --libs` `pkg-config --libs SDL_ttf`

SOURCES_MAIN=main.c src/c/affichage.c src/c/roulette.c
OBJECTS_MAIN=$(SOURCES_MAIN:.c=.o)
EXECUTABLE_MAIN=prog

SOURCES_CLIENT=src/NET/client.c src/c/affichage.c src/c/roulette.c
OBJECTS_CLIENT=$(SOURCES_CLIENT:.c=.o)
EXECUTABLE_CLIENT=client

SOURCES_SERVER=src/NET/serveur.c src/c/affichage.c src/c/roulette.c
OBJECTS_SERVER=$(SOURCES_SERVER:.c=.o)
EXECUTABLE_SERVER=serveur

all: $(EXECUTABLE_MAIN) $(EXECUTABLE_CLIENT) $(EXECUTABLE_SERVER)

$(EXECUTABLE_MAIN): $(OBJECTS_MAIN)
	$(CC) $(OBJECTS_MAIN) -o $@ $(LDFLAGS)

$(EXECUTABLE_CLIENT): $(OBJECTS_CLIENT)
	$(CC) $(OBJECTS_CLIENT) -o $@ $(LDFLAGS)

$(EXECUTABLE_SERVER): $(OBJECTS_SERVER)
	$(CC) $(OBJECTS_SERVER) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *o src/NET/*o src/c/*o $(EXECUTABLE_MAIN) $(EXECUTABLE_CLIENT) $(EXECUTABLE_SERVER)

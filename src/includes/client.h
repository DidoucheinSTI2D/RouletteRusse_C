#ifndef CLIENT_U
#define CLIENT_U

#include <SDL/SDL.h>
#include <SDL/SDL_net.h>
#include <SDL/SDL_thread.h>

typedef struct {
    int id; // Identifiant unique pour le client
    TCPsocket socket; // Socket TCP du client
    IPaddress ip; // Adresse IP du client
    // Ajoutez d'autres champs selon les besoins de votre application
} ClientInfo;

#endif
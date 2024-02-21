#ifndef THREAD_U
#define THREAD_U
#include "client.h"

int processClient(void* data) {
    ClientInfo* clientInfo = (ClientInfo*)data;
    char choix[2]; // Buffer pour stocker le caractère reçu plus le caractère de fin de chaîne

    // Attendre un caractère du client
    int receivedBytes = SDLNet_TCP_Recv(clientInfo->socket, choix, 1); // Reçoit uniquement 1 caractère
    if (receivedBytes > 0) {
        choix[receivedBytes] = '\0'; // Assurez-vous que le message est une C-string valide
        printf("Client %d: Caractère reçu : %s\n",clientInfo->id, choix);

        // Ici, vous pouvez traiter le caractère et envoyer une réponse si nécessaire
        // Par exemple, effectuer une action basée sur le caractère reçu
    } else {
        // Gérer l'erreur ou la déconnexion du client
        printf("Client %d: Erreur de réception ou client déconnecté.\n", clientInfo->id);
    }

    SDLNet_TCP_Close(clientInfo->socket); // Fermer la connexion avec le client
    free(clientInfo);
    return 0;
}

#endif
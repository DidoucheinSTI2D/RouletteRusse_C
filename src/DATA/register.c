#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "register.h"

#define QUERY "INSERT INTO users (username) VALUES (?)"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define TEXTBOX_WIDTH 200
#define TEXTBOX_HEIGHT 30
#define BUTTON_WIDTH 100
#define BUTTON_HEIGHT 50

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "Impossible d'initialiser SDL : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    if (TTF_Init() != 0)
    {
        fprintf(stderr, "Impossible d'initialiser SDL_ttf : %s\n", TTF_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    SDL_Surface *screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (!screen)
    {
        fprintf(stderr, "Erreur lors de la création de la fenêtre SDL : %s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    MYSQL *conn;
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[1];

    conn = mysql_init(NULL);
    if (conn == NULL)
    {
        fprintf(stderr, "Erreur d'initialisation MySQL\n");
        TTF_Quit();
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    if (mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 3306, NULL, 0) == NULL)
    {
        fprintf(stderr, "Erreur de connexion MySQL\n");
        mysql_close(conn);
        TTF_Quit();
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    stmt = mysql_stmt_init(conn);
    if (!stmt)
    {
        fprintf(stderr, "Erreur de statement MySQL\n");
        mysql_close(conn);
        TTF_Quit();
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    if (mysql_stmt_prepare(stmt, QUERY, strlen(QUERY)))
    {
        fprintf(stderr, "Erreur de préparation MySQL\n");
        mysql_stmt_close(stmt);
        mysql_close(conn);
        TTF_Quit();
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    TTF_Font *font = TTF_OpenFont("/usr/share/fonts/truetype/ubuntu/Ubuntu-C.ttf", 24);
    if (!font)
    {
        fprintf(stderr, "Impossible de charger la police : %s\n", TTF_GetError());
        mysql_stmt_close(stmt);
        mysql_close(conn);
        TTF_Quit();
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    char name[256] = "";

    int quit = 0;
    SDL_Event event;
    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                quit = 1;
                break;
            case SDL_KEYDOWN:
                if (strlen(name) < sizeof(name) - 1)
                {
                    char key = event.key.keysym.sym;
                    if ((key >= SDLK_a && key <= SDLK_z) || (key >= SDLK_0 && key <= SDLK_9))
                    {
                        strncat(name, SDL_GetKeyName(key), sizeof(name) - strlen(name) - 1);
                    }
                    else if (key == SDLK_BACKSPACE && strlen(name) > 0)
                    {
                        name[strlen(name) - 1] = '\0';
                    }
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT &&
                    event.button.x >= SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2 &&
                    event.button.x <= SCREEN_WIDTH / 2 + BUTTON_WIDTH / 2 &&
                    event.button.y >= SCREEN_HEIGHT / 2 + TEXTBOX_HEIGHT / 2 + 10 &&
                    event.button.y <= SCREEN_HEIGHT / 2 + TEXTBOX_HEIGHT / 2 + 10 + BUTTON_HEIGHT)
                {
                    size_t name_length = strlen(name);
                    memset(bind, 0, sizeof(bind));
                    bind[0].buffer_type = MYSQL_TYPE_STRING;
                    bind[0].buffer = name;
                    bind[0].buffer_length = name_length + 1;
                    bind[0].is_null = 0;
                    bind[0].length = &name_length;

                    if (mysql_stmt_bind_param(stmt, bind) != 0)
                    {
                        fprintf(stderr, "Erreur de liaison MySQL\n");
                        mysql_stmt_close(stmt);
                        mysql_close(conn);
                        TTF_Quit();
                        SDL_Quit();
                        exit(EXIT_FAILURE);
                    }

                    if (mysql_stmt_execute(stmt))
                    {
                        fprintf(stderr, "Erreur d'exécution MySQL\n");
                        mysql_stmt_close(stmt);
                        mysql_close(conn);
                        TTF_Quit();
                        SDL_Quit();
                        exit(EXIT_FAILURE);
                    }

                    printf("Utilisateur ajouté avec succès : %s\n", name);
                    quit = 1;
                }
                break;
            }
        }

        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

        if (strlen(name) > 0)
        {
            SDL_Surface *textBoxSurface = TTF_RenderText_Solid(font, name, (SDL_Color){255, 255, 255});
            if (!textBoxSurface)
            {
                fprintf(stderr, "Erreur lors du rendu du texte : %s\n", TTF_GetError());
                TTF_CloseFont(font);
                mysql_stmt_free_result(stmt);
                mysql_stmt_close(stmt);
                mysql_close(conn);
                TTF_Quit();
                SDL_Quit();
                exit(EXIT_FAILURE);
            }

            if (TEXTBOX_WIDTH < textBoxSurface->w)
            {
                fprintf(stderr, "La largeur de la zone de texte est insuffisante pour afficher le texte\n");
                TTF_CloseFont(font);
                SDL_FreeSurface(textBoxSurface);
                mysql_stmt_free_result(stmt);
                mysql_stmt_close(stmt);
                mysql_close(conn);
                TTF_Quit();
                SDL_Quit();
                exit(EXIT_FAILURE);
            }

            SDL_Rect textBoxRect = {SCREEN_WIDTH / 2 - textBoxSurface->w / 2, SCREEN_HEIGHT / 2 - TEXTBOX_HEIGHT / 2, TEXTBOX_WIDTH, TEXTBOX_HEIGHT};
            SDL_BlitSurface(textBoxSurface, NULL, screen, &textBoxRect);
            SDL_FreeSurface(textBoxSurface);
        }

        SDL_Surface *buttonSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, BUTTON_WIDTH, BUTTON_HEIGHT, 32, 0, 0, 0, 0);
        SDL_FillRect(buttonSurface, NULL, SDL_MapRGB(buttonSurface->format, 0, 255, 0));
        SDL_Rect buttonRect = {SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT / 2 + TEXTBOX_HEIGHT / 2 + 10, BUTTON_WIDTH, BUTTON_HEIGHT};
        SDL_BlitSurface(buttonSurface, NULL, screen, &buttonRect);
        SDL_FreeSurface(buttonSurface);

        SDL_Flip(screen);
    }

    TTF_CloseFont(font);
    mysql_stmt_free_result(stmt);
    mysql_stmt_close(stmt);
    mysql_close(conn);
    TTF_Quit();
    SDL_Quit();

    exit(EXIT_SUCCESS);
}
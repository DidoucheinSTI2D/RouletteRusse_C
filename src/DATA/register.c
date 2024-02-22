#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define SERVER "192.168.1.124"
#define USER "user"
#define PASSWORD "password"
#define DATABASE "game"
#define QUERY "INSERT INTO users (username) VALUES (?)"

int main() {
    MYSQL *conn;
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[1];

    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "Erreur d'initialisation : %s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }

    if (mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 3306, NULL, 0) == NULL) {
        fprintf(stderr, "Erreur de connexion : %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "Erreur de statement : %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    if (mysql_stmt_prepare(stmt, QUERY, strlen(QUERY))) {
        fprintf(stderr, "Erreur de préparation : %s\n", mysql_error(conn));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    char *name;

    printf("Entrez votre nom d'utilisateur : ");
    scanf("%s", name);

    if (strlen(name) > 15) {
        printf("Nom d'utilisateur trop long\n");
        exit(EXIT_FAILURE);
    }

    size_t name_length = strlen(name);
    memset(bind, 0, sizeof(bind));
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = name;
    bind[0].buffer_length = name_length + 1;
    bind[0].is_null = 0;
    bind[0].length = &name_length;

    if (mysql_stmt_bind_param(stmt, bind) != 0) {
        fprintf(stderr, "Erreur de liaison : %s\n", mysql_error(conn));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "Erreur d'exécution : %s\n", mysql_error(conn));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    mysql_stmt_close(stmt);
    mysql_close(conn);

    exit(EXIT_SUCCESS);
}

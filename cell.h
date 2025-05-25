#ifndef CELL_H
#define CELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h> // Pour bool, true, false
#include <sysexits.h> // Pour EX_OK, EX_OSERR, etc.

// Couleurs
#define RED   "\033[0;31m"
#define RST   "\033[0m"
#define C     "\033[0;36m"

// Pour afficher facilement
#define p(...)  printf(__VA_ARGS__)

// Définir l'équivalent de `SPACE` utilisé dans strtok
#define SPACE " \t\r\n\a"

// Constante pour le fork
#define CELL_JR 0

// Structure pour builtin
typedef struct s_builtin {
    const char *builtin_name;
    int (*foo)(char **args);
} t_builtin;

// Fonctions de builtins à déclarer
int cell_echo(char **args);
int cell_env(char **args);
int cell_exit(char **args);

// Wrappers POSIX (redéfinis comme fonctions dans utils.c)
char *Getcwd(char *buf, size_t size);
void Getline(char **lineptr, size_t *n, FILE *stream);
pid_t Fork(void);
void Execvp(const char *file, char *const argv[]);
pid_t Wait(int *status);
pid_t Waitpid(pid_t pid, int *status, int options);
void *Malloc(size_t size);
void *Realloc(void *ptr, size_t size);
void Chdir(const char *path);

// Déclaration de dbzSpinnerLoading
void dbzSpinnerLoading(void);

// Déclaration de printbanner
void printbanner(void);

#endif /* CELL_H */

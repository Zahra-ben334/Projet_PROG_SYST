#define _POSIX_C_SOURCE 200809L // Enable POSIX functions like fileno
#include "cell.h"

int status = 0;

t_builtin g_builtin[] = {
    {.builtin_name = "echo", .foo = cell_echo},
    {.builtin_name = "env", .foo = cell_env},
    {.builtin_name = "exit", .foo = cell_exit},
    {.builtin_name = NULL},
};

void cell_launch(char **args) {
    pid_t pid = Fork();
    if (pid == CELL_JR) {
        Execvp(args[0], args);
    } else {
        Wait(&status);
    }
}

void cell_execute(char **args) {
    int i;
    const char *curr_builtin;

    if (!args || !args[0])
        return;

    i = 0;
    while ((curr_builtin = g_builtin[i].builtin_name)) {
        if (!strcmp(args[0], curr_builtin)) {
            if ((status = (g_builtin[i].foo)(args)))
                p("%s failed\n", curr_builtin);
            return;
        }
        i++;
    }
    cell_launch(args);
}

char *cell_read_line(void) {
    char *line = NULL;
    size_t bufsize = 0;
    char cwd[BUFSIZ];

    if (isatty(fileno(stdin))) {
        if (status)
            p("🌸" C "[%s]" RED "[%d]" RST "🌸 > ", Getcwd(cwd, BUFSIZ), status);
        else
            p("🌸" C "[%s]" RST "🌸 > ", Getcwd(cwd, BUFSIZ));
    }

    Getline(&line, &bufsize, stdin);
    return line;
}

char **cell_split_line(char *line) {
    size_t bufsize = BUFSIZ;
    unsigned long position = 0;
    char **tokens = Malloc(bufsize * sizeof(*tokens));

    for (char *token = strtok(line, SPACE); token; token = strtok(NULL, SPACE)) {
        tokens[position++] = token;
        if (position >= bufsize) {
            bufsize *= 2;
            tokens = Realloc(tokens, bufsize * sizeof(*tokens));
        }
    }
    tokens[position] = NULL;
    return tokens;
}

int main() {
    char *line;
    char **args;

    printbanner();
    while ((line = cell_read_line())) {
        args = cell_split_line(line);

        if (args[0] && !strcmp(args[0], "cd"))
            Chdir(args[1]);

        cell_execute(args);

        free(line);
        free(args);
    }

    return EXIT_SUCCESS;
}

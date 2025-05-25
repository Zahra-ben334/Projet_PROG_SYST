#define _POSIX_C_SOURCE 200809L // Enable POSIX functions like getline, usleep
#include "cell.h"

void Chdir(const char *path) {
    if (!path) {
        fprintf(stderr, RED "cd: path argument required\n" RST);
        return;
    }
    if (chdir(path) == -1)
        perror(RED "cd failed" RST);
}

pid_t Fork(void) {
    pid_t pid = fork();
    if (pid < 0) {
        perror(RED "Fork failed" RST);
        exit(EX_OSERR);
    }
    return pid;
}

void Execvp(const char *file, char *const argv[]) {
    if (!file || !argv) {
        fprintf(stderr, RED "Execvp: invalid arguments\n" RST);
        exit(EXIT_FAILURE);
    }
    if (execvp(file, argv) == -1) {
        perror(RED "🌺HELLO_Jr failed🌺" RST);
        exit(EX_UNAVAILABLE);
    }
}

pid_t Wait(int *status) {
    pid_t result;
    if (!status) {
        fprintf(stderr, RED "Wait: status argument required\n" RST);
        return -1;
    }
    result = wait(status);
    if (result == -1)
        perror(RED "Wait failed" RST);
    if (WIFEXITED(*status))
        *status = WEXITSTATUS(*status);
    return result;
}

pid_t Waitpid(pid_t pid, int *status, int options) {
    pid_t result;
    if (!status)
        return -1;
    result = waitpid(pid, status, options);
    if (result == -1)
        perror(RED "Waitpid failed" RST);
    if (WIFEXITED(*status))
        *status = WEXITSTATUS(*status);
    return result;
}

void *Malloc(size_t size) {
    void *ptr;
    if (size == 0)
        return NULL;
    ptr = malloc(size);
    if (!ptr) {
        perror(RED "Malloc failed" RST);
        exit(EXIT_FAILURE);
    }
    return ptr;
}

void *Realloc(void *ptr, size_t size) {
    void *new_ptr = realloc(ptr, size);
    if (!new_ptr && size != 0) {
        perror(RED "Realloc failed" RST);
        exit(EXIT_FAILURE);
    }
    return new_ptr;
}

char *Getcwd(char *buf, size_t size) {
    char *result = getcwd(buf, size);
    if (!result)
        perror(RED "Getcwd failed" RST);
    return result;
}

void Getline(char **lineptr, size_t *n, FILE *stream) {
    if (!lineptr || !stream) {
        fprintf(stderr, RED "Getline: invalid arguments\n" RST);
        return;
    }
    if (getline(lineptr, n, stream) == -1) {
        free(*lineptr);
        *lineptr = NULL;
        if (feof(stream))
            printf(RED "[EOF]" RST "\n");
        else
            perror(RED "Getline failed" RST);
    }
}

void dbzSpinnerLoading() {
    const char *charging[] = {
        "[            ]",
        "[=           ]",
        "[==          ]",
        "[===         ]",
        "[====        ]",
        "[=====       ]",
        "[======      ]",
        "[=======     ]",
        "[========    ]",
        "[=========   ]",
        "[==========  ]",
        "[=========== ]",
        "[===========🌺]",
    };
    const int frames = sizeof(charging) / sizeof(charging[0]);
    p(RED "Shutting down...\n" RST);
    for (int i = 0; i < frames; i++) {
        p("\r" C "%s" RST, charging[i]);
        fflush(stdout);
        usleep(421337);
    }
    p(C "\n✅ EXIT ✅\n" RST);
    exit(EX_OK);
}

void printbanner(void) {
    p(C "██╗  ██╗███████╗██╗     ██╗      \n"
        "██║  ██║██╔════╝██║     ██║      \n"
        "███████║█████╗  ██║     ██║      \n"
        "██╔══██║██╔══╝  ██║     ██║      \n"
        "██║  ██║███████╗███████╗███████╗ \n"
        "╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝ \n"
        "              HELLO               \n" RST);
}

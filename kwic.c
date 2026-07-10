#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>

char path[256];
char temppath[256];
char value[8192];

static int mkdir_if_missing(const char *dir) {
    if (mkdir(dir, 0755) == 0) return 0;
    if (errno == EEXIST) return 0;
    return -1;
}

static void usage(void) {
    printf("Usage error.\n");
    exit(1);
}

void new(const char *alias, const char *value) {
    FILE *kwicd;
    kwicd = fopen(path, "a");
    if (!kwicd) { printf("Kwicd file not found."); exit(0); };

    fprintf(kwicd, "%s:%s\n", alias, value);
    fflush(kwicd);
    fclose(kwicd);
}

void copy(const char *alias) {
    FILE *kwicd;
    char line[4096];

    kwicd = fopen(path, "r");
    if (!kwicd) { printf("Kwicd file not found."); exit(0); }

    while (fgets(line, sizeof(line), kwicd)) {
        line[strcspn(line, "\r\n")] = '\0';

        char *colon = strchr(line, ':');
        if (!colon) continue;

        *colon = '\0';
        char *key = line; // alias
        char *val = colon + 1; // value


        if (strcmp(key, alias) != 0) continue; // doesn't match

        // matches:
        char cmd[8192];
        snprintf(cmd, sizeof(cmd), "wl-copy '%s'", val);
        system(cmd);
        break;
    }

    fclose(kwicd);
}

int scan(const char *alias) {  // -2 = file not found, -1 = alias not found
    FILE *kwicd;
    char line[4096];
    int ln = 1;

    kwicd = fopen(path, "r");
    if (!kwicd) return -2;

    while (fgets(line, sizeof(line), kwicd)) {
        line[strcspn(line, "\r\n")] = '\0';

        char *colon = strchr(line, ':');
        if (!colon) { ln++; continue; }

        *colon = '\0';
        char *key = line;
        char *val = colon + 1;

        if (strcmp(key, alias) != 0) { ln++; continue; }

        fclose(kwicd);
        return ln;
    }

    fclose(kwicd);
    return -1;
}

void delete(const char *alias) {
    FILE *kwicd;
    FILE *temp;

    char line[4096];
    int cur_ln = 1;
    int del_ln = scan(alias);

    if (del_ln == -2) { printf("Kwicd file not found.\n"); exit(0); }
    else if (del_ln == -1) { printf("Alias not found.\n"); exit(0); }
    
    kwicd = fopen(path, "r");
    temp = fopen(temppath, "w");

    if (!kwicd) { printf("Kwicd file not found."); exit(0); }
    if (!temp) {printf("Temporary Kwicd file could not be created."); exit(0); }

    while (fgets(line, sizeof(line), kwicd)) {
        if (cur_ln != del_ln) {
            fputs(line, temp);
        }
        cur_ln++;
    }

    fclose(kwicd);
    fclose(temp);

    remove(path);
    rename(temppath, path);
}

int main(int argc, char *argv[]) {
    const char *home = getenv("HOME");
    if (!home || !*home) return 1;

    char dir[256];
    snprintf(dir, sizeof(dir), "%s/.local/share/kwic", home); // data dir
    if (mkdir_if_missing(dir) != 0) return 1;

    snprintf(path, sizeof(path), "%s/.local/share/kwic/kwicd.txt", home); // data file
    snprintf(temppath, sizeof(temppath), "%s/.local/share/kwic/kwicd-temp.txt", home);

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-n") == 0) {
            if (i + 2 >= argc) { usage(); return 1; }
            new(argv[i + 1], argv[i + 2]);
            i += 2;
        } 
        
        else if (strcmp(argv[i], "-c") == 0) {
            if (i + 1 >= argc) { usage(); return 1; }
            copy(argv[i + 1]);
            i += 1;
        }

        else if (strcmp(argv[i], "ls") == 0) {
            char cmd[64];
            snprintf(cmd, sizeof(cmd), "cat '%s'", path);
            system(cmd);
            printf("\n");
        }

        else if (strcmp(argv[i], "rm" ) == 0 || strcmp(argv[i], "-r") == 0) {
            if (i + 1 >= argc) { usage(); return 1; }
            delete(argv[i + 1]);
            i += 1;
        }

        else if (strcmp(argv[i], "clear") == 0) {
            system("printf '' | wl-copy");
        } 


        else {
            usage();
        }
    }
    return 0;
}

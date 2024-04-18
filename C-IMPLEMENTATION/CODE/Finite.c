#include <stdio.h>
#include <string.h>

#define NO_OF_CHARS 256

int getNextState(char pat[], int M, int state, char x) {
    if (state < M && x == pat[state]) {
        return state + 1;
    }

    int i = 0;
    for (int ns = state; ns > 0; ns--) {
        if (pat[ns - 1] == x) {
            while (i < ns - 1) {
                if (pat[i] != pat[state - ns + 1 + i]) {
                    break;
                }
                i++;
            }
            if (i == ns - 1) {
                return ns;
            }
        }
    }
    return 0;
}

void computeTF(char pat[], int M, int TF[][NO_OF_CHARS]) {
    for (int state = 0; state <= M; state++) {
        for (int x = 0; x < NO_OF_CHARS; x++) {
            int z = getNextState(pat, M, state, x);
            TF[state][x] = z;
        }
    }
}

void search(char pat[], char txt[]) {
    int M = strlen(pat);
    int N = strlen(txt);
    int TF[M + 1][NO_OF_CHARS];
    computeTF(pat, M, TF);

    int state = 0;
    int pattern_found = 0;

    for (int i = 0; i < N; i++) {
        state = TF[state][(int)txt[i]];
        if (state == M) {
            printf("Pattern found at index: %d\n", i - M + 1);
            pattern_found = 1;
        }
    }
    if (!pattern_found) {
        printf("Pattern not found\n");
    }
}

int main() {
    char file_path[100];
    printf("Enter the file path: ");
    scanf("%s", file_path);

    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        printf("File not found.\n");
        return 1;
    }

    char txt[1000];
    char pat[1000];

    // Read text and pattern from file
    fgets(txt, 1000, file);  // First line is text
    fgets(pat, 1000, file);  // Second line is pattern

    // Removing newline characters if present
    if (txt[strlen(txt) - 1] == '\n') {
        txt[strlen(txt) - 1] = '\0';
    }
    if (pat[strlen(pat) - 1] == '\n') {
        pat[strlen(pat) - 1] = '\0';
    }

    search(pat, txt);

    fclose(file);
    return 0;
}
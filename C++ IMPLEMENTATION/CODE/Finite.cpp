#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define NO_OF_CHARS 256

int getNextState(const std::string& pat, int M, int state, char x) {
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

void computeTF(const std::string& pat, int M, std::vector<std::vector<int>>& TF) {
    for (int state = 0; state <= M; state++) {
        for (int x = 0; x < NO_OF_CHARS; x++) {
            int z = getNextState(pat, M, state, x);
            TF[state][x] = z;
        }
    }
}

void search(const std::string& pat, const std::string& txt) {
    int M = pat.length();
    int N = txt.length();
    std::vector<std::vector<int>> TF(M + 1, std::vector<int>(NO_OF_CHARS));
    computeTF(pat, M, TF);

    int state = 0;
    int pattern_found = 0;

    for (int i = 0; i < N; i++) {
        state = TF[state][txt[i]];
        if (state == M) {
            std::cout << "Pattern found at index: " << i - M + 1 << std::endl;
            pattern_found = 1;
        }
    }
    if (!pattern_found) {
        std::cout << "Pattern not found" << std::endl;
    }
}

int main() {
    std::string file_path;
    std::cout << "Enter the file path: ";
    std::cin >> file_path;

    std::ifstream file(file_path);
    if (!file.is_open()) {
        std::cout << "File not found." << std::endl;
        return 1;
    }

    std::string txt, pat;

    // Read text and pattern from file
    std::getline(file, txt);  // First line is text
    std::getline(file, pat);  // Second line is pattern

    // Removing newline characters if present
    if (!txt.empty() && txt.back() == '\n') {
        txt.pop_back();
    }
    if (!pat.empty() && pat.back() == '\n') {
        pat.pop_back();
    }

    search(pat, txt);

    file.close();
    return 0;
}

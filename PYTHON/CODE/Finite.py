NO_OF_CHARS = 256

def getNextState(pat, M, state, x):
    if state < M and x == ord(pat[state]):
        return state + 1

    i = 0
    for ns in range(state, 0, -1):
        if ord(pat[ns - 1]) == x:
            while i < ns - 1:
                if pat[i] != pat[state - ns + 1 + i]:
                    break
                i += 1
            if i == ns - 1:
                return ns
    return 0

def computeTF(pat, M):
    TF = [[0 for i in range(NO_OF_CHARS)] for _ in range(M + 1)]
    for state in range(M + 1):
        for x in range(NO_OF_CHARS):
            z = getNextState(pat, M, state, x)
            TF[state][x] = z
    return TF

def search(pat, txt):
    M = len(pat)
    N = len(txt)
    TF = computeTF(pat, M) 
    state = 0
    pattern_found = False
    for i in range(N):
        state = TF[state][ord(txt[i])]
        if state == M:
            print("Pattern found at index: {}".format(i - M + 1))
            pattern_found = True
    if not pattern_found:
        print("Pattern not found")

def main():
    file_path = input("Enter the file path: ")
    try:
        with open(file_path, 'r') as file:
            lines = file.readlines()
            txt = lines[0].strip()  # First line is text
            pat = lines[1].strip()  # Second line is pattern
            search(pat, txt)
    except FileNotFoundError:
        print("File not found.")

if __name__ == '__main__':
    main()

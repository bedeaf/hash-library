// Kalip 2: Yalnizca anahtarin bicimi kontrol edilir: AAAA-1234.
#include <cstring>
#include <iostream>

bool valid(const char* key) {
    if (std::strlen(key) != 9 || key[4] != '-')
        return false;
    for (int i = 0; i < 4; ++i)
        if (key[i] < 'A' || key[i] > 'Z')
            return false;
    for (int i = 5; i < 9; ++i)
        if (key[i] < '0' || key[i] > '9')
            return false;
    return true;
}

int main(int argc, char** argv) {
    const char* key = argc > 1 ? argv[1] : "";
    std::cout << (valid(key) ? "VALID" : "INVALID") << '\n';
}

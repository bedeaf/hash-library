// Kalıp 18: İki sayısal anahtar grubu arasında aritmetik ilişki kurulur.
#include <cstring>
#include <iostream>

bool valid(const char* key) {
    if (std::strlen(key) != 9 || key[4] != '-')
        return false;
    unsigned int first = 0;
    unsigned int second = 0;
    for (int i = 0; i < 9; ++i) {
        if (i == 4)
            continue;
        if (key[i] < '0' || key[i] > '9')
            return false;
        if (i < 4)
            first = first * 10u + (key[i] - '0');
        else
            second = second * 10u + (key[i] - '0');
    }
    return second == first * 7u + 11u;
}

int main(int argc, char** argv) {
    const char* key = argc > 1 ? argv[1] : "";
    std::cout << (valid(key) ? "VALID" : "INVALID") << '\n';
}

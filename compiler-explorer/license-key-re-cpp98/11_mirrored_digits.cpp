// Kalıp 11: Simetrik konumdaki rakamların toplamı sabit olmalıdır.
#include <cstring>
#include <iostream>

bool valid(const char* key) {
    if (std::strlen(key) != 6)
        return false;
    for (int i = 0; i < 6; ++i)
        if (key[i] < '0' || key[i] > '9')
            return false;
    for (int i = 0; i < 3; ++i)
        if ((key[i] - '0') + (key[5 - i] - '0') != 7)
            return false;
    return true;
}

int main(int argc, char** argv) {
    const char* key = argc > 1 ? argv[1] : "";
    std::cout << (valid(key) ? "VALID" : "INVALID") << '\n';
}

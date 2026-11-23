// Kalıp 13: Karakterler sabit bir dönüştürme tablosundan geçirilir.
#include <cstring>
#include <iostream>

bool valid(const char* key) {
    const char table[] = "QWERTYUIOPASDFGHJKLZXCVBNM";
    const char expected[] = "QWER";
    if (std::strlen(key) != 4)
        return false;
    for (int i = 0; i < 4; ++i) {
        if (key[i] < 'A' || key[i] > 'Z')
            return false;
        if (table[key[i] - 'A'] != expected[i])
            return false;
    }
    return true;
}

int main(int argc, char** argv) {
    const char* key = argc > 1 ? argv[1] : "";
    std::cout << (valid(key) ? "VALID" : "INVALID") << '\n';
}

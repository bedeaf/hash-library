// Kalip 4: Beklenen metin XOR ile gizlenir. Bu, gercek sifreleme degildir.
#include <cstring>
#include <iostream>

bool valid(const char* key) {
    const unsigned char encoded[5] = { 0x15, 0x08, 0x18, 0x13, 0x0e };
    if (std::strlen(key) != 5)
        return false;
    for (int i = 0; i < 5; ++i)
        if ((static_cast<unsigned char>(key[i]) ^ 0x5a) != encoded[i])
            return false;
    return true;
}

int main(int argc, char** argv) {
    const char* key = argc > 1 ? argv[1] : "";
    std::cout << (valid(key) ? "VALID" : "INVALID") << '\n';
}

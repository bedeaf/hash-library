// Kalıp 17: Onaltılık değerdeki lisans özellikleri bit maskesiyle denetlenir.
#include <cstring>
#include <iostream>

int hex_digit(char c) {
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    return -1;
}

bool valid(const char* key) {
    if (std::strlen(key) != 2)
        return false;
    int high = hex_digit(key[0]);
    int low = hex_digit(key[1]);
    if (high < 0 || low < 0)
        return false;
    unsigned int flags = static_cast<unsigned int>(high * 16 + low);
    return (flags & 0xA0u) == 0xA0u && (flags & 0x0Fu) != 0;
}

int main(int argc, char** argv) {
    const char* key = argc > 1 ? argv[1] : "";
    std::cout << (valid(key) ? "VALID" : "INVALID") << '\n';
}

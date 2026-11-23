// Kalıp 20: Kullanıcı adı TEA benzeri 16 turlu dönüşümden geçirilir.
// Anahtar kodun içinde bulunduğu için bu örnek güvenli lisans imzası değildir.
#include <climits>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <sstream>

#if UINT_MAX != 0xFFFFFFFFU
#error "Bu örnek 32 bit unsigned int gerektirir"
#endif

void token(const char* name, unsigned int& left, unsigned int& right) {
    unsigned char bytes[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    for (unsigned int i = 0; i < 8 && name[i] != '\0'; ++i)
        bytes[i] = static_cast<unsigned char>(name[i]);

    left = 0;
    right = 0;
    for (int i = 0; i < 4; ++i) {
        left |= static_cast<unsigned int>(bytes[i]) << (8 * i);
        right |= static_cast<unsigned int>(bytes[i + 4]) << (8 * i);
    }

    const unsigned int key[4] = { 0xA56BABCDu, 0x0000FACEu,
                                  0x01234567u, 0x89ABCDEFu };
    unsigned int sum = 0;
    for (int round = 0; round < 16; ++round) {
        sum += 0x9E3779B9u;
        left += ((right << 4) + key[0]) ^ (right + sum) ^
                ((right >> 5) + key[1]);
        right += ((left << 4) + key[2]) ^ (left + sum) ^
                 ((left >> 5) + key[3]);
    }
}

bool valid(const char* name, const char* serial) {
    const std::size_t length = std::strlen(name);
    if (length == 0 || length > 8)
        return false;
    unsigned int left = 0;
    unsigned int right = 0;
    token(name, left, right);
    std::ostringstream expected;
    expected << std::uppercase << std::hex << std::setfill('0')
             << std::setw(8) << left << std::setw(8) << right;
    return expected.str() == serial;
}

int main(int argc, char** argv) {
    const char* name = argc > 1 ? argv[1] : "";
    const char* serial = argc > 2 ? argv[2] : "";
    std::cout << (valid(name, serial) ? "VALID" : "INVALID") << '\n';
}

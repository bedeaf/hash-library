// Kalıp 4: Beklenen metin XOR ile gizlenir. Bu, gerçek şifreleme değildir.
#include <cstring>
#include <iostream>

bool valid(const char* key) {
    const unsigned char encoded_key[] = { 0x15, 0x08, 0x18, 0x13, 0x0E };
    const unsigned char xor_mask = 0x5A;

    if (std::strlen(key) != sizeof(encoded_key)) {
        return false;
    }

    for (unsigned int position = 0; position < sizeof(encoded_key); ++position) {
        const unsigned char character = static_cast<unsigned char>(key[position]);
        if ((character ^ xor_mask) != encoded_key[position]) {
            return false;
        }
    }

    return true;
}

int main(int argc, char** argv) {
    const char* key = argc > 1 ? argv[1] : "";
    std::cout << (valid(key) ? "VALID" : "INVALID") << '\n';
}

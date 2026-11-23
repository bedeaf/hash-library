// Kalıp 10: Kullanıcı adından 31 çarpanlı basit bir özet üretilir.
#include <climits>
#include <iostream>
#include <sstream>

#if UINT_MAX != 0xFFFFFFFFU
#error "Bu örnek 32 bit unsigned int gerektirir"
#endif

unsigned int hash_name(const char* name) {
    const unsigned int multiplier = 31u;
    unsigned int hash = 0;
    const unsigned char* byte = reinterpret_cast<const unsigned char*>(name);
    for (; *byte != 0; ++byte) {
        hash = hash * multiplier + *byte;
    }
    return hash;
}

bool valid(const char* name, const char* serial) {
    if (*name == '\0') {
        return false;
    }

    std::ostringstream expected;
    expected << hash_name(name);
    return expected.str() == serial;
}

int main(int argc, char** argv) {
    const char* name = argc > 1 ? argv[1] : "";
    const char* serial = argc > 2 ? argv[2] : "";
    std::cout << (valid(name, serial) ? "VALID" : "INVALID") << '\n';
}

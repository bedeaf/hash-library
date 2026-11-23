// Kalıp 19: Her baytta döndürme ve XOR kullanılarak kısa seri üretilir.
// Bu küçük durum değeri güvenli kimlik doğrulaması sağlamaz.
#include <iomanip>
#include <iostream>
#include <sstream>

unsigned int token(const char* name) {
    unsigned int state = 0x5Au;
    const unsigned char* p = reinterpret_cast<const unsigned char*>(name);
    for (; *p; ++p) {
        state = ((state << 1) | (state >> 7)) & 0xFFu;
        state ^= *p;
    }
    return state;
}

bool valid(const char* name, const char* serial) {
    if (*name == '\0')
        return false;
    std::ostringstream expected;
    expected << std::uppercase << std::hex << std::setw(2)
             << std::setfill('0') << token(name);
    return expected.str() == serial;
}

int main(int argc, char** argv) {
    const char* name = argc > 1 ? argv[1] : "";
    const char* serial = argc > 2 ? argv[2] : "";
    std::cout << (valid(name, serial) ? "VALID" : "INVALID") << '\n';
}

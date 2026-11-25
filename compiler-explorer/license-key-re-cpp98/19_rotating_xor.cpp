// Kalıp 19: Her baytta döndürme ve XOR kullanılarak kısa seri üretilir.
// Bu küçük durum değeri güvenli kimlik doğrulaması sağlamaz.
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

unsigned int rotate_left_one_bit(unsigned int value) {
    return ((value << 1) | (value >> 7)) & 0xFFu;
}

unsigned int token(const char* name) {
    unsigned int state = 0x5Au;
    const unsigned char* byte = reinterpret_cast<const unsigned char*>(name);
    while (*byte != 0) {
        state = rotate_left_one_bit(state);
        state ^= *byte;
        ++byte;
    }
    return state;
}

bool valid(const char* name, const char* serial) {
    if (*name == '\0') {
        return false;
    }

    ostringstream expected;
    expected << uppercase << hex << setw(2)
             << setfill('0') << token(name);
    return expected.str() == serial;
}

int main(int argc, char** argv) {
    const char* name = argc > 1 ? argv[1] : "";
    const char* serial = argc > 2 ? argv[2] : "";
    cout << (valid(name, serial) ? "VALID" : "INVALID") << '\n';
}

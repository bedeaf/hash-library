// Kalıp 14: CRC-16/CCITT-FALSE ile 16 bitlik kontrol değeri hesaplanır.
// CRC, hata saptama içindir; kriptografik doğrulama sağlamaz.
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

unsigned int crc16(const char* text) {
    const unsigned int initial_value = 0xFFFFu;
    const unsigned int polynomial = 0x1021u;
    const unsigned int high_bit = 0x8000u;
    const unsigned int word_mask = 0xFFFFu;
    unsigned int crc = initial_value;
    const unsigned char* byte = reinterpret_cast<const unsigned char*>(text);

    while (*byte != 0) {
        crc ^= static_cast<unsigned int>(*byte) << 8;
        for (int bit = 0; bit < 8; ++bit) {
            const bool carry = (crc & high_bit) != 0;
            crc = (crc << 1) & word_mask;
            if (carry) {
                crc ^= polynomial;
            }
        }
        ++byte;
    }
    return crc;
}

bool valid(const char* text, const char* serial) {
    if (*text == '\0') {
        return false;
    }

    ostringstream expected;
    expected << uppercase << hex << setw(4)
             << setfill('0') << crc16(text);
    return expected.str() == serial;
}

int main(int argc, char** argv) {
    const char* text = argc > 1 ? argv[1] : "";
    const char* serial = argc > 2 ? argv[2] : "";
    cout << (valid(text, serial) ? "VALID" : "INVALID") << '\n';
}

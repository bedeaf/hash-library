// Kalıp 14: CRC-16/CCITT-FALSE ile 16 bitlik kontrol değeri hesaplanır.
// CRC, hata saptama içindir; kriptografik doğrulama sağlamaz.
#include <iostream>
#include <iomanip>
#include <sstream>

unsigned int crc16(const char* text) {
    unsigned int crc = 0xFFFFu;
    const unsigned char* p = reinterpret_cast<const unsigned char*>(text);
    for (; *p; ++p) {
        crc ^= static_cast<unsigned int>(*p) << 8;
        for (int bit = 0; bit < 8; ++bit)
            crc = (crc & 0x8000u) ? ((crc << 1) ^ 0x1021u) & 0xFFFFu
                                  : (crc << 1) & 0xFFFFu;
    }
    return crc;
}

bool valid(const char* text, const char* serial) {
    if (*text == '\0')
        return false;
    std::ostringstream expected;
    expected << std::uppercase << std::hex << std::setw(4)
             << std::setfill('0') << crc16(text);
    return expected.str() == serial;
}

int main(int argc, char** argv) {
    const char* text = argc > 1 ? argv[1] : "";
    const char* serial = argc > 2 ? argv[2] : "";
    std::cout << (valid(text, serial) ? "VALID" : "INVALID") << '\n';
}

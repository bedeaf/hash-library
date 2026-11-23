// Kalip 6: Kullanici adinin 32 bit FNV-1a ozeti seri olarak karsilastirilir.
// Bu yalnizca bir RE alistirmasidir; FNV-1a kriptografik MAC degildir.
#include <climits>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#if UINT_MAX != 0xFFFFFFFFU
#error "Bu ornek 32 bit unsigned int gerektirir"
#endif

unsigned int fnv1a(const char* text) {
    unsigned int hash = 2166136261u;
    const unsigned char* p = reinterpret_cast<const unsigned char*>(text);
    for (; *p; ++p) {
        hash ^= *p;
        hash *= 16777619u;
    }
    return hash;
}

bool valid(const char* name, const char* serial) {
    if (*name == '\0')
        return false;
    std::ostringstream expected;
    expected << std::uppercase << std::hex << std::setw(8)
             << std::setfill('0') << fnv1a(name);
    return expected.str() == serial;
}

int main(int argc, char** argv) {
    const char* name = argc > 1 ? argv[1] : "";
    const char* serial = argc > 2 ? argv[2] : "";
    std::cout << (valid(name, serial) ? "VALID" : "INVALID") << '\n';
}

// Kalıp 6: Kullanıcı adının 32 bit FNV-1a özeti seri olarak karşılaştırılır.
// Bu yalnızca bir tersine mühendislik alıştırmasıdır; FNV-1a kriptografik MAC değildir.
#include <climits>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

#if UINT_MAX != 0xFFFFFFFFU
#error "Bu örnek 32 bit unsigned int gerektirir"
#endif

unsigned int fnv1a(const char* text) {
    const unsigned int offset_basis = 2166136261u;
    const unsigned int prime = 16777619u;
    unsigned int hash = offset_basis;
    const unsigned char* byte = reinterpret_cast<const unsigned char*>(text);
    while (*byte != 0) {
        hash ^= *byte;
        hash *= prime;
        ++byte;
    }
    return hash;
}

bool valid(const char* name, const char* serial) {
    if (*name == '\0') {
        return false;
    }

    ostringstream expected;
    expected << uppercase << hex << setw(8)
             << setfill('0') << fnv1a(name);
    return expected.str() == serial;
}

int main(int argc, char** argv) {
    const char* name = argc > 1 ? argv[1] : "";
    const char* serial = argc > 2 ? argv[2] : "";
    cout << (valid(name, serial) ? "VALID" : "INVALID") << '\n';
}

// Kalip 5: Seri numarasi kullanici adindan hesaplanir.
#include <iostream>
#include <sstream>
#include <string>

bool valid(const char* name, const char* serial) {
    if (*name == '\0')
        return false;
    unsigned int sum = 0;
    for (const unsigned char* p =
             reinterpret_cast<const unsigned char*>(name); *p; ++p)
        sum += *p;
    std::ostringstream expected;
    expected << (sum * 7u + 31u);
    return expected.str() == serial;
}

int main(int argc, char** argv) {
    const char* name = argc > 1 ? argv[1] : "";
    const char* serial = argc > 2 ? argv[2] : "";
    std::cout << (valid(name, serial) ? "VALID" : "INVALID") << '\n';
}

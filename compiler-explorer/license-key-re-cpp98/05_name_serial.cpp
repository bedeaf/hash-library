// Kalıp 5: Seri numarası kullanıcı adından hesaplanır.
#include <iostream>
#include <sstream>

using namespace std;

unsigned int sum_bytes(const char* text) {
    unsigned int sum = 0;
    const unsigned char* byte = reinterpret_cast<const unsigned char*>(text);
    while (*byte != 0) {
        sum += *byte;
        ++byte;
    }
    return sum;
}

bool valid(const char* name, const char* serial) {
    if (*name == '\0') {
        return false;
    }

    const unsigned int expected_number = sum_bytes(name) * 7u + 31u;
    ostringstream expected;
    expected << expected_number;
    return expected.str() == serial;
}

int main(int argc, char** argv) {
    const char* name = argc > 1 ? argv[1] : "";
    const char* serial = argc > 2 ? argv[2] : "";
    cout << (valid(name, serial) ? "VALID" : "INVALID") << '\n';
}

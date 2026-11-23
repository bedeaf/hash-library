// Kalıp 15: Seri numarası kullanıcı adı ve makine kimliğine bağlanır.
#include <iostream>
#include <sstream>

unsigned int byte_sum(const char* text) {
    unsigned int sum = 0;
    const unsigned char* p = reinterpret_cast<const unsigned char*>(text);
    for (; *p; ++p)
        sum += *p;
    return sum;
}

bool valid(const char* name, const char* machine, const char* serial) {
    if (*name == '\0' || *machine == '\0')
        return false;
    unsigned int value = (byte_sum(name) * 31u) ^ byte_sum(machine);
    std::ostringstream expected;
    expected << value;
    return expected.str() == serial;
}

int main(int argc, char** argv) {
    const char* name = argc > 1 ? argv[1] : "";
    const char* machine = argc > 2 ? argv[2] : "";
    const char* serial = argc > 3 ? argv[3] : "";
    std::cout << (valid(name, machine, serial) ? "VALID" : "INVALID") << '\n';
}

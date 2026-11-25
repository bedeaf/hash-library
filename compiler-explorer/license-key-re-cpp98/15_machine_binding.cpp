// Kalıp 15: Seri numarası kullanıcı adı ve makine kimliğine bağlanır.
#include <iostream>
#include <sstream>

using namespace std;

unsigned int byte_sum(const char* text) {
    unsigned int sum = 0;
    const unsigned char* byte = reinterpret_cast<const unsigned char*>(text);
    while (*byte != 0) {
        sum += *byte;
        ++byte;
    }
    return sum;
}

bool valid(const char* name, const char* machine, const char* serial) {
    if (*name == '\0' || *machine == '\0') {
        return false;
    }

    const unsigned int name_value = byte_sum(name) * 31u;
    const unsigned int machine_value = byte_sum(machine);
    const unsigned int expected_number = name_value ^ machine_value;
    ostringstream expected;
    expected << expected_number;
    return expected.str() == serial;
}

int main(int argc, char** argv) {
    const char* name = argc > 1 ? argv[1] : "";
    const char* machine = argc > 2 ? argv[2] : "";
    const char* serial = argc > 3 ? argv[3] : "";
    cout << (valid(name, machine, serial) ? "VALID" : "INVALID") << '\n';
}

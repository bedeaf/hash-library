// Kalıp 9: Ön ek, gövde ve son ek ayrı ayrı denetlenir.
#include <cstring>
#include <iostream>

bool valid(const char* key) {
    return std::strlen(key) == 13 &&
           std::strncmp(key, "LIC-", 4) == 0 &&
           std::strncmp(key + 4, "ORBIT", 5) == 0 &&
           std::strcmp(key + 9, "-END") == 0;
}

int main(int argc, char** argv) {
    const char* key = argc > 1 ? argv[1] : "";
    std::cout << (valid(key) ? "VALID" : "INVALID") << '\n';
}

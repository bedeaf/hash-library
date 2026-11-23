// Kalip 1: Anahtar dogrudan sabit metinle karsilastirilir.
#include <cstring>
#include <iostream>

bool valid(const char* key) {
    return std::strcmp(key, "ORBIT-2026") == 0;
}

int main(int argc, char** argv) {
    const char* key = argc > 1 ? argv[1] : "";
    std::cout << (valid(key) ? "VALID" : "INVALID") << '\n';
}

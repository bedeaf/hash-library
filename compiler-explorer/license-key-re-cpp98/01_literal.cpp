// Kalıp 1: Anahtar doğrudan sabit metinle karşılaştırılır.
#include <cstring>
#include <iostream>

using namespace std;

bool valid(const char* key) {
    const char expected_key[] = "ORBIT-2026";
    return strcmp(key, expected_key) == 0;
}

int main(int argc, char** argv) {
    const char* key = argc > 1 ? argv[1] : "";
    cout << (valid(key) ? "VALID" : "INVALID") << '\n';
}

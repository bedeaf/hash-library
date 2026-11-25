// Kalıp 9: Ön ek, gövde ve son ek ayrı ayrı denetlenir.
#include <cstring>
#include <iostream>

using namespace std;

bool valid(const char* key) {
    const int prefix_length = 4;
    const int name_length = 5;
    const int total_length = 13;

    if (strlen(key) != total_length) {
        return false;
    }
    if (strncmp(key, "LIC-", prefix_length) != 0) {
        return false;
    }
    if (strncmp(key + prefix_length, "ORBIT", name_length) != 0) {
        return false;
    }
    return strcmp(key + prefix_length + name_length, "-END") == 0;
}

int main(int argc, char** argv) {
    const char* key = argc > 1 ? argv[1] : "";
    cout << (valid(key) ? "VALID" : "INVALID") << '\n';
}

// Kalip 3: Son rakam, ilk bes rakamin agirlikli toplamindan uretilir.
#include <cstring>
#include <iostream>

bool valid(const char* key) {
    if (std::strlen(key) != 6)
        return false;
    int sum = 0;
    for (int i = 0; i < 6; ++i) {
        if (key[i] < '0' || key[i] > '9')
            return false;
        if (i < 5)
            sum += (key[i] - '0') * (i + 1);
    }
    return sum % 10 == key[5] - '0';
}

int main(int argc, char** argv) {
    const char* key = argc > 1 ? argv[1] : "";
    std::cout << (valid(key) ? "VALID" : "INVALID") << '\n';
}

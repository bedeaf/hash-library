// Kalıp 8: Büyük-küçük harf farkı kaldırılarak sabit anahtar karşılaştırılır.
#include <cstring>
#include <iostream>

bool valid(const char* key) {
    const char expected[] = "ORBIT-2026";
    if (std::strlen(key) != sizeof(expected) - 1)
        return false;
    for (unsigned int i = 0; i < sizeof(expected) - 1; ++i) {
        char current = key[i];
        if (current >= 'a' && current <= 'z')
            current = static_cast<char>(current - 'a' + 'A');
        if (current != expected[i])
            return false;
    }
    return true;
}

int main(int argc, char** argv) {
    const char* key = argc > 1 ? argv[1] : "";
    std::cout << (valid(key) ? "VALID" : "INVALID") << '\n';
}

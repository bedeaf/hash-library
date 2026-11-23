// Kalıp 8: Büyük-küçük harf farkı kaldırılarak sabit anahtar karşılaştırılır.
#include <cstring>
#include <iostream>

bool valid(const char* key) {
    const char expected_key[] = "ORBIT-2026";
    const unsigned int key_length = sizeof(expected_key) - 1;

    if (std::strlen(key) != key_length) {
        return false;
    }

    for (unsigned int position = 0; position < key_length; ++position) {
        char normalized = key[position];
        if (normalized >= 'a' && normalized <= 'z') {
            normalized = static_cast<char>(normalized - 'a' + 'A');
        }
        if (normalized != expected_key[position]) {
            return false;
        }
    }

    return true;
}

int main(int argc, char** argv) {
    const char* key = argc > 1 ? argv[1] : "";
    std::cout << (valid(key) ? "VALID" : "INVALID") << '\n';
}

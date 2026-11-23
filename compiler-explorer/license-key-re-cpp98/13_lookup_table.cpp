// Kalıp 13: Karakterler sabit bir dönüştürme tablosundan geçirilir.
#include <cstring>
#include <iostream>

bool valid(const char* key) {
    const char substitution_table[] = "QWERTYUIOPASDFGHJKLZXCVBNM";
    const char expected_pattern[] = "QWER";
    const int key_length = 4;

    if (std::strlen(key) != key_length) {
        return false;
    }

    for (int position = 0; position < key_length; ++position) {
        if (key[position] < 'A' || key[position] > 'Z') {
            return false;
        }
        const int table_index = key[position] - 'A';
        if (substitution_table[table_index] != expected_pattern[position]) {
            return false;
        }
    }

    return true;
}

int main(int argc, char** argv) {
    const char* key = argc > 1 ? argv[1] : "";
    std::cout << (valid(key) ? "VALID" : "INVALID") << '\n';
}

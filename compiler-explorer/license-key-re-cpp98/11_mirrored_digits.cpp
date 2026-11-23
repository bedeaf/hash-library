// Kalıp 11: Simetrik konumdaki rakamların toplamı sabit olmalıdır.
#include <cstring>
#include <iostream>

bool valid(const char* key) {
    const int key_length = 6;
    const int pair_count = key_length / 2;
    const int expected_pair_sum = 7;

    if (std::strlen(key) != key_length) {
        return false;
    }

    for (int position = 0; position < key_length; ++position) {
        if (key[position] < '0' || key[position] > '9') {
            return false;
        }
    }

    for (int pair = 0; pair < pair_count; ++pair) {
        const int first_digit = key[pair] - '0';
        const int last_digit = key[key_length - 1 - pair] - '0';
        if (first_digit + last_digit != expected_pair_sum) {
            return false;
        }
    }

    return true;
}

int main(int argc, char** argv) {
    const char* key = argc > 1 ? argv[1] : "";
    std::cout << (valid(key) ? "VALID" : "INVALID") << '\n';
}

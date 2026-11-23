// Kalıp 3: Son rakam, ilk beş rakamın ağırlıklı toplamından üretilir.
#include <cstring>
#include <iostream>

bool valid(const char* key) {
    const int key_length = 6;
    const int data_digits = 5;

    if (std::strlen(key) != key_length) {
        return false;
    }

    for (int position = 0; position < key_length; ++position) {
        if (key[position] < '0' || key[position] > '9') {
            return false;
        }
    }

    int weighted_sum = 0;
    for (int position = 0; position < data_digits; ++position) {
        const int digit = key[position] - '0';
        const int weight = position + 1;
        weighted_sum += digit * weight;
    }

    const int check_digit = key[data_digits] - '0';
    return weighted_sum % 10 == check_digit;
}

int main(int argc, char** argv) {
    const char* key = argc > 1 ? argv[1] : "";
    std::cout << (valid(key) ? "VALID" : "INVALID") << '\n';
}

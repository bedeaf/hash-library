// Kalıp 18: İki sayısal anahtar grubu arasında aritmetik ilişki kurulur.
#include <cstring>
#include <iostream>

using namespace std;

bool parse_four_digits(const char* start, unsigned int& number) {
    number = 0;
    for (int position = 0; position < 4; ++position) {
        if (start[position] < '0' || start[position] > '9') {
            return false;
        }
        number = number * 10u + (start[position] - '0');
    }
    return true;
}

bool valid(const char* key) {
    const int group_length = 4;
    if (strlen(key) != 9 || key[group_length] != '-') {
        return false;
    }

    unsigned int first_group = 0;
    unsigned int second_group = 0;
    if (!parse_four_digits(key, first_group) ||
        !parse_four_digits(key + group_length + 1, second_group)) {
        return false;
    }

    return second_group == first_group * 7u + 11u;
}

int main(int argc, char** argv) {
    const char* key = argc > 1 ? argv[1] : "";
    cout << (valid(key) ? "VALID" : "INVALID") << '\n';
}

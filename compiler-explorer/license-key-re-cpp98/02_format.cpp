// Kalıp 2: Yalnızca anahtarın biçimi kontrol edilir: AAAA-1234.
#include <cstring>
#include <iostream>

using namespace std;

bool valid(const char* key) {
    const int key_length = 9;
    const int separator_position = 4;

    if (strlen(key) != key_length || key[separator_position] != '-') {
        return false;
    }

    for (int position = 0; position < separator_position; ++position) {
        if (key[position] < 'A' || key[position] > 'Z') {
            return false;
        }
    }

    for (int position = separator_position + 1; position < key_length; ++position) {
        if (key[position] < '0' || key[position] > '9') {
            return false;
        }
    }

    return true;
}

int main(int argc, char** argv) {
    const char* key = argc > 1 ? argv[1] : "";
    cout << (valid(key) ? "VALID" : "INVALID") << '\n';
}

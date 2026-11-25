// Kalıp 12: Harf-rakam karışımı anahtarın taban-36 değeri denetlenir.
#include <cstring>
#include <iostream>
#include <sstream>

using namespace std;

int digit_value(char character) {
    if (character >= '0' && character <= '9') {
        return character - '0';
    }
    if (character >= 'A' && character <= 'Z') {
        return character - 'A' + 10;
    }
    return -1;
}

bool decode_base36(const char* text, unsigned int& value) {
    const int key_length = 2;
    const unsigned int base = 36u;
    if (strlen(text) != key_length) {
        return false;
    }

    value = 0;
    for (int position = 0; position < key_length; ++position) {
        const int digit = digit_value(text[position]);
        if (digit < 0) {
            return false;
        }
        value = value * base + static_cast<unsigned int>(digit);
    }
    return true;
}

bool valid(const char* key, const char* serial) {
    unsigned int value = 0;
    if (!decode_base36(key, value)) {
        return false;
    }

    ostringstream expected;
    expected << value;
    return expected.str() == serial;
}

int main(int argc, char** argv) {
    const char* key = argc > 1 ? argv[1] : "";
    const char* serial = argc > 2 ? argv[2] : "";
    cout << (valid(key, serial) ? "VALID" : "INVALID") << '\n';
}

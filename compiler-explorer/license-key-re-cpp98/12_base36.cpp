// Kalıp 12: Harf-rakam karışımı anahtarın taban-36 değeri denetlenir.
#include <cstring>
#include <iostream>
#include <sstream>

bool decode(const char* text, unsigned int& value) {
    if (std::strlen(text) != 2)
        return false;
    value = 0;
    for (int i = 0; i < 2; ++i) {
        unsigned int digit;
        if (text[i] >= '0' && text[i] <= '9')
            digit = text[i] - '0';
        else if (text[i] >= 'A' && text[i] <= 'Z')
            digit = text[i] - 'A' + 10;
        else
            return false;
        value = value * 36u + digit;
    }
    return true;
}

bool valid(const char* key, const char* serial) {
    unsigned int value = 0;
    if (!decode(key, value))
        return false;
    std::ostringstream expected;
    expected << value;
    return expected.str() == serial;
}

int main(int argc, char** argv) {
    const char* key = argc > 1 ? argv[1] : "";
    const char* serial = argc > 2 ? argv[2] : "";
    std::cout << (valid(key, serial) ? "VALID" : "INVALID") << '\n';
}

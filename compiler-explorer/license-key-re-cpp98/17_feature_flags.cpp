// Kalıp 17: Onaltılık değerdeki lisans özellikleri bit maskesiyle denetlenir.
#include <cstring>
#include <iostream>

int hex_digit(char character) {
    if (character >= '0' && character <= '9') {
        return character - '0';
    }
    if (character >= 'A' && character <= 'F') {
        return character - 'A' + 10;
    }
    return -1;
}

bool valid(const char* key) {
    if (std::strlen(key) != 2) {
        return false;
    }

    const int high_digit = hex_digit(key[0]);
    const int low_digit = hex_digit(key[1]);
    if (high_digit < 0 || low_digit < 0) {
        return false;
    }

    const unsigned int required_features = 0xA0u;
    const unsigned int license_tier_mask = 0x0Fu;
    const unsigned int flags = static_cast<unsigned int>(high_digit * 16 + low_digit);
    const bool has_required_features = (flags & required_features) == required_features;
    const bool has_license_tier = (flags & license_tier_mask) != 0;
    return has_required_features && has_license_tier;
}

int main(int argc, char** argv) {
    const char* key = argc > 1 ? argv[1] : "";
    std::cout << (valid(key) ? "VALID" : "INVALID") << '\n';
}

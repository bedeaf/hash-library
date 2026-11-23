// Kalıp 7: İmza doğrulamanın küçük sayılarla matematik modeli.
// n=3233 ve e=17 güvensiz eğitim değerleridir. Gerçek RSA lisansı değildir.
#include <cerrno>
#include <cstdlib>
#include <iostream>

bool parse_unsigned_decimal(const char* text, unsigned long& value) {
    if (*text == '\0') {
        return false;
    }
    for (const char* digit = text; *digit != '\0'; ++digit) {
        if (*digit < '0' || *digit > '9') {
            return false;
        }
    }
    errno = 0;
    char* end = 0;
    value = std::strtoul(text, &end, 10);
    return errno == 0 && *end == '\0';
}

unsigned long modular_power(unsigned long base, unsigned long exponent,
                            unsigned long modulus) {
    unsigned long result = 1;
    // Üssün her biti için kare al; bit 1 ise çarpımı sonuca ekle.
    while (exponent != 0) {
        if ((exponent & 1ul) != 0) {
            result = (result * base) % modulus;
        }
        base = (base * base) % modulus;
        exponent >>= 1;
    }
    return result;
}

bool valid(const char* message_text, const char* signature_text) {
    const unsigned long modulus = 3233ul;
    const unsigned long public_exponent = 17ul;
    unsigned long message = 0;
    unsigned long signature = 0;
    if (!parse_unsigned_decimal(message_text, message) ||
        !parse_unsigned_decimal(signature_text, signature)) {
        return false;
    }
    if (message >= modulus || signature >= modulus) {
        return false;
    }
    return modular_power(signature, public_exponent, modulus) == message;
}

int main(int argc, char** argv) {
    const char* message = argc > 1 ? argv[1] : "";
    const char* signature = argc > 2 ? argv[2] : "";
    std::cout << (valid(message, signature) ? "VALID" : "INVALID") << '\n';
}

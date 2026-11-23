// Kalıp 7: İmza doğrulamanın küçük sayılarla matematik modeli.
// n=3233 ve e=17 güvensiz eğitim değerleridir. Gerçek RSA lisansı değildir.
#include <cerrno>
#include <cstdlib>
#include <iostream>

bool parse_number(const char* text, unsigned long& value) {
    if (*text == '\0')
        return false;
    for (const char* p = text; *p; ++p)
        if (*p < '0' || *p > '9')
            return false;
    errno = 0;
    char* end = 0;
    value = std::strtoul(text, &end, 10);
    return errno == 0 && *end == '\0';
}

unsigned long power_mod(unsigned long base, unsigned long exponent,
                        unsigned long modulus) {
    unsigned long result = 1;
    while (exponent != 0) {
        if (exponent & 1ul)
            result = (result * base) % modulus;
        base = (base * base) % modulus;
        exponent >>= 1;
    }
    return result;
}

bool valid(const char* message_text, const char* signature_text) {
    unsigned long message = 0;
    unsigned long signature = 0;
    if (!parse_number(message_text, message) ||
        !parse_number(signature_text, signature))
        return false;
    if (message >= 3233ul || signature >= 3233ul)
        return false;
    return power_mod(signature, 17ul, 3233ul) == message;
}

int main(int argc, char** argv) {
    const char* message = argc > 1 ? argv[1] : "";
    const char* signature = argc > 2 ? argv[2] : "";
    std::cout << (valid(message, signature) ? "VALID" : "INVALID") << '\n';
}

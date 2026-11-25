// Kalıp 20: Kullanıcı adı TEA benzeri 16 turlu dönüşümden geçirilir.
// Anahtar kodun içinde bulunduğu için bu örnek güvenli lisans imzası değildir.
#include <climits>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

#if UINT_MAX != 0xFFFFFFFFU
#error "Bu örnek 32 bit unsigned int gerektirir"
#endif

unsigned int load_little_endian_word(const unsigned char* bytes) {
    unsigned int word = 0;
    for (int byte_index = 0; byte_index < 4; ++byte_index) {
        word |= static_cast<unsigned int>(bytes[byte_index]) << (8 * byte_index);
    }
    return word;
}

void make_token(const char* name, unsigned int& left_word, unsigned int& right_word) {
    const int word_size = 4;
    const int name_capacity = 2 * word_size;
    const int round_count = 16;
    const unsigned int round_delta = 0x9E3779B9u;
    const unsigned int key[4] = { 0xA56BABCDu, 0x0000FACEu,
                                  0x01234567u, 0x89ABCDEFu };

    unsigned char name_bytes[name_capacity] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    for (int byte_index = 0;
         byte_index < name_capacity && name[byte_index] != '\0';
         ++byte_index) {
        name_bytes[byte_index] = static_cast<unsigned char>(name[byte_index]);
    }

    // Sekiz baytı iki adet 32 bit sözcüğe düşük bayt önce olacak biçimde yerleştir.
    left_word = load_little_endian_word(name_bytes);
    right_word = load_little_endian_word(name_bytes + word_size);

    unsigned int sum = 0;
    for (int round = 0; round < round_count; ++round) {
        sum += round_delta;
        left_word += ((right_word << 4) + key[0]) ^ (right_word + sum) ^
                     ((right_word >> 5) + key[1]);
        right_word += ((left_word << 4) + key[2]) ^ (left_word + sum) ^
                      ((left_word >> 5) + key[3]);
    }
}

bool valid(const char* name, const char* serial) {
    const size_t maximum_name_length = 8;
    const size_t length = strlen(name);
    if (length == 0 || length > maximum_name_length) {
        return false;
    }
    unsigned int left_word = 0;
    unsigned int right_word = 0;
    make_token(name, left_word, right_word);
    ostringstream expected;
    expected << uppercase << hex << setfill('0')
             << setw(8) << left_word << setw(8) << right_word;
    return expected.str() == serial;
}

int main(int argc, char** argv) {
    const char* name = argc > 1 ? argv[1] : "";
    const char* serial = argc > 2 ? argv[2] : "";
    cout << (valid(name, serial) ? "VALID" : "INVALID") << '\n';
}

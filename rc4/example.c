#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "rc4.h"

int main(void)
{
    const uint8_t key[] = "vxtruog";
    const uint8_t plaintext[] = "Xin chao, toi ten la Truong.";
    const size_t discard_byte_count = 28;

    size_t data_length = sizeof(plaintext) - 1;
    uint8_t ciphertext[sizeof(plaintext) - 1];
    uint8_t decrypted_data[sizeof(plaintext) - 1];

    RC4 *encryption_state;
    RC4 *decryption_state;

    encryption_state = rc4_init(key, sizeof(key) - 1);

    if (encryption_state == NULL)
    {
        fprintf(stderr, "failed to initialize encryption state.\n");
        return 1;
    }

    rc4_discard(encryption_state, discard_byte_count);

    if (rc4_crypt(encryption_state, plaintext, ciphertext, data_length) != 0)
    {
        fprintf(stderr, "encryption failed.\n");
        rc4_free(encryption_state);
        return 1;
    }

    printf("Plaintext : %s\n", plaintext);
    printf("Ciphertext: ");

    for (size_t index = 0; index < data_length; index++)
    {
        printf("%02X ", ciphertext[index]);
    }
    printf("\n");

    decryption_state = rc4_init(key, sizeof(key) - 1);

    if (decryption_state == NULL)
    {
        fprintf(stderr, "failed to initialize decryption state.\n");
        rc4_free(encryption_state);
        return 1;
    }

    rc4_discard(decryption_state, discard_byte_count);

    if (rc4_crypt(decryption_state, ciphertext, decrypted_data, data_length) != 0)
    {
        fprintf(stderr, "decryption failed.\n");
        rc4_free(encryption_state);
        rc4_free(decryption_state);
        return 1;
    }

    printf("Decrypted : ");
    for (size_t index = 0; index < data_length; index++)
    {
        printf("%c", decrypted_data[index]);
    }
    printf("\n");

    if (memcmp(plaintext, decrypted_data, data_length) == 0)
    {
        printf("PASS\n");
    }
    else
    {
        printf("FAIL\n");
    }

    rc4_free(encryption_state);
    rc4_free(decryption_state);

    return 0;
}
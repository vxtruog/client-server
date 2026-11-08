#include <stdio.h>
#include <stdlib.h>

#include "rc4.h"

RC4_API RC4 *rc4_init(const uint8_t *key, size_t key_length)
{
    RC4 *state;
    uint16_t i;
    uint16_t j = 0;

    if (key == NULL)
    {
        fprintf(stderr, "rc4_init: key pointer is NULL.\n");
        return NULL;
    }

    if (key_length == 0 || key_length > 256)
    {
        fprintf(stderr, "rc4_init: invalid key length (%zu).\n", key_length);
        return NULL;
    }

    state = malloc(sizeof(*state));

    if (state == NULL)
    {
        fprintf(stderr, "rc4_init: memory allocation failed.\n");
        return NULL;
    }

    for (i = 0; i < RC4_STATE_SIZE; i++)
        state->s[i] = (uint8_t)i;

    for (i = 0; i < RC4_STATE_SIZE; i++)
    {
        j = (j + state->s[i] + key[i % key_length]) % RC4_STATE_SIZE;

        uint8_t temporary_value = state->s[i];
        state->s[i] = state->s[j];
        state->s[j] = temporary_value;
    }

    state->i = 0;
    state->j = 0;

    return state;
}

RC4_API uint8_t rc4_byte(RC4 *state)
{
    uint8_t temporary_value;
    uint8_t keystream_index;

    state->i = (state->i + 1) % RC4_STATE_SIZE;
    state->j = (state->j + state->s[state->i]) % RC4_STATE_SIZE;

    temporary_value = state->s[state->i];
    state->s[state->i] = state->s[state->j];
    state->s[state->j] = temporary_value;

    keystream_index = (state->s[state->i] + state->s[state->j]) % RC4_STATE_SIZE;

    return state->s[keystream_index];
}

RC4_API void rc4_discard(RC4 *state, size_t byte_count)
{
    size_t index;

    if (state == NULL)
    {
        fprintf(stderr, "rc4_discard: state pointer is NULL.\n");
        return;
    }

    for (index = 0; index < byte_count; index++)
    {
        (void)rc4_byte(state);
    }
}

RC4_API int rc4_crypt(RC4 *state, const uint8_t *input, uint8_t *output, size_t length)
{
    size_t index;

    if (state == NULL)
    {
        fprintf(stderr, "rc4_crypt: state pointer is NULL.\n");
        return -1;
    }

    if (input == NULL || output == NULL)
    {
        fprintf(stderr, "rc4_crypt: input or output buffer is NULL.\n");
        return -1;
    }

    for (index = 0; index < length; index++)
    {
        output[index] = input[index] ^ rc4_byte(state);
    }

    return 0;
}

RC4_API void rc4_free(RC4 *state)
{
    free(state);
}
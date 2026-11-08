#ifndef RC4_H
#define RC4_H

#include <stdint.h>
#include <stddef.h>

#if defined(__GNUC__)
#define RC4_API __attribute__((visibility("default")))
#else
#define RC4_API
#endif

/* ============================================================
 *  Định nghĩa cấu trúc RC4
 * ============================================================ */

#define RC4_STATE_SIZE 256

typedef struct s_rc4
{
    uint8_t i;
    uint8_t j;
    uint8_t s[RC4_STATE_SIZE];
} RC4;

/* ============================================================
 *  Public API
 * ============================================================ */

/* KSA (Key Scheduling Algorithm) */
RC4_API RC4 *rc4_init(const uint8_t *key, size_t keylen);

/* PRGA (Pseudo-Random Generation Algorithm) => Keystream */
RC4_API uint8_t rc4_byte(RC4 *state);

/* Loại bỏ một số byte đầu tiên trước khi dùng keystream */
RC4_API void rc4_discard(RC4 *state, size_t count);

/* Mã hóa và Giải mã */
RC4_API int rc4_crypt(RC4 *state, const uint8_t *input, uint8_t *output, size_t length);

/* Giải phóng bộ nhớ sau khi dùng xong RC4 */
RC4_API void rc4_free(RC4 *state);

#endif
#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>

#define export                  __attribute__((visibility("default")))
#define MS                      50
#define rc4decrypt(x, y, z)     rc4encrypt(x, y, z)
#define rc4uninit(x)            free(x)
#define rc4whitewash(x, y)      for(x = 0; x < (MS * 1000000); x++) \
                                    (volatile int8)rc4byte(y);

typedef unsigned char int8;
typedef unsigned short int int16;
typedef unsigned int int32;

struct s_rc4 {
    int16 i, j, k;
    int8 s[256];
};

typedef struct s_rc4 RC4;

export RC4 *rc4init(int8*, int16);
int8 rc4byte(RC4*);
export int8 *rc4encrypt(RC4*, int8*, int16);
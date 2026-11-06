#include "rc4.h"

#define F fflush(stdout)

int main(void);

void printbin(int8 *input, const int16 size) {
    int16 i;
    int8 *p;

    assert(size > 0);

    for(i = size, p = input; i; i--, p++) {
        if(!(i % 2))
            printf(" ");
        printf("%.02x", *p);
    }
    printf("\n");

    return;
}

int main() {
    RC4 *rc4;
    char *key, *from;
    int8 *encrypted, *decrypted;
    int16 skey, stext;

    key = "tomatoes";
    skey = strlen(key);
    from = "Shall I compare thee to a summer's day?";
    stext = strlen(from);

    printf("Initializing encryption ..."); F;
    rc4 = rc4init((int8 *)key, skey);
    printf("Done\n");

    printf("'%s'\n ->", from);
    encrypted = rc4encrypt(rc4, (int8 *)from, stext);
    printbin(encrypted, stext);
    rc4uninit(rc4);

    printf("Initializing decryption ..."); F;
    rc4 = rc4init((int8 *)key, skey);
    printf("Done\n");

    decrypted = rc4decrypt(rc4, encrypted, stext);
    printf("   -> '%s'\n ->", decrypted);
    rc4uninit(rc4);

    return 0;

}
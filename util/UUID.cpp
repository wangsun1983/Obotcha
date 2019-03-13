#include "UUID.hpp"

_UUID::_UUID() {
    char uuidBuf[UUID4_LEN];
    
    if(init() == 0) {
        generate(uuidBuf);
        uuid = createString(uuidBuf);
    }
}

String _UUID::toValue() {
    return uuid;
}

uint64_t _UUID::xorshift128plus(uint64_t *s) {
    /* http://xorshift.di.unimi.it/xorshift128plus.c */
    uint64_t s1 = s[0];
    const uint64_t s0 = s[1];
    s[0] = s0;
    s1 ^= s1 << 23;
    s[1] = s1 ^ s0 ^ (s1 >> 18) ^ (s0 >> 5);
    return s[1] + s0;
}

int _UUID::init() {
    int res;
    FILE *fp = fopen("/dev/urandom", "rb");
    if (!fp) {
        return -1;
    }
    res = fread(seed, 1, sizeof(seed), fp);
    fclose(fp);
    if ( res != sizeof(seed) ) {
        return -1;
    }

    return 0;
}

void _UUID::generate(char *dst) {
    static const char *format = "xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx";
    static const char *chars = "0123456789abcdef";
    union { unsigned char b[16]; uint64_t word[2]; } s;
    const char *p;
    int i, n;
    /* get random */
    s.word[0] = xorshift128plus(seed);
    s.word[1] = xorshift128plus(seed);
    /* build string */
    p = format;
    i = 0;
    while (*p) {
        n = s.b[i >> 1];
        n = (i & 1) ? (n >> 4) : (n & 0xf);
        switch (*p) {
            case 'x'  : *dst = chars[n];              i++;  break;
            case 'y'  : *dst = chars[(n & 0x3) + 8];  i++;  break;
            default   : *dst = *p;
        }
        dst++, p++;
    }

    *dst = '\0';
}
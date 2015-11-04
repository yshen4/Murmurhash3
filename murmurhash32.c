/*
 * This function implements the alogrithm given in
 *     https://en.wikipedia.org/wiki/MurmurHash#Algorithm
 *     https://code.google.com/p/smhasher/wiki/MurmurHash3
 * */
#define C1 0xcc9e2d51
#define C2 0x1b873593
#define N 0xe6546b64
#define M 5
#define C3 0x85ebca6b
#define C4 0xc2b2ae35
#define R1 15
#define R2 13
#define R3 16
#define R4 13
#define ROTL32(v, shift) ( ((v)<<(shift)) | ( (v)>>(32 - (shift))) )
uint32_t murmurhash32(const char *key, uint32_t key_len, uint32_t seed) {
    int i = 0, l = key_len/4;

    uint32_t h = seed, k = 0;
    uint8_t *d = (uint8_t *)key;
    const uint32_t *chunks = (const uint32_t *)(d + l * 4);
    const uint8_t *tail = (const uint8_t *)(d + l * 4);

    //Mix
    for (i = -l; i != 0; ++i) {
        k = chunks[i];

        //encode next 6 bytes
        k *= C1;
        k = ROTL32(k, R1);
        k *= C2;

        //append to hash
        h ^= k;
        h = ROTL32(k, R2);
        h = h * M + N;
    }

    //Remaining bytes (tail)
    k = 0;
    switch(key_len & 3) {
        case 3:
            k ^= (tail[2] << 16);
        case 2:
            k ^= (tail[1] << 8);
        case 1:
            k ^= tail[0];
            //encode tail bytes
            k *= C1;
            k = ROTL32(k, R1);
            k *= C2;
            //append to hash
            h ^= k;
    }

    //Finalize hash
    h ^= key_len; //this will distringuish strings with different length.
    h ^= (h >> R3);
    h *= C3;
    h ^= (h >> R4);
    h *= C4;
    h ^= (h >> R3);

    return h;
}
